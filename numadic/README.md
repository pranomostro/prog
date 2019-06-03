About
=====

Separates an image into subimages from a background. The background is
defined by the pixel in the left upper corner.


The subimages are written into the folder 'subimages' and have random
names. The files are saved in the png format.

Compilation
-----------

Type `make` to build separate.

Requirements
------------

* A POSIX system (POSIX 2001)
* A standard C99 compiler
* GNU make

Acknowledgements
----------------

Thanks to the [stb project](https://github.com/nothings/stb)
for providing small and simple libraries for reading and writing
image files.

License
=======

MIT/X11 license, see [LICENSE](./LICENSE).
