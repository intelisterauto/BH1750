/*
 * File:   bh1750.c
 * Author: automatyk
 *
 * Created on April 13, 2020, 11:06 AM
 */


#include "xc.h"
#include "mcc_generated_files/i2c1.h"
#include "bh1750.h"


//uint8_t state_;
//uint8_t mode_;

uint8_t bh1750Buffer[64];



void I2CxBH_MasterWrite(BH1750_T * bh1750Instance, uint8_t *data, uint8_t size, uint8_t busAddress, ERR_BH_STATUS_T *pstatus)
{   
    switch(bh1750Instance->channel){
        case BH1750_CH0_I2C:
        break;
        
        case BH1750_CH1_I2C:
            I2C1_MasterWrite(data, size, busAddress,((I2C1_MESSAGE_STATUS *)pstatus));
        break;
        
        case BH1750_CH2_I2C:
        break;
        
        case BH1750_CH3_I2C:
        break;
        
        case BH1750_MSSP_I2C:
        break;

        case BH1750_MSSP1_I2C:
        break;

        case BH1750_MSSP2_I2C:
        break;
    }      
}

void I2CxBH_MasterRead(BH1750_T * bh1750Instance, uint8_t *data, uint8_t size, uint8_t busAddress, ERR_BH_STATUS_T *pstatus)
{
    switch(bh1750Instance->channel){
        case BH1750_CH0_I2C:
        break;
        
        case BH1750_CH1_I2C:
            I2C1_MasterRead(data, size, busAddress,((I2C1_MESSAGE_STATUS *)pstatus));
        break;
        
           case BH1750_CH2_I2C:
        break;
        
        case BH1750_CH3_I2C:
        break;
        
        case BH1750_MSSP_I2C:
        break;

        case BH1750_MSSP1_I2C:
        break;

        case BH1750_MSSP2_I2C:
        break;
    }  
}


ERR_BH_STATUS_T BH1750_LuxRead  (BH1750_T * bh1750Instance)
{
   
    uint16_t    timeOut, slaveTimeOut;
    uint32_t result;

    bh1750Buffer[0] = bh1750Instance->mode;

    timeOut = 0;
    slaveTimeOut = 0;
    
    ERR_BH_STATUS_T status = STEP_BH_I2C_MESSAGE_PENDING;
   
    
    while(status != STEP_BH_I2C_MESSAGE_FAIL)
    {
        I2CxBH_MasterWrite(bh1750Instance,  bh1750Buffer, 1, bh1750Instance->busAddress, &status);
        
        while(status == STEP_BH_I2C_MESSAGE_PENDING)
        {               
            if (slaveTimeOut == BH1750_GENERIC_DEVICE_TIMEOUT)
                break;
            else
                slaveTimeOut++;
            
        } 
        if ((slaveTimeOut == BH1750_GENERIC_DEVICE_TIMEOUT) || 
            (status == STEP_BH_I2C_MESSAGE_COMPLETE))
           
            break;
        if (timeOut == BH1750_GENERIC_RETRY_MAX)
            return STEP_BH_I2C_MESSAGE_FAIL;
        else
            timeOut++;
    }
    
    if (status == STEP_BH_I2C_MESSAGE_COMPLETE)
    {
       
        timeOut = 0;
        slaveTimeOut = 0;
        
        while(status != STEP_BH_I2C_MESSAGE_FAIL)
        {           
            I2CxBH_MasterRead(bh1750Instance, bh1750Buffer, 2,  bh1750Instance->busAddress, &status);
            while(status == STEP_BH_I2C_MESSAGE_PENDING)
            {
                if (slaveTimeOut == BH1750_GENERIC_DEVICE_TIMEOUT)
                    return (0);
                else
                    slaveTimeOut++;
            }
            if (status == STEP_BH_I2C_MESSAGE_COMPLETE)
   
            result = ((bh1750Buffer[0] << 8) | bh1750Buffer[1]) * 10;	//Lux = Register / 1,2 == reg*10 / 12
            
            bh1750Instance->lux = (uint16_t)(result / 12);
  
                break;  
                
            if (timeOut == BH1750_GENERIC_RETRY_MAX)
                break;
            else
                timeOut++;
        }
    }
    
    return status;
}  



