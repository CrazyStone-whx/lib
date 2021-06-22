#include "eepromfun.h"
#include "iic_soft.h"
#include "iic_gpio.h"
#include "stm32f1xx_hal.h"
#include "string.h"
#include "hal_delay_us.h"
#define IIC_DELAY_MS(ms)  DelayMS(ms)
void eeprom_init(void)
{
	iic_gpio_init();
}

static enum EEPROM_RESULT eeprom_iic_write(char cAddr, char *pData,unsigned short usLen)
{
	enum IIC_RESULT emResult;
    if(NULL== pData)
    return EEPROMF_ADDR_WRONG;
	
 IIC_FAST_MODE_SET();
    iic_start();
    emResult=iic_send_device_addr(EEPROM_DEVADDR|0);
	if(emResult != IIC_SUCCESS)
		return EEPROM_DEV_ADR_INVALID;
    emResult=iic_send_reg_addr(cAddr);
	if(emResult != IIC_SUCCESS)
		return EEPROM_REG_ADR_INVALID;
    emResult=iic_send(pData, usLen);
	if(emResult != IIC_SUCCESS)
		return EEPROM_WRITE_FAIL;
    iic_stop();
	return EEPROM_SUCCESS;
}

static enum EEPROM_RESULT eeprom_iic_read(char cAddr, char *pData,unsigned short usLen)
{
	enum IIC_RESULT emResult;
    if(NULL== pData)
		return EEPROMF_ADDR_WRONG;
	IIC_FAST_MODE_SET();
    iic_start();
    emResult=iic_send_device_addr(EEPROM_DEVADDR|0);
	if(emResult != IIC_SUCCESS)
		return EEPROM_DEV_ADR_INVALID;
    emResult=iic_send_reg_addr(cAddr);
	if(emResult != IIC_SUCCESS)
		return EEPROM_REG_ADR_INVALID;
    iic_start();
	emResult=iic_send_device_addr(EEPROM_DEVADDR|1);
	if(emResult != IIC_SUCCESS)
		return EEPROM_DEV_ADR_INVALID;
    emResult=iic_read(pData, usLen); 
	if(emResult != IIC_SUCCESS)
		return EEPROM_READ_FAIL;
    iic_stop();
	return EEPROM_SUCCESS;
}

enum EEPROM_RESULT eeprom_write(char cAddr, char *pData,unsigned short usLen)
{ 
	enum EEPROM_RESULT emResult;
	unsigned short usNum;
	char aRxBuf[EEPROM_PAGE_SIZE]={0};
	while(usLen)
	{
		if(cAddr&(EEPROM_PAGE_SIZE-1))
		{
			usNum = EEPROM_PAGE_SIZE - (cAddr&(EEPROM_PAGE_SIZE-1));
		}
		else
		{usNum = EEPROM_PAGE_SIZE;}
		if(usNum>usLen)
		{
			usNum = usLen;
		}
		emResult=eeprom_iic_write(cAddr, pData, usNum); //ҳд
		if( emResult != EEPROM_SUCCESS)
		{
			return EEPROM_FAIL;
		}
		Wdg_Inc(10);
		IIC_DELAY_MS(5);
		emResult=eeprom_iic_read(cAddr, aRxBuf,usNum);
		if( emResult != EEPROM_SUCCESS)
		{
			return EEPROM_FAIL;
		}
		if(memcmp(pData,aRxBuf,usNum))
		{
			return EEPROM_WRITE_FAIL;
		}
		usLen -= usNum;
		cAddr += usNum;
		pData += usNum;  
	}
	return EEPROM_SUCCESS;
}

enum EEPROM_RESULT eeprom_read(char cAddr, char *pData,unsigned short usLen)
{
	enum EEPROM_RESULT emResult;
	emResult=eeprom_iic_read(cAddr, pData,usLen);
	if( emResult != EEPROM_SUCCESS)
	{
		return EEPROM_FAIL;
	}
	return EEPROM_SUCCESS;

}
