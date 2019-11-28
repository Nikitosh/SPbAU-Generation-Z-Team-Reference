#!/bin/bash

for ((i = 0;; i++)); do
	./gen $i >in || exit
	./main <in >out1 || exit
	./stupid <in >out2 || exit
	diff out1 out2 || exit
	echo $i OK
done
