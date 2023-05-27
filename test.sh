#!/bin/sh

test_failed()
{
    set +x

    echo ""
    echo ""
    echo -------- -------- -------- -------- --------
    echo "TEST FAILED"
    echo -------- -------- -------- -------- --------
    echo ""
    echo "DIFF"
    echo ""
    diff --color -u __test_output__.txt example.txt
    rm __test_output__.txt

    exit 1
}

set -e
echo "BUILDING"
set -x
./build.sh
set +x
echo "TESTING"

EXIT_CODE=0
echo "+ ./main > __test_output__.txt"
./main > __test_output__.txt || EXIT_CODE=$?

set -x
cmp --silent example.txt __test_output__.txt || test_failed;

set +x
echo ""
echo ""
echo -------- -------- -------- -------- --------
echo "TEST PASSED"
echo -------- -------- -------- -------- --------
echo ""

rm __test_output__.txt

exit 0