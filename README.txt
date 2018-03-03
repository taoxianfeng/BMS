# BMS 
1.如何启动设备can0

1）首先设置波特率（设备进行通信时，要确保波特率一定设置的都一样）

sudo ip link set can0 type can bitrate 125000 
#设置can0 的波特率为 125kbps

2）然后在打开设备
#sudo ifconfig can0 up
#开启can0设备

其他常见命令简介

sudo ifconfig can0 down
#关闭can0设备

sudo ip -details link show can0
#显示can0的参数

ip link set can0 type can --help 
#显示帮助


2.配置虚拟vcan设备

1）sudo modprobe vcan
#加载虚拟can模块

2）sudo ip link add dev vcan0 type vcan
#添加vcan0网卡


3. 查看系统设备

ifconfig -a

can0: flags=193<UP,RUNNING,NOARP>  mtu 16
        unspec 00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00  txqueuelen 10  (UNSPEC)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0


vcan0: flags=128<NOARP>  mtu 16
        unspec 00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00  txqueuelen 1  (UNSPEC)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
