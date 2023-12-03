# Libra Mini
Compile the firmware using QMK MSYS and flash using the .hex file with QMK Toolbox (Ensure the selected MCU is ATmega32U4)

For any support on how to change the keyboard to your liking, visit https://docs.qmk.fm/#/ or visit the QMK Discord at https://discord.gg/qmk

# Keymap info

The current default keymap is set up with 2 layers, and with the joystick having different functionality on each layer.

## Joystick

Shoutout to Joshinator, their blog is what helped me get to the finish line on the joystick portion of the firmware, since I hadn't ever worked with them before. You can find their page at https://joshinator.de/posts/qmk-gamepad-part-3/, which I highly recommend doing.

To change the functionality of the joystick look inside the ```#ifdef JOYSTICK_ENABLE```.

The following lines of code will change the joystick functionality on Layer 1, and can be changed around. If another layer is added with additional functionality for the joystick, ensure that the check for ```if(IS_LAYER_ON(X)``` is before ```if(IS_LAYER_ON(0)```. Because the default layer 0 is always on, it must be checked last.

```if(IS_LAYER_ON(1)) {
        yPos = analogReadPin(D7);
        if (!yDownHeld && yPos >= _DOWN_TRESHOLD) {
            register_code(KC_MPLY); // Left joystick register code
            yDownHeld = true;
        } else if (yDownHeld && yPos < _DOWN_TRESHOLD) {
            yDownHeld = false;
            unregister_code(KC_MPLY); // Left joystick unregister code
        } else if (!yUpHeld && yPos <= _UP_TRESHOLD) {
            yUpHeld = true;
            register_code(KC_MNXT); // Right joystick register code
        } else if (yUpHeld && yPos > _UP_TRESHOLD) {
            yUpHeld = false;
            unregister_code(KC_MNXT); // Right joystick unregister code
        }
        
        xPos = analogReadPin(B6);
        if (!xLeftHeld && xPos >= _DOWN_TRESHOLD) {
        register_code(KC_AUDIO_VOL_UP); // Up joystick register code
        xLeftHeld = true;
        } else if (xLeftHeld && xPos < _DOWN_TRESHOLD) {
        xLeftHeld = false;
        unregister_code(KC_AUDIO_VOL_UP); // Up joystick unregister code
        } else if (!xRightHeld && xPos <= _UP_TRESHOLD) {
        xRightHeld = true;
        register_code(KC_AUDIO_VOL_DOWN	); // Down joystick register code
        } else if (xRightHeld && xPos > _UP_TRESHOLD) {
        xRightHeld = false;
        unregister_code(KC_AUDIO_VOL_DOWN); // Down joystick unregister code
        }
    }
```
