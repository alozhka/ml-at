#!/bin/bash

OUTPUT=$(../cmake-build-release/timber-cutter input1.txt)
if [ "$OUTPUT" != "20" ] ; then
  echo "7 and 6 => 20 failed"
  exit 1
fi

OUTPUT=$(../cmake-build-release/timber-cutter input2.txt)
if [ "$OUTPUT" != "15" ] ; then
  echo "10 and 3 => 15 failed"
  exit 1
fi

OUTPUT=$(../cmake-build-release/timber-cutter input3.txt)
if [ "$OUTPUT" != "27" ] ; then
  echo "9 and 7 => 27 failed"
  exit 1
fi

OUTPUT=$(../cmake-build-release/timber-cutter input4.txt)
if [ "$OUTPUT" != "29" ] ; then
  echo "10 and 7 => 29 failed"
  exit 1
fi

OUTPUT=$(../cmake-build-release/timber-cutter input5.txt)
if [ "$OUTPUT" != "45" ] ; then
  echo "13 and 10 => 45 failed" # 44
  exit 1
fi

OUTPUT=$(../cmake-build-release/timber-cutter input6.txt)
if [ "$OUTPUT" != "105" ] ; then
  echo "100 and 3 => 105 failed"
  exit 1
fi

OUTPUT=$(../cmake-build-release/timber-cutter input7.txt)
if [ "$OUTPUT" != "18" ] ; then
  echo "10 and 4 => 18 failed"
  exit 1
fi

echo "All tests finished correctly"
exit 0