/**
 * @file        ILI9341.c
 * @brief       Implementacion de las funciones que interactuan directamente con el modulo
 *              ILI9341.
 * 
 * @author      Jorge Fernández Marín
 * @date        Abril de 2025
 * 
 * @details     Este archivo contiene la implementación de funciones del modulo ILI9341.
 *              Incluye funciones para inicialización, dibujo de píxeles, rotación de pantalla
 *              y llenado de color.
 * 
 * @note        Este archivo fue creado como parte del proyecto "Diseño de shield PCDB para
 *              un nRF52840DK" para la asignatura Laboratorio de sistemas empotrados 2025, 
 *              perteneciente al plan de estudios del itinerario Ingeniería Informática en Unizar.
 * @see         ILI9341.h
 */
#include <stdlib.h>
#include <string.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "ILI9341.h"
#include "nrfx_spi.h"
#include "LCD_pinout.h"


uint8_t gpio_out[3] = {LCD_RESET, LCD_CS, LCD_DC};

#define SPI_INSTANCE 0	// TODO CREO QUE HAY PONER EL 3
static const nrfx_spi_t spi = NRFX_SPI_INSTANCE(SPI_INSTANCE);

/**
 * @brief Inicializa los pines GPIO necesarios para controlar el ILI9341.
 */
static void ILI9341_gpio_init(void) {
    // Configurar pines de control
    for(uint8_t i = 0; i < 3; i++) {
        nrf_gpio_pin_dir_set(gpio_out[i], NRF_GPIO_PIN_DIR_OUTPUT);
        nrf_gpio_pin_write(gpio_out[i], 1);
    }
    
    // CS inicialmente alto (deseleccionado)
    nrf_gpio_pin_write(LCD_CS, 1);
}

/**
 * @brief Inicializa la interfaz SPI para la comunicación con el ILI9341.
 */
static void ILI9341_spi_init(void) {
    nrfx_spi_config_t spi_config = NRFX_SPI_DEFAULT_CONFIG;
    spi_config.sck_pin  = SPI_SCK_PIN;
    spi_config.mosi_pin = SPI_MOSI_PIN;
    spi_config.miso_pin = SPI_MISO_PIN;
    spi_config.ss_pin   = NRFX_SPI_PIN_NOT_USED;
    spi_config.frequency = NRF_SPI_FREQ_4M;
    spi_config.mode = NRF_SPI_MODE_0;
    spi_config.bit_order = NRF_SPI_BIT_ORDER_MSB_FIRST;
    
    nrfx_spi_init(&spi, &spi_config, NULL, NULL);
}

/**
 * @brief Envía un comando al controlador ILI9341 por SPI.
 * 
 * @param cmd Código del comando a enviar.
 */
static void ILI9341_writeCommand(uint8_t cmd) {
    nrf_gpio_pin_write(LCD_DC, 0);	// Command mode
    nrf_gpio_pin_write(LCD_CS, 0);
    
    nrfx_spi_xfer_desc_t xfer = NRFX_SPI_XFER_TX(&cmd, 1);
    nrfx_spi_xfer(&spi, &xfer, 0);
    
    nrf_gpio_pin_write(LCD_CS, 1); 
}

/**
 * @brief Envía un byte de datos al controlador ILI9341 por SPI.
 * 
 * @param data Byte de datos a enviar.
 */
static void ILI9341_writeData(uint8_t data) {
    nrf_gpio_pin_write(LCD_DC, 1); // Data mode
    nrf_gpio_pin_write(LCD_CS, 0);
    
    nrfx_spi_xfer_desc_t xfer = NRFX_SPI_XFER_TX(&data, 1);
    nrfx_spi_xfer(&spi, &xfer, 0);
    
    nrf_gpio_pin_write(LCD_CS, 1); 
}

/**
 * @brief Envía dos bytes (16 bits) de datos al controlador ILI9341 por SPI.
 * 
 * @param data Palabra de 16 bits a enviar.
 */
static void ILI9341_writeData16(uint16_t data) {
    nrf_gpio_pin_write(LCD_DC, 1);
    nrf_gpio_pin_write(LCD_CS, 0);
    
    uint8_t buffer[2] = {data >> 8, data & 0xFF};
    nrfx_spi_xfer_desc_t xfer = NRFX_SPI_XFER_TX(buffer, 2);
    nrfx_spi_xfer(&spi, &xfer, 0);
    
    nrf_gpio_pin_write(LCD_CS, 1);
}

/**
 * @brief Escribe un valor de 8 bits en un registro del ILI9341.
 * 
 * @param addr Dirección del registro.
 * @param data Valor de 8 bits a escribir.
 */
static void ILI9341_writeRegister8(uint8_t addr, uint8_t data) {
    ILI9341_writeCommand(addr);
    ILI9341_writeData(data);
}

/**
 * @brief Escribe un valor de 16 bits en un registro del ILI9341.
 * 
 * @param addr Dirección del registro.
 * @param data Valor de 16 bits a escribir.
 */
static void ILI9341_writeRegister16(uint8_t addr, uint16_t data) {
    ILI9341_writeCommand(addr);
    ILI9341_writeData16(data);
}

