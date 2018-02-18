#!/bin/sh

set -e 

SRC_ROOT=.

output_dir=/tmp/coverage/DerivativeSolver
mkdir -p $output_dir

echo "Generating coverage reports..."

# collect coverage data
lcov  -c --no-external -d $SRC_ROOT -o $output_dir/coverage.info > $output_dir/lcov.log

#remove helpers and tests source code from coverage
lcov  -r $output_dir/coverage.info "*/test/*" -o $output_dir/coverage.info >> $output_dir/lcov.log
lcov  -r $output_dir/coverage.info "*/googletest/*" -o $output_dir/coverage.info >> $output_dir/lcov.log
lcov  -r $output_dir/coverage.info "*/usr/include/*" -o $output_dir/coverage.info >> $output_dir/lcov.log

# generate coverage reports
genhtml $output_dir/coverage.info  --branch-coverage --function-coverage --output-directory $output_dir/html_report >> $output_dir/lcov.log

echo "... completed! Check the $output_dir/html_report/ directory."
