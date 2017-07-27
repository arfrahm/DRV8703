# DRV8703
a library for control and programming of TI DRV8703 EVM

To implement this library, make a call to the class with four parameters: In1 pin, In2 pin, nSleep pin, and Mode pin. Our implementation of the library is Hi-Z mode, or the last mode. To change this, alter the line in the library which configure the Mode pin as an input pull-up to 1 or 0 as in the DRV data sheet.
