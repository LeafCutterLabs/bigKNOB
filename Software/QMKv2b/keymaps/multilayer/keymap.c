#include QMK_KEYBOARD_H

#define _MAIN 0

//encoder
void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    switch(biton32(layer_state)){
      case 3:
		if (clockwise) {
		    tap_code(KC_RBRC);
          } else {
		    tap_code(KC_LBRC);
          }
          break;			 
	  case 2:
		if (clockwise) {
		    register_code(KC_LCTL);
            tap_code(KC_EQL);
            unregister_code(KC_LCTL);
          } else {
			register_code(KC_LCTL);
            tap_code(KC_MINS);
            unregister_code(KC_LCTL);
          }
          break;
      case 1:
		if (clockwise) {
		    register_code(KC_LCTL);
            tap_code(KC_EQL);
            unregister_code(KC_LCTL);
          } else {
			register_code(KC_LCTL);
            tap_code(KC_MINS);
            unregister_code(KC_LCTL);
          }
          break;
      default:
		if (clockwise) {
		    register_code(KC_LCTL);
            tap_code(KC_EQL);
            unregister_code(KC_LCTL);
          } else {
			register_code(KC_LCTL);
            tap_code(KC_MINS);
            unregister_code(KC_LCTL);
          }
          break;
    }
  }
}

enum custom_keycodes {
    CTRLZ = SAFE_RANGE,
	CTRLY,
	CTRLSFTZ,
	CTRLMIN,
	CTRLPLUS,
	CTRLC,
	CTRLF,
	CTRLB,
	GUILSFTZ,
	GUIZ,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CTRLZ:
		if (record->event.pressed) {
            //pressed
            SEND_STRING(SS_LCTRL("z"));
        } else {
            //released
        }
		break;
    case CTRLY:
		if (record->event.pressed) {
            //pressed
            SEND_STRING(SS_LCTRL("y"));
        } else {
            //released
        }
		break;
    case CTRLSFTZ:
		if (record->event.pressed) {
            //pressed
            SEND_STRING(SS_TAP(X_LSFT)SS_LCTRL("z"));
        } else {
            //released
        }
		break;
    case CTRLMIN:
		if (record->event.pressed) {
            //pressed
            SEND_STRING(SS_LCTRL("-"));
        } else {
            //released
        }
		break;
    case CTRLPLUS:
		if (record->event.pressed) {
            //pressed
            SEND_STRING(SS_LCTRL("+"));
        } else {
            //released
        }
		break;
	case CTRLC:
		if (record->event.pressed) {
            //pressed
            SEND_STRING(SS_LCTRL("c"));
        } else {
            //released
        }
		break;
	case CTRLF:
		if (record->event.pressed) {
            //pressed
            SEND_STRING(SS_LCTRL("f"));
        } else {
            //released
        }
		break;
	case CTRLB:
		if (record->event.pressed) {
            //pressed
            SEND_STRING(SS_LCTRL("b"));
        } else {
            //released
        }
		break;
	case GUIZ:
		if (record->event.pressed) {
            //pressed
            SEND_STRING(SS_LGUI("z"));
        } else {
            //released
        }
		break;
	case GUILSFTZ:
		if (record->event.pressed) {
            //pressed
            SEND_STRING(SS_TAP(X_LSFT)SS_LGUI("z"));
        } else {
            //released
        }
		break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { //buttion closest to usb is first
  [_MAIN] = LAYOUT(
     TO(1), KC_P, KC_V, KC_A, KC_LALT 
  ),
  [1] = LAYOUT(
     TO(2), CTRLY, CTRLZ, CTRLSFTZ, KC_TRANSPARENT 
  ),
  [2] = LAYOUT(
     TO(3), CTRLC, CTRLF, CTRLB, KC_TRANSPARENT
  ),
  [3] = LAYOUT(
     TO(_MAIN), KC_TRANSPARENT, GUIZ, GUILSFTZ, KC_B
  ),
};
