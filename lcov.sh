#!/bin/sh

set -e 

LCOV_HOME=/opt/lcov-1.12
LCOV_CFG=/opt/lcovrc
SRC_ROOT=.

output_dir=/tmp/coverage/DerivativeSolver
mkdir -p $output_dir

echo "Generating coverage reports..."

# collect coverage data
$LCOV_HOME/bin/lcov --config-file $LCOV_CFG -c --no-external -d $SRC_ROOT -o $output_dir/coverage.info > $output_dir/lcov.log

#remove helpers and tests source code from coverage
$LCOV_HOME/bin/lcov --config-file $LCOV_CFG -r $output_dir/coverage.info "*/test/*" -o $output_dir/coverage.info >> $output_dir/lcov.log
$LCOV_HOME/bin/lcov --config-file $LCOV_CFG -r $output_dir/coverage.info "*/googletest/*" -o $output_dir/coverage.info >> $output_dir/lcov.log
$LCOV_HOME/bin/lcov --config-file $LCOV_CFG -r $output_dir/coverage.info "*/usr/include/*" -o $output_dir/coverage.info >> $output_dir/lcov.log

# generate coverage reports
$LCOV_HOME/bin/genhtml $output_dir/coverage.info --config-file $LCOV_CFG --branch-coverage --function-coverage --output-directory $output_dir/html_report >> $output_dir/lcov.log

echo "... completed! Check the $output_dir/html_report/ directory."
