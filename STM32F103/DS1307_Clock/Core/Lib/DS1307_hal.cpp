#include "DS1307_hal.h"
#include "main.h"
#ifdef __cplusplus
extern "C"{
    #endif

    I2C_HandleTypeDef *_ds1307_ui2c;

    void DS1307_Init(I2C_HandleTypeDef *hi2c)
    {
        _ds1307_ui2c = hi2c;
        DS1307_SetClockHalt(0);
    }

    void DS1307_SetClockHalt(uint8_t halt)
    {
        uint8_t ch = (halt ? 1 << 7 : 0);
        DS1307_SetRegByte(SEC, ch | (DS1307_GetRegByte(SEC) & 0x7F));
    }

    uint8_t DS1307_GetClockHalt(void)
    {
        return(DS1307_GetRegByte(SEC) & 0x80) >> 7;
    }

    void DS1307_SetRegByte(uint8_t regAddr, uint8_t val)
    {
        uint8_t bytes[2] = {regAddr,val};
        HAL_I2C_Master_Transmit(_ds1307_ui2c, ADDR << 1, bytes, 2, TIMEOUT);
    }  

    uint8_t DS1307_GetRegByte(uint8_t regAddr)
    {
        uint8_t val;
        HAL_I2C_Master_Transmit(_ds1307_ui2c, ADDR << 1, &regAddr, 1, TIMEOUT);
        HAL_I2C_Master_Receive(_ds1307_ui2c, ADDR << 1, &val, 1, TIMEOUT);
        return val;
    }

    void DS1307_SetEnableSquareWave(DS1307_SWE mode)
    {
        uint8_t controlReg = DS1307_GetRegByte(CONTROL);
        uint8_t newcontrolReg = (controlReg & ~(1 << 4)) | ((mode & 1) << 4);
        DS1307_SetRegByte(CONTROL, newcontrolReg);
    }

    void DS1307_SetInterrupRate(DS1307_Rate rate)
    {
        uint8_t controlReg = DS1307_GetRegByte(CONTROL);
        uint8_t newcontrolReg = (controlReg & ~0x03) | rate;
        DS1307_SetRegByte(CONTROL, newcontrolReg);
    }

    uint8_t DS1307_GetDOW(void)
    {
        return DS1307_DecodeBCD(DS1307_GetRegByte(DOW));
    }

    uint8_t DS1307_GetDate(void)
    {
        return DS1307_DecodeBCD(DS1307_GetRegByte(DATE));
    }

    uint8_t DS1307_GetMonth(void)
    {
        return DS1307_DecodeBCD(DS1307_GetRegByte(MONTH));
    }

    uint16_t DS1307_GetYear(void)
    {
        uint16_t cen = DS1307_GetRegByte(CENT) * 100;
        return DS1307_DecodeBCD(DS1307_GetRegByte(YEAR)) + cen;
    }

    uint8_t DS1307_GetHour(void)
    {
        return DS1307_DecodeBCD(DS1307_GetRegByte(HOUR) & 0x3F);
    }

    uint8_t DS1307_GetMin(void)
    {
        return DS1307_DecodeBCD(DS1307_GetRegByte(MINS));
    }

    int8_t DS1307_GetTimeZoneHour(void) 
    {
	return DS1307_GetRegByte(UTC_HR);
    }

    uint8_t DS1307_GetTimeZoneMin(void)
    {
	return DS1307_GetRegByte(UTC_MIN);
    }

    uint8_t DS1307_GetSec(void)
    {
        return DS1307_DecodeBCD(DS1307_GetRegByte(SEC) & 0x7F);
    }

    void DS1307_SetDOW(uint8_t sdow) // sdow = set day of week
    {
        DS1307_SetRegByte(DOW, DS1307_EncodeBCD(sdow));
    }

    void DS1307_SetMonth(uint8_t smonth)
    {
        DS1307_SetRegByte(MONTH, DS1307_EncodeBCD(smonth));
    }

    void DS1307_SetDate(uint8_t sdate)
    {
        DS1307_SetRegByte(DATE, DS1307_EncodeBCD(sdate));
    }

    void DS1307_SetYear(uint16_t syear)
    {
        DS1307_SetRegByte(CENT, syear / 100);
        DS1307_SetRegByte(YEAR, DS1307_EncodeBCD(syear % 100));
    }

    void DS1307_SetHour(uint8_t shour)
    {
        DS1307_SetRegByte(HOUR, DS1307_EncodeBCD(shour));
    }

    void DS1307_SetMin(uint8_t smin)
    {
        DS1307_SetRegByte(MINS, DS1307_EncodeBCD(smin));
    }

    void DS1307_SetSec(uint8_t ssec)
    {
        uint8_t ch = DS1307_GetClockHalt();
        DS1307_SetRegByte(SEC, DS1307_EncodeBCD(ssec | ch ));
    }

    void DS1307_SetTimeZone(int8_t shr, uint8_t mins) {
	    DS1307_SetRegByte(UTC_HR, shr);
	    DS1307_SetRegByte(UTC_MIN, mins);
    }

    uint8_t DS1307_DecodeBCD(uint8_t bin)
    {
        return(((bin & 0xF0) >> 4) * 10) + (bin & 0x0F);
    }

    uint8_t DS1307_EncodeBCD(uint8_t dec)
    {
        return (dec % 10 + ((dec / 10) << 4));
    }

    #ifdef __cplusplus
}
#endif
