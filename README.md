# Enki

a fast 2D robot simulator

© 1999-2017 Stéphane Magnenat and others ([full list](AUTHORS))

Hacked for QT5 by Bernd Porr

## License

[GPL 2.0](LICENSE).

## Source distribution

This section explains how to compile Enki from the source distribution.

### Prerequisites

To compile Enki and programs who depend on it, you need:
* a working and fairly recent c++ compiler
* [CMake](https://cmake.org/)
* A build environment compatible with CMake.

In addition, if you want the support for the viewer and Python bindings, you need:
* QT5
* [Python](https://www.python.org/) with development support
* [Boost.Python](http://www.boost.org/doc/libs/1_65_1/libs/python/doc/html/)

### Compilation under Unix

Those short instructions assume that you want to use "make" to build Enki.
If you want to use another build environment, such as Microsoft Visual Studio, please refer to [cmake documentation](https://cmake.org/documentation/).
Once you have downloaded and extracted the source distribution, you can create the Makefiles by running:

	cmake .

and then build Enki by running:

	make

You can also change the build options by running:

	ccmake .

or

	cmake-gui .

prior to cmake.

In order to compile the viewer you need to go to the subdir "viewer" and
do `qmake`, `make` and `sudo make install`.

To run the demo "playground" you need to do again `qmake` and `make`.

### Use

Check out the .pro file in playground to see how to link against the libraries.

## Documentation

HTML documentation (including examples and cookbooks) can be generated by the
`doc` target of the build system.  Doxygen tool can be downloaded from
http://www.doxygen.org/
