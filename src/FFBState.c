#include "include.h"

void FFB_handleControl(uint8_t cmd) {
    if (cmd & 0x01) {
        FFB_enableActuators();
    }
    if (cmd & 0x02) {
        // disable actuators
    }
    if (cmd & 0x04) {
        FFB_effectStop();
    }
    if (cmd & 0x08) {
        FFB_deviceReset();
    }
    if (cmd & 0x10) {
        // device pause
    }
    if (cmd & 0x20) {
        // device continue
    }
}

void FFB_enableActuators(void) {
    pendHIDStateInRept.reportID = 3;
    pendHIDStateInRept.state |= HID_ACTUATORS_ENABLED;
    pendHIDStateInRept.state &= ~HID_DEVICE_PAUSED;

    // stop effect
    inputFlags |= (1 << 1);
    SH1107_drawString(0,9,1,"start%u",inputFlags);
}

void FFB_effectStop(void) {
    pendHIDStateInRept.reportID = 3;
    pendHIDStateInRept.state &= ~HID_EFFECT_PLAYING;
    pendHIDStateInRept.state |= HID_DEVICE_PAUSED;

    // stop effect
    inputFlags |= (1 << 1);
    SH1107_drawString(0,9,1,"stop  %u",inputFlags);
}

void FFB_deviceReset(void) {
    pendHIDStateInRept.reportID = 3;
    pendHIDStateInRept.state = (HID_ACTUATOR_POWER) | (HID_ACTUATORS_ENABLED);
    inputFlags |= (1 << 1);
    SH1107_drawString(0,9,1,"reset %u",inputFlags);
}