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
sec_path="CodeSign4SecureBoot/"                          # 三星加密引导方式路径
ROOT_DIR=$(pwd)                                          # 顶层(当前)目录路径
CUR_DIR=${ROOT_DIR##*/}

# ===================配置与编译===========================
case "$1" in
	clean)
                # 清除编译过程中产生的中间文件而不清除加密文件
                echo
                echo "\033[1;33m************************************************\033[0m"
                echo "\033[1;33m[INFO ]make ${MAKE_PARAM} clean                 \033[0m"
                echo "\033[1;33m************************************************\033[0m" 
                make ${MAKE_PARAM} mrproper
                ;;
        image)
                # 制作镜像文件
                echo
                echo "\033[1;33m************************************************\033[0m"
                echo "\033[1;33m[INFO ]Creating an Image File...                \033[0m"
                echo "\033[1;33m************************************************\033[0m" 
                sudo dd if=/dev/zero of=zero.bin count=1     # 制作一个512Bytes的空镜像
                sudo dd if=/dev/zero of=clear.bin count=2048 # 制作一个1M的空镜像
                # 判断 u-boot-fs4412.bin 文件是否存在
                if [ ! -e u-boot-fs4412.bin ]
                        then
                        echo
                        echo "\033[1;31m************************************************\033[0m"
                        echo "\033[1;31m[ERROR]please get the u-boot-fs4412.bin first!  \033[0m"
                        echo "\033[1;31m************************************************\033[0m"
                        return
                        fi
                cat zero.bin u-boot-fs4412.bin > win-u-boot-fs4412.bin
                echo
                echo "\033[1;32m************************************************\033[0m"
                echo "\033[1;32m[INFO ]Image finished!!!                        \033[0m"
                echo "\033[1;32m************************************************\033[0m" 
                ;;
	*)
                # 判断加密引导方式文件目录是否存在
                if [ ! -d ${sec_path} ]
                        then
                        echo
                        echo "\033[1;31m************************************************\033[0m"
                        echo "\033[1;31m[ERROR]please get the CodeSign4SecureBoot first!\033[0m"
                        echo "\033[1;31m************************************************\033[0m"
                        return
                        fi

                # 指定当前使用的硬件平台 make <BOARD_NAME>_config
                echo
                echo "\033[1;33m************************************************\033[0m"
                echo "\033[1;33m[INFO ]Configuring the Project ...              \033[0m"
                echo "\033[1;33m************************************************\033[0m"
                make ${MAKE_PARAM} ${BOARD_NAME}_config

                # 开始编译整个 uboot
                echo
                echo "\033[1;33m************************************************\033[0m"
                echo "\033[1;33m[INFO ]Building project in progress ...         \033[0m"
                echo "\033[1;33m************************************************\033[0m"
                make V=1 ${MAKE_PARAM} -j${CPU_JOB_NUM}

                # 判断是否编译成功
                if [ ! -f checksum_bl2_14k.bin ]
                        then
                        echo
                        echo "\033[1;31m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\033[0m"
                        echo "\033[1;31m[ERROR]There are some error(s) while building uboot, please use command make to check.\033[0m"
                        echo "\033[1;31m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\033[0m"
                        exit 0
                        fi
                # 三星加密引导方式相关操作，必须要有
                cp -rf checksum_bl2_14k.bin ${sec_path}
                cp -rf u-boot.bin ${sec_path}
                rm checksum_bl2_14k.bin

                cd ${sec_path}
                cat E4412_N.bl1.SCP2G.bin bl2.bin all00_padding.bin u-boot.bin tzsw_SMDK4412_SCP_2GB.bin > u-boot-fs4412.bin
                mv u-boot-fs4412.bin ${ROOT_DIR}
                
                rm checksum_bl2_14k.bin
                rm u-boot.bin

                # 编译完成提示已经完成
                echo
                echo "\033[1;32m************************************************\033[0m"
                echo "\033[1;32m[INFO ]The compilation is complete!!!\033[0m"
                echo "\033[1;32m************************************************\033[0m"
                echo 
                ;;
esac
