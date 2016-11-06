#Serial-Log

This is a program for logging data from the terminal to `stdout`. 
It's primary purpose is for use with microprocessors where debug info is printed to the serial port.
Microprocessors frequently use the serial port only for output, making interactive functionality superfluous. This
application aims to provide easy access to logging from a serial port to a terminal with the least possible hassle.

#Usage 

The program has the following parameters:

* **Serial Port**: the serial port to log from.
* **Baud**: the baud rate to set the serial port to (default 115200).

these settings can be set as positional arguments, or through the use of flags.

as positional arguments, the program is invoked as follows

    $ serial-log /dev/ttyUSB0 115200

the arguments can also be invoked as flags:

    $ serial-log --port /dev/ttyUSB0 --baud 9600

# Platforms

So far the program has only been tested on `OSX`, but it should work on `Linux` as well.
Windows support is not planned at this time.


