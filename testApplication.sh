#/bin/sh

VALGRIND=
VALGRIND_ERROR_CODE=101

check_result(){
    expected=$1
    actual=$2
    precision=$3
    
    if [ "$precision" = "substring" ]; then
        if echo $actual | grep -Fqe "$expected"; then
            return 1
        fi
        return 0        
    fi

    if [ "$expected" = "$actual" ]; then
        return 1
    fi
    return 0
}

check(){
   testId=$1
   expected=$2
   arg1=$3
   arg2=$4
   match_precision=${5:-"exactmatch"} 


   actual=$($CMD "$arg1" $arg2)
   if [ "$?" = "${VALGRIND_ERROR_CODE}" ]; then
         echo "$testId - FAILED"
         echo "   Memory leak detected."
         failedTests=1
   else
      check_result "$expected" "$actual" "$match_precision"
      if [ "$?" = "1" ]; then
         echo "$testId - OK"
      else
         echo "$testId - FAILED"
         echo "   Expected: $expected"
         echo "   Actual: $actual"
         failedTests=1
      fi
   fi
}

if [ "$DO_VALGRIND_TEST" = "1" ]; then
   VALGRIND="valgrind --error-exitcode=${VALGRIND_ERROR_CODE} --leak-check=full"
fi

CMD="$VALGRIND ./DerivativeSolver"

failedTests=0

echo "========================================"
echo "Execitiong application tests."
echo "----------------------------------------"

check T01 '1'       'x' 'x'
check T02 '0'       'x' 'y'
check T03 '2*x'                                              'x^2'                     'x' 
check T04 '2+(2*x)'                                          '2x + x^2'                'x'
check T05 '7*(1+(tan(x)^2))'                                 '7tan(x)'                 'x'
check T06 '(((x^2)+1)-(2*(x^2)))/(((x^2)+1)^2)'              'x/(x^2+1)'               'x' # answer is right but is still not completely simplified
check T07 '(cos(x)^2)-(sin(x)^2)'                            'sin(x)cos(x)'            'x'
check T08 '-1*(exp(x)^-1)'                                   '1/exp(x)'                'x'
check T09 '(-2*((4-(2*x))^-1))+(1.5*(((3*x)+9)^-0.5))'       'ln(4-2*x) + (3*x+9)^0.5' 'x'
check T10 '(((1-sin(x))*cos(x+cos(x)))*4)*(sin(x+cos(x))^3)' '(sin(x+cos(x)))^4'       'x'
check T11 'x^-1'                                             'ln(x/2)'                 'x'
check T12 '(2*x)*cos((x^2)+13)'                              'sin(x^2 + 13)'           'x'
check T13 '0.5*((x+2.7)^-0.5)'                               '(x+exp(1))^0.5'          'x'
check T14 '((3*(x^2))*cos(x))+((x^3)*(-1*sin(x)))'           '(x^3)*cos(x)'            'x'
check T15 'exp(x+1)'                                         'exp(x+1)'                'x'
check T16 '(((-1*(1+(ctan(x)^2)))*(x+1))-ctan(x))/((x+1)^2)' 'ctan(x)/(x+1)'           'x'
check T17 'exp(x)+(x*exp(x))'                                'x*exp(x)'                'x'
check T18 '-2*(x^-3)'                                        '1/x^2'                   'x'
check T19 '(2^cos(x))*(-0.69*sin(x))'                        '2^cos(x)'                'x'
check T20 '((x^-1)*0.7)/((ln(x)-8)^0.3)'                     '(ln(x)-8)^0.7'           'x'

check T21 'The specified expression is ambiguous. Not able to completely reduce syntax tree.'     'x^(3+)' 'x'     'substring' 
check T22 'Division by zero.'     'x/0' 'x'      'substring'

echo "========================================"

exit $failedTests
