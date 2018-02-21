#/bin/sh

check_ok(){
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

check_fail(){
   testId=$1
   expected=$2
   arg1=$3
   arg2=$4

   actual=$($CMD "$arg1" $arg2)

    if echo $actual | grep -Fqe "$expected"; then
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

check_ok T01 '1'       'x' 'x'
check_ok T02 '0'       'x' 'y'
check_ok T03 '2*x'     'x^2' 'x' 
check_ok T04 '2+(2*x)' '2x + x^2' 'x'
check_ok T05 '7*(1+(tan(x)^2))' '7tan(x)' 'x'
check_ok T06 '(((x^2)+1)-(2*(x^2)))/(((x^2)+1)^2)' 'x/(x^2+1)' 'x' # answer is right but is still not completely simplified
check_ok T07 '(cos(x)^2)-(sin(x)^2)' 'sin(x)cos(x)' 'x'
check_ok T08 '-1*(exp(x)^-1)' '1/exp(x)' 'x'
check_ok T09 '(-2*((4-(2*x))^-1))+(1.5*(((3*x)+9)^-0.5))' 'ln(4-2*x) + (3*x+9)^0.5' 'x'
check_ok T10 '(((1-sin(x))*cos(x+cos(x)))*4)*(sin(x+cos(x))^3)' '(sin(x+cos(x)))^4' 'x'

check_fail T11 'The specified expression is ambiguous. Not able to completely reduce syntax tree.'     'x^(3+)' 'x' 
check_fail T12 'Division by zero.'     'x/0' 'x' 

echo "========================================"

exit $failedTests
