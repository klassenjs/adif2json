adif2json
=========

A set of utilities to convert ADIF `.adi` files [1] to and from JSON so that
logfiles can be bulk queried and bulk updated using standard command
line tools like `jq`.

These tools are a minimal implementation and don't do any validation
against valid data types or domain values.  These tools were primarily
developed to work with the ADIF v2.2.7 files as produced by fldigi [2].  I
have only tested this as much as it did what I needed done. If it
doesn't work for you or eats your logs, you are on your own. I advise
you keep backups of any important logs.

License:
--------

This code is provided under a MIT style license. See
the `LICENSE` file in this repo for more information.


Compiling:
----------

`make` should work on recent Linux distributions (assuming the dependencies are installed).

The binaries will be placed in the source directory. There is no
install step, however you can copy the binaries anywhere you'd like
after that.

Dependencies:
  * C++17
  * JSON support is via the nlohmann/json library.


Usage:
------
For examples of usage see the `scripts` file in the repo.


[1] http://www.adif.org/
[2] http://www.w1hkj.com/
