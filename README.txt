# BMS 
1.设备初始化

1.1如何启动设备can0

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


1.2 配置虚拟vcan设备

1）sudo modprobe vcan
#加载虚拟can模块

2）sudo ip link add dev vcan0 type vcan
#添加vcan0网卡


1.3 查看系统设备

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
        
2.Canbus在Linux 常见开发底层介绍
  2.1 socketCan
  开发者可参考下面的链接了解SocketCan API及相关内容
  https://www.kernel.org/doc/Documentation/networking/can.txt
  
  2.2 在Qt上can常见的开发模块 Qtserialbus Modules
  
   Qt CAN Bus  
   http://doc.qt.io/qt-5/qtcanbus-backends.html
   
   Qt Serial Bus C++ Classes的介绍
   https://doc-snapshots.qt.io/qt5-5.9/qtserialbus-module.html
   
   2.3 QtSerialBus 如何安装在树莓派的系统上
   在树莓派测试系统上直接安装完Qt5.7.1后，系统并没有默认安装所有的Qt Add ons Modules（包括QtSrialBus modules）。用户需要自己安装模块
   
   qtserialbus的地址如下(安装的版本一定要和Qt版本一致)：
   http://code.qt.io/cgit/qt/qtserialbus.git/
   git://code.qt.io/qt/qtserialbus.git
   安装步骤 ：
           1)git clone http://code.qt.io/qt/qtserialbus.git           
           2) cd qtserialbus
           3）git branch -a  #选择适合的版本
           4）git checkout -b 5.7.1 origin/5.7.1 #树莓派安装的Qt版本为5.7.1
           5) qmake
           6) make
           7) make install
            
3. Qt开发环境的搭建
   3.1 Ubuntu 下 树莓派交叉编译开发环境的搭建
   https://wiki.qt.io/RaspberryPi2EGLFS#Initial_notes
   https://wiki.qt.io/Raspberry_Pi_Beginners_Guide
   http://blog.csdn.net/luofenglian/article/details/79040686
   
   3.2 直接在树莓的系统安装Qt
   
   http://blog.csdn.net/wangmi0354/article/details/50850702
   http://blog.csdn.net/coekjin/article/details/52049273
