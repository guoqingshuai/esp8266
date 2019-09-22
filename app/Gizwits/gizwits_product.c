/**
************************************************************
* @file         gizwits_product.c
* @brief        Control protocol processing, and platform-related hardware initialization
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"
#include "driver/hal_key.h"
#include "driver/GPIO_Init.h"
protocolTime_t protocolTime;
/** User area The current device state structure */

uint16_t GPIO_ADC;
uint16_t GPIO_16;
uint16_t GPIO_FLOW_1_IO_NUM;

uint32_t realPulse;
uint32_t totalPulse;


dataPoint_t currentDataPoint;

/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t ICACHE_FLASH_ATTR gizwitsEventProcess(eventInfo_t *info, uint8_t *data, uint32_t len)
{
    uint8_t i = 0;
    dataPoint_t * dataPointPtr = (dataPoint_t *)data;
    moduleStatusInfo_t * wifiData = (moduleStatusInfo_t *)data;

    if((NULL == info) || (NULL == data))
    {
        GIZWITS_LOG("!!! gizwitsEventProcess Error \n");
        return -1;
    }

    for(i = 0; i < info->num; i++)
    {
        switch(info->event[i])
        {
        case EVENT_Motor :
            currentDataPoint.valueMotor = dataPointPtr->valueMotor;
            GIZWITS_LOG("Evt: EVENT_Motor %d \n", currentDataPoint.valueMotor);
            if(0x01 == currentDataPoint.valueMotor)
            {      
              
            RELAY_ON(RELAY_TWO); 
                //user handle
            }
            else
            {
               
            RELAY_OFF(RELAY_TWO);           
                //user handle
            }
            break;
			        case EVENT_Motor_Spare :
            currentDataPoint.valueMotor_Spare = dataPointPtr->valueMotor_Spare;
            GIZWITS_LOG("Evt: EVENT_Motor_Spare %d \n", currentDataPoint.valueMotor_Spare);
            if(0x01 == currentDataPoint.valueMotor_Spare)
            {
                //user handle

            RELAY_ON(RELAY_ONE);
            }
            else
            {
            RELAY_OFF(RELAY_ONE);
             //user handle
            }
            break;
        case EVENT_Flow_clean :
            currentDataPoint.valueFlow_clean = dataPointPtr->valueFlow_clean;
            GIZWITS_LOG("Evt: EVENT_Flow_clean %d \n", currentDataPoint.valueFlow_clean);
            if(0x01 == currentDataPoint.valueFlow_clean)
            {
                totalPulse=0;

            }
            else
            {
                totalPulse=0;
                //user handle
            }
            break;
        case WIFI_SOFTAP:
            break;
        case WIFI_AIRLINK:
            break;
        case WIFI_STATION:
            break;
        case WIFI_CON_ROUTER:
            GIZWITS_LOG("@@@@ connected router\n");
 
            break;
        case WIFI_DISCON_ROUTER:
            GIZWITS_LOG("@@@@ disconnected router\n");
 
            break;
        case WIFI_CON_M2M:
            GIZWITS_LOG("@@@@ connected m2m\n");
			setConnectM2MStatus(0x01);
 
            break;
        case WIFI_DISCON_M2M:
            GIZWITS_LOG("@@@@ disconnected m2m\n");
			setConnectM2MStatus(0x00);
 
            break;
        case WIFI_RSSI:
            GIZWITS_LOG("@@@@ RSSI %d\n", wifiData->rssi);
            break;
        case TRANSPARENT_DATA:
            GIZWITS_LOG("TRANSPARENT_DATA \n");
            //user handle , Fetch data from [data] , size is [len]
            break;
        case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
            break;
            
        default:
            break;
        }
    }
    system_os_post(USER_TASK_PRIO_2, SIG_UPGRADE_DATA, 0);
    
    return 0; 
}


/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void ICACHE_FLASH_ATTR userHandle(void)
{
// gpio 16  高
// gpio adc 中
// gpio13 底
    GIZWITS_LOG("FLOW_1_IO_NUM=%d\n",GPIO_FLOW_1_IO_NUM);
    GIZWITS_LOG("ADC=%d\n",system_adc_read());
    GIZWITS_LOG("gpio16=%d\n",gpio16InputGet()); 
   if((GPIO_FLOW_1_IO_NUM==0)&&(GPIO_ADC<10)&&(GPIO_16==0))
   {
    currentDataPoint.valueLiquid=3;  
   }else
   {
    if(1==GPIO_FLOW_1_IO_NUM)
    {
     currentDataPoint.valueLiquid=2;
     if(GPIO_ADC>10)
     {
      currentDataPoint.valueLiquid=1;
      if(1==GPIO_16)
      {
       currentDataPoint.valueLiquid=0;
      }
     }   
    }
   }
   GIZWITS_LOG("currentDataPoint.valueLiquid=%d\n",currentDataPoint.valueLiquid);
   GIZWITS_LOG("totalPulse=%d\n",totalPulse);  
   GIZWITS_LOG("realPulse=%d\n",realPulse);  
    currentDataPoint.valuecumulative_flow = totalPulse/300;//累计流量
    protocolTime=gizwitsGetNTPTime();
    if(0==protocolTime.second%10)
    {
      currentDataPoint.valueSpeed=(realPulse/10.0)*3.33;//实时流量
      realPulse=0;
    }
    // GIZWITS_LOG("year=%d.month=%d.day=%d.hour=%d.minute=%d.second=%d\n",protocolTime.year,
    //                                                                     protocolTime.month,
    //                                                                     protocolTime.day,
    //                                                                     protocolTime.hour,
    //                                                                     protocolTime.minute,
    //                                                                     protocolTime.second
    //                                                                     );
system_os_post(USER_TASK_PRIO_2, SIG_UPGRADE_DATA, 0);
}

void ICACHE_FLASH_ATTR inputHandle(void)
{
    GPIO_ADC          =  system_adc_read();
    GPIO_16           =  gpio16InputGet();
    GPIO_FLOW_1_IO_NUM=  GPIO_INPUT_GET(GPIO_ID_PIN(FLOW_1_IO_NUM));
    

}


/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void ICACHE_FLASH_ATTR userInit(void)
{
    gizMemset((uint8_t *)&currentDataPoint, 0, sizeof(dataPoint_t));

 	/** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
   		currentDataPoint.valueMotor = ;
   		currentDataPoint.valueMotor_Spare = ;
   		currentDataPoint.valueFlow_clean = ;
   		currentDataPoint.valueLiquid = ;
   		currentDataPoint.valueSpeed = ;
   		currentDataPoint.valuecumulative_flow = ;
    */
}


