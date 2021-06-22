#include "iic_soft.h"
#include "iic_gpio.h"
#include "hal_delay_us.h"
enum IIC_MODE  emIIC_mode;
#define IIC_DELAY()  { if(IIC_NORMAL_MODE()) HAL_Delay_us(50); \
	else if(IIC_FAST_MODE()) __NOP();}


//起始条件
void iic_start(void)
{
	IIC_SDA_OUTPUT();
	IIC_SCL_H();
	IIC_SDA_H();
	IIC_DELAY();
	IIC_SDA_L();//when sclk is high,sda change from high to low;
	IIC_DELAY();
	IIC_SCL_L();//ready send or receive data
}

//停止条件
void iic_stop(void)
{
	IIC_SDA_OUTPUT();
	IIC_SCL_L();
	IIC_SDA_L();
	IIC_DELAY();
	IIC_SCL_H();
	IIC_DELAY();
	IIC_SDA_H();
	IIC_DELAY();
	IIC_SDA_INPUT();
}

//应答
void iic_ack(void)
{
	IIC_SCL_L();
	IIC_SDA_OUTPUT();
	IIC_DELAY();
	IIC_SDA_L();
	IIC_DELAY();
	IIC_SCL_H();
	IIC_DELAY();
	IIC_SCL_L();
}

//无应答
void iic_nack(void)
{
	IIC_SCL_L();
	IIC_SDA_OUTPUT();
	IIC_DELAY();
	IIC_SDA_H();
	IIC_DELAY();
	IIC_SCL_H();
	IIC_DELAY();
	IIC_SCL_L();
}

//等待应答
enum IIC_RESULT iic_wait_ack(void)
{
	unsigned char ucErrTime=0;
	IIC_SCL_L();
	IIC_SDA_INPUT();
	IIC_SCL_H();
	IIC_DELAY();
    
	while(IIC_SDA_STATE_GET())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			iic_stop();
			return IIC_NOACK;
		}
	}
	IIC_SCL_L();
	return IIC_ACK;

}

//发送字节
enum IIC_RESULT iic_send_byte(char cData)
{
	char i=0;
	IIC_SDA_OUTPUT();
	IIC_SCL_L();
    while( i<8 )
    {
        if(cData&0x80)
        IIC_SDA_H();
        else
        IIC_SDA_L();
		cData <<=1;
		IIC_DELAY();
		IIC_SCL_H();
		IIC_DELAY();
		IIC_SCL_L();
 
        i++;
    }
		return iic_wait_ack();
}

//接收字节
char  iic_read_byte(void)
{
    char i=0, cData=0;
    IIC_SDA_INPUT();
    while( i<8 )
    {
		IIC_SCL_L();
		IIC_DELAY();
		IIC_SCL_H();
		cData<<=1;
		if(IIC_SDA_STATE_GET())
			cData++;    
        IIC_DELAY();
        i++;
    }
	IIC_SCL_L();
    return cData;
}

enum IIC_RESULT iic_send_device_addr(char cDevAddr)
{	
	enum IIC_RESULT emResult;
	emResult= iic_send_byte(cDevAddr);  
		if(IIC_NOACK==emResult)
			return IIC_FAIL;
		return IIC_SUCCESS;
	
}

enum IIC_RESULT iic_send_reg_addr(char cRegAddr)
{
	enum IIC_RESULT emResult;
	emResult= iic_send_byte(cRegAddr);  
		if(IIC_NOACK ==emResult)
			return IIC_FAIL;
		return IIC_SUCCESS;
}

enum IIC_RESULT iic_send(char *pData, unsigned short usLen)
{ 
	unsigned short i=0;
	enum IIC_RESULT emResult;
    while(i<usLen)
    {
		emResult=iic_send_byte(*(pData+i));
			i++;
		if(IIC_NOACK ==emResult)
			return IIC_FAIL;    
    }
	return IIC_SUCCESS;
}

enum IIC_RESULT iic_read(char *pData, unsigned short usLen)
{
    unsigned int i=0;
    while(i<usLen)
    {
		*(pData+i)=iic_read_byte();
		if(i==usLen-1)
			iic_nack();
		else
			iic_ack();					 
		i++;
    }
	return IIC_SUCCESS;
}

