#!/bin/sh
files=$(find src sim -name \*.cpp -o -name \*.hpp -o -name \*.ino)
perl0pie="perl -0 -p -i -e"
$perl0pie "s/ +$//gm" $files
$perl0pie "s/\n{2,}(^\s*})/\n\1/gm" $files
$perl0pie "s/(\s*{$)\n{2,}/\1\n/gm" $files
$perl0pie "s/\n{3,}/\n\n/gm" $files
astyle -A10s2pn $files
