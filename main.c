/**
 * @file 	main.c
 * @brief 	Programa de ejemplo para mostrar la funcionalidad del controlador 
 * 			gráfico LCD y la pantalla táctil.
 * 
 * 			Módulos utilizados:
 *  			- LCD_GFX: Controlador de gráficos para la pantalla LCD.
 *  			- LCD_TouchScreen: Módulo de control de la pantalla táctil.
 *  			- LCD_GFX_test: Funciones de prueba para los gráficos.
 *  			- LCD_TouchScreen_test: Funciones de prueba para la pantalla táctil.
 *
 * @author Jorge Fernández Marín
 * @date   Abril de 2025
 * 
 * @note   Este archivo fue creado como parte del proyecto "Diseño de shield PCDB para
 *         un nRF52840DK" para la asignatura Laboratorio de sistemas empotrados 2025, 
 *         perteneciente al plan de estudios del itinerario Ingeniería Informática en Unizar.
 */
#include "LCD_GFX.h"
#include "LCD_TouchScreen.h"
#include "LCD_GFX_test.h"
#include "LCD_TouchScreen_test.h"

#include "nrf_gpio.h"

#define BTN_LEFT 11
#define BTN_DOWN 12
#define BTN_RIGHT 24
#define BTN_UP 25

void buttons_init() {
	nrf_gpio_cfg_input(BTN_UP, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BTN_LEFT, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BTN_DOWN, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BTN_RIGHT, NRF_GPIO_PIN_PULLUP);
}
int main(void)
{
  	// Inicializar los módulos
	LCD_GFX_init();
	LCD_TouchScreen_init();
	buttons_init();
	
   	// Start tests.
	LCD_GFX_test_text();
	while(1) {
		if 		(!nrf_gpio_pin_read(BTN_UP))	LCD_GFX_test_shapes();
		else if (!nrf_gpio_pin_read(BTN_LEFT)) 	LCD_TouchScreen_test_paint();
		else if (!nrf_gpio_pin_read(BTN_DOWN)) 	LCD_GFX_test_bitmap();
		else if (!nrf_gpio_pin_read(BTN_RIGHT)) LCD_GFX_test_text();
	}
}
