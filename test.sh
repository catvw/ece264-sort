#!/bin/bash

run_test() {
	program=$1
	number=$2
	input=samples/sample${number}.txt
	output=output${number}_${program}.txt
	correct=samples/out_sample${number}.txt

	echo "** $program test $number **"
	echo -e "$input\n$output" \
		| ./$program
	echo

	echo -en "\e[91m"
	diff -q $output $correct
	echo -en "\e[0m"
}

for i in 1 2 3 4; do
	run_test reference $i
	echo
	run_test mine $i
	echo -e "\n****************\n"
done
