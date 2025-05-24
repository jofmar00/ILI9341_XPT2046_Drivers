/**
 * @file        ILI9341.h
 * @brief       Cabeceras para las funciones que interactuan directamente con el modulo
 *              ILI9341.
 * 
 * @author      Jorge Fernández Marín
 * @date        Abril de 2025
 * 
 * @details     Este archivo contiene las declaraciones de funciones del modulo ILI9341.
 *              Incluye funciones para inicialización, dibujo de píxeles, rotación de pantalla
 *              y llenado de color.
 * 
 * @note        Este archivo fue creado como parte del proyecto "Diseño de shield PCDB para
 *              un nRF52840DK" para la asignatura Laboratorio de sistemas empotrados 2025, 
 *              perteneciente al plan de estudios del itinerario Ingeniería Informática en Unizar.
 * @see         ILI9341.c
 */

#ifndef _ILI9341_H_
#define _ILI9341_H_

#include <stdint.h>

// Dimensiones de la pantalla
#define TFTHEIGHT ((rotation_direction % 2 == 0) ? 320 : 240)
#define TFTWIDTH  ((rotation_direction % 2 == 0) ? 240 : 320)

// Registros del módulo
#define ILI9341_NOOP               0x00
#define ILI9341_SOFTRESET          0x01
#define ILI9341_SLEEPIN            0x10
#define ILI9341_SLEEPOUT           0x11
#define ILI9341_NORMALDISP         0x13
#define ILI9341_INVERTOFF          0x20
#define ILI9341_INVERTON           0x21
#define ILI9341_GAMMASET           0x26
#define ILI9341_DISPLAYOFF         0x28
#define ILI9341_DISPLAYON          0x29
#define ILI9341_COLADDRSET         0x2A
#define ILI9341_PAGEADDRSET        0x2B
#define ILI9341_MEMORYWRITE        0x2C
#define ILI9341_PIXELFORMAT        0x3A
#define ILI9341_FRAMECONTROL       0xB1
#define ILI9341_DISPLAYFUNC        0xB6
#define ILI9341_ENTRYMODE          0xB7
#define ILI9341_POWERCONTROL1      0xC0
#define ILI9341_POWERCONTROL2      0xC1
#define ILI9341_VCOMCONTROL1      0xC5
#define ILI9341_VCOMCONTROL2      0xC7
#define ILI9341_MADCTL  0x36
#define ILI9341_ID4  0xD3

#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04

static int rotation_direction = 0;
/**
 * @brief Inicializa el controlador del ILI9341
 * @note Esta funcion debe ser llamada antes de cualquier otra de este módulo.
 */
void ILI9341_init(void);

/**
 * @brief Dibuja un píxel en la pantalla LCD.
 * 
 * @param x Coordenada X del píxel.
 * @param y Coordenada Y del píxel.
 * @param color Color del píxel.
 */
void ILI9341_drawPixel(int16_t x, int16_t y, uint16_t color);

/**
 * @brief Establece la rotacion de la pantalla cambiando el modo en el que
 * se escribe en el buffer de la pantalla. 
 * @param dir Nueva direccion en la que se escriben los datos [0-3]
 */
void ILI9341_setRotation(uint8_t dir);

/**
 * @brief LLena la pantalla del color pasado por parametro.
 */
void ILI9341_fillScreen(uint16_t color);

#endif
