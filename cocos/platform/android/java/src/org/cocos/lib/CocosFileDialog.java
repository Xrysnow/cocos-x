package org.cocos.lib;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.ClipData;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.provider.DocumentsContract;
import android.provider.DocumentsContract.Document;
import android.util.Log;
import android.webkit.MimeTypeMap;

import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.Locale;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.RejectedExecutionException;
import java.util.concurrent.SynchronousQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;

/** Storage Access Framework selection and provider access for the native FileDialog service. */
public final class CocosFileDialog {
    private static final String TAG = "CocosFileDialog";
    private static final String NEXT_CODE = "org.cocos.lib.fileDialog.nextCode";
    // Reserved for engine activity results. LuaSTG's permission bridge uses 0x4000-0x7fff.
    private static final int FIRST_CODE = 0x8000;
    private static final int LAST_CODE = 0xbfff;
    private static final int OPEN = 0, FOLDER = 1, EXPORT = 2;
    private static final int OK = 0, CANCELLED = 1, UNAVAILABLE = 2, BUSY = 3,
            PARENT_CLOSED = 4, DENIED = 5, INVALID_RESULT = 6, LIMIT = 7, BACKEND_ERROR = 8,
            NOT_FOUND = 9, IO_ERROR = 10, OUT_OF_MEMORY = 11, TIMEOUT = 12;
    private static final long METADATA_TIMEOUT_MS = 30_000;
    private static final int READ = Intent.FLAG_GRANT_READ_URI_PERMISSION;
    private static final int WRITE = Intent.FLAG_GRANT_WRITE_URI_PERMISSION;
    private static final String[] COLUMNS = {
            Document.COLUMN_DISPLAY_NAME, Document.COLUMN_MIME_TYPE, Document.COLUMN_SIZE
    };
    private static final String[] CHILD_COLUMNS = {
            Document.COLUMN_DISPLAY_NAME, Document.COLUMN_MIME_TYPE, Document.COLUMN_SIZE,
            Document.COLUMN_DOCUMENT_ID
    };
    private static final Handler UI = new Handler(Looper.getMainLooper());
    // A stalled provider must not queue unbounded selection or cleanup work.
    private static final ThreadPoolExecutor METADATA = new ThreadPoolExecutor(
            2, 2, 30, TimeUnit.SECONDS, new SynchronousQueue<>());
    private static final ThreadPoolExecutor CLEANUP = new ThreadPoolExecutor(
            1, 1, 30, TimeUnit.SECONDS, new ArrayBlockingQueue<>(8));

    private static volatile CocosActivity activity;
    private static volatile Context application;
    private static boolean resumed;
    private static int nextCode = FIRST_CODE;
    private static Request picker;
    private static final AtomicReference<Request> inspecting = new AtomicReference<>();

    private static final class Request {
        final long id;
        final int operation;
        final int code;
        final int maximum;
        boolean cancelled;
        Uri created;
        String[] postFilters;

        Request(long id, int operation, int code, int maximum) {
            this.id = id;
            this.operation = operation;
            this.code = code;
            this.maximum = maximum;
        }
    }

    private CocosFileDialog() {}

    static void bind(CocosActivity owner, Bundle state) {
        application = owner.getApplicationContext();
        resumed = false;
        activity = owner;
        if (state != null)
            nextCode = Math.max(nextCode, Math.min(LAST_CODE + 1, state.getInt(NEXT_CODE, FIRST_CODE)));
    }

    static void saveState(CocosActivity owner, Bundle state) {
        if (activity == owner) state.putInt(NEXT_CODE, nextCode);
    }

    static void setResumed(CocosActivity owner, boolean value) {
        if (activity == owner) resumed = value;
    }

    static void unbind(CocosActivity owner, boolean changingConfiguration) {
        if (activity != owner) return;
        activity = null;
        resumed = false;
        if (!changingConfiguration && picker != null) {
            Request request = picker;
            picker = null;
            finish(request.id, PARENT_CLOSED, "Activity closed", null);
        }
    }

    private static int availability() {
        return activity == null ? 0 : Build.VERSION.SDK_INT;
    }

