# Serial Character Display

This document describes my hardware test target

## Parts

| Ref   |   Partno.  | Manuf. | Description |
| --- | --- | --- | --- |
|  A1   | [DMC40202A](https://www.alldatasheet.com/datasheet-pdf/pdf/100923/OPTREX/DMC40202.html) | Optrex  |  Character Display Assembly |
|  U1   | [ATmega8](https://www.alldatasheet.com/datasheet-pdf/pdf/80247/ATMEL/ATMEGA8.html)   |  Microchip |  8-bit Atmel with 8KBytes InSystem Programmable Flash DIP 28 THT|
|  P1   | - | - | Female Header Straight 2x7 Pin THT |
|  P2   | - | - | Male Header Angled 2 Pin THT |
|  P3   | - | - | Male Header Angled 8 Pin THT |
|  P4   | - | - | Male Header Angled 4 Pin THT |
|  R1   | - | - | Precision Multi-Turn Potentiometer 25 kOhm THT|
|  R2   | - | - | Axial Leaded Resistor Metal Film xx Ohm THT |


## Wiring

The LCD voltage V_LCD is generated using a potentiometer voltage divider circuit. Changing the voltage sets the contrast of the LCD. I found that 0.4 V works best for my display, but your results may vary.
```
    +5V
     |
 R2  []<--- V_LCD
     |
    GND
```

U1 Wiring to Display I/O Interface (P1 / A1)

| U1 Pin | Signal Name | Description |
| --- | --- | --- |
| 4 (PD2) | RS | Register Select |
| 5 (PD3) | E | Enable |
| 6 (PD4) | D4 | Data-bus bit 4  |
| 11 (PD5) | D5 |  Data-bus bit 5 |
| 12 (PD6) | D6 | Data-bus bit 6 |
| 13 (PD7) | D7 | Data-bus bit 7 |