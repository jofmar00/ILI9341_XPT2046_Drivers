/**
 * @file        LCD_TouchScreen_test.c
 * @brief       Implementación de las funciones de pruebas gráficas que utilizan el módulo
 *              LCD_TouchScreen.
 * 
 * @author      Jorge Fernández Marín
 * @date        Abril de 2025
 * 
 * @details     Este archivo contiene la implementación de funciones de pruebas del módulo
 *              tactil, incluyendo test de detección de presión y pintado en pantalla.
 * 
 * @note        Este archivo fue creado como parte del proyecto "Diseño de shield PCDB para
 *              un nRF52840DK" para la asignatura Laboratorio de sistemas empotrados 2025, 
 *              perteneciente al plan de estudios del itinerario Ingeniería Informática en Unizar.
 * @see         LCD_TouchScreen_test.h, LCD_TouchScreen.c
 */

#include "LCD_GFX.h"
#include "LCD_TouchScreen.h"
#include "XPT2046.h"
#include "nrf_delay.h"
#include <stdio.h>

void LCD_TouchScreen_test_pressure() {
	LCD_GFX_fillScreen(BLACK);
	uint16_t pressure;
	char buffer[100];
	LCD_GFX_drawString(0, LCD_HEIGHT >> 2, "Touch the screen!", WHITE, BLACK, 2);
	LCD_GFX_drawString(0, LCD_HEIGHT >> 1, "Pressure:", WHITE, BLACK, 3);
	while(1) {
		pressure = LCD_TouchScreen_readPressure();
		sprintf(buffer,"%d   ", pressure);
		LCD_GFX_drawString(160, LCD_HEIGHT >> 1, buffer, GREEN, BLACK, 3);
	}
}

void LCD_TouchScreen_test_paint() {
    LCD_GFX_fillScreen(WHITE);
	LCD_GFX_setRotation(1);
	LCD_GFX_drawString(120,10, "PINTA!", MAGENTA, WHITE, 3);
    LCD_GFX_setRotation(0);
	LCD_GFX_drawString(70, 5, "Salir", BLACK, RED, 2);
	uint16_t x = 0, y = 0;
	uint8_t terminado = 0;
    while (!terminado) {
        if (LCD_TouchScreen_isTouched()) {
			LCD_TouchScreen_readPosition(&x, &y);
			// Terminar sesion pintado
			if(y < 30 && (x > 70 && x <150)) {
				terminado = 1;
			}
			// Pintar normal
			else {
				LCD_GFX_fillRect(LCD_WIDTH - x, y, 5, 5, BLUE);
			}
        }
    }
	LCD_GFX_fillScreen(BLACK);
}

void LCD_TouchScreen_test_calibrate() {
	uint16_t min_x, min_y, max_x, max_y;
	char buff [100];
	LCD_GFX_fillScreen(BLACK);
	LCD_GFX_drawString(0, LCD_HEIGHT >> 1, "Toca los cuadrados", GREEN, BLACK, 2);
	
	LCD_GFX_fillRect(0, 0, 10, 10, RED);
	while (!LCD_TouchScreen_isTouched());
	XPT2046_readPosition(&min_x, &min_y);
	LCD_GFX_fillRect(0, 0, 10, 10, BLACK);
	while (LCD_TouchScreen_isTouched())

	nrf_delay_us(10000000);

	LCD_GFX_fillRect(LCD_WIDTH - 10, LCD_HEIGHT - 10, 10, 10, RED);
	while (!LCD_TouchScreen_isTouched());
	XPT2046_readPosition(&max_x, &max_y);
	LCD_GFX_fillRect(LCD_WIDTH - 10, LCD_HEIGHT - 10, 10, 10, BLACK);
	

	sprintf(buff, "MIN_X:%d\nMIN_Y:%d\nMAX_X:%d\nMAX_Y:%d", min_x, min_y, max_x, max_y);
	LCD_GFX_fillScreen(BLACK);
	LCD_GFX_drawString(0, LCD_HEIGHT >> 2, buff, WHITE, BLACK, 2);
}
