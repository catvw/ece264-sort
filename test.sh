#!/bin/bash

run_test() {
	program=$1
	number=$2

	echo "** $program test $number **"
	echo -e "samples/sample${number}.txt\noutput${number}_reference.txt" \
		| ./$program
	echo
}

for i in 1 2 3 4; do
	run_test reference $i
	echo
	run_test mine $i
	echo -e "\n****************\n"
done
