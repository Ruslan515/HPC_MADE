#!/bin/bash

dirr=Linux
if [ -d "./$dirr" ]; then
	echo "course"
else
	echo "very easy"
	mkdir $dirr
fi
