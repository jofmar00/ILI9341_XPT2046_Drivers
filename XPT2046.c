/**
 * @file        XPT2046.c
 * @brief       Cabeceras de implementación de funciones que interactuan directamente
 *              con el modulo XPT2046.
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
 * @see         XPT2046.h
 */
#include "nrfx_spi.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "XPT2046.h"
#include "LCD_pinout.h"

#define SPI_INSTANCE 0
static const nrfx_spi_t spi = NRFX_SPI_INSTANCE(SPI_INSTANCE);

/**
 * @brief Inicializa el pin de selección de chip (CS) del controlador táctil XPT2046.
 */
static void XPT2046_gpio_init() {
    nrf_gpio_pin_dir_set(TOUCH_CS, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_write(TOUCH_CS, 1);
}

/**
 * @brief Inicializa el periférico SPI para la comunicación con el XPT2046.
 */
static void XPT2046_spi_init() {
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
 * @brief Envía un comando al XPT2046 y lee el valor de 12 bits de su respuesta.
 * 
 * Envía el byte de comando seguido de dos bytes vacíos para recibir la respuesta.
 * 
 * @param cmd Comando a enviar al XPT2046.
 * @return Valor de 12 bits leído del controlador táctil.
 */
static uint16_t XPT2046_readData(uint8_t cmd) {
    // 1 byte de comando y 2 de respuesta
    uint8_t tx_buffer[3] = {cmd, 0x00, 0x00};
    uint8_t rx_buffer[3] = {0};

    nrf_gpio_pin_write(TOUCH_CS, 0);
    nrfx_spi_xfer_desc_t xfer = NRFX_SPI_XFER_TRX(tx_buffer, 3, rx_buffer, 3);
    nrfx_spi_xfer(&spi, &xfer, 0);
    nrf_gpio_pin_write(TOUCH_CS, 1);

    // Devolver solo los 12 bits utiles
    return ((rx_buffer[1] << 8) | rx_buffer[2]) >> 3;
}

/**
 * @brief Realiza múltiples lecturas de un comando del XPT2046 y devuelve el valor promedio.
 * 
 * Lee el valor correspondiente al comando `cmd` varias veces (definido por `SAMPLES`)
 * y devuelve la media aritmética. Esto reduce el ruido y mejora la precisión.
 * 
 * @param cmd Comando a enviar al XPT2046.
 * @return Valor promedio de las lecturas.
 */
#define SAMPLES 5
static uint16_t XPT2046_readFiltered(uint8_t cmd) {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < SAMPLES; i++) {
        sum += XPT2046_readData(cmd);
        nrf_delay_us(100); // Peque�o delay entre lecturas
    }
    return sum / SAMPLES;
}

void XPT2046_readPosition(uint16_t *x, uint16_t *y) {
    *x = XPT2046_readFiltered(XPT2046_CMD_X);
    *y = XPT2046_readFiltered(XPT2046_CMD_Y);
}

uint16_t XPT2046_readPressure() {
    uint16_t z1 = XPT2046_readData(XPT2046_CMD_Z1);
    uint16_t z2 = XPT2046_readData(XPT2046_CMD_Z2);

    if(z1 == 0 || z2 == 0 || z1 >= z2) return 0;  // Resultados invalidos

    return (z1 + 4095 - z2);
}
void XPT2046_init() {
    XPT2046_gpio_init();
    XPT2046_spi_init();
}
