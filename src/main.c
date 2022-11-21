#include "lcd.h"
#include "uart.h"
#include <avr/sleep.h>

int main(void) {
  // set_sleep_mode(SLEEP_MODE_IDLE);
  lcdBegin();
  
  uart_init();

  lcdPrintln("Character Display 40x2");
  for(;;){
    if (uart_available()) {
      lcdPrint(uart_read());
    }
  }
}