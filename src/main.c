#include "lcd.h"
#include "uart.h"

int main(void) {
  lcdBegin(16, 2);
  
  uart_init();

  lcdPrintln("Character Display 40x2");
  for(;;){
    if (uart_available()) {
      lcdPrint(uart_read());
    }
  }
}
