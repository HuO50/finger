# README

## for 908 finger detect

## hardware live 20R

## url:www.zkteco.com

## how to use the demo

1. 将lib文件下的库加入到/user/lib中，或者将lib文件所在路径加入到/etc/ld.so.conf文件中

2. make clean 清除已有的main文件

3. make 编译当前文件

4. 使用管理员命令进行运行该文件 example: sudo ./main 

## 说明

该指纹识别型号的机器需要使用支持arm的库文件才能够使用，我在虚拟机下尝试使用该demo时，出现了如下问题：

1. 虚拟机与该指纹识别的链接自动断开，无法继续进行连接，猜测是虚拟机和硬件的问题

2. 还有一个问题在于x86架构下的linux确实需要一定的优化，整体使用起来的感受一般

3. 解决方案：1、解决驱动问题，自己写驱动进行编写  2、更换语言，使用python写这个脚本。
