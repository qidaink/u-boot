#!/bin/sh
# =====================================================
# Copyright © hk. 2022-2025. All rights reserved.
# File name: qidaink_make.sh
# Author   : qidaink
# Date     : 2022-08-13
# Version  : 
# Description: 编译命令脚本文件。
# Others   : 
# Log      : 
# ======================================================
##

# ======================================================
## 编译 NXP 官方开发板对应的 uboot
echo "\033[1;32m[INFO]Cleaning up project files ... \033[0m"
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean
echo "\033[1;32m[INFO]Configuring the Project ... \033[0m"
# make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- mx6ull_14x14_evk_emmc_defconfig # 编译的是 NXP 官方的板子
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- mx6ull_alientek_emmc_defconfig  # 正点原子 IMX6ULL linux 开发板
echo "\033[1;32m[INFO]Building project in progress ... \033[0m"
make V=0 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j12
echo "\033[1;32m[INFO]Compile the complete!!!\033[0m"