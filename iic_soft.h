#ifndef IIC_SOFT_H
#define IIC_SOFT_H


enum IIC_RESULT
{
	IIC_FAIL=0,
	IIC_SUCCESS,
	IIC_ACK,
	IIC_NOACK,	
};
enum IIC_MODE 
{
	IIC_NORMAL_MODE,
	IIC_FAST_MODE,
	IIC_HS_MODE,	
};

extern enum IIC_MODE emIIC_mode;
#define IIC_MODE_SET(mode) emIIC_mode=mode
#define IIC_NORMAL_MODE_SET() IIC_MODE_SET(IIC_NORMAL_MODE)
#define IIC_FAST_MODE_SET() IIC_MODE_SET(IIC_FAST_MODE)
#define IIC_HS_MODE_SET() IIC_MODE_SET(IIC_HS_MODE)

#define IIC_NORMAL_MODE() (IIC_NORMAL_MODE==emIIC_mode)
#define IIC_FAST_MODE() (IIC_FAST_MODE==emIIC_mode)
#define IIC_HS_MODE() (IIC_HS_MODE==emIIC_mode)
void iic_start(void);
void iic_stop(void);
enum IIC_RESULT iic_send_device_addr(char cDevAddr);
enum IIC_RESULT iic_send_reg_addr(char cRegAddr);
enum IIC_RESULT iic_send(char *pData, unsigned short usLen);
enum IIC_RESULT iic_read(char *pData, unsigned short usLen);

#endif
