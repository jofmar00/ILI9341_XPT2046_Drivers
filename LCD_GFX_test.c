/**
 * @file        LCD_GFX_test.c
 * @brief       Implementación para las funciones de pruebas gráficas que utilizan el módulo
 *              LCD_GFX.
 * 
 * @author      Jorge Fernández Marín
 * @date        Abril de 2025
 * 
 * @details     Este archivo contiene las implementacion de funciones de pruebas gráficas
 *              de dibujado de circulos, lineas, rectangulos, bitmaps, llenado de pantalla
 *              y escritura de texto.
 * 
 * @note        Este archivo fue creado como parte del proyecto "Diseño de shield PCDB para
 *              un nRF52840DK" para la asignatura Laboratorio de sistemas empotrados 2025, 
 *              perteneciente al plan de estudios del itinerario Ingeniería Informática en Unizar.
 * @see         LCD_GFX_test.h, LCD_GFX.c
 */
#include "LCD_GFX_test.h"
#include "LCD_GFX.h"
#include "bitmaps.h"


void LCD_GFX_test_circles(uint8_t radius, uint16_t color) {
    int16_t w = LCD_WIDTH + radius;
    int16_t h = LCD_HEIGHT + radius;
    int16_t r2 = radius << 1;
    for (uint16_t x = 0; x < w; x+= r2) {
        for (uint16_t y = 0; y < h; y+= r2) {
            LCD_GFX_drawCircle(x, y, radius, color);
        }
    }
}

void LCD_GFX_test_filledCircles(uint8_t radius, uint16_t color) {
    LCD_GFX_fillScreen(BLACK);
    uint16_t r2 = radius << 1;
    for (uint16_t x = radius; x < LCD_WIDTH; x+=r2) {
        for (uint16_t y = radius; y < LCD_HEIGHT; y+=r2) {
            LCD_GFX_fillCircle(x, y, radius, color);
        }
    }
}

void LCD_GFX_test_lines(uint16_t color) {
    LCD_GFX_fillScreen(BLACK);
    int16_t x1 = 0, y1 = 0, x2 = 0, y2 = LCD_HEIGHT;
    for (x2 = 0; x2 < LCD_WIDTH; x2 += 6) {
        LCD_GFX_drawLine(x1, y1, x2, y2, color);
    }
    x2 = LCD_WIDTH - 1;
    y2 = LCD_HEIGHT - 1;
    for (; y2 > 0; y2 -= 6) {
        LCD_GFX_drawLine(x1, y1, x2, y2, color);
    }
}

void LCD_GFX_test_rects(uint16_t color) {
    uint16_t center_x = (LCD_WIDTH >> 1) - 1, center_y = (LCD_HEIGHT >> 1) - 1;
    uint16_t n_rects = LCD_WIDTH <= LCD_HEIGHT ? LCD_WIDTH : LCD_HEIGHT;
    
    for (uint16_t i = 2; i < n_rects; i+=10) {
        uint8_t j = i >> 1;
        LCD_GFX_drawRect(center_x - j, center_y -j, i, i, color);
    }
}

void LCD_GFX_test_filledRects(uint16_t color1, uint16_t color2, uint16_t color3) {
    uint16_t center_x = (LCD_WIDTH >> 1) - 1, center_y = (LCD_HEIGHT >> 1) - 1;
    uint16_t n_rects = LCD_WIDTH <= LCD_HEIGHT ? LCD_WIDTH-1 : LCD_HEIGHT-1;
    LCD_GFX_fillScreen(BLACK);
    uint16_t color;
    for (int16_t i=n_rects; i >= 0; i-=10) {
        color = (((i/10)&1)==0) ? color2 : color3;
        uint16_t j = i >> 1;
        LCD_GFX_drawRect(center_x - j, center_y - j, i, i, color1);
        LCD_GFX_fillRect(center_x - j + 1, center_y - j + 1, i-1, i-2, color);
    }
}

void LCD_GFX_test_fillScreen() {
    LCD_GFX_fillScreen(BLACK);
	LCD_GFX_fillScreen(RED);
	LCD_GFX_fillScreen(GREEN);
	LCD_GFX_fillScreen(BLUE);
	LCD_GFX_fillScreen(BLACK);
}

void LCD_GFX_test_text() {
    LCD_GFX_fillScreen(BLACK);
    LCD_GFX_setRotation(1);
    char *titulo = "LSE 2024";
    char *nombre = "Jorge";
    char *apellido = "Fernandez Marin";
    char *texto =   "Este es un test de impresion de texto para verificar "
                    "que la pantalla funciona correctamente.\n \n"
                    "Si puedes leer este mensaje, significa que el sistema"
                    "es capaz de mostrar caracteres en la pantalla. :)";
    LCD_GFX_drawString(40, 0, titulo, BLUE, BLUE, 5);
    LCD_GFX_drawString(80, 50, nombre, RED, WHITE, 4);
    LCD_GFX_drawString(60, 100, apellido, MAGENTA, WHITE, 2);
    LCD_GFX_drawString(0, 150, texto, YELLOW, YELLOW, 1);
    LCD_GFX_setRotation(0);
}

void LCD_GFX_test_bitmap() {
    LCD_GFX_fillScreen(BLACK);
    char *text = "Mi cara XD";

    LCD_GFX_drawBitmap(0, 0, foto, LCD_WIDTH, LCD_HEIGHT, WHITE);
    LCD_GFX_drawString(LCD_WIDTH >> 3, 20, text, MAGENTA, MAGENTA, 3);

}

void LCD_GFX_test_rotation() {
    for (uint8_t i = 0; i < 4; i++) {
        LCD_GFX_setRotation(i);
        LCD_GFX_fillScreen(BLACK);
        LCD_GFX_drawString(LCD_WIDTH >> 2, LCD_HEIGHT >> 1, "TEST", RED, WHITE, 3);
        
    }
}

void LCD_GFX_test_shapes() {
    LCD_GFX_test_fillScreen();
    LCD_GFX_test_lines(CYAN);
    LCD_GFX_test_rects(GREEN);
    // LCD_GFX_test_filledRects(RED, BLACK, WHITE);
    LCD_GFX_test_filledCircles(15, MAGENTA);
    LCD_GFX_test_circles(15, WHITE);
}

void LCD_GFX_test_all() {
    LCD_GFX_test_fillScreen();
    LCD_GFX_test_lines(CYAN);
    LCD_GFX_test_rects(GREEN);
    LCD_GFX_test_filledRects(RED, BLACK, WHITE);
    LCD_GFX_test_filledCircles(15, MAGENTA);
    LCD_GFX_test_circles(15, WHITE);
    LCD_GFX_test_bitmap();
    LCD_GFX_test_rotation();
    LCD_GFX_test_text();
}
