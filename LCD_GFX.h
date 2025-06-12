/**
 * @file        LCD_GFX.h
 * @brief       Cabeceras para el módulo gráfico que interactua con el display LCD.
 * 
 * @author      Jorge Fernández Marín
 * @date        Abril de 2025
 * 
 * @details     Este archivo contiene las declaraciones de funciones gráficas de dibujado 
 *              de circulos, lineas, rectangulos, bitmaps, llenado de pantalla
 *              y escritura de texto.
 * 
 *              El módulo depende de una implementación a un nivel inferior, en este caso
 *              al módulo ILI9341 que es el que se comunica a nivel hardware con la pantalla.
 * 
 * @note        Este archivo fue creado como parte del proyecto "Diseño de shield PCDB para
 *              un nRF52840DK" para la asignatura Laboratorio de sistemas empotrados 2025, 
 *              perteneciente al plan de estudios del itinerario Ingeniería Informática en Unizar.
 * @see         LCD_GFX.c, ILI9341.h
 */

#ifndef LCD_GFX_H
#define LCD_GFX_H

#include <stdint.h>

#define LCD_HEIGHT ((rotation_direction_GFX % 2 == 0) ? 320 : 240)
#define LCD_WIDTH  ((rotation_direction_GFX % 2 == 0) ? 240 : 320)
#define swap(a, b) { int16_t t = a; a = b; b = t; }

// Colores en formato RGB565
#define	BLACK   0x0
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

static int rotation_direction_GFX = 0;
/**
 * @brief Inicializa la pantalla LCD.
 */
void LCD_GFX_init(void);

/**
 * @brief Establece la rotacion de la pantalla. 
 * @param dir Nueva direccion en la que se escriben los datos [0-3]
 */
void LCD_GFX_setRotation(uint8_t dir);

/**
 * @brief Dibuja una imagen en la pantalla a partir de un bitmap.
 * 
 * Esta función dibuja un bitmap de tamaño `w` x `h` en las coordenadas (`x`, `y`) de la pantalla, 
 * utilizando el color especificado. El bitmap debe ser una imagen en formato de bits donde cada bit 
 * representa un píxel.
 * 
 * @param x Coordenada X del punto superior izquierdo donde se dibujará el bitmap.
 * @param y Coordenada Y del punto superior izquierdo donde se dibujará el bitmap.
 * @param bitmap Puntero al array que contiene los datos del bitmap. Los datos del bitmap están 
 *               almacenados de forma comprimida, donde cada byte representa 8 píxeles (de izquierda a derecha).
 * @param w Ancho del bitmap (en píxeles).
 * @param h Alto del bitmap (en píxeles).
 * @param color Color con el que se dibujarán los píxeles del bitmap (utilizando el formato de color de la pantalla).
 */
void LCD_GFX_drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);

/**
 * @brief Dibuja el contorno de un círculo en la pantalla LCD.
 * 
 * @param x0 Coordenada X del centro del círculo.
 * @param y0 Coordenada Y del centro del círculo.
 * @param r Radio del círculo.
 * @param color Color del contorno del círculo.
 */
void LCD_GFX_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

/**
 * @brief Dibuja un círculo sólido (relleno) en la pantalla LCD.
 * 
 * @param x0 Coordenada X del centro del círculo.
 * @param y0 Coordenada Y del centro del círculo.
 * @param r Radio del círculo.
 * @param color Color ocn el que rellenar el círculo.
 */
void LCD_GFX_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

/**
 * @brief Dibuja una línea entre dos puntos en la pantalla LCD.
 * 
 * @param x0 Coordenada X del punto de inicio.
 * @param y0 Coordenada Y del punto de inicio.
 * @param x1 Coordenada X del punto final.
 * @param y1 Coordenada Y del punto final.
 * @param color Color de la línea.
 */
void LCD_GFX_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

/**
 * @brief Dibuja un rectángulo sin relleno en la pantalla LCD.
 * 
 * @param x Coordenada X de la esquina superior izquierda.
 * @param y Coordenada Y de la esquina superior izquierda.
 * @param w Ancho del rectángulo en píxeles.
 * @param h Alto del rectángulo en píxeles.
 * @param color Color del contorno del rectángulo.
 */
void LCD_GFX_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);


/**
 * @brief Dibuja un rectángulo sólido (relleno) en la pantalla LCD.
 * 
 * @param x Coordenada X de la esquina superior izquierda.
 * @param y Coordenada Y de la esquina superior izquierda.
 * @param w Ancho del rectángulo en píxeles.
 * @param h Alto del rectángulo en píxeles.
 * @param color Color de relleno del rectángulo.
 */
void LCD_GFX_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

/**
 * @brief Dibuja una cadena de texto en la pantalla LCD.
 * 
 * @param x Coordenada X donde se iniciará el texto.
 * @param y Coordenada Y donde se iniciará el texto.
 * @param text Puntero a la cadena de caracteres a dibujar.
 * @param color Color del texto.
 * @param bg Color de fondo del texto. Si es el mismo que el color del texto
 *           entonces no se dibujará color de fondo. 
 * @param size Tamaño de la fuente.
 */
void LCD_GFX_drawString(int16_t x, int16_t y, char* c, uint16_t color, uint16_t bg, uint8_t size);

/**
 * @brief Dibuja un píxel en la pantalla LCD.
 * 
 * @param x Coordenada X del píxel.
 * @param y Coordenada Y del píxel.
 * @param color Color del píxel.
 */
void LCD_GFX_drawPixel(int16_t x, int16_t y, uint16_t color);

/**
 * @brief Llena toda la pantalla LCD con un color sólido.
 * 
 * @param color Color con el que se llenará la pantalla.
 */
void LCD_GFX_fillScreen(uint16_t color);


#endif
