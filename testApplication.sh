#/bin/sh

check(){
   testId=$1
   expected=$2
   cmd=$3

   actual=`$cmd`

   if [ "$expected" == "$actual" ]; then
      echo "$testId - OK"
   else
      echo "$testId - FAILED"
      echo "   Expected: $expected"
      echo "   Actual: $actual"
   fi
   
}

CMD=./DerivativeSolver

echo "========================================"
echo "Execitiong application tests."
echo "----------------------------------------"

check T01 "1" "$CMD x x" 
check T02 "0" "$CMD x y" 
check T03 "2*x" "$CMD x^2 x" 
check T04 "x + 2*x" "$CMD \"2x + x^2\" y" 

echo "========================================"

# TODO consider all FAILED tests as errors

exit 0

