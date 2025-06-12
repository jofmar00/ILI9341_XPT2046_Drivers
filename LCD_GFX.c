/**
 * @file        LCD_GFX.c
 * @brief       Implementacion del módulo gráfico que interactua con el display LCD.
 * 
 * @author      Jorge Fernández Marín
 * @date        Abril de 2025
 * 
 * @details     Este archivo contiene la implementación de funciones gráficas de dibujado 
 *              de circulos, lineas, rectangulos, bitmaps, llenado de pantalla
 *              y escritura de texto.
 * 
 *              El módulo depende de una implementación a un nivel inferior, en este caso
 *              al módulo ILI9341 que es el que se comunica a nivel hardware con la pantalla.
 * 
 * @note        Este archivo fue creado como parte del proyecto "Diseño de shield PCDB para
 *              un nRF52840DK" para la asignatura Laboratorio de sistemas empotrados 2025, 
 *              perteneciente al plan de estudios del itinerario Ingeniería Informática en Unizar.
 * @see         LCD_GFX.h, ILI9341.c
 */
#include <stdlib.h>
#include <string.h>
#include "LCD_GFX.h"
#include "ILI9341.h"
#include "bitmaps.h"

#define pgm_read_byte(addr) (*(const unsigned char *)(addr))


void LCD_GFX_init() {
    ILI9341_init();
    rotation_direction_GFX = 0;
}

// ------------------------
// Utils, unicos módulos que usan ILI9341.h
// -----------------------
void LCD_GFX_fillScreen(uint16_t color) {
    ILI9341_fillScreen(color);
}

void LCD_GFX_drawPixel(int16_t x, int16_t y, uint16_t color) {
    ILI9341_drawPixel(x, y, color);
}

void LCD_GFX_setRotation(uint8_t dir) {
    ILI9341_setRotation(dir);
    rotation_direction_GFX = dir;
}

void LCD_GFX_drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
    ILI9341_setRotation(0);
    int16_t byteWidth = (w+7)/8;
    for (uint16_t j=0; j < h; j++) {
        for (uint16_t i=0; i < w; i++){
            unsigned char byte = pgm_read_byte(bitmap + j * byteWidth + i / 8);
            if (byte & (0x80 >> (i & 0x07))) {
                LCD_GFX_drawPixel(x+i, y+j, color);
            }
        }
    }
}

// ------------------
// Circulos
// ------------------
void LCD_GFX_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;
  
    LCD_GFX_drawPixel(x0, y0+r, color);
    LCD_GFX_drawPixel(x0, y0-r, color);
    LCD_GFX_drawPixel(x0+r, y0, color);
    LCD_GFX_drawPixel(x0-r, y0, color);
  
    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
  
        LCD_GFX_drawPixel(x0 + x, y0 + y, color);
        LCD_GFX_drawPixel(x0 - x, y0 + y, color);
        LCD_GFX_drawPixel(x0 + x, y0 - y, color);
        LCD_GFX_drawPixel(x0 - x, y0 - y, color);
        LCD_GFX_drawPixel(x0 + y, y0 + x, color);
        LCD_GFX_drawPixel(x0 - y, y0 + x, color);
        LCD_GFX_drawPixel(x0 + y, y0 - x, color);
        LCD_GFX_drawPixel(x0 - y, y0 - x, color);
    }
}
void LCD_GFX_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    LCD_GFX_drawLine(x0, y0 - r, x0, y0 + r, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;

        // Simetría en los 4 "sectores verticales" del círculo
        LCD_GFX_drawLine(x0 + x, y0 - y, x0 + x, y0 + y, color);
        LCD_GFX_drawLine(x0 - x, y0 - y, x0 - x, y0 + y, color);
        LCD_GFX_drawLine(x0 + y, y0 - x, x0 + y, y0 + x, color); 
        LCD_GFX_drawLine(x0 - y, y0 - x, x0 - y, y0 + x, color); 
    }
}

// ------------------
// Lineas
// ------------------
void LCD_GFX_drawHLine(int16_t x0, int16_t y0, int16_t line_size, uint16_t color) {
    for (int16_t x = x0; x <= x0 + line_size; x++) {
        LCD_GFX_drawPixel(x, y0, color);
    }
}

void LCD_GFX_drawVLine(int16_t x0, int16_t y0, int16_t line_size, uint16_t color) {
    for (int16_t y = y0; y <= y0 + line_size; y++) {
        LCD_GFX_drawPixel(x0, y, color);
    }
}
void LCD_GFX_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    }
    else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            LCD_GFX_drawPixel(y0, x0, color);
        }
        else {
            LCD_GFX_drawPixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

// ------------------
// Rectangulos
// ------------------
void LCD_GFX_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    LCD_GFX_drawHLine(x, y, w, color);      // (x,y) -> (x+w,y)
    LCD_GFX_drawHLine(x, y+h, w, color);  // (x,y+h) -> (x+w,y+h)

    LCD_GFX_drawVLine(x, y, h, color);      // (x,y) -> (x,y+h)
    LCD_GFX_drawVLine(x+w, y, h, color);   // (x+w,y) -> (x+w,y+h)
}

void LCD_GFX_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    for (int16_t i=x; i<x+w; i++) {
        LCD_GFX_drawVLine(i, y, h,color);
    }
}

// ------------------
// Texto
// ------------------
void LCD_GFX_drawChar(int16_t x, int16_t y, char c, uint16_t color, uint16_t bg, uint8_t size) {
    if  ((x >= LCD_WIDTH)        || // Clip right
        (y >= LCD_HEIGHT)        || // Clip bottom
        ((x + 5 * size - 1) < 0) || // Clip left
        ((y + 8 * size - 1) < 0))   // Clip top
   return;

   // Bucle sobre las columnas de pixeles del caracter
   for (uint8_t i=0; i < 6; i++) {
        uint8_t line;
        if (i == 5) {
            line = 0x0;
        }
        else {
            line = pgm_read_byte(font+(c*5)+i);
        }
        // Bucle sobre los pixeles de cada columna
        for (uint8_t j=0; j < 8; j++) {
            if (line & 0x1) {   
                if (size == 1) {    // Tamaño normal
                    LCD_GFX_drawPixel(x+i, y+j, color);
                }
                else {  // Tamaño aumentado
                    LCD_GFX_fillRect(x+(i*size), y+(j*size), size, size, color);
                }
            }
            else if (bg != color){  // Si el fondo es distinto del color de la letra
                if (size == 1) {
                    LCD_GFX_drawPixel(x+i, y+j, bg);
                }
                else {
                    LCD_GFX_fillRect(x+(i*size), y+(j*size), size, size, bg);
                }
            }
            line >>= 1; // Leer siguiente bit
        }
   }
}

void LCD_GFX_drawString(int16_t x, int16_t y, char* c, uint16_t color, uint16_t bg, uint8_t size) {
    uint16_t cursor_x = x;
    uint16_t cursor_y = y;
    for (uint16_t i = 0; i < strlen((const char *)c); i++) {
        if (c[i] == '\n') { // Saltos de linea
            cursor_y += size * 8; 
            cursor_x = 0;
        }
        else if (c[i] == '\r') { // Retorno de carro
            cursor_x = x;
        }
        else { // Catacteres normales
            LCD_GFX_drawChar(cursor_x, cursor_y, c[i], color, bg, size);
            cursor_x += size*6;

            // Si nos salimos de la linea printamos mas abajo
            if (cursor_x > (LCD_WIDTH - size*6)) { 
                cursor_x = x;
                cursor_y += size*8;
            }
        }
    }
}

