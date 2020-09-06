
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BH1750_H_
#define	BH1750_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/mcc.h"
#include <stdint.h>   
#include "mcc_generated_files/i2c1.h"
#define FCY 60000000UL 
#include <libpic30.h> /*biblioteka dajaca dostepp do delay-i.*/
#include "dogm204.h"


#define BH1750_SLA 	((uint8_t)0x23)

#define BH1750_Power_OFF	((uint8_t)0x00)
#define BH1750_Power_ON		((uint8_t)0x01)
#define BH1750_RESET		((uint8_t)0x07)

/** @ Defgroup: BH1750 measurement modes definition
  */
#define BH1750_CHR_MODE    ((uint8_t)0x10)		/* BH1750 Continuously H-Resolution Mode */
#define BH1750_CHR_MODE2   ((uint8_t)0x11)		/* Continuously H-Resolution Mode2 */
#define BH1750_CLR_MODE    ((uint8_t)0x13)		/* Continuously L-Resolution Mode */
#define BH1750_OTHR_MODE   ((uint8_t)0x20)		/* One Time H-Resolution Mode */
#define BH1750_OTHR_MODE2  ((uint8_t)0x21)		/* One Time H-Resolution Mode2 */
#define BH1750_OTLR_MODE   ((uint8_t)0x23)		/* One Time L-Resolution Mode */


#define BH1750_GENERIC_RETRY_MAX 10
#define BH1750_GENERIC_DEVICE_TIMEOUT 500

typedef uint8_t BH_MODE;
#define BH1750_ONE_TIME_HIGH_RES_MODE 0x20
#define BH1750_ONE_TIME_HIGH_RES_MODE_2 0x21
#define BH1750_ONE_TIME_LOW_RES_MODE 0x23


typedef uint8_t BH_CHANNEL_I2C;
#define BH1750_CH0_I2C 0
#define BH1750_CH1_I2C 1
#define BH1750_CH2_I2C 2
#define BH1750_CH3_I2C 3
#define BH1750_MSSP_I2C 4
#define BH1750_MSSP1_I2C 5
#define BH1750_MSSP2_I2C 6

typedef struct
{
  unsigned char busAddress; ///< Slave Address bits A2, A1
  BH_CHANNEL_I2C channel; ///< I2C channel identifier
  BH_MODE mode; ///< mode read lux for BH1750
  uint16_t lux;
} BH1750_T;


typedef enum
{
    STEP_BH_I2C_MESSAGE_FAIL,           /**< The I2C communication failed.*/
    STEP_BH_I2C_MESSAGE_PENDING,        /**< The I2C communication is stuck. Usually, this is because of wrong MCC settings.*/
    STEP_BH_I2C_MESSAGE_COMPLETE,       /**< The communication was successful.*/
    STEP_BH_I2C_STUCK_START,            /**< Other I2C error*/
    STEP_BH_I2C_MESSAGE_ADDRESS_NO_ACK, /**< Other I2C error*/
    STEP_BH_I2C_DATA_NO_ACK,            /**< Other I2C error*/
    STEP_BH_I2C_LOST_STATE              /**< Other I2C error*/
} ERR_BH_STATUS_T;

extern BH1750_T bh1750;


ERR_BH_STATUS_T BH1750_LuxRead  (BH1750_T * bh1750Instance);


/**
 * \brief Function for initializing lux sensor BH1750
 *
 * @param	[in]	bh1750 instance 		pointer of I2C_BH1750_T type
 * 
 * Example Usage:
 * @code
 * I2C_BH1750_T newBH1750Instance;
 * I2C_BH1750InstanceAppend(&newBH1750Instance, 35, I2C_BH1750_CH1, BH1750_ONE_TIME_LOW_RES_MODE);
 * @endcode
 */
BH1750_T* BH1750_InstanceAppend(BH1750_T *bh1750Instance, uint8_t busAddress, BH_CHANNEL_I2C channel, BH_MODE mode);




void BH1750_PowerOn(BH1750_T *bh1750);



void BH1750_PowerDown(BH1750_T *bh1750);


void BH1750_ResetData(BH1750_T *bh1750);



#endif	/* XC_HEADER_TEMPLATE_H */

