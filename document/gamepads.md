# Gamepad input and feedback

Use `cc::input::GamepadService` for controller input, mappings, motion and feedback. Get the service from `cc::Director::getInstance()->getGamepads()` in C++, or use `cc.gamepad` in Lua. The Director owns the service and publishes one frame for each logical update. Call the service on the engine thread. [Public API](../cocos/input/gamepad/GamepadService.h) · [Lua binding](../cocos/scripting/lua-bindings/manual/gamepad/cclua_gamepad.cpp)

## Read a frame and send feedback

Read the current frame during your update. Use `pressed` and `released` for edges and `down` for held state. A short tap can produce both edges in one frame. Keep the `DeviceId` while the controller is connected and look up its view again each tick. The frame, pad views and their spans expire at the next publish. [Frame and events](../cocos/input/gamepad/GamepadFrame.h)

```cpp
#include "base/Director.h"
#include "input/gamepad/GamepadService.h"

void updateController(cc::input::DeviceId id)
{
    using namespace cc::input;
    auto& gamepads = cc::Director::getInstance()->getGamepads();
    const auto* pad = gamepads.frame().find(id);
    if (pad && pad->pressed(Button::South) && pad->caps().has(Feature::BodyRumble))
        gamepads.submit(id, Rumble{0.25f, 0.5f, std::chrono::milliseconds(120)});
}
```

In Lua, use `cc.gamepad.frame():find(id)`, `pad:pressed("south")` and `pad:has("bodyRumble")`. Submit the same effect with `cc.gamepad.submit(id, {kind = "rumble", low = 0.25, high = 0.5, durationMs = 120})`. Check the returned command ID or error and use the matching `outputDone` event (`OutputDone` in C++) to observe completion. A queued command may be superseded, cancelled or fail before reaching the controller. [Output commands](../cocos/input/gamepad/GamepadOutput.h)

- Use `caps()` in C++ or `pad:has(...)` in Lua to check each control, sensor or feedback feature. Capabilities can change after the first native report or after a backend falls back. A battery reading can be unknown or supply a coarse level from 0 to 3.
- Use `Rumble` for the low and high body channels, `TriggerRumble` for independent trigger motors, and `AdaptiveTrigger` for supported trigger resistance and vibration modes. Check the corresponding capability for each command. Keep the `subscribeSensor` lease while consuming motion samples and close it when finished.
- A device can expose raw buttons, axes and hats before it has a logical mapping. Use `inputLayout()` with `setLocalBindings` to bind that device's raw indices, or import SDL-format mapping text with `importMappings`. Layouts can differ across transports and backends. Mapping import and the native backends work without linking SDL. [Mapping API](../cocos/input/gamepad/GamepadMapping.h)
- Use `assignPlayer` to associate the current device with a logical player slot. To change physical player LEDs, submit `PlayerLights` when the controller exposes that capability.

## Play a DualSense haptic waveform

Use an `AudioSource` to drive the left and right grips independently. Stereo maps left and right samples to the corresponding grips. Mono drives both. Use `GamepadService::createHapticPlayback(id, source)` in C++ or `cc.gamepad.createHapticPlayback(id, source)` in Lua. Both accept static sources and independently reopenable file sources. [Playback handle](../cocos/input/gamepad/GamepadOutput.h)

```lua
local gamepad = cc.gamepad
local function feedback(id, music)
    local pad = gamepad.frame():find(id)
    if pad and pad:has("bodyHaptics") then
        local playback = assert(gamepad.createHapticPlayback(id, music:getSource()))
        assert(playback:setIntensity(0.7))
        assert(playback:play())
        return playback
    end
end

-- Keep the returned handle while it plays and call playback:close() on scene exit.
```

`setIntensity` takes a value in [0, 1], with a default of 1. The handle also provides `pause`, `resume`, `seekTime`, `setLooping`, `stop`, `snapshot` and `close`. Controls return `true` on acceptance, or `nil` and an error. The snapshot reports state, error, source time and duration, intensity, looping, seekability and stop reason. Use it to observe the first effective audio and natural completion.

