#include "uinput.h"
#include <stddef.h>

struct libevdev_uinput *uinput_initialize() {
    // Create a evdev first to describe the features
    struct libevdev *evdev = libevdev_new();
    libevdev_set_name(evdev, "Simulated Right Button");
    libevdev_enable_event_type(evdev, EV_KEY);
    libevdev_enable_event_code(evdev, EV_KEY, KEY_F1, NULL);
    libevdev_enable_event_code(evdev, EV_KEY, KEY_F2, NULL);
    libevdev_enable_event_code(evdev, EV_KEY, KEY_F3, NULL);
    libevdev_enable_event_code(evdev, EV_KEY, KEY_F4, NULL);
    libevdev_enable_event_code(evdev, EV_KEY, KEY_F5, NULL);
    libevdev_enable_event_code(evdev, EV_KEY, KEY_F6, NULL);
    libevdev_enable_event_code(evdev, EV_KEY, KEY_LEFTMETA, NULL);
    libevdev_enable_event_code(evdev, EV_KEY, BTN_TOUCH, NULL);
    libevdev_enable_event_code(evdev, EV_KEY, BTN_RIGHT, NULL);
    libevdev_enable_event_type(evdev, EV_ABS);
    libevdev_enable_event_code(evdev, EV_ABS, ABS_X, &(struct input_absinfo) { .minimum=0, .maximum=1919 });
    libevdev_enable_event_code(evdev, EV_ABS, ABS_Y, &(struct input_absinfo) { .minimum=0, .maximum=1199 });
    libevdev_enable_event_code(evdev, EV_ABS, ABS_MT_SLOT, &(struct input_absinfo) { .minimum=0, .maximum=9 });
    libevdev_enable_event_code(evdev, EV_ABS, ABS_MT_TOUCH_MAJOR, &(struct input_absinfo) { .minimum=0, .maximum=255 });
    libevdev_enable_event_code(evdev, EV_ABS, ABS_MT_WIDTH_MAJOR, &(struct input_absinfo) { .minimum=0, .maximum=255 });
    libevdev_enable_event_code(evdev, EV_ABS, ABS_MT_POSITION_X, &(struct input_absinfo) { .minimum=0, .maximum=1919 });
    libevdev_enable_event_code(evdev, EV_ABS, ABS_MT_POSITION_Y, &(struct input_absinfo) { .minimum=0, .maximum=1199 });
    libevdev_enable_event_code(evdev, EV_ABS, ABS_MT_TRACKING_ID, &(struct input_absinfo) { .minimum=0, .maximum=65535 });
    libevdev_enable_property(evdev, INPUT_PROP_DIRECT);
    // Initialize uinput device from the evdev descriptor
    struct libevdev_uinput *uinput = NULL;
    if (libevdev_uinput_create_from_device(evdev,
            LIBEVDEV_UINPUT_OPEN_MANAGED, &uinput) != 0) {
        uinput = NULL;
    }
    // We don't need the fake evdev anymore.
    libevdev_free(evdev);
    return uinput;
}

void uinput_send_right_click(struct libevdev_uinput *uinput) {
    libevdev_uinput_write_event(uinput, EV_KEY, BTN_RIGHT, 1);
    libevdev_uinput_write_event(uinput, EV_SYN, SYN_REPORT, 0);
    libevdev_uinput_write_event(uinput, EV_KEY, BTN_RIGHT, 0);
    libevdev_uinput_write_event(uinput, EV_SYN, SYN_REPORT, 0);
}
