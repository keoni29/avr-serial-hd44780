#include "lcd.h"
#include "uart.h"

int main(void) {
  lcdBegin();
  
  uart_init();

  lcdPrintln("Character Display 40x2");
  for(;;){
    if (uart_available()) {
      lcdPrint(uart_read());
    }
  }
}
