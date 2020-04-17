echo 0|sudo tee /sys/devices/system/cpu/cpu1/online
echo 0|sudo tee /sys/devices/system/cpu/cpu2/online
echo 0|sudo tee /sys/devices/system/cpu/cpu3/online
echo 0|sudo tee /sys/devices/system/cpu/cpu4/online
echo 0|sudo tee /sys/devices/system/cpu/cpu5/online
echo 0|sudo tee /sys/devices/system/cpu/cpu6/online
echo 0|sudo tee /sys/devices/system/cpu/cpu7/online
./test.out >processor1.txt
echo 1|sudo tee /sys/devices/system/cpu/cpu1/online
./test.out >processor2.txt
echo 1|sudo tee /sys/devices/system/cpu/cpu2/online
./test.out >processor3.txt
echo 1|sudo tee /sys/devices/system/cpu/cpu3/online
./test.out >processor4.txt
echo 1|sudo tee /sys/devices/system/cpu/cpu4/online
./test.out >processor5.txt
echo 1|sudo tee /sys/devices/system/cpu/cpu5/online
./test.out >processor6.txt
echo 1|sudo tee /sys/devices/system/cpu/cpu6/online
./test.out >processor7.txt
echo 1|sudo tee /sys/devices/system/cpu/cpu7/online
./test.out >processor8.txt

