#!/bin/bash

#first test
cat -b test.txt file > cat_result.txt
./s21_cat -b test.txt file > program_result.txt

DIFF=$(diff cat_result.txt program_result.txt) 
if [ "$DIFF" == "" ] 
then
    echo "TEST -b PASSED"
else
    echo "TEST -b FAIL"
fi

#second test
cat -e test.txt file > cat_result.txt
./s21_cat -e test.txt file > program_result.txt

DIFF=$(diff cat_result.txt program_result.txt) 
if [ "$DIFF" == "" ] 
then
    echo "TEST -e PASSED"
else
    echo "TEST -e FAIL"
fi

#third test
cat -n test.txt file > cat_result.txt
./s21_cat -n test.txt file > program_result.txt

DIFF=$(diff cat_result.txt program_result.txt) 
if [ "$DIFF" == "" ] 
then
    echo "TEST -n PASSED"
else
    echo "TEST -n FAIL"
fi

#fourth test
cat -s test.txt file > cat_result.txt
./s21_cat -s test.txt file > program_result.txt

DIFF=$(diff cat_result.txt program_result.txt) 
if [ "$DIFF" == "" ] 
then
    echo "TEST -s PASSED"
else
    echo "TEST -s FAIL"
fi


#fifth test
cat -t test.txt file > cat_result.txt
./s21_cat -t test.txt file > program_result.txt

DIFF=$(diff cat_result.txt program_result.txt) 
if [ "$DIFF" == "" ] 
then
    echo "TEST -t PASSED"
else
    echo "TEST -t FAIL"
fi
