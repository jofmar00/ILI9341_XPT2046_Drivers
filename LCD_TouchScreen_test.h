/**
 * @file        LCD_TouchScreen_test.h
 * @brief       Cabeceras para las funciones de pruebas gráficas que utilizan el módulo
 *              LCD_TouchScreen.
 * 
 * @author      Jorge Fernández Marín
 * @date        Abril de 2025
 * 
 * @details     Este archivo contiene las declaraciones de funciones de pruebas del módulo
 *              tactil, incluyendo test de detección de presión y pintado en pantalla.
 * 
 * @note        Este archivo fue creado como parte del proyecto "Diseño de shield PCDB para
 *              un nRF52840DK" para la asignatura Laboratorio de sistemas empotrados 2025, 
 *              perteneciente al plan de estudios del itinerario Ingeniería Informática en Unizar.
 * @see         LCD_TouchScreen_test.c, LCD_TouchScreen.h
 */

#ifndef LCD_TOUCHSCREEN_TEST_H
#define LCD_TOUCHSCREEN_TEST_H

/**
 * @brief Muestra una pantalla roja si no detecta una pulsacion en 
 * la pantalla y de otra forma muestra una pantalla verde.
 */
void LCD_TouchScreen_test_pressure(void);

/**
 * @brief Muestra una pantalla cyan en la que se puede pintar con el lapiz táctil.
 */
void LCD_TouchScreen_test_paint(void);

/**
 * @brief Test para hayar los valores de calibracion de la pantalla
 */
void LCD_TouchScreen_test_calibrate(void);
#endif
