#include "driver/GPIO_Init.h"
#include "stdio.h"
#include "c_types.h"
#include "driver/gpio16.h"
#include "../../include/eagle_soc.h"
#include "gpio.h"




void ICACHE_FLASH_ATTR
RELAY_Init(void)
{
	PIN_FUNC_SELECT(RELAY_MUX_1,RELAY_FUNC_1);
	PIN_FUNC_SELECT(RELAY_MUX_2,RELAY_FUNC_2);
}
void ICACHE_FLASH_ATTR
RELAY_ON(int  RELAY_NUM)
{
	switch(RELAY_NUM)
	{
	case RELAY_ONE:
	GPIO_OUTPUT_SET(GPIO_ID_PIN(RELAY_PIN_1),1);
	break;
	case RELAY_TWO:
	GPIO_OUTPUT_SET(GPIO_ID_PIN(RELAY_PIN_2),1);
	break;
	}
}
void ICACHE_FLASH_ATTR
RELAY_OFF(int RELAY_NUM)
{
	switch(RELAY_NUM)
	{
	case RELAY_ONE:
	GPIO_OUTPUT_SET(GPIO_ID_PIN(RELAY_PIN_1),0);
	break;
	case RELAY_TWO:
	GPIO_OUTPUT_SET(GPIO_ID_PIN(RELAY_PIN_2),0);
	break;
	}
}

