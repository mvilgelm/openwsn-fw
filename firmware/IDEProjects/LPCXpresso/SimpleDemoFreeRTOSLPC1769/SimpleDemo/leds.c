/**
\brief LPC17XX-specific definition of the "leds" bsp module.

\author Xavi Vilajosana <xvilajosana@eecs.berkeley.edu>, February 2012.
*/

#include "stdint.h"
#include "leds.h"
#include "LPC17xx.h"



//=========================== defines =========================================
#define redLED_BIT 						( 22 )
//=========================== variables =======================================

//=========================== prototypes ======================================


static void private_led_on(unsigned int ledbit);
static void private_led_off(unsigned int ledbit);
static void private_led_toggle(unsigned int ledbit);

//=========================== public ==========================================

void leds_init() {
	/* Initialise P0_22 for the LED. Datasheet RevB page 5. */
		LPC_PINCON->PINSEL1	&= ( ~( 3 << 12 ) );//page 104 Pin Connect Block, PINSEL1 is the upper 16 bits of P0 we want to set
												//we want to set to 00 bits 12&13 as we want primary default function of the GPIO port
												// this means that we reset this two bits by & (11001111 11111111)
		LPC_GPIO0->FIODIR |= ( 1 << redLED_BIT );// set the direction register. set direction output (1) to the bid redLED_BIT mapped to the position (22)
}


static void private_led_on(unsigned int ledbit){
	unsigned long ulLEDState;

	ulLEDState = LPC_GPIO0->FIOPIN;//get led state
	LPC_GPIO0->FIOSET = ( ( ~ulLEDState ) & ( 1 << ledbit ) );//turn it on! does nothing if it is already on
}


static void private_led_off(unsigned int ledbit){
	unsigned long ulLEDState;

	ulLEDState = LPC_GPIO0->FIOPIN;	//get led state
	LPC_GPIO0->FIOCLR = ulLEDState & ( 1 << ledbit );//turn it off! does nothing if already off
}

static void private_led_toggle(unsigned int ledbit){
	unsigned long ulLEDState;
	ulLEDState = LPC_GPIO0->FIOPIN;	//get led state
	LPC_GPIO0->FIOCLR = ulLEDState & ( 1 << ledbit );//turn it off! does nothing if already off
	LPC_GPIO0->FIOSET = ( ( ~ulLEDState ) & ( 1 << ledbit ) );//turn it on! does nothing if it is already on
}

void led_error_on() {
	private_led_on(redLED_BIT );
}
void led_error_off() {
   private_led_off(redLED_BIT);
}
void led_error_toggle() {
   private_led_toggle(redLED_BIT);
}
void led_radio_on() {
	private_led_on(redLED_BIT);
}
void led_radio_off() {
	private_led_off(redLED_BIT);
}
void led_radio_toggle() {
	private_led_toggle(redLED_BIT);
}

void led_sync_on() {
	private_led_on(redLED_BIT );
}
void led_sync_off() {
	private_led_off(redLED_BIT);
}
void led_sync_toggle() {
	private_led_toggle(redLED_BIT);
}

void led_all_on() {
	private_led_on(redLED_BIT);
}
void led_all_off() {
	private_led_off(redLED_BIT);
}
void led_all_toggle() {
	private_led_toggle(redLED_BIT);
}

void leds_circular_shift() {
	private_led_toggle(redLED_BIT);
}

void leds_increment() {
	private_led_toggle(redLED_BIT);
}

//=========================== private =========================================