BH1750_T* BH1750_InstanceAppend(BH1750_T * bh1750Instance, uint8_t busAddress, BH_CHANNEL_I2C channel, BH_MODE mode)
{    
    bh1750Instance->busAddress=busAddress;
    bh1750Instance->channel=channel;
    bh1750Instance->mode=mode;
    return bh1750Instance;
}


void BH1750_PowerOn(BH1750_T *bh1750Instance)
{
    uint16_t    timeOut, slaveTimeOut;
  
    timeOut = 0;
    slaveTimeOut = 0;
    bh1750Buffer[0] = BH1750_Power_ON;
            
        ERR_BH_STATUS_T status = STEP_BH_I2C_MESSAGE_PENDING;
           
    
    while(status != STEP_BH_I2C_MESSAGE_FAIL)
    {
        I2CxBH_MasterWrite(bh1750Instance,  bh1750Buffer, 1, bh1750Instance->busAddress, &status);
        
        while(status == STEP_BH_I2C_MESSAGE_PENDING)
        {               
            if (slaveTimeOut == BH1750_GENERIC_DEVICE_TIMEOUT)
                break;
            else
                slaveTimeOut++;
            
        } 
        if ((slaveTimeOut == BH1750_GENERIC_DEVICE_TIMEOUT) || 
            (status == STEP_BH_I2C_MESSAGE_COMPLETE))
           
            break;
        if (timeOut == BH1750_GENERIC_RETRY_MAX)
            return STEP_BH_I2C_MESSAGE_FAIL;
        else
            timeOut++;
    }
}

void BH1750_PowerDown(BH1750_T *bh1750Instance)
{
    uint16_t    timeOut, slaveTimeOut;
  
    timeOut = 0;
    slaveTimeOut = 0;
    bh1750Buffer[0] = BH1750_Power_OFF;
            
           ERR_BH_STATUS_T status = STEP_BH_I2C_MESSAGE_PENDING;
           
            
        while(status != STEP_BH_I2C_MESSAGE_FAIL)
    {
        I2CxBH_MasterWrite(bh1750Instance,  bh1750Buffer, 1, bh1750Instance->busAddress, &status);
          
        while(status == STEP_BH_I2C_MESSAGE_PENDING)
        {               
            if (slaveTimeOut == BH1750_GENERIC_DEVICE_TIMEOUT)
                break;
            else
               
                slaveTimeOut++; 
        } 
        if ((slaveTimeOut == BH1750_GENERIC_DEVICE_TIMEOUT) || 
            (status == STEP_BH_I2C_MESSAGE_COMPLETE))

            break;
        if (timeOut == BH1750_GENERIC_RETRY_MAX)
            return STEP_BH_I2C_MESSAGE_FAIL;
        else
            timeOut++;
    }   
}


void BH1750_ResetData(BH1750_T *bh1750Instance)
{
    uint16_t    timeOut, slaveTimeOut;
  
    timeOut = 0;
    slaveTimeOut = 0;
    bh1750Buffer[0] = BH1750_RESET;
            
           ERR_BH_STATUS_T status = STEP_BH_I2C_MESSAGE_PENDING;
           
            
        while(status != STEP_BH_I2C_MESSAGE_FAIL)
    {
        I2CxBH_MasterWrite(bh1750Instance,  bh1750Buffer, 1, bh1750Instance->busAddress, &status);
          
        while(status == STEP_BH_I2C_MESSAGE_PENDING)
        {               
            if (slaveTimeOut == BH1750_GENERIC_DEVICE_TIMEOUT)
                break;
            else
              
                slaveTimeOut++; 
        } 
        if ((slaveTimeOut == BH1750_GENERIC_DEVICE_TIMEOUT) || 
            (status == STEP_BH_I2C_MESSAGE_COMPLETE))
            
            BH1750_PowerDown(bh1750Instance);// Power down

            break;
        if (timeOut == BH1750_GENERIC_RETRY_MAX)
            return STEP_BH_I2C_MESSAGE_FAIL;
        else
            timeOut++;
    }   
}