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

# Copyright (C) 2022, C. R. Van West
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
