# BMS 
sudo ip link set can0 type can bitrate 125000

sudo ifconfig can0 up

sudo ifconfig can0 down

sudo ip -details link show can0

ip link set can0 type can --help 
