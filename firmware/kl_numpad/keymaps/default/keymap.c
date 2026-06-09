#include QMK_KEYBOARD_H
#include "gpio.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,             KC_DOT, KC_PENT
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }

    return true;
}

void keyboard_post_init_user(void) {
    gpio_set_pin_input_high(ENCODER_BTN_PIN);
}

void matrix_scan_user(void) {
    static bool pressed = false;

    if (!gpio_read_pin(ENCODER_BTN_PIN)) {
        if (!pressed) {
            tap_code(KC_MPLY);
            pressed = true;
        }
    } else {
        pressed = false;
    }
}

#ifdef OLED_ENABLE

bool oled_task_user(void) {
    oled_clear();

    oled_write_ln("KL NUMPAD", false);
    oled_write_ln("", false);

    oled_write_ln("Volume Knob", false);

    if (host_keyboard_led_state().num_lock) {
        oled_write_ln("NUMLOCK ON", false);
    } else {
        oled_write_ln("NUMLOCK OFF", false);
    }

    return false;
}

#endif

