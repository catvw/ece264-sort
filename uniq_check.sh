#!/bin/bash
file=$1
chars=$2

repeats=`sort $file | uniq | sed -E -e "s/^(.{,$chars}).*$/\\1/" | uniq -d`

for rep in $repeats; do
	grep ^$rep $file
done
