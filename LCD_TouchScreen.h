/**
 * @file        LCD_TouchScreen.h
 * @brief       Cabeceras para el módulo de abstraccion que interactua con el tactil del LCD.
 * 
 * @author      Jorge Fernández Marín
 * @date        Abril de 2025
 * 
 * @details     El módulo depende de una implementación a un nivel inferior, en este caso
 *              al módulo XPT2046 que es el que se comunica a nivel hardware con la pantalla.
 * 
 * @note        Este archivo fue creado como parte del proyecto "Diseño de shield PCDB para
 *              un nRF52840DK" para la asignatura Laboratorio de sistemas empotrados 2025, 
 *              perteneciente al plan de estudios del itinerario Ingeniería Informática en Unizar.
 * @see         LCD_TouchScreen.c, XPT2046.h
 */

#ifndef LCD_TOUCHSCREEN_H
#define LCD_TOUCHSCREEN_H

#include <stdint.h>
#include <stdbool.h>

// Calibracion de la pantalla
#define MIN_X 225
#define MIN_Y 300
#define MAX_X 3800
#define MAX_Y 3700

/**
 * @brief Lee y procesa la posición de donde está siendo tocada la pantalla
 * @param x Puntero a la variable donde se almacenará X (en píxeles, rango [0, LCD_WIDTH - 1])
 * @param y Puntero a la variable donde se almacenará Y (en píxeles, rango [0, LCD_HEIGHT - 1])
 */
void LCD_TouchScreen_readPosition(uint16_t *x, uint16_t *y);

/**
 * @brief Mide la presión del toque actual.
 * @return Valor de presión, rango [0-4095].
 */
uint16_t LCD_TouchScreen_readPressure(void);

/**
 * @brief Detecta presencia de toque en el panel.
 * @return true si se detecta toque válido (presión > umbral mínimo), false en caso contrario.
 */
bool LCD_TouchScreen_isTouched(void);

/**
 * @brief Inicializa el táctil.
 */
void LCD_TouchScreen_init(void);

#endif
