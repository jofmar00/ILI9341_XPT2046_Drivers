#include "LCD_TouchScreen.h"
#include "XPT2046.h"
#include "LCD_GFX.h"

void LCD_TouchScreen_readPosition(uint16_t *x, uint16_t *y) {
    uint16_t raw_x, raw_y;
    XPT2046_readPosition(&raw_x, &raw_y);

    // Fórmulas invertidas (para 0,0 = esquina superior izquierda)
    *x = (uint16_t)((raw_x - MIN_X) * LCD_WIDTH / (MAX_X - MIN_X));
    *y = (uint16_t)((raw_y - MIN_Y) * LCD_HEIGHT / (MAX_Y - MIN_Y));

}

uint16_t LCD_TouchScreen_readPressure() {
    return XPT2046_readPressure();
}
bool LCD_TouchScreen_isTouched() {
    // El valor 350 es un valor de pruebas, cuanto más bajo, más sensible será la pantalla
    return XPT2046_readPressure() > 350;
}

void LCD_TouchScreen_init() {
    XPT2046_init();
}