    private static boolean present(long id, int operation, String initialUri, String name,
                                   String[] types, boolean allFiles, boolean multiple, int maxSelection) {
        CocosActivity owner = activity;
        return UI.post(() -> {
            if (owner == null || owner != activity || owner.isFinishing() || owner.isDestroyed() || !resumed) {
                finish(id, PARENT_CLOSED, "Activity is unavailable", null);
                return;
            }
            if (picker != null) {
                finish(id, BUSY, "A system file selector is active", null);
                return;
            }
            if (nextCode > LAST_CODE) {
                finish(id, LIMIT, "File selector request codes exhausted", null);
                return;
            }
            Request request = new Request(id, operation, nextCode++, multiple ? maxSelection : 1);
            try {
                Intent intent = new Intent(operation == FOLDER ? Intent.ACTION_OPEN_DOCUMENT_TREE
                        : operation == EXPORT ? Intent.ACTION_CREATE_DOCUMENT : Intent.ACTION_OPEN_DOCUMENT);
                if (operation != FOLDER) {
                    intent.addCategory(Intent.CATEGORY_OPENABLE);
                    LinkedHashSet<String> mime = mimeTypes(types);
                    if (operation == EXPORT) {
                        String type = mime.isEmpty() ? "application/octet-stream" : mime.iterator().next();
                        intent.setType(type.endsWith("/*") ? "application/octet-stream" : type);
                        intent.putExtra(Intent.EXTRA_TITLE, name);
                    } else {
                        if (allFiles || mime.isEmpty() || mime.contains("*/*")) {
                            intent.setType("*/*");
                            if (!allFiles && mime.contains("*/*")) request.postFilters = types;
                        } else if (mime.size() == 1) {
                            intent.setType(mime.iterator().next());
                        } else {
                            intent.setType("*/*");
                            intent.putExtra(Intent.EXTRA_MIME_TYPES, mime.toArray(new String[0]));
                        }
                        intent.putExtra(Intent.EXTRA_ALLOW_MULTIPLE, multiple);
                    }
                }
                if (initialUri != null && Build.VERSION.SDK_INT >= 26)
                    intent.putExtra(DocumentsContract.EXTRA_INITIAL_URI, Uri.parse(initialUri));
                picker = request;
                owner.startActivityForResult(intent, request.code);
            } catch (ActivityNotFoundException e) {
                launchFailed(request, UNAVAILABLE, e);
            } catch (SecurityException e) {
                launchFailed(request, DENIED, e);
            } catch (RuntimeException e) {
                launchFailed(request, BACKEND_ERROR, e);
            } catch (OutOfMemoryError e) {
                launchFailed(request, OUT_OF_MEMORY, e);
            }
        });
    }

    private static LinkedHashSet<String> mimeTypes(String[] types) {
        LinkedHashSet<String> mime = new LinkedHashSet<>();
        for (String type : types) {
            if (type.startsWith(".")) {
                String mapped = MimeTypeMap.getSingleton()
                        .getMimeTypeFromExtension(type.substring(1).toLowerCase(Locale.ROOT));
                mime.add(mapped == null ? "*/*" : mapped);
            } else mime.add(type.toLowerCase(Locale.ROOT));
        }
        return mime;
    }

    private static boolean matchesFilter(String[] types, String[] document) {
        if (types == null) return true;
        String name = document[1].toLowerCase(Locale.ROOT);
        String mime = document[2].toLowerCase(Locale.ROOT);
        for (String value : types) {
            String type = value.toLowerCase(Locale.ROOT);
            if (type.startsWith(".")) {
                if (name.endsWith(type)) return true;
                type = MimeTypeMap.getSingleton().getMimeTypeFromExtension(type.substring(1));
                if (type == null) continue;
            }
            if (type.equals("*/*") || type.equals(mime)
                    || (type.endsWith("/*") && mime.startsWith(type.substring(0, type.length() - 1))))
                return true;
        }
        return false;
    }

    private static void launchFailed(Request request, int error, Throwable cause) {
        if (picker == request) picker = null;
        finish(request.id, error, cause.toString(), null);
    }

    private static void cancel(long id) {
        UI.post(() -> {
            if (picker != null && picker.id == id) {
                picker.cancelled = true;
            } else {
                Request request = inspecting.get();
                if (request != null && request.id == id)
                    abandonInspection(request, CANCELLED, "");
            }
        });
    }

