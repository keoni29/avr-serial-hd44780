# Serial Character Display

## Parts

| Ref   |   Partno.  | Manuf. | Description |
| --- | --- | --- | --- |
|  A1   | Optrex    |  DCM40202A |  Character Display Assembly |
|  U1   | ATmega8   |  Microchip |  8-bit Atmel with 8KBytes InSystem Programmable Flash DIP 28 THT|
|  P1   | - | - | Female Header Straight 2x7 Pin THT |
|  P2   | - | - | Male Header Angled 2 Pin THT |
|  P3   | - | - | Male Header Angled 8 Pin THT |
|  P4   | - | - | Male Header Angled 4 Pin THT |
|  R1   | - | - | Precision Multi-Turn Potentiometer 25 kOhm THT|
|  R2   | - | - | Axial Leaded Resistor Metal Film xx Ohm THT |


## Wiring

```
    +5V
     |
 R2  R<--- V_LCD
     |
    GND
```

U1 Wiring to Display I/O Interface (P1 / A1)
| Pin | Signal Name | Description |
| --- | --- | --- |
| 4 (PD2) | RS | Register Select |
| 5 (PD3) | E | Enable |
| 6 (PD4) | D4 | Data-bus bit 4  |
| 11 (PD5) | D5 |  Data-bus bit 5 |
| 12 (PD6) | D6 | Data-bus bit 6 |
| 13 (PD7) | D7 | Data-bus bit 7 |