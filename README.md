# BMS 
1.如何启动设备can0
1）sudo ip link set can0 type can bitrate 125000 
#设置can0 的波特率为 125kbps

#sudo ifconfig can0 up
#开启can0设备

#sudo ifconfig can0 down
#关闭can0设备

#sudo ip -details link show can0
#显示can0的参数

#ip link set can0 type can --help 
#显示帮助