Playing claims the grip and can replace body rumble or another waveform. A paused waveform retains the grip. A new rumble can replace it. To release the grip explicitly, use `playback:stop()` or submit `{kind = "stop", channel = "body"}`. Focus loss stops waveform playback. An audio endpoint disconnect ends the handle's connection, and a subsequent connection needs a new handle.

The Windows and Linux USB backends expose `bodyHaptics` when the matching controller's four-channel output is verified and its HID output can be opened for writing. On Linux, this requires a running PipeWire session and the `libpipewire-0.3` pkg-config module at build time. Waveform playback stays routed to the paired controller when the default output changes. When the game mixer uses the controller's audio endpoint, ordinary sound uses the front channels and grip waveforms use the rear channels.

## Platform input paths

| Platform | Base backend | Limits and fallback |
| --- | --- | --- |
| Windows | XInput for compatible controllers. Raw Input and direct HID reads for other joystick or gamepad collections, with DirectInput as a legacy fallback. | XInput supports four slots, standard controls, two body motors and battery information where the DLL and device provide it. It supplies no stable physical device ID, Guide, Share, paddles or trigger motors through the calls used here. Generic HID and DirectInput expose input. Device-specific feedback requires an enhanced backend. The engine skips proven XInput mirrors and deduplicates Raw Input and DirectInput when they identify the same interface. |
| Linux | evdev for buttons, sticks, triggers and hats. It also reads a matched motion event node and uses `FF_RUMBLE` when the kernel and permissions allow. | Driver mappings and exported features depend on the kernel. Generic evdev has no gamepad battery, touchpad contacts, trigger motors or light output in this module. Device discovery uses libudev when built with it. An inotify and periodic scan path can discover devices without libudev. |
| macOS | GameController profiles, with a read-only IOHIDManager fallback for joystick and gamepad collections outside the GameController path. | The OS profile, hardware and OS release determine which extra buttons, sensors, battery data and feedback are available. The IOHIDManager fallback supplies raw buttons, axes and hats only. |
| iOS | GameController profiles. | Support depends on the connected controller's OS profile and available APIs. There is no generic IOHIDManager fallback on iOS. |
| Android | `InputManager` and `InputDevice` for device discovery, with key and motion events forwarded by `CocosActivity`. | Keep the activity's input and lifecycle hooks in a custom host. Buttons and axes depend on the OS layout. The generic path can use a controller vibrator and can expose OS-provided touch, motion and an input RGB light where the device and API level allow. Generic vibration uses one controller vibrator. This path has no independent motor channels, adaptive triggers or generic battery reporting. |

## Controller-specific backends

| Controller | Backend and transport | Features and limits |
| --- | --- | --- |
| Xbox One, Series and Elite | Windows.Gaming.Input (WGI) on Windows, selected at launch. The controller must be exposed by Windows as a supported Xbox `Gamepad`. | Body and trigger motors, battery information and Elite paddles where WGI exposes them. The WGI mapping omits Guide and Share. Some controllers visible only through XInput can be absent in WGI mode. |
| Xbox One S, Series and Elite Series 2 | Native Bluetooth reports on Windows and Linux. | Windows uses a directly readable, supported Bluetooth HID gamepad interface outside the XInput mirror path. It can expose Guide, Series Share and independent Elite Series 2 paddles on supported report formats and profiles. Linux keeps evdev input, including the keys exported by the kernel, and uses hidraw only for a uniquely matched controller. Bluetooth battery reports provide a coarse level. Four-motor feedback requires a valid output report and a successful write probe. Linux returns body feedback to `FF_RUMBLE` when hidraw output becomes unavailable. Linux USB and Xbox Wireless Adapter input and feedback remain with the kernel. |
| DualShock 4 | Sony HID over USB or Bluetooth on Windows and Linux. Sony USB Host on Android. | Two touch contacts, motion, battery, body rumble and RGB where reports and transport allow. Expect reduced capabilities when enhanced reports, calibration or writes are unavailable. The Sony USB Host path requires a user grant and a successful HID interface claim. Android Bluetooth uses the OS path. |
| DualSense and DualSense Edge | Sony HID over USB or Bluetooth on Windows and Linux. Sony USB Host on Android. | Touchpad, motion, battery, body rumble, RGB, player lights and adaptive triggers where available. USB grip waveforms on Windows and Linux require the matching four-channel controller audio endpoint. Edge extra controls depend on the report layout. Bluetooth can start with a simpler input report and may need protocol initialization before full features appear. The Android USB Host path requires a grant and a successful claim. |
| Switch Pro Controller and first-generation Joy-Con | Nintendo HID on Windows and Linux over supported USB and Bluetooth interfaces. | Full reports provide battery and motion. The driver sends body rumble with independent low and high frequency components and sets player LEDs where supported. Left and right Joy-Con are separate devices. The driver targets the first-generation Pro Controller and Joy-Con. On Linux, the dedicated path takes over after valid input, otherwise evdev remains available. On Windows, a device that cannot open the dedicated path can still use the generic HID stack. |
| Platform-managed controllers on Apple | GameController and Core Haptics. | Supported profiles can supply battery, motion, touch, paddles, RGB, body haptics and DualSense adaptive triggers. RGB, battery and haptics use APIs introduced in macOS 11 and iOS 14. DualSense adaptive triggers require macOS 11.3 or iOS 14.5. The native profile decides which features are exposed. |

