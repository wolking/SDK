/*************************************************************************
    > File Name:    apps.c
    > Author:       Guangdong Research Institute of China Telecom Corporation Ltd.
	> See More:     https://www.easy-iot.cn/
	> Description:  本文件示例了EasyIoT SDK 的使用方式
    > Created Time: 2017/12/21
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "easyiot.h"
#include "example.h"

#ifdef _WIN32
void data_report()
{
	struct Messages* msg = NewMessage();

	setMessages(msg, CMT_USER_UP, MSG_MSGID);
	AddFloat(msg, LON_TLV_PARAMID, 123.123f);
	AddFloat(msg, LAT_TLV_PARAMID, 321.456f);
	AddInt8(msg, STATUS_TLV_PARAMID, 129);
	AddFloat(msg, 4, 321.456f);
	AddString(msg, 5, "HELLO,WORLD");
	pushMessages(msg);

	FreeMessage(msg);
}

uint8_t getBattery(void)
{
	return 99;
}

uint64_t getTimestamp(void)
{
	return 1514906998853;
}

int32_t getSignal(void)
{
	return -66;
}

void ack_handler(struct Messages* req)
{
	printf("recv ack, ack_handler ignore it.\n");
}

void show_cmd_req_info(struct Messages* req)
{
	int ret;
	int8_t vint8;
	int16_t vint16;
	float vfloat;

	vint8 = 0;
	vfloat = 0.0f;

	// 以指定的type值，获取一个 Int8 的TLV值
	ret = GetInt8(req, STATUS_TLV_PARAMID, &vint8);
	if (ret < 0) {
		printf("fetch int8 %d faied.\n", STATUS_TLV_PARAMID);
	} else {
		printf("fetch %d value %d\n", STATUS_TLV_PARAMID, vint8);
	}

	ret = GetFloat(req, TEMPERATURE_TLV_PARAMID, &vfloat);
	if (ret < 0) {
		printf("fetch float %d faied.\n", TEMPERATURE_TLV_PARAMID);
	} else {
		printf("fetch %d value %.4f\n", TEMPERATURE_TLV_PARAMID, vfloat);
	}

	ret = GetInt16(req, HUMIDITY_TLV_PARAMID, &vint16);
	if (ret < 0) {
		printf("fetch float %d faied.\n", HUMIDITY_TLV_PARAMID);
	} else {
		printf("fetch %d value %d\n", HUMIDITY_TLV_PARAMID, vint16);
	}
}

void process_response(struct Messages* req)
{
	struct Messages* rsp = NewMessage();
	setMessages(rsp, CMT_USER_CMD_RSP, req->msgid);

	rsp->dtag_mid = req->dtag_mid;

	AddFloat(rsp, LON_TLV_PARAMID, 123.123f);
	AddFloat(rsp, LAT_TLV_PARAMID, 321.456f);
	pushMessages(rsp);

	FreeMessage(rsp);
}

void cmd_handler(struct Messages* req)
{
	show_cmd_req_info(req);
	process_response(req);
}

void test_api()
{
	// 测试上传业务
	data_report();
	// ack
	CoapHexInput("01F1000200F4");
	// single tlv cmd.
	CoapHexInput("01F2000A00010300040300010009");
	// triple tlv cmd.
	CoapHexInput("01F2001600020300100300010104000441BBA5E3050002006117");
}

void data_report_static(uint8_t *buf, uint16_t inMaxLength)
{
	struct Messages* msg;

	msg = NewMessageStatic(buf, inMaxLength);

	setMessages(msg, CMT_USER_UP, MSG_MSGID);
	AddFloat(msg, LON_TLV_PARAMID, 123.123f);
	AddFloat(msg, LAT_TLV_PARAMID, 321.456f);
	AddInt8(msg, STATUS_TLV_PARAMID, 129);
	AddFloat(msg, 4, 321.456f);
	AddString(msg, 5, "HELLO,WORLD");
	printf("used memory %d\n", msg->sbuf_offset);
	pushMessages(msg);

	// 可选，函数返回时，buf空间被收回，则msg自动被free
	FreeMessage(msg);
}

void test_static_api()
{
	uint8_t buf[1024];
	// 无动态内存分配的数据上报，使用指定的栈变量空间。
	data_report_static(buf, sizeof(buf));

	// ack
	CoapHexInputStatic("01F1000200F4", buf, sizeof(buf));
	// single tlv cmd.
	CoapHexInputStatic("01F2000A00010300040300010009", buf, sizeof(buf));
	// triple tlv cmd.
	CoapHexInputStatic("01F2001600020300100300010104000441BBA5E3050002006117", buf, sizeof(buf));
}

// 测试各对象默认大小
void output_size()
{
	printf("sizeof(Messages) == %d\n", sizeof(struct Messages));
	printf("sizeof(TLV) == %d\n", sizeof(struct TLV));
}

void outputfunc(const uint8_t* data, uint16_t inLength)
{
	printf("%s", data);
}

// 用法示例
int main_(int argc, char** argv)
{
	// 初始化，以下所有初始化都是全局操作，EasyIotInit 以 IMEI和 IMSI进行全局初始化
	EasyIotInit("863703035110241", "460111174809981");

	// 设置上传信息获取回调函数 以下三个回调函数可选，若不设置，则 时间戳、电量、信号强度取0值。
	setsTimestampCb(getTimestamp);
	setSignalCb(getSignal);
	setBatteryCb(getBattery);

	// 设置日志输出，设置指令输出，在MCU中需要分开
	setLogSerialOutputCb(outputfunc);
	setNbSerialOutputCb(outputfunc);

	// 设置ACK数据确认回调函数，若无需处理ACK，则可选
	setAckHandler(ack_handler);

	// 设置指令回调函数，若无指令，则可选，指令的回调ID，取 EasyIoT 平台中指令的ID。
	setCmdHandler(CMD_CMDID, cmd_handler);

	// 测试普通使用流程，在此流程中，内存使用操作系统 malloc 分配
	test_api();
	// 测试静态内存分配API使用，无malloc内存分配，所有内存使用一次性分配；
	test_static_api();

	system("pause");
	return 0;
}

int main()
{
	// 初始化，以下所有初始化都是全局操作，EasyIotInit 以 IMEI和 IMSI进行全局初始化
	EasyIotInit("863703030452234", "460111174808787");

	// 设置上传信息获取回调函数 以下三个回调函数可选，若不设置，则 时间戳、电量、信号强度取0值。
	setsTimestampCb(getTimestamp);
	setSignalCb(getSignal);
	setBatteryCb(getBattery);

	// 设置日志输出，设置指令输出，在MCU中需要分开
	setLogSerialOutputCb(outputfunc);
	setNbSerialOutputCb(outputfunc);

	struct Messages* msg = NewMessage();

	setMessages(msg, CMT_USER_UP, 1);
	AddInt32(msg, 1, 12345);
	pushMessages(msg);

	FreeMessage(msg);

	system("pause");
	return 0;
}

#endif
