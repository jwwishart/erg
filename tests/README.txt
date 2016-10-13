Copyright (c) 2016 Justin William Wishart
Full License is found in the LICENSE.txt file

This folder contains compiler tests.

Each cpp file is complied into a separate executable and will then be run.
The cpp file is expected to:
- have a main method
- include erg.h from its normal location "../erg.h"
- use expect() method to assert test conditions throughout main
    NOTE: expect() is just an alias for assert() and works the same way


All tests can be executed by running the test.sh or test.bat files