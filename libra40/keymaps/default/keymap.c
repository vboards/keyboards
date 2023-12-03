#include QMK_KEYBOARD_H
#include "analog.h"

#define _CENTER 512
#define _DEAD 200

#define _DOWN_TRESHOLD (_CENTER+_DEAD)
#define _UP_TRESHOLD (_CENTER-_DEAD)

#ifdef JOYSTICK_ENABLE
  int16_t xPos = 0;
  int16_t yPos = 0;

  bool yDownHeld = false;
  bool yUpHeld = false;
  bool xLeftHeld = false;
  bool xRightHeld = false;
  bool shiftHeld = false;

  void matrix_scan_user(void) {
    if(IS_LAYER_ON(1)) {
        yPos = analogReadPin(D7);
        if (!yDownHeld && yPos >= _DOWN_TRESHOLD) {
            register_code(KC_MPLY);
            yDownHeld = true;
        } else if (yDownHeld && yPos < _DOWN_TRESHOLD) {
            yDownHeld = false;
            unregister_code(KC_MPLY);
        } else if (!yUpHeld && yPos <= _UP_TRESHOLD) {
            yUpHeld = true;
            register_code(KC_MNXT);
        } else if (yUpHeld && yPos > _UP_TRESHOLD) {
            yUpHeld = false;
            unregister_code(KC_MNXT);
        }
        
        xPos = analogReadPin(B6);
        if (!xLeftHeld && xPos >= _DOWN_TRESHOLD) {
        register_code(KC_AUDIO_VOL_UP);
        xLeftHeld = true;
        } else if (xLeftHeld && xPos < _DOWN_TRESHOLD) {
        xLeftHeld = false;
        unregister_code(KC_AUDIO_VOL_UP);
        } else if (!xRightHeld && xPos <= _UP_TRESHOLD) {
        xRightHeld = true;
        register_code(KC_AUDIO_VOL_DOWN	);
        } else if (xRightHeld && xPos > _UP_TRESHOLD) {
        xRightHeld = false;
        unregister_code(KC_AUDIO_VOL_DOWN	);
        }
    }
    
    if(IS_LAYER_ON(0)) {
        yPos = analogReadPin(D7);
        if (!yDownHeld && yPos >= _DOWN_TRESHOLD) {
            register_code(KC_LEFT);
            yDownHeld = true;
        } else if (yDownHeld && yPos < _DOWN_TRESHOLD) {
            yDownHeld = false;
            unregister_code(KC_LEFT);
        } else if (!yUpHeld && yPos <= _UP_TRESHOLD) {
            yUpHeld = true;
            register_code(KC_RIGHT);
        } else if (yUpHeld && yPos > _UP_TRESHOLD) {
            yUpHeld = false;
            unregister_code(KC_RIGHT);
        }
        
        xPos = analogReadPin(B6);
        if (!xLeftHeld && xPos >= _DOWN_TRESHOLD) {
        register_code(KC_UP);
        xLeftHeld = true;
        } else if (xLeftHeld && xPos < _DOWN_TRESHOLD) {
        xLeftHeld = false;
        unregister_code(KC_UP);
        } else if (!xRightHeld && xPos <= _UP_TRESHOLD) {
        xRightHeld = true;
        register_code(KC_DOWN);
        } else if (xRightHeld && xPos > _UP_TRESHOLD) {
        xRightHeld = false;
        unregister_code(KC_DOWN);
        }
    }

  }

  //joystick config
    joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
        JOYSTICK_AXIS_IN(D7, 0, 512, 1023),
        JOYSTICK_AXIS_IN(B6, 0, 512, 1023)
    };
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_12x4(
        KC_ESC,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
        KC_TAB,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,   KC_ENT,
        KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_B,   KC_N,   KC_M,   KC_COMM,   KC_DOT,   KC_SLSH,
        KC_LCTL,   KC_LGUI,   KC_NO,   KC_MINS,   LT(1, KC_BSPC),   KC_NO,   LT(1, KC_SPC),   KC_RALT,   KC_RGUI,   KC_RCTL,   KC_DEL,   KC_NO
    ),
    [1] = LAYOUT_ortho_12x4(
        _______,   KC_HOME,   KC_END,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_NO,   KC_EQL,   KC_BSPC,
        _______,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_QUOT,
        KC_LSFT,   KC_GRV,   KC_SLEP,   KC_LPRN,   KC_LCBR,   KC_LBRC,   KC_RBRC,   KC_RCBR,   KC_RPRN,   _______,   _______,   KC_BSLS,
        _______,   _______,   _______,   _______,   _______,   KC_NO,   KC_SPC,   _______,   _______,   _______,   KC_DEL,   KC_NO
    ),

};
