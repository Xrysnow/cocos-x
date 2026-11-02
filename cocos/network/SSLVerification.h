#pragma once

#include "platform/CCPlatformMacros.h"
#include "yasio/yasio.hpp"
#include "yasio/detail/logging.hpp"
#include <string>

#if YASIO_SSL_BACKEND == 1
#include <openssl/ssl.h>
#include <openssl/x509v3.h>

NS_CC_BEGIN
namespace network
{
namespace ssl_verification
{
inline int rejectCertificate(int, X509_STORE_CTX*) { return 0; }

inline int verifyCertificate(int verified, X509_STORE_CTX* store)
{
    if (!verified)
        YASIO_LOG("TLS certificate rejected: %s", X509_verify_cert_error_string(X509_STORE_CTX_get_error(store)));
    return verified;
}

// yasio sets SNI before the handshake, but its OpenSSL backend does not set
// the certificate's expected DNS name/IP. Keep that policy in the caller.
inline void onHandshake(const SSL* connection, int where, int)
{
    if (!(where & SSL_CB_HANDSHAKE_START))
        return;
    auto ssl = const_cast<SSL*>(connection);
    const char* host = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name);
    bool valid = false;
    if (host && *host)
    {
        auto param = SSL_get0_param(ssl);
        X509_VERIFY_PARAM_set_hostflags(param, X509_CHECK_FLAG_NO_PARTIAL_WILDCARDS);
        auto ip = a2i_IPADDRESS(host);
        if (ip)
        {
            valid = X509_VERIFY_PARAM_set1_ip(param, ASN1_STRING_get0_data(ip), ASN1_STRING_length(ip)) == 1;
            ASN1_OCTET_STRING_free(ip);
        }
        else
            valid = SSL_set1_host(ssl, host) == 1;
    }
    valid = valid && SSL_CTX_get_verify_callback(SSL_get_SSL_CTX(ssl)) != rejectCertificate;
    SSL_set_verify(ssl, SSL_VERIFY_PEER, valid ? verifyCertificate : rejectCertificate);
}

// Called only on the io_service thread, before creating the SSL connection.
// An unreadable CA file leaves an empty store; it must never disable checking.
inline bool configure(SSL_CTX* ctx, const std::string& caFile)
{
    if (!ctx)
    {
        YASIO_LOG("TLS client context unavailable; secure open rejected");
        return false;
    }
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verifyCertificate);
    SSL_CTX_set_info_callback(ctx, onHandshake);
    auto store = X509_STORE_new();
    if (!store)
    {
        SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, rejectCertificate);
        return true;
    }
    SSL_CTX_set_cert_store(ctx, store);
    int loaded = caFile.empty() ? SSL_CTX_set_default_verify_paths(ctx)
                                : SSL_CTX_load_verify_locations(ctx, caFile.c_str(), nullptr);
    if (loaded != 1)
    {
        YASIO_LOG("TLS CA trust source could not be loaded; certificate verification remains required");
        SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, rejectCertificate);
    }
    return true;
}

// Schedule policy and open together. This also works before service.start(),
// and cannot race the worker's initial SSL_CTX creation or a fast handshake.
// The caller must keep one CA policy for all pending/active opens on a service.
inline bool open(yasio::io_service& service, size_t channel, std::string caFile)
{
    if (!service.channel_at(channel))
        return false;
    service.schedule(std::chrono::microseconds(0), [channel, caFile = std::move(caFile)](yasio::io_service& worker) {
        if (configure(worker.channel_at(channel)->get_ssl_context(true), caFile))
            worker.open(channel, yasio::YCK_SSL_CLIENT);
        else
            worker.close(static_cast<int>(channel));
        return true;
    });
    return true;
}
} // namespace ssl_verification
} // namespace network
NS_CC_END
#endif
