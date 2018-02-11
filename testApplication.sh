#/bin/sh

check(){
   testId=$1
   expected=$2
   arg1=$3
   arg2=$4

   actual=$($CMD "$arg1" $arg2)
   if [ "$expected" = "$actual" ]; then
      echo "$testId - OK"
   else
      echo "$testId - FAILED"
      echo "   Expected: $expected"
      echo "   Actual: $actual"
      failedTests=1
   fi
}

CMD=./DerivativeSolver

failedTests=0

echo "========================================"
echo "Execitiong application tests."
echo "----------------------------------------"

check T01 '1'       'x' 'x'
check T02 '0'       'x' 'y'
check T03 '2*x'     'x^2' 'x' 
check T04 '2+(2*x)' '2x + x^2' 'x'
check T05 '7*(1+(tan(x)^2))' '7tan(x)' 'x'
check T06 '(1-x^2)/((x^2+1)^2)' 'x/(x^2+1)' 'x'
check T07 '(cos(x)^2)-(sin(x)^2)' 'sin(x)cos(x)' 'x'
check T08 '-1*(exp(x)^-1)' '1/exp(x)' 'x'
check T50 '(-2*((4-(2*x))^-1))+(1.5*(((3*x)+9)^-0.5))' 'ln(4-2*x) + (3*x+9)^0.5' 'x'
check T51 '(((1-sin(x))*cos(x+cos(x)))*4)*(sin(x+cos(x))^3)' '(sin(x+cos(x)))^4' 'x'

echo "========================================"

exit $failedTests
