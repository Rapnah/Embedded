/* Learn and write form Library by @eepj*/
/* Github library by @eepj: www.github.com/eepj */
#ifndef DS1307_HAL_H
#define DS1307_HAL_H
#include "main.h"
/*--------------------------------------------------------*/
#define ADDR    0x68 // Address I2C
#define SEC     0x00 // Seccond Time
#define MINS    0x01 // Minute Time
#define HOUR    0x02 // Hour Time 
#define DOW     0x03 // Day of week
#define DATE    0x04
#define MONTH   0x05
#define YEAR    0x06
#define CONTROL 0x07 // Control
#define UTC_HR  0x08
#define UTC_MIN 0x09
#define CENT    0x10
#define RAM     0x11
#define TIMEOUT 1000

/*--------------------------------------------------------*/
extern I2C_HandleTypeDef *_ds1307_ui2c;

typedef enum DS1307_Rate{
    DS1307_1HZ, DS1307_4096HZ, DS1307_8192HZ, DS1307_32768HZ
} DS1307_Rate; //set up rate crystal 

typedef enum DS1307_SWE{
    DS1307_ENABLE, DS1307_DISABLE
} DS1307_SWE; // Set up square wave enable

void DS1307_Init(I2C_HandleTypeDef *hi2c);

void DS1307_SetClockHalt(uint8_t halt);
uint8_t DS1307_GetClockHalt(void);

void DS1307_SetRegByte(uint8_t regAddr, uint8_t val);
uint8_t DS1307_GetRegByte(uint8_t regAddr);

void DS1307_SetEnableSquareWave(DS1307_SWE mode);
void DS1307_SetInterrupRate(DS1307_Rate rate);

uint8_t DS1307_GetDOW(void); // DOW = day of week
uint8_t DS1307_GetDate(void);
uint8_t DS1307_GetMonth(void);
uint16_t DS1307_GetYear(void);

uint8_t DS1307_GetHour(void);
uint8_t DS1307_GetMin(void); // Minute
uint8_t DS1307_GetSec(void); //Second
int8_t DS1307_GetTimeZoneHour(void);
uint8_t DS1307_GetTimeZoneMin(void);

void DS1307_SetHour(uint8_t shour); 
void DS1307_SetMin(uint8_t smin);
void DS1307_SetSec(uint8_t ssec);

void DS1307_SetDOW(uint8_t sdow);
void DS1307_SetDate(uint8_t sdate);
void DS1307_SetMonth(uint8_t smonth);
void DS1307_SetYear(uint16_t syear);
void DS1307_SetTimeZone(int8_t shr, uint8_t mins);

uint8_t DS1307_DecodeBCD(uint8_t bin); // Dec to Bin
uint8_t DS1307_EncodeBCD(uint8_t dec); // Bin to Dec

#endif