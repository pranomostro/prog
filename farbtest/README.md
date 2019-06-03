Compare farbfeld and png/jpg by size
====================================

In this repository you find 2 utilities, star2ff and ffstats, which
let you convert images to farbfeld and then compare the size of the
compressed farbfeld image with the original image.

Usage
-----

	./star2ff cpm files

star2ff converts files to compressed farbfeld. The first argument of
star2ff is the compression program that will be used. files is the list
of source images (which can be either png or jpg).

	./ffstats cpm files

ffstats prints the ratio of the compressed farbfeld file and the
original file. cpm is again the used compression method (for the file
extensions), files are the original non-farbfeld images. ffstats prints
the original filename and the ratio farbfeldsize/originalsize. Lower
values mean farbfeld scored better, values smaller than 1 mean compressed
farbfeld even beat the original format.

Requirements
------------

* [farbfeld](http://tools.suckless.org/farbfeld)
* rc, the plan9 shell (included in [9base](http://tools.suckless.org/9base))
* bzip2/gzip
* some standard unix utilities everybody has

Thanks
------

Of course, thanks to the suckless guys for farbfeld and its implementation.

License
=======

The [MIT license](./LICENSE).
