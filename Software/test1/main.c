/*
 * blinky example for ATTiny84A on blinky AVR
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define LED_PORTA 0
#define LED_PORTB 1


// LED pin assignments
const uint8_t led_port_code[] PROGMEM = {
  // these are valid for SMT layout for 2023
  LED_PORTA, 0,
  LED_PORTA, 1,
  LED_PORTA, 2,
  LED_PORTA, 3,
  LED_PORTA, 7,
  LED_PORTB, 0,
  LED_PORTB, 1,
  LED_PORTB, 2
};

#define led_bit(n) (pgm_read_byte(&(led_port_code[((n)<<1)+1])))
#define led_port(n) (pgm_read_byte(&(led_port_code[((n)<<1)])))

static void inline setup_led_ports()
{
  uint8_t i;
  for( i=0; i<8; i++) {
    if( led_port(i) == LED_PORTA)
      DDRA |= _BV(led_bit(i));
    else
      DDRB |= _BV(led_bit(i));
  }
}




// create masks for ports A/B for LEDs specified
// PORT A = low byte
// PORT B = high byte
static uint16_t led_mask( uint8_t leds)
{
  uint16_t v = 0;
  uint8_t i;
  uint8_t b = 1;

  for( i=0; i<8; i++) {
    if( leds & b) {
      if( led_port(i) == LED_PORTA)
	v |= _BV(led_bit(i));
      else
	v |= (_BV(led_bit(i)) << 8);
    }
    b <<= 1;
  }
  return v;
}

// toggle LEDs per mask
static void led_flip( uint8_t flip_mask)
{
  uint16_t v = led_mask( flip_mask);
  PORTA ^= (v & 0xff);
  PORTB ^= ((v>>8) & 0xff);
}

// turn on LEDs per mask
static void led_on( uint8_t on_mask)
{
  uint16_t v = led_mask( on_mask);
  PORTA |= (v & 0xff);
  PORTB |= ((v>>8) & 0xff);
}

// turn off LEDs per mask
static void led_off( uint8_t off_mask)
{
  uint16_t v = led_mask( off_mask);
  PORTA &= ~(v & 0xff);
  PORTB &= ~((v>>8) & 0xff);
}

// set LEDs per mask
static void led_set( uint8_t set_mask)
{
  led_off( 0xff);
  led_on( set_mask);
}


int main (void)
{
  uint8_t i;

  setup_led_ports();

  while( 1) {
    for( i=0; i<8; i++) {
      uint8_t m = (1<<i);
      led_on( m);
      _delay_ms(250);
      led_off(m);
    }      
  }
}


