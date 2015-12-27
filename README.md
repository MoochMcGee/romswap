romswap
=======

Romswap is a ROM image utility that byteswaps your ROMs in whatever fashion
you like, as dictated by a config file.

Syntax
======

./romswap [input] [output]

or

./romswap [config] [input] [output]

Config syntax
=============

[property] = [value];

Here is a list of properties:

mode: Valid values are 16bits, which byteswaps in 16-bit chunks, 32bits,
which byteswaps in 32-bit chunks, and 64bits, which byteswaps in 64-bit
chunks.