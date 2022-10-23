/** =====================================================
 * Copyright © hk. 2022-2025. All rights reserved.
 * File name  : imxdownload.h
 * Author     : qidaink
 * Date       : 2022-09-25
 * Version    : 
 * Description: 烧写逻裸机程序和uboot到SD卡
 * Others     : 
 * Log        : 
 * ======================================================
 */

#ifndef _IMXDOWNLOAD_H
#define _IMXDOWNLOAD_H
/* IMX6U IVT DCD表信息  暂时定义为1K Bytes，此表是读取的u-boot.imx前1K Bytes
 * imx6_ivedcd_table[9]是指明代码长度的，本应该根据实际的代码长度来修改
 * 这里为了方便，就直接定义为2M Bytes，即
 */

const int imx6_512mb_ivtdcd_table[256] = {
0X402000D1,0X87800000,0X00000000,0X877FF42C,0X877FF420,0X877FF400,0X00000000,0X00000000,
0X877FF000,0X00200000,0X00000000,0X40E801D2,0X04E401CC,0X68400C02,0XFFFFFFFF,0X6C400C02,
0XFFFFFFFF,0X70400C02,0XFFFFFFFF,0X74400C02,0XFFFFFFFF,0X78400C02,0XFFFFFFFF,0X7C400C02,
0XFFFFFFFF,0X80400C02,0XFFFFFFFF,0XB4040E02,0X00000C00,0XAC040E02,0X00000000,0X7C020E02,
0X30000000,0X50020E02,0X30000000,0X4C020E02,0X30000000,0X90040E02,0X30000000,0X88020E02,
0X30000C00,0X70020E02,0X00000000,0X60020E02,0X30000000,0X64020E02,0X30000000,0XA0040E02,
0X30000000,0X94040E02,0X00000200,0X80020E02,0X30000000,0X84020E02,0X30000000,0XB0040E02,
0X00000200,0X98040E02,0X30000000,0XA4040E02,0X30000000,0X44020E02,0X30000000,0X48020E02,
0X30000000,0X1C001B02,0X00800000,0X00081B02,0X030039A1,0X0C081B02,0X0B000300,0X3C081B02,
0X44014801,0X48081B02,0X302C4040,0X50081B02,0X343E4040,0X1C081B02,0X33333333,0X20081B02,
0X33333333,0X2C081B02,0X333333F3,0X30081B02,0X333333F3,0XC0081B02,0X09409400,0XB8081B02,
0X00080000,0X04001B02,0X2D000200,0X08001B02,0X3030331B,0X0C001B02,0XF3526B67,0X10001B02,
0X630B6DB6,0X14001B02,0XDB00FF01,0X18001B02,0X40172000,0X1C001B02,0X00800000,0X2C001B02,
0XD2260000,0X30001B02,0X23106B00,0X40001B02,0X4F000000,0X00001B02,0X00001884,0X90081B02,
0X00004000,0X1C001B02,0X32800002,0X1C001B02,0X33800000,0X1C001B02,0X31800400,0X1C001B02,
0X30802015,0X1C001B02,0X40800004,0X20001B02,0X00080000,0X18081B02,0X27020000,0X04001B02,
0X2D550200,0X04041B02,0X06100100,0X1C001B02,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000
};

const int imx6_256mb_ivtdcd_table[256] = {
0X402000D1,0X87800000,0X00000000,0X877FF42C,0X877FF420,0X877FF400,0X00000000,0X00000000,
0X877FF000,0X00076000,0X00000000,0X40E801D2,0X04E401CC,0X68400C02,0XFFFFFFFF,0X6C400C02,
0XFFFFFFFF,0X70400C02,0XFFFFFFFF,0X74400C02,0XFFFFFFFF,0X78400C02,0XFFFFFFFF,0X7C400C02,
0XFFFFFFFF,0X80400C02,0XFFFFFFFF,0XB4040E02,0X00000C00,0XAC040E02,0X00000000,0X7C020E02,
0X30000000,0X50020E02,0X30000000,0X4C020E02,0X30000000,0X90040E02,0X30000000,0X88020E02,
0X30000C00,0X70020E02,0X00000000,0X60020E02,0X30000000,0X64020E02,0X30000000,0XA0040E02,
0X30000000,0X94040E02,0X00000200,0X80020E02,0X30000000,0X84020E02,0X30000000,0XB0040E02,
0X00000200,0X98040E02,0X30000000,0XA4040E02,0X30000000,0X44020E02,0X30000000,0X48020E02,
0X30000000,0X1C001B02,0X00800000,0X00081B02,0X030039A1,0X0C081B02,0X04000000,0X3C081B02,
0X3C013C01,0X48081B02,0X38324040,0X50081B02,0X28304040,0X1C081B02,0X33333333,0X20081B02,
0X33333333,0X2C081B02,0X333333F3,0X30081B02,0X333333F3,0XC0081B02,0X09409400,0XB8081B02,
0X00080000,0X04001B02,0X2D000200,0X08001B02,0X3030331B,0X0C001B02,0XF352433F,0X10001B02,
0X630B6DB6,0X14001B02,0XDB00FF01,0X18001B02,0X40172000,0X1C001B02,0X00800000,0X2C001B02,
0XD2260000,0X30001B02,0X23104300,0X40001B02,0X47000000,0X00001B02,0X00001883,0X90081B02,
0X00004000,0X1C001B02,0X32800002,0X1C001B02,0X33800000,0X1C001B02,0X31800400,0X1C001B02,
0X30802015,0X1C001B02,0X40800004,0X20001B02,0X00080000,0X18081B02,0X27020000,0X04001B02,
0X2D550200,0X04041B02,0X06100100,0X1C001B02,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000,
};

#endif