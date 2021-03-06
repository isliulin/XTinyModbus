/********************************************************************************
* @File name: MD_RTU_Serial.c
* @Author: zspace
* @Version: 1.0
* @Date: 2020-4-10
* @Description: Modbus RTU 串口有关模块
* 开源地址: https://github.com/lotoohe-space/XTinyModbus
********************************************************************************/
/*********************************头文件包含************************************/
#include "MD_RTU_Serial.h"
#include "MD_RTU_Fun.h"

#include "usart.h"
/*********************************结束******************************************/

/*********************************全局变量************************************/
PModbusBase pModbusBase=NULL;			/*当前串口的Modbus*/
/*********************************结束******************************************/

/*********************************函数申明************************************/
void MDSSerialSendBytes(uint8 *bytes,uint16 num);
void MDSSerialSWRecv_Send(uint8 mode);
void MDSTimeHandler100US(void);
/*********************************结束******************************************/

/*******************************************************
*
* Function name :MDSInitSerial
* Description        :硬件初始化函数，可在此初始化串口
* Parameter         :
*        @obj        从机对象指针    
*        @baud    波特率
*        @dataBits    数据位
*        @stopBit    停止位
*        @parity    奇偶校验位
* Return          : 无
**********************************************************/
void MDSInitSerial(void* obj,uint32 baud,uint8 dataBits,uint8 stopBit,uint8 parity){
	pModbusBase=obj;
	if(obj==NULL){return ;}
	
	pModbusBase->mdRTUSendBytesFunction=MDSSerialSendBytes;
	pModbusBase->mdRTURecSendConv=MDSSerialSWRecv_Send;
	
	
	/*硬件初始化*/
	uart_init(baud);
}
/*******************************************************
*
* Function name :MDSSerialRecvByte
* Description        :bsp层中断接收调用这个函数
* Parameter         :
*        @byte        接收到的一个字节    
* Return          : 无
**********************************************************/
void MDSSerialRecvByte(uint8 byte){
	if(pModbusBase==NULL){return;}
	pModbusBase->mdRTURecByteFunction(pModbusBase , byte);
}
/*******************************************************
*
* Function name :MDSSerialSWRecv_Send
* Description        :切换接收，或者发送
* Parameter         :
*        @mode        TRUE 发 ,FALSE 收
* Return          : 无
**********************************************************/
void MDSSerialSWRecv_Send(uint8 mode){
	/*收发转换*/
	/*下面填写转换的代码*/
	
	/*不同的硬件可能在设置转换后需要一点延时*/
}
/*******************************************************
*
* Function name :MDSSerialSendBytes
* Description        :发送函数
* Parameter         :
*        @bytes        发送的数据
*        @num        发送多少字节
* Return          : 无
**********************************************************/
void MDSSerialSendBytes(uint8 *bytes,uint16 num){
	/*在下面调用bsp的发送函数*/
	uart_send_bytes_by_isr(bytes,num);
}
/*******************************************************
*
* Function name :MDSTimeHandler100US
* Description        :定时器中调用该函数，定时单位100US
* Parameter         :无
* Return          : 无
**********************************************************/
void MDSTimeHandler100US(void){
	if(pModbusBase==NULL){return;}
	pModbusBase->mdRTUTimeHandlerFunction(pModbusBase);
}
