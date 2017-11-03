#!/bin/sh

${CPPCHECK_HOME}cppcheck --enable=all src/* -itest/* -isrc/MathParser/test -ibuild > /tmp/cppckeck_std.out 2> /tmp/cppckeck_err.out

cat /tmp/cppckeck_err.out 

err=`cat /tmp/cppckeck_err.out | grep -E "(error)|(warning)"`

if [ "$err" != "" ]; then
    echo "-------------------------------------------"
    echo "Code check errors:"
    echo $err
    exit 1
fi

exit 0