#!/bin/sh
astyle -A10s2pn $(find src sim -name \*.cpp -o -name \*.hpp)
