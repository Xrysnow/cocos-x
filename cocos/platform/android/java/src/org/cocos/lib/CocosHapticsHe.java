package org.cocos.lib;

import java.lang.reflect.Constructor;
import java.lang.reflect.Method;

/** Optional, finite HE v1 preset adapter. All methods run on the actuator's serial worker. */
final class CocosHapticsHe
{
    private final Method create, start, stop, setSource;
    private final Constructor<?> constructor;
    private Object playing;

    private CocosHapticsHe(Class<?> player, Class<?> effect) throws ReflectiveOperationException
    {
        create = effect.getMethod("create", String.class);
        start = player.getMethod("start", int.class, int.class, int.class);
        stop = player.getMethod("stop");
        Constructor<?> ctor;
        Method setter = null;
        try
        {
            ctor = player.getConstructor(effect);
        }
        catch (NoSuchMethodException missing)
        {
            ctor = player.getConstructor();
            setter = player.getMethod("setDataSource", effect);
        }
        constructor = ctor;
        setSource = setter;
    }

    static CocosHapticsHe open() throws ReflectiveOperationException
    {
        Class<?> player = Class.forName("android.os.HapticPlayer");
        if (!Boolean.TRUE.equals(player.getMethod("isAvailable").invoke(null)))
            return null;
        return new CocosHapticsHe(player, Class.forName("android.os.DynamicEffect"));
    }

    // Sample boundary minima ensure the linear HE curve stays inside each mixed step.
    // Emit only corners, reserving one sample for each end ramp. Frequency is relative to 50.
    static String encode(long[] times, int[] amps, float[] texture)
    {
        if (times.length != amps.length || amps.length != texture.length)
            return null;
        int[] level = new int[1000], frequency = new int[1000];
        int size = 0;
        for (int i = 0; i < times.length; ++i)
        {
            if (times[i] <= 0 || times[i] > 1000 - size || amps[i] < 0 || amps[i] > 255
                    || !(texture[i] >= 0 && texture[i] <= 1))
                return null;
            int end = size + (int) times[i];
            java.util.Arrays.fill(level, size, end, amps[i] * 100 / 255);
            java.util.Arrays.fill(frequency, size, end, Math.round(texture[i] * 100) - 50);
            size = end;
        }
        StringBuilder json = new StringBuilder("{\"Metadata\":{\"Version\":1},\"Pattern\":[");
        int events = 0;
        for (int begin = 0; begin < size;)
        {
            if (level[begin] == 0)
            {
                ++begin;
                continue;
            }
            int end = begin + 1;
            while (end < size && level[end] > 0)
                ++end;
            int length = end - begin;
            if (length < 3 || ++events > 16)
                return null;
            if (events > 1)
                json.append(',');
            json.append("{\"Event\":{\"Type\":\"continuous\",\"RelativeTime\":").append(begin)
                .append(",\"Duration\":").append(length)
                .append(",\"Parameters\":{\"Intensity\":100,\"Frequency\":50,\"Curve\":[");
            int points = 0;
            for (int t = 0; t <= length; ++t)
            {
                int pos = begin + t;
                int a = t == 0 || t == length ? 0 : Math.min(level[pos - 1], level[pos]);
                int f = frequency[Math.min(pos, end - 1)];
                if (t > 1 && t < length - 1 && level[pos - 2] == level[pos - 1]
                        && level[pos - 1] == level[pos] && level[pos] == level[pos + 1]
                        && frequency[pos - 1] == f && frequency[pos + 1] == f)
                    continue;
                if (++points > 16)
                    return null;
                if (points > 1)
                    json.append(',');
                json.append("{\"Time\":").append(t).append(",\"Intensity\":").append(a / 100.0)
                    .append(",\"Frequency\":").append(f).append('}');
            }
            json.append("]}}}");
            begin = end;
        }
        return events == 0 ? null : json.append("]}").toString();
    }

    Object prepare(String json) throws ReflectiveOperationException
    {
        Object effect = create.invoke(null, json);
        if (effect == null)
            return null;
        if (setSource == null)
            return constructor.newInstance(effect);
        Object player = constructor.newInstance();
        setSource.invoke(player, effect);
        return player;
    }

    boolean playing() { return playing != null; }

    void start(Object player) throws ReflectiveOperationException
    {
        // Keep the handle even if start throws after handing the effect to the service.
        playing = player;
        start.invoke(player, 1, 0, 255);
    }

    void stop() throws ReflectiveOperationException
    {
        if (playing != null)
        {
            stop.invoke(playing);
            playing = null;
        }
    }
}
