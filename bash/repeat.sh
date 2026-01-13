#!/usr/bin/bash


count=0

while [ $count != $2 ]; do
	$1
	count=$((count+1))
done

