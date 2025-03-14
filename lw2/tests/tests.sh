PROGRAM=$1

OUTPUT=$($PROGRAM < input/in.txt)

if [ "$OUTPUT" != "2 1" ]; then
  echo "Test 1 failed. Got $OUTPUT"
  exit 1
fi

echo "All tests finished correctly"