    static boolean onActivityResult(int code, int result, Intent data) {
        if (code < FIRST_CODE || code > LAST_CODE) return false;
        nextCode = Math.max(nextCode, code + 1);
        Request request = picker;
        if (request == null || request.code != code) return true;
        picker = null;

        if (result == Activity.RESULT_CANCELED) {
            finish(request.id, CANCELLED, "", null);
            return true;
        }
        if (result != Activity.RESULT_OK || data == null) {
            finish(request.id, INVALID_RESULT, "File selector returned an invalid result", null);
            return true;
        }

        Uri created = null;
        try {
            int grants = data.getFlags() & (READ | WRITE);
            Uri direct = data.getData();
            if (request.operation == EXPORT && validUri(direct) && (grants & WRITE) != 0)
                created = direct;
            if (request.cancelled) {
                cleanupUri(created);
                finish(request.id, CANCELLED, "", null, created != null);
                return true;
            }
            LinkedHashSet<Uri> uris = new LinkedHashSet<>();
            if (direct != null) uris.add(direct);
            ClipData clip = data.getClipData();
            if (clip != null && request.operation != EXPORT) {
                for (int i = 0; i < clip.getItemCount(); ++i) {
                    uris.add(clip.getItemAt(i).getUri());
                    if (uris.size() > request.maximum) {
                        cleanupUri(created);
                        finish(request.id, LIMIT, "File selection exceeds the requested limit", null);
                        return true;
                    }
                }
            }
            if (uris.isEmpty() || uris.stream().anyMatch(uri -> !validUri(uri))) {
                cleanupUri(created);
                finish(request.id, INVALID_RESULT, "File selector returned no valid content URI", null, created != null);
            } else if ((grants & (request.operation == EXPORT ? WRITE : READ)) == 0) {
                finish(request.id, DENIED, "File selector did not grant document access", null);
            } else {
                request.created = created;
                if (!inspecting.compareAndSet(null, request))
                    throw new RejectedExecutionException("Another Android document selection is being resolved");
                METADATA.execute(() -> completeSelection(request, uris, grants));
                UI.postDelayed(() -> abandonInspection(request, TIMEOUT, "Android document metadata timed out"),
                        METADATA_TIMEOUT_MS);
            }
        } catch (RejectedExecutionException e) {
            inspecting.compareAndSet(request, null);
            cleanupUri(created);
            finish(request.id, BUSY, "Android document metadata workers are busy", null, created != null);
        } catch (RuntimeException e) {
            inspecting.compareAndSet(request, null);
            cleanupUri(created);
            finish(request.id, INVALID_RESULT, e.toString(), null, created != null);
        } catch (OutOfMemoryError e) {
            inspecting.compareAndSet(request, null);
            cleanupUri(created);
            finish(request.id, OUT_OF_MEMORY, "", null, created != null);
        }
        return true;
    }

    private static void abandonInspection(Request request, int status, String message) {
        if (!inspecting.compareAndSet(request, null)) return;
        cleanupUri(request.created);
        finish(request.id, status, message, null, request.created != null);
    }

    private static void completeSelection(Request request, LinkedHashSet<Uri> uris, int grants) {
        int failure = BACKEND_ERROR;
        String message = "File selector returned invalid metadata";
        try {
            String[][] documents = new String[uris.size()][];
            int index = 0;
            for (Uri uri : uris) {
                if (inspecting.get() != request) return;
                if (request.operation == FOLDER)
                    uri = DocumentsContract.buildDocumentUriUsingTree(uri, DocumentsContract.getTreeDocumentId(uri));
                String[] row = query(uri, grants);
                if ((request.operation == FOLDER) != Document.MIME_TYPE_DIR.equals(row[2])) {
                    failure = INVALID_RESULT;
                    break;
                }
                if (!matchesFilter(request.postFilters, row)) {
                    failure = INVALID_RESULT;
                    message = "Selected document does not match the requested file types";
                    break;
                }
                documents[index++] = row;
            }
            if (index == documents.length) {
                if (inspecting.compareAndSet(request, null)
                        && !finish(request.id, OK, "", documents, request.created != null))
                    cleanupUri(request.created);
                return;
            }
        } catch (SecurityException e) {
            failure = DENIED;
            message = e.toString();
        } catch (FileNotFoundException e) {
            failure = NOT_FOUND;
            message = e.toString();
        } catch (IllegalArgumentException e) {
            failure = INVALID_RESULT;
            message = e.toString();
        } catch (RuntimeException e) {
            failure = IO_ERROR;
            message = e.toString();
        } catch (OutOfMemoryError e) {
            failure = OUT_OF_MEMORY;
            message = "";
        }
        abandonInspection(request, failure, message);
    }

    private static boolean validUri(Uri uri) {
        return uri != null && ContentResolver.SCHEME_CONTENT.equals(uri.getScheme())
                && uri.getAuthority() != null && !uri.getAuthority().isEmpty();
    }

    private static ContentResolver resolver() {
        return application.getContentResolver();
    }