### Enable Windows.Gaming.Input

Connect the Xbox controller before launching the application. Enable WGI in `cc.Configuration` from the startup script before the first engine frame.

```lua
cc.Configuration:getInstance():setValue("cocos.gamepad.windows.wgi", true)
```

Pass a boolean `true` to opt in. Use `false` or omit the setting to keep the default XInput path. The Windows gamepad service reads the setting once at startup on the first engine frame. The engine resolves WinRT entry points and checks `Gamepad` and `RawGameController` at runtime. The identification API is available from Windows 10 version 1703, build 15063. If activation or enumeration fails, or the startup probe finds no supported Xbox controller with trigger rumble capability, the process uses XInput. [Microsoft API requirements](https://learn.microsoft.com/en-us/uwp/api/windows.gaming.input.rawgamecontroller?view=winrt-26100) · [Windows backend selection](../cocos/input/gamepad/private/win/WinGamepadBackend.cpp)

The two Xbox paths are exclusive. XInput slots cannot be matched reliably to WGI objects, especially with identical controllers or after hotplug. Exclusive selection prevents duplicate pads and competing motor writes. WGI mode also filters the known Xbox interfaces from the legacy Windows paths. [WGI backend](../cocos/input/gamepad/private/win/WinWgi.cpp)

## Linux device permissions

Run the game as your normal user. Check access to the nodes corresponding to the controller and its transport. Node numbers can change on reconnect.

| Backend | Required access | Behavior with less access |
| --- | --- | --- |
| evdev | Read the controller's `/dev/input/event*` node. A separate motion node needs read access when used. Write the controller event node for `FF_RUMBLE`. | Read-only access allows input. Without read access the event node cannot supply input. |
| Sony hidraw | Read `/dev/hidraw*` for native reports. Open it read-write for output and Bluetooth mode changes that send a report. | A readable node can take over input once full reports arrive. A read-only native endpoint has no Sony output. If the native endpoint cannot attach, evdev can still supply the controls its driver exposes. |
| Switch hidraw | Open `/dev/hidraw*` read-write to initialize the report mode and send commands. | If the node cannot be opened read-write or protocol initialization fails, evdev can still supply the controls its driver exposes. |
| Xbox Bluetooth hidraw | Read the matching `/dev/hidraw*` node for battery reports. Open it read-write for both body and trigger output. The associated evdev node still needs read access. | Without hidraw, evdev keeps input and available `FF_RUMBLE`. Read-only hidraw can add battery data while body vibration stays with evdev. |

### Grant access with `uaccess`

On a desktop using systemd-udev and logind, `uaccess` grants a device ACL to the active local seat user. Upstream rules already tag gamepad event nodes classified as `ID_INPUT_JOYSTICK`. Check the existing ACL before adding a rule. Put a local rule in `/etc/udev/rules.d/71-cocos-gamepads.rules` so it runs before the seat ACL rule, normally `73-seat-late.rules`. [Default joystick rule](https://github.com/systemd/systemd/blob/main/rules.d/70-uaccess.rules.in) · [Seat ACL rule](https://github.com/systemd/systemd/blob/main/rules.d/73-seat-late.rules.in)

1. Connect the controller. Use `udevadm info --attribute-walk --name=/dev/hidrawN` to find its `KERNELS` HID parent. Replace `N` with the actual node number. A HID parent such as `0005:045E:0B13.0007` identifies the Bluetooth bus, vendor and product. `0003` is USB and `0005` is Bluetooth. The suffix identifies the current kernel instance. [udevadm(8)](https://www.freedesktop.org/software/systemd/man/latest/udevadm.html) · [udev(7)](https://www.freedesktop.org/software/systemd/man/latest/udev.html)
2. As an administrator, save the rule file with mode `0644` and add only the line matching the controller. The examples grant access to a DualSense over USB or Bluetooth, a Switch Pro Controller over USB or Bluetooth, and an Xbox Series controller over Bluetooth. Use the observed HID parent and the product IDs below to adapt a line for another model.

   ```udev
   SUBSYSTEM=="hidraw", KERNEL=="hidraw[0-9]*", KERNELS=="000[35]:054C:0CE6.*", TAG+="uaccess"
   SUBSYSTEM=="hidraw", KERNEL=="hidraw[0-9]*", KERNELS=="000[35]:057E:2009.*", TAG+="uaccess"
   SUBSYSTEM=="hidraw", KERNEL=="hidraw[0-9]*", KERNELS=="0005:045E:0B13.*", TAG+="uaccess"
   ```

   | Vendor and transport | Product IDs accepted by the Linux native backend |
   | --- | --- |
   | Sony `054C`, USB or Bluetooth | DualShock 4 `05C4`, `09CC`. DualSense `0CE6`. DualSense Edge `0DF2`. |
   | Nintendo `057E`, USB or Bluetooth | Joy-Con left `2006`, Joy-Con right `2007`, Pro Controller `2009`. The controller must expose the matching HID interface on that transport. |
   | Microsoft `045E`, Bluetooth | Xbox One S `02E0`, `02FD`, `0B20`. Series `0B13`. Elite Series 2 `0B05`, `0B22`. |

   If the distribution leaves a needed evdev node inaccessible, check its properties with `udevadm info --query=property --name=/dev/input/eventN` and inspect its parent with `--attribute-walk`. Add a separate rule only for the relevant event interface. For example, this matches a Bluetooth Switch Pro event node classified as a joystick. Use `ID_INPUT_ACCELEROMETER` for a separate motion interface that actually carries that property.

   ```udev
   SUBSYSTEM=="input", KERNEL=="event[0-9]*", ENV{ID_INPUT_JOYSTICK}=="1", KERNELS=="0005:057E:2009.*", TAG+="uaccess"
   ```

3. Run `sudo udevadm control --reload-rules`, then unplug and reconnect the USB controller or disconnect and reconnect it over Bluetooth. Reloading rules alone leaves existing nodes in their current state.
4. From the local session that runs the game, use `udevadm info --query=property --name=/dev/hidrawN` to check for the `uaccess` tag. Run `getfacl /dev/hidrawN` or `getfacl /dev/input/eventN` to check the effective ACL. Restart the game if it already had the node open read-only. If the tag exists and there is no user ACL, check the active seat with `loginctl session-status`. A headless service, SSH login or container may lack an active desktop seat or access to the node. Use a device-specific group and a scoped device grant for that deployment.

Keep rules narrow enough to match the specific controller and interface. Broad access to input event nodes can expose keyboard and mouse input. The game requires no `/dev/uinput` or `/dev/uhid` access during ordinary use. Those nodes are for virtual test devices. [Linux event backend](../cocos/input/gamepad/private/linux/EvdevGamepadBackend.cpp)
