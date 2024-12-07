#!/bin/bash

#first some test
grep -e some test.txt file1 > grep_result.txt
./s21_grep -e some test.txt file1 > program_result.txt

DIFF=$(diff grep_result.txt program_result.txt) 
if [ "$DIFF" == "" ] 
then
    echo "TEST -e PASSED"
else
    echo "TEST -e FAIL"
fi

#second some test
grep -i some test.txt file1 > grep_result.txt
./s21_grep -i some test.txt file1 > program_result.txt

DIFF=$(diff grep_result.txt program_result.txt) 
if [ "$DIFF" == "" ] 
then
    echo "TEST -i PASSED"
else
    echo "TEST -i FAIL"
fi

#third some test
grep -v some test.txt file1 > grep_result.txt
./s21_grep -v some test.txt file1 > program_result.txt

DIFF=$(diff grep_result.txt program_result.txt) 
if [ "$DIFF" == "" ] 
then
    echo "TEST -v PASSED"
else
    echo "TEST -v FAIL"
fi

#fourth some test
grep -c some test.txt file1 > grep_result.txt
./s21_grep -c some test.txt file1 > program_result.txt

DIFF=$(diff grep_result.txt program_result.txt) 
if [ "$DIFF" == "" ] 
then
    echo "TEST -c PASSED"
else
    echo "TEST -c FAIL"
fi


#fifth some test
grep -l some test.txt file1 > grep_result.txt
./s21_grep -l some test.txt file1 > program_result.txt

DIFF=$(diff grep_result.txt program_result.txt) 
if [ "$DIFF" == "" ] 
then
    echo "TEST -l PASSED"
else
    echo "TEST -l FAIL"
fi

#sixths some test
grep -n some test.txt file1 > grep_result.txt
./s21_grep -n some test.txt file1 > program_result.txt

DIFF=$(diff grep_result.txt program_result.txt) 
if [ "$DIFF" == "" ] 
then
    echo "TEST -n PASSED"
else
    echo "TEST -n FAIL"
fi