/**
 * @brief Escribe un valor de 32 bits en un registro del ILI9341.
 * 
 * @param addr Dirección del registro.
 * @param data Valor de 32 bits a escribir.
 */
static void ILI9341_writeRegister32(uint8_t addr, uint32_t data) {
    ILI9341_writeCommand(addr);
    ILI9341_writeData(data >> 24);
    ILI9341_writeData(data >> 16);
    ILI9341_writeData(data >> 8);
    ILI9341_writeData(data);
}

/**
 * @brief Establece una ventana de direcciones para el área de dibujo.
 * 
 * @param x1 Coordenada X inicial.
 * @param y1 Coordenada Y inicial.
 * @param x2 Coordenada X final.
 * @param y2 Coordenada Y final.
 */
static void ILI9341_setAddrWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	uint32_t t;

	t = x1 << 16 | x2;
    ILI9341_writeRegister32(ILI9341_COLADDRSET, t);
    t = y1 << 16 | y2;
    ILI9341_writeRegister32(ILI9341_PAGEADDRSET, t);
}

/**
 * @brief Llena un área de la pantalla con un color especificado.
 * 
 * @param color Color de relleno (16 bits).
 * @param len Número de píxeles a rellenar.
 */
static void ILI9341_flood(uint16_t color, uint32_t len) {
    ILI9341_writeCommand(ILI9341_MEMORYWRITE);
    
    nrf_gpio_pin_write(LCD_DC, 1);
    nrf_gpio_pin_write(LCD_CS, 0);
    
    uint8_t msb = color >> 8;
    uint8_t lsb = color & 0xFF;
    
    uint8_t buffer[64];
    for (int i = 0; i < 32; i++) {
        buffer[2*i] = msb;
        buffer[2*i+1] = lsb;
    }
    
    // Enviar datos en bloques
    while (len >= 32) {
        nrfx_spi_xfer_desc_t xfer = NRFX_SPI_XFER_TX(buffer, 64);
        nrfx_spi_xfer(&spi, &xfer, 0);
        len -= 32;
    }
    
    // Enviar los datos restantes
    if (len > 0) {
        nrfx_spi_xfer_desc_t xfer = NRFX_SPI_XFER_TX(buffer, 2*len);
        nrfx_spi_xfer(&spi, &xfer, 0);
    }
    
    nrf_gpio_pin_write(LCD_CS, 1);
}

/**
 * @brief Realiza un reinicio por software del controlador ILI9341.
 */
static void ILI9341_reset(void) {
    nrf_gpio_pin_write(LCD_RESET, 0);
    nrf_delay_ms(10);
    nrf_gpio_pin_write(LCD_RESET, 1);
    nrf_delay_ms(120);
}

void ILI9341_init(void) {
    ILI9341_spi_init();
    ILI9341_gpio_init();
    ILI9341_reset();

    rotation_direction = 0;
    ILI9341_writeCommand(ILI9341_SOFTRESET);
    nrf_delay_ms(150);
    
    ILI9341_writeCommand(ILI9341_DISPLAYOFF);
    
    ILI9341_writeRegister8(ILI9341_POWERCONTROL1, 0x23);
    ILI9341_writeRegister8(ILI9341_POWERCONTROL2, 0x10);
    ILI9341_writeRegister16(ILI9341_VCOMCONTROL1, 0x2B2B);
    ILI9341_writeRegister8(ILI9341_VCOMCONTROL2, 0xC0);
    ILI9341_writeRegister8(ILI9341_MADCTL, ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
    ILI9341_writeRegister8(ILI9341_PIXELFORMAT, 0x55);
    ILI9341_writeRegister16(ILI9341_FRAMECONTROL, 0x001B);
    
    ILI9341_writeRegister8(ILI9341_ENTRYMODE, 0x07);
    
    ILI9341_writeCommand(ILI9341_SLEEPOUT);
    nrf_delay_ms(150);
    
    ILI9341_writeCommand(ILI9341_DISPLAYON);
    nrf_delay_ms(500);
    
    ILI9341_setAddrWindow(0, 0, TFTWIDTH - 1, TFTHEIGHT - 1);
}


void ILI9341_drawPixel(int16_t x, int16_t y, uint16_t color) {
	if(x < 0 || y < 0 || x >= TFTWIDTH || y >= TFTHEIGHT) return;

    ILI9341_setAddrWindow(x, y, x, y);
	ILI9341_writeRegister16(ILI9341_MEMORYWRITE, color);
}

void ILI9341_setRotation(uint8_t dir) {
	uint8_t val;
	rotation_direction = dir;
	switch(dir) {
		case 1: //90 degree rotation
			val = ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR;
			break;
		case 2: //180 degree rotation
			val = ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR;
			break;
		case 3: //270 degree rotation
			val = ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR;
			break;
		default: //0 degree rotation, 240x320
			val = ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR;
	}
	ILI9341_writeRegister8(ILI9341_MADCTL, val);
    ILI9341_setAddrWindow(0, 0, TFTWIDTH - 1, TFTHEIGHT - 1);
}

void ILI9341_fillScreen(uint16_t color) {	
	ILI9341_setAddrWindow(0, 0, TFTWIDTH - 1, TFTHEIGHT - 1);
	ILI9341_flood(color, TFTWIDTH * TFTHEIGHT);
}
