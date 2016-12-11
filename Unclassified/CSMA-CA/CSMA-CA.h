/******************************************************************************
* file   ：CSMA-CA.h
* Brief  ：Header file of 802.15.4 CSMA-CA algorithm - Ver. Beta
* Version：V0.10
* Author ：Ian
* Date   ：19th Mar 2015
* History：    Date      Editor Version         Record
             2015-03-19   Ian    V0.10    Create, only CSMA-CA without
                                          time slots is realized.
******************************************************************************/
#ifndef _CSMA_CS_H_
#define _CSMA_CS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define CSMA_CA_WITH_SLOTTED    (1)  /* CSMA-CA with time slott mode      */
#define CSMA_CA_WITHOUT_SLOTTED (0)  /* CSMA-CA with no time slott mode   */
#define MAC_BE_MIN              (3)  /* Min. value of Backoff Exponent    */
#define MAC_BE_MAX              (5)  /* Max. value of Backoff Exponent    */
#define MAC_NB_MAX              (4)  /* Max. number of Backoff            */
#define CHANNEL_BUSY            (0)  /* Indicate that channel is busy     */
#define CHANNEL_CLR             (1)  /* Indicate that channel is clear    */
#define BACKOFF_PERIOD_IN_US    (20) /* Backoff time in us                */
#define SW_OK                   (0)  /* Successful operation              */
#define SW_ERR                  (-1) /* Successful operation              */
#define BATTERY_EXTENSION_EN    (1)  /* Battery life extension is enable  */
#define BATTERY_EXTENSION_DIS   (0)  /* Battery life extension is disable */


typedef unsigned char CSMA_CA_MODE; /* Mode type of csma-ca */
typedef int RESULT;                 /* Result of function   */

typedef struct _CSMA_CA_
{
    CSMA_CA_MODE ucSlotted;     /* CSAM-CA mode: Time slotted or non-slotted */
    uint8_t ucBatteryExtension; /* Use batteryExtension or not               */
    uint8_t (*pfCCA)(void);     /* CCA performing function interface         */
    uint8_t (*pfRandom)(void);  /* Random function interface                 */
}T_CSMA_CA_DATA;

/*************************************************************************
* Function    ：RESULT CSMA_CA_Init(T_CSMA_CA_DATA* ptCsma)
* Description ：Init CSMA-CA, Get & check necessary data struct
* Input Param ：T_CSMA_CA_DATA* ptCsma Data struct for CSMA-CA
* Output Param：None
* Return      ：SW_ERR: Failed operation
                SW_OK : Successful operation
**************************************************************************/
RESULT CSMA_CA_Init(T_CSMA_CA_DATA* ptCsma);

/*************************************************************************
* Function    ：RESULT CSMA_CA()
* Description ：Perform CSMA-CA, check a channel is available or not
* Input Param ：None
* Output Param：None
* Return      ：SW_ERR: Failed operation
                SW_OK : Successful operation
**************************************************************************/
RESULT CSMA_CA();

/*************************************************************************
* Function    ：void CSMA_Backoff_Delay(uint8_t ucNum)
* Description ：Perform CSMA-CA Backoff
* Input Param ：uint8_t ucNum Number of backoff period
* Output Param：None
* Return      ：None
**************************************************************************/
void CSMA_Backoff_Delay(uint8_t ucNum);

/*************************************************************************
* Function    ：void Delay_ns(uint16_t ucNum)
* Description ：Wait for ucNum of backoff period
* Input Param ：uint8_t ucNum Number of backoff period
* Output Param：None
* Return      ：None
**************************************************************************/
void Delay_ns(uint16_t ucNum);


#ifdef __cplusplus
}
#endif

#endif /* _CSMA_CA_H_ */

