#!/usr/bin/bash

count=0
for x in $(cat $2); do
	if [ $1 == $x ]; then
		count=$((count+1))
	fi
done
echo $count

