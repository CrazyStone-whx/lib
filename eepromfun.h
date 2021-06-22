#ifndef EEPROMFUN_H
#define EEPROMFUN_H

enum EEPROM_DEV_TYPE
{
	DEV_NULL =0,
	DEV_AT24C02,
	DEV_AT24C04,
	DEV_AT24C08,
	
	DEV_AT24C16,
	DEV_AT24C32,
	DEV_AT24C64,
	DEV_AT24C256
};
enum EEPROM_RESULT
{
	EEPROMF_ADDR_WRONG,
	EEPROM_DEV_ADR_INVALID,
	EEPROM_REG_ADR_INVALID,
	EEPROM_WRITE_FAIL,
	EEPROM_READ_FAIL,
	EEPROM_SUCCESS,
	EEPROM_FAIL,
};
#define  EEPROM_DEV  DEV_AT24C02
#if (EEPROM_DEV==DEV_AT24C02)
#define EEPROM_DEVADDR 0xA0
#define EEPROM_PAGE_SIZE 8
#define EEPROM_TOTAL_SIZE 256
#endif
void eeprom_init(void);
enum EEPROM_RESULT eeprom_write(char cAddr, char *pData,unsigned short usLen);
enum EEPROM_RESULT eeprom_read(char cAddr, char *pData,unsigned short usLen);
#endif
