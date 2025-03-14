PROGRAM=$1

OUTPUT=$($PROGRAM < input/in.txt)

if [ "$OUTPUT" != "1" ]; then
  echo "Test 1 failed"
  exit 1
fi

echo "All tests finished correctly"
