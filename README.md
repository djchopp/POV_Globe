#POV_Globe

##Blue Marble Enterprise POV Globe

###Hardware:
**MCU:** TI Tiva C Launchpad

**LED Controllers:** TI blah

###Files and Useful Variables
Filename        | Variables     | Description
-------------   | ------------- | -------------
**main.c**      |               | Main loop file. Inits and then starts loop. KISS
->              | delay         | cycle delay of test loop
**POV_Helper.h**|               | Header file for POV_Helper.c
->              | NUM_MODULES   | The number of LED Modules(set of 4 LEDS) connected in series
->              | NUM_ROWS      | The number columns in the picture
->              | multiplier    | Global Brightness multiplier
**POV_Helper.c**|               | Nothing really to change here. All params in .h file
**SPI_Helper.h**|               | Header file for SPI_Helper.c
->              | SPI_CLOCK     | Clock speed of spi. WARNING, changing this without changing the init may result in                                        failed SPI initialization
**SPI_Helper.c**|               | Nothing really to change here. All params in .h file


