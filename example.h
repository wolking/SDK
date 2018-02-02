/*
* Copyright (C) 2017-, ChinaTelecom. Ltd.
* FileName:     SmartLed_example.h
* Description:  EasyIoT 产品定义头文件
* Created:      2018.01.02
* Notice:       注意, 请不要随意编辑此文件，且在 EasyIoT 产品中心更新了产品定义后，
* 此文件需要重新导出，旧有的设备消息定义极有可能导致您无法收到新的设备消息或指令
*/

#ifndef _GUARD_H_SmartLed
#define _GUARD_H_SmartLed

#include <stdint.h>

/*
* 传感器 Lon
* 如下为所有您在 EasyIoT产品中心定义的传感器，每个传感器为一个 struct类型
* 本struct为 TLV (Type-Length-Value) 结构，具体定义请参考 EasyIoT文档中心
* 《开发板套件 => 终端接口协议》 有详细介绍
* LON_TLV_PARAMID为此传感器的 Type值，请勿修改
*/
#define LON_TLV_PARAMID 1

/*
* 传感器 Lat
* 如下为所有您在 EasyIoT产品中心定义的传感器，每个传感器为一个 struct类型
* 本struct为 TLV (Type-Length-Value) 结构，具体定义请参考 EasyIoT文档中心
* 《开发板套件 => 终端接口协议》 有详细介绍
* LAT_TLV_PARAMID为此传感器的 Type值，请勿修改
*/
#define LAT_TLV_PARAMID 2

/*
* 传感器 Status
* 如下为所有您在 EasyIoT产品中心定义的传感器，每个传感器为一个 struct类型
* 本struct为 TLV (Type-Length-Value) 结构，具体定义请参考 EasyIoT文档中心
* 《开发板套件 => 终端接口协议》 有详细介绍
* STATUS_TLV_PARAMID为此传感器的 Type值，请勿修改
*/
#define STATUS_TLV_PARAMID 3

/*
* 传感器 Temperature
* 如下为所有您在 EasyIoT产品中心定义的传感器，每个传感器为一个 struct类型
* 本struct为 TLV (Type-Length-Value) 结构，具体定义请参考 EasyIoT文档中心
* 《开发板套件 => 终端接口协议》 有详细介绍
* TEMPERATURE_TLV_PARAMID为此传感器的 Type值，请勿修改
*/
#define TEMPERATURE_TLV_PARAMID 4

/*
* 传感器 Humidity
* 如下为所有您在 EasyIoT产品中心定义的传感器，每个传感器为一个 struct类型
* 本struct为 TLV (Type-Length-Value) 结构，具体定义请参考 EasyIoT文档中心
* 《开发板套件 => 终端接口协议》 有详细介绍
* HUMIDITY_TLV_PARAMID为此传感器的 Type值，请勿修改
*/
#define HUMIDITY_TLV_PARAMID 5

/*
* 传感器 result
* 如下为所有您在 EasyIoT产品中心定义的传感器，每个传感器为一个 struct类型
* 本struct为 TLV (Type-Length-Value) 结构，具体定义请参考 EasyIoT文档中心
* 《开发板套件 => 终端接口协议》 有详细介绍
* RESULT_TLV_PARAMID为此传感器的 Type值，请勿修改
*/
#define RESULT_TLV_PARAMID 0

/*
* 消息：MSG
* 在 EasyIoT产品中心定义的设备消息
* 其中每个字段为您选择的待上报的传感器值列表
* 首字段 _msgid为消息唯一标识符
* MSG_MSGID为消息的标识符值，请勿修改
*/
#define MSG_MSGID 1

/*
* 命令请求：CMD
* 在 EasyIoT产品中心定义的设备指令，CMD_Command是指令的请求 Request类型
* 其中每个字段为您选择的待配置的传感器列表，设备需受理此消息，并读取传感器值
* 首字段 _cmdid为消息唯一标识符
*/
#define CMD_CMDID 3

#endif
