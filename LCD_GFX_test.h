/**
 * @file        LCD_GFX_test.h
 * @brief       Cabeceras para las funciones de pruebas gráficas que utilizan el módulo
 *              LCD_GFX.
 * 
 * @author      Jorge Fernández Marín
 * @date        Abril de 2025
 * 
 * @details     Este archivo contiene las declaraciones de funciones de pruebas gráficas
 *              de dibujado de circulos, lineas, rectangulos, bitmaps, llenado de pantalla
 *              y escritura de texto.
 * 
 * @note        Este archivo fue creado como parte del proyecto "Diseño de shield PCDB para
 *              un nRF52840DK" para la asignatura Laboratorio de sistemas empotrados 2025, 
 *              perteneciente al plan de estudios del itinerario Ingeniería Informática en Unizar.
 * @see         LCD_GFX_test.c, LCD_GFX.h
 */

#ifndef LCD_GFX_TEST_H
#define LCD_GFX_TEST_H

#include <stdint.h>
#include "ILI9341.h"

/**
 * @brief Dibuja multiples contornos de circulos hasta llenar la pantalla LCD.
 * 
 * @param radius Radio en pixeles de cada circulo
 * @param color Color del contorno del círculo.
 */
void LCD_GFX_test_circles(uint8_t radius, uint16_t color);

/**
 * @brief Dibuja multiples circulos rellenos hasta llenar la pantalla LCD.
 * 
 * @param radius Radio en pixeles de cada circulo
 * @param color Color del contorno del círculo.
 */
void LCD_GFX_test_filledCircles(uint8_t radius, uint16_t color);

/**
 * @brief Dibuja lineas desde la esquina superior derecha hasta llenar toda la
 *  pantalla LCD.
 * 
 * @param color Color de la línea.
 */
void LCD_GFX_test_lines(uint16_t color);

/**
 * @brief Dibuja contornos de rectangulos progresivamente más grandes
 * desde el centro hasta llenar toda la pantalla LCD.
 * 
 * @param color Color del contorno del rectangulo.
 */
void LCD_GFX_test_rects(uint16_t color);

/**
 * @brief Dibuja rectangulos rellenos progresivamente más grandes
 * desde el centro hasta llenar toda la pantalla LCD.
 * 
 * @param color1 Color del contorno del rectangulo.
 * @param color2 Color de rellemo del rectangulo
 */
void LCD_GFX_test_filledRects(uint16_t color1, uint16_t color2, uint16_t color3);

/**
 * @brief Alterna entre el color de fondo de la pantalla LCD.
 */
void LCD_GFX_test_fillScreen(void);

/**
 * @brief Escribe un texto de ejemplo en la pantalla LCD. 
 */
void LCD_GFX_test_text(void);

/**
 * @brief Dibuja en pantalla una imagen del creador de este módulo. 
 */
void LCD_GFX_test_bitmap(void);

/**
 * @brief Prueba la funcion de rotacion de la pantalla.
 */
void LCD_GFX_test_rotation(void);

/**
 * @brief Ejecuta todos los test que generan formas secuencialmente. 
 */
void LCD_GFX_test_shapes(void);

/**
 * @brief Ejecuta todos los test de LCD_GFX_test secuencialmente. 
 */
void LCD_GFX_test_all(void);

#endif
