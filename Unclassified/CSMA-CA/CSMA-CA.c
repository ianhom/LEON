/******************************************************************************
* file ：CSMA-CA.c
* Brief ：802.15.4 CSMA-CA algorithm - Ver. Beta
* Version：V0.10
* Author ：Ian
* Date ：2015年3月19日
* History：     Date     Editor Version    Record
            2015-03-19    Ian    V0.10     Create, only CSMA-CA without
                                           time slots is realized.
******************************************************************************/

#include "common.h"
#include "csma_ca.h"

static T_CSMA_CA_DATA *sg_ptCsma = {NULL}; /* Pointer for CSMA-CA data struct */

/*************************************************************************
* Function ：RESULT CSMA_CA_Init(T_CSMA_CA_DATA* ptCsma)
* Description ：Init CSMA-CA, Get & check necessary data struct
* Input Param ：T_CSMA_CA_DATA* ptCsma Data struct for CSMA-CA
* Output Param：None
* Return ：SW_ERR: Failed operation
                SW_OK : Successful operation
**************************************************************************/
RESULT CSMA_CA_Init(T_CSMA_CA_DATA* ptCsma)
{
    if ((NULL == ptCsma)\
      ||(NULL == ptCsma->pfCCA)\
      ||(NULL == ptCsma->pfRandom)) /* If the pointer is invalid, or if CCA/Random is not available */
    {
        return SW_ERR; /* return error */
    }
        
    sg_ptCsma = ptCsma; /* Get the data struct for the module */
    return SW_OK;
}

/*************************************************************************
* Function ：RESULT CSMA_CA()
* Description ：Perform CSMA-CA, check a channel is available or not
* Input Param ：None
* Output Param：None
* Return ：SW_ERR: Failed operation
                SW_OK : Successful operation
**************************************************************************/
RESULT CSMA_CA()
{
    uint8_t ucBE,ucNB,ucRand,ucChClr;
    switch(sg_ptCsma->ucSlotted) /* Check if it is slotted mode of csma */
    {
        case CSMA_CA_WITH_SLOTTED: /* If it is slotted mode */
        {
            /* To be continued.. */
            break;
            
        }
        case CSMA_CA_WITHOUT_SLOTTED: /* If it is not slotted mode */
        {
            ucNB = 0; /* Set init value of NB */
            ucBE = MAC_BE_MIN; /* Set init value of BE */
            
            for (;ucNB <= MAC_NB_MAX;)/* If Number of backoff does not reach MAX.*/
            {
                ucRand = sg_ptCsma->pfRandom()%((1<<ucBE)-1); /* Get Random uint backoff delay */
                printf("Random value is %d , Max value is %d\n",ucRand, ((1<<ucBE) -1));
                CSMA_Backoff_Delay(ucRand); /* Delay random uint backoff period */
                ucChClr = sg_ptCsma->pfCCA(); /* Perform a CCA */
    
                if (CHANNEL_CLR == ucChClr) /* If the channel is clear */
                {
                    printf("CSMA-CA is ok!\n");
                    return SW_OK; /* Get the channel */
                }
                else /* If the channel is busy */
                {
                    ucNB++; /* Update NB value */
                    ucBE++; /* Update BE value */
                    ucBE = ((ucBE<MAC_BE_MAX)?ucBE : MAC_BE_MAX); /* Get the Min. value*/
                    printf("CSMA-CA is trying!, NB=%d, BE=%d\n",ucNB,ucBE);
                }
            }
            printf("CSMA-CA is failed!\n");
            return SW_ERR; /* Max number of backoff is over, fail to get clear channel */
            break;
        }
        default: /* Invalid mode */
        {
            break;
        }
    }
    return SW_ERR; /* failed operation */
}


/*************************************************************************
* Function ：void CSMA_Backoff_Delay(uint8_t ucNum)
* Description ：Perform CSMA-CA Backoff
* Input Param ：uint8_t ucNum Number of backoff period
* Output Param：None
* Return ：None
**************************************************************************/
void CSMA_Backoff_Delay(uint8_t ucNum)
{
    if(0 == ucNum)
    {
        return; /* if the number of backoff unit is 0, no delay is needed */
    }
    else
    {
        Delay_ns(ucNum*BACKOFF_PERIOD_IN_US);
    }
    return;
}

/*************************************************************************
* Function ：void Delay_ns(uint16_t ucNum)
* Description ：Wait for ucNum of backoff period
* Input Param ：uint8_t ucNum Number of backoff period
* Output Param：None
* Return ：None
**************************************************************************/
void Delay_ns(uint16_t ucNum)
{
    uint16_t wTemp;
    
    for (wTemp = 0; wTemp < ucNum; wTemp++)
    {
        ; /* Just wait */
    }
    return;
}

/* End of file */
