#!/bin/sh
# =====================================================
# Copyright © hk. 2022-2025. All rights reserved.
# File name: qidaink_make.sh
# Author   : qidaink
# Date     : 2022-08-19
# Version  : 
# Description: 
# Others   : CROSS_COMPILE -- 当前使用的编译器
# Log      : 
# ======================================================
##

# ===================相关参数定义=========================
CPU_JOB_NUM=$(grep processor /proc/cpuinfo | awk '{field=$NF};END{print field+1}') # 参与编译的内核数量获取
BOARD_NAME="fs4412"                                         # 硬件平台,后续以 origen 评估板为模板
MAKE_PARAM="ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi-" # 交叉编译器

# ====================配置与编译============================
# 清除编译过程中产生的中间文件
# distclean : 删除所有编译生成文件，包括 .bin
# clean     : 只删除所有编译生成的 .o 文件
echo "\033[1;33m************************************************\033[0m"
echo "\033[1;33m[INFO ]Cleaning up project files ...            \033[0m"
echo "\033[1;33m************************************************\033[0m"
make ${MAKE_PARAM} distclean

# 指定当前使用的硬件平台 make <BOARD_NAME>_config
echo "\033[1;33m************************************************\033[0m"
echo "\033[1;33m[INFO ]Configuring the Project ...              \033[0m"
echo "\033[1;33m************************************************\033[0m"
make ${MAKE_PARAM} ${BOARD_NAME}_config

# 开始编译整个 uboot
echo "\033[1;33m************************************************\033[0m"
echo "\033[1;33m[INFO ]Building project in progress ...         \033[0m"
echo "\033[1;33m************************************************\033[0m"
make V=1 ${MAKE_PARAM} -j${CPU_JOB_NUM}

# 编译完成提示已经完成
echo "\033[1;32m************************************************\033[0m"
echo "\033[1;32m[INFO ]The compilation is complete!!!\033[0m"
echo "\033[1;32m************************************************\033[0m"

