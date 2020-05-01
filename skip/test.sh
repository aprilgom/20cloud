#!/bin/bash
for ((i=1;i<8;i++));do
	echo 0|sudo tee /sys/devices/system/cpu/cpu$i/online
done
./test.out >res0.txt
for ((i=1;i<8;i++));do
	./test.out >res$i.txt
	echo 1|sudo tee /sys/devices/system/cpu/cpu$i/online
done

