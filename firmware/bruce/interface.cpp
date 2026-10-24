// Interface do BMO v1 para o Bruce. Base: boards/ESP32-C5-tft/interface.cpp do Bruce 1.16.1
// (ILI9341 no SPI compartilhado + 3 botões), sem o touch, que o BMO não usa.
#include "core/powerSave.h"
#include "core/utils.h"
#include <interface.h>

void _setup_gpio() {
    // Todo CS do barramento compartilhado começa em HIGH, para ninguém responder fora da vez.
    for (int cs : {TFT_CS, CC1101_SS_PIN, SDCARD_CS}) {
        pinMode(cs, OUTPUT);
        digitalWrite(cs, HIGH);
    }
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    for (int btn : {UP_BTN, SEL_BTN, DW_BTN}) pinMode(btn, INPUT_PULLUP);
    bruceConfig.colorInverted = 0;
}

void _post_setup_gpio() {}

int getBattery() { return 0; }

bool isCharging() { return false; }

void _setBrightness(uint8_t brightval) {
    if (brightval == 0) {
        analogWrite(TFT_BL, brightval);
    } else {
        int bl = MINBRIGHT + round(((255 - MINBRIGHT) * brightval / 100));
        analogWrite(TFT_BL, bl);
    }
}

void InputHandler(void) {
    static unsigned long tm = 0;
    if (millis() - tm < 200 && !LongPress) return;

    bool upPressed = digitalRead(UP_BTN) == BTN_ACT;
    bool selPressed = digitalRead(SEL_BTN) == BTN_ACT;
    bool dwPressed = digitalRead(DW_BTN) == BTN_ACT;

    bool anyPressed = upPressed || selPressed || dwPressed;
    if (anyPressed) tm = millis();
    if (anyPressed && wakeUpScreen()) return;

    AnyKeyPress = anyPressed;
    if (upPressed && dwPressed) {
        EscPress = true;
        return;
    }
    PrevPress = upPressed;
    NextPress = dwPressed;
    SelPress = selPressed;
}

void powerOff() {}

void checkReboot() {}
