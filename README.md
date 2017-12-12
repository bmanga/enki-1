# Enki (QT5)

a fast 2D robot simulator, with QT5 build system. This is a hacked
version of the original enki simulator which uses QT5's qmake command
and not cmake.

© 1999-2017 Stéphane Magnenat and others ([full list](AUTHORS))

© 2017 Bernd Porr <mail@berndporr.me.uk>

## License

[GPL 2.0](LICENSE).

## Source distribution

This section explains how to compile Enki from the source distribution.

### Prerequisites

To compile Enki and programs who depend on it, you need:
* a working and fairly recent C++ compiler
* QT5

### Enki simulator compilation under Unix (library)

Change into the enki subdirectory and type:

	qmake

and then build Enki by running:

	make

and finally install the library with
	
	sudo make install


### Compiling/running the examples

To compile the examples you need to do again `qmake` and `make`. This uses the
previously compiled enki library.

To run it type `./playground`

### Use

Check out `playground.pro` in the examples to see how to create your own project.