    private static String[] row(Uri uri, Cursor cursor, int grants) {
        String displayName = optionalText(cursor, Document.COLUMN_DISPLAY_NAME);
        String mime = optionalText(cursor, Document.COLUMN_MIME_TYPE);
        int size = cursor.getColumnIndex(Document.COLUMN_SIZE);
        return new String[]{uri.toString(), displayName, mime,
                size < 0 || cursor.isNull(size) ? "" : Long.toString(cursor.getLong(size)), Integer.toString(grants)};
    }

    private static String optionalText(Cursor cursor, String column) {
        int index = cursor.getColumnIndex(column);
        String value = index < 0 ? null : cursor.getString(index);
        return value == null ? "" : value;
    }

    private static String[] query(Uri uri, int grants) throws FileNotFoundException {
        try (Cursor cursor = resolver().query(uri, COLUMNS, null, null, null)) {
            if (cursor == null || !cursor.moveToFirst()) throw new FileNotFoundException("Document is unavailable");
            return row(uri, cursor, grants);
        }
    }

    private static String[][] children(String value, int maximum, int grants) throws FileNotFoundException {
        Uri directory = Uri.parse(value);
        Uri children = DocumentsContract.buildChildDocumentsUriUsingTree(
                directory, DocumentsContract.getDocumentId(directory));
        ArrayList<String[]> rows = new ArrayList<>();
        try (Cursor cursor = resolver().query(children, CHILD_COLUMNS, null, null, null)) {
            if (cursor == null) throw new FileNotFoundException("Document directory is unavailable");
            int id = cursor.getColumnIndexOrThrow(Document.COLUMN_DOCUMENT_ID);
            while (cursor.moveToNext()) {
                if (rows.size() == maximum) return null;
                Uri child = DocumentsContract.buildDocumentUriUsingTree(directory, cursor.getString(id));
                rows.add(row(child, cursor, grants));
            }
            Bundle extras = cursor.getExtras();
            if (extras != null && extras.getBoolean(DocumentsContract.EXTRA_LOADING))
                throw new IllegalStateException("Android provider is still loading the directory");
        }
        return rows.toArray(new String[0][]);
    }

    private static String[] create(String value, String name, int grants) throws FileNotFoundException {
        int dot = name.lastIndexOf('.');
        String mime = dot < 0 ? null : MimeTypeMap.getSingleton()
                .getMimeTypeFromExtension(name.substring(dot + 1).toLowerCase(Locale.ROOT));
        if (mime == null) mime = "application/octet-stream";
        Uri uri = DocumentsContract.createDocument(resolver(), Uri.parse(value), mime, name);
        if (!validUri(uri)) throw new FileNotFoundException("Provider cannot create the document");
        try {
            return query(uri, grants);
        } catch (RuntimeException | FileNotFoundException | Error e) {
            cleanupUri(uri);
            throw e;
        }
    }

    private static InputStream openRead(String value) throws FileNotFoundException {
        // ContentResolver respects an AssetFileDescriptor's start offset and declared length.
        InputStream input = resolver().openInputStream(Uri.parse(value));
        if (input == null) throw new FileNotFoundException("Provider cannot open the document for reading");
        return input;
    }

    private static OutputStream openWrite(String value) throws FileNotFoundException {
        OutputStream output = resolver().openOutputStream(Uri.parse(value), "w");
        if (output == null) throw new FileNotFoundException("Provider cannot open the document for writing");
        return output;
    }

    private static boolean remove(String value) throws FileNotFoundException {
        Uri uri = Uri.parse(value);
        return DocumentsContract.isDocumentUri(application, uri) && DocumentsContract.deleteDocument(resolver(), uri);
    }

    private static void cleanup(String value) {
        cleanupUri(Uri.parse(value));
    }

    private static void cleanupUri(Uri uri) {
        if (uri == null) return;
        try {
            CLEANUP.execute(() -> {
                try {
                    if (!remove(uri.toString())) Log.w(TAG, "Provider declined to remove an incomplete export");
                } catch (FileNotFoundException | RuntimeException e) {
                    Log.w(TAG, "Unable to remove an incomplete export", e);
                }
            });
        } catch (RejectedExecutionException e) {
            Log.w(TAG, "Android document cleanup worker is busy");
        }
    }

    private static boolean finish(long id, int status, String message, String[][] documents) {
        return finish(id, status, message, documents, false);
    }

    private static boolean finish(long id, int status, String message, String[][] documents, boolean created) {
        return nativeResult(id, status, message, documents, created);
    }

    private static native boolean nativeResult(long id, int status, String message, String[][] documents, boolean created);
}
