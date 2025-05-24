/**
 * @file        XPT2046.h
 * @brief       Cabeceras para las funciones que interactuan directamente con el modulo
 *              XPT2046.
 * 
 * @author      Jorge Fernández Marín
 * @date        Abril de 2025
 * 
 * @details     Este archivo contiene las declaraciones de funciones del modulo XPT2046.
 *              Incluye funciones para inicialización, lectura de presión en la pantalla
 *              y lectura de la posición en la que se está ocando el táctil.
 * 
 * @note        Este archivo fue creado como parte del proyecto "Diseño de shield PCDB para
 *              un nRF52840DK" para la asignatura Laboratorio de sistemas empotrados 2025, 
 *              perteneciente al plan de estudios del itinerario Ingeniería Informática en Unizar.
 * @see         XPT2046.c
 */

#ifndef XPT2046_h
#define XPT2046_h

#include <stdint.h>

#define XPT2046_CMD_X  0xD0 // X
#define XPT2046_CMD_Y  0x90  // Y

#define XPT2046_CMD_Z1 0xB0  // Z1
#define XPT2046_CMD_Z2 0xC0  // Z2

/**
 * @brief Inicializa el controlador del XPT2046
 * @note Esta funcion debe ser llamada antes de cualquier otra de este módulo.
 */
void XPT2046_init(void);

/**
 * @brief Lee y procesa, aplicando un algoritmo de anti-aliasing de 3 muestras, la posición de donde está siendo tocada la pantalla
 * @param x Puntero a la variable donde se almacenará X (valor en crudo, rango [0, 4095])
 * @param y Puntero a la variable donde se almacenará Y (valor en crudo, rango [0, 4095])
 */
void XPT2046_readPosition(uint16_t *x, uint16_t *y);

/**
 * @brief Mide la presión del toque actual.
 * @return Valor de presión, rango [0-4095].
 */
uint16_t XPT2046_readPressure(void);


#endif
