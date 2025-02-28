#!/bin/bash

PROGRAM=$1
OUTPUT="/tmp/output.txt"

$PROGRAM input1.txt $OUTPUT
if ! cmp output1.txt $OUTPUT ; then
  echo "7 and 6 => 20 failed"
  exit 1;
fi

$PROGRAM input2.txt $OUTPUT
if ! cmp output2.txt $OUTPUT ; then
  echo "10 and 3 => 15 failed"
  exit 1;
fi

$PROGRAM input3.txt $OUTPUT
if ! cmp output3.txt $OUTPUT ; then
  echo "9 and 7 => 27 failed"
  exit 1;
fi

$PROGRAM input4.txt $OUTPUT
if ! cmp output4.txt $OUTPUT ; then
  echo "10 and 7 => 29 failed"
  exit 1;
fi

$PROGRAM input5.txt $OUTPUT
if ! cmp output5.txt $OUTPUT ; then
  echo "13 and 10 => 44 failed"
  exit 1;
fi

$PROGRAM input6.txt $OUTPUT
if ! cmp output6.txt $OUTPUT ; then
  echo "50 and 49 => 286 failed"
  exit 1;
fi

$PROGRAM input7.txt $OUTPUT
if ! cmp output7.txt $OUTPUT ; then
  echo "100 and 70 => 524 failed"
  exit 1;
fi

$PROGRAM input8.txt $OUTPUT
if ! cmp output8.txt $OUTPUT ; then
  echo "100 and 98 => 670 failed"
  exit 1;
fi

$PROGRAM input9.txt $OUTPUT
if ! cmp output9.txt $OUTPUT ; then
  echo "300 and 99 => 964 failed"
  exit 1;
fi

$PROGRAM input10.txt $OUTPUT
if ! cmp output10.txt $OUTPUT ; then
  echo "400 and 390 => 3454 failed"
  exit 1;
fi

echo "All tests finished correctly"
exit 0