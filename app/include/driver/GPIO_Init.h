#ifndef __GPIO_INIT__
#define __GPIO_INIT__
#include "c_types.h"
#include "driver/gpio16.h"
#include "../../include/eagle_soc.h"

#define RELAY_PIN_1        12
#define RELAY_FUNC_1 	   FUNC_GPIO12
#define RELAY_MUX_1        PERIPHS_IO_MUX_MTDI_U
#define RELAY_PIN_2        14
#define RELAY_FUNC_2       FUNC_GPIO14
#define RELAY_MUX_2        PERIPHS_IO_MUX_MTMS_U

#define RELAY_ONE    0x01
#define RELAY_TWO    0x02

#define KEY_0_IO_MUX                            PERIPHS_IO_MUX_GPIO0_U      ///< ESP8266 GPIO 鍔熻兘
#define KEY_0_IO_NUM                            0                           ///< ESP8266 GPIO 缂栧彿
#define KEY_0_IO_FUNC                           FUNC_GPIO0                  ///< ESP8266 GPIO 鍚嶇О
//#define KEY_1_IO_MUX                            PERIPHS_IO_MUX_MTMS_U       ///< ESP8266 GPIO 鍔熻兘
//#define KEY_1_IO_NUM                            14                          ///< ESP8266 GPIO 缂栧彿
//#define KEY_1_IO_FUNC                           FUNC_GPIO14                 ///< ESP8266 GPIO 鍚嶇О
#define KEY_1_IO_MUX                            PERIPHS_IO_MUX_GPIO5_U       ///< ESP8266 GPIO 鍔熻兘
#define KEY_1_IO_NUM                            5                          ///< ESP8266 GPIO 缂栧彿
#define KEY_1_IO_FUNC                           FUNC_GPIO5                 ///< ESP8266 GPIO 鍚嶇О



#define FLOW_1_IO_MUX                            PERIPHS_IO_MUX_MTCK_U       ///< ESP8266 GPIO 功能
#define FLOW_1_IO_NUM                            13                          ///< ESP8266 GPIO 编号
#define FLOW_1_IO_FUNC                           FUNC_GPIO13                 ///< ESP8266 GPIO 名称

#define FLOW_3_IO_MUX                            PERIPHS_IO_MUX_GPIO4_U       ///< ESP8266 GPIO 功能
#define FLOW_3_IO_NUM                            4                          ///< ESP8266 GPIO 编号
#define FLOW_3_IO_FUNC                           FUNC_GPIO4                 ///< ESP8266 GPIO 名称

void ICACHE_FLASH_ATTR RELAY_Init(void);
void ICACHE_FLASH_ATTR RELAY_ON(int  RELAY_NUM);
void ICACHE_FLASH_ATTR RELAY_OFF(int RELAY_NUM);



#endif
