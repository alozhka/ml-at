PROGRAM=$1
OUTPUT="/tmp/output.txt"

$PROGRAM test1/in.txt $OUTPUT

if ! cmp test1/out.txt $OUTPUT; then
  echo "Test 1 failed"
  exit 1
fi

echo "All tests finished correctly"
