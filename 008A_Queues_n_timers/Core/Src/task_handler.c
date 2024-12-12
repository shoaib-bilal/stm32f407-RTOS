/*
 * task_handler.c
 *
 *  Created on: Dec 9, 2024
 *      Author: shoai
 */

#include"main.h"

void process_command(command_t *cmd);
int extract_command(command_t *cmd);

const char* msg_inv= "////Invalid option/////\n";
void menu_handler(void *parameters)
{

	uint32_t cmd_addr;
	command_t *cmd;
	int option;
	const char* msg_menu= "========================|\n"
						 "|         msg_menu       |\n"
						 "==========================\n"
			    		    "Led Effect    ---->0   \n"
			    		    "Date and time ---->1   \n"
							"Exit          ---->2   \n"
							"Enter your choice here:";



	while(1)
	{
		xQueueSend(q_print, &msg_menu, portMAX_DELAY);
		xTaskNotifyWait(0,0,&cmd_addr,portMAX_DELAY);

		cmd=(command_t*)cmd_addr;

		if(cmd->len ==1)
		{
			option=cmd->payload[0]-48;
			switch(option)
			{
			case 0:
				current_state=sLedEffect;
				xTaskNotify(led_handle,0,eNoAction);
				break;
			case 1:
				current_state=sRtcMenu;
				xTaskNotify(rtc_handle,0,eNoAction);
				break;

			case 2:
				break;
			default:
				xQueueSend(q_print,&msg_inv, portMAX_DELAY);
				continue;
			}

		}
		else
		{
			xQueueSend(q_print,&msg_inv, portMAX_DELAY);
			continue;
		}
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
	}
}
void cmd_handler(void *parameters)
{
command_t cmd;

BaseType_t ret;

	while(1)
	{
		ret= xTaskNotifyWait(0,0,NULL,portMAX_DELAY);

		if (ret == pdTRUE )
		{
		process_command(&cmd);
		}
	}
}

void process_command(command_t *cmd)
{
	extract_command(cmd);

	switch(current_state)
	{
	case sMainmenu:
		xTaskNotify(menue_handle,(uint32_t)cmd,eSetValueWithOverwrite);
		break;

	case sLedEffect:
		xTaskNotify(led_handle,(uint32_t)cmd,eSetValueWithOverwrite);
		break;

	case sRtcMenu:
		xTaskNotify(rtc_handle,(uint32_t)cmd,eSetValueWithOverwrite);
		break;

	case sRtcTimeConfig:
		xTaskNotify(rtc_handle,(uint32_t)cmd,eSetValueWithOverwrite);
		break;
	case SRtcDataConfig:
		xTaskNotify(rtc_handle,(uint32_t)cmd,eSetValueWithOverwrite);
		break;
	case sRtcReport:
		xTaskNotify(rtc_handle,(uint32_t)cmd,eSetValueWithOverwrite);
		break;
	}

}

int extract_command(command_t *cmd)
{

	BaseType_t status;
	uint8_t item;

	status= uxQueueMessagesWaiting(q_data);

	if(!status)
		return -1;


	uint8_t i=0;

	do{
		status=xQueueReceive(q_data, &item, portMAX_DELAY);
		if (status==pdTRUE)
		{
			cmd->payload[i++]= item;
		}


	}while(item !='\n');

	cmd->payload[i-1]= '\0';

	cmd->len= i-1;

	return 0;

}

void led_handler(void *parameters)
{
	uint32_t cmd_addr;
	command_t *cmd;

	const char* led_msg= "======================\n"
						 "|      Led menue     |\n"
						 "======================\n"
						 "   none-------->none  \n"
						 "   Led effect1 -->e1  \n"
						 "   Led effect2 --->e2 \n"
			 	 	     "   Led effect3 --->e3 \n"
			             "   Led effect4 --->e4 \n"
						 " Enter your choice here:";

	while(1)
	{
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
		xQueueSend(q_print,&led_msg,portMAX_DELAY);
		xTaskNotifyWait(0,0,&cmd_addr,portMAX_DELAY);

		cmd=(command_t*)cmd_addr;

		if(cmd->len <=4)
		{
			if(! strcmp( (char*)cmd->payload,"none"))
				led_effect_stop();
			else if(! strcmp( (char*)cmd->payload,"e1"))
				led_effect(1);
			else if (! strcmp( (char*)cmd->payload,"e2"))
				led_effect(2);
			else if(! strcmp( (char*)cmd->payload,"e3"))
				led_effect(3);
			else if (! strcmp( (char*)cmd->payload,"e4"))
				led_effect(4);
			else
				xQueueSend(q_print,&msg_inv, portMAX_DELAY);
		}
		else
		{
			xQueueSend(q_print,&msg_inv, portMAX_DELAY);
		}
		current_state=sMainmenu;

		xTaskNotify(menue_handle,0,eNoAction);

	}

}
/*
void rtc_handler(void *parameters)
{
	while(1)
	{


	}

}
*/
void print_handler(void *parameters)
{

	uint32_t *msg;
	while(1)
	{
		xQueueReceive(q_print, &msg, portMAX_DELAY);
		HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen((char*)msg), HAL_MAX_DELAY);

	}
}
