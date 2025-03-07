/*
 * handler.c
 *
 *  Created on: Dec 4, 2024
 *      Author: shoai
 */
#include"main.h"


int extract_command(command_t *cmd);
void process_command(command_t *cmd);


const char* msg_inv= "////Invalid option/////\n";

void menu_task(void *parameters)
{
	uint32_t cmd_addr;
	command_t *cmd;
	int option;
	const char* msg_menu = "===========================\n"
							"|           Menu           |\n"
							"==========================\n"
			                    "LED Effect     ----> 0\n"
							    "Date and time  ----> 1\n"
								"Exit           ----> 2\n"
								"Enter your choice here : ";
	while(1)
	{
		xQueueSend(q_print,&msg_menu,portMAX_DELAY);

		xTaskNotifyWait(0,0,&cmd_addr,portMAX_DELAY);
		cmd= (command_t*)cmd_addr;

		if (cmd->Len ==1)
		{
			option= cmd->payload[0] - 48;
			switch(option)
			{
			case 0:
				current_state=sLedEffect;
				xTaskNotify(handle_led_task,0,eNoAction);
				break;
			case 1:
				current_state=sRtcMenu;
				xTaskNotify(handle_rtc_task,0,eNoAction);
				break;
			case 2:		//implement exit
				break;
			default:
				xQueueSend(q_print,&msg_inv,portMAX_DELAY);
				continue;
			}
		}
		else
		{
			//invalid entry
			xQueueSend(q_print,&msg_inv,portMAX_DELAY);
			continue;

		}

		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
	}

}
void cmd_handler_task(void *parameters)
{

	BaseType_t ret;
	command_t cmd;
	while(1)
	{
		ret=xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
		if (ret==pdTRUE)
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
		xTaskNotify(handle_menu_task,(uint32_t)cmd,eSetValueWithOverwrite);
	    break;
	case sLedEffect:
		xTaskNotify(handle_led_task,(uint32_t)cmd,eSetValueWithOverwrite);
	    break;
	case sRtcMenu:
		xTaskNotify(handle_rtc_task,(uint32_t)cmd,eSetValueWithOverwrite);
	    break;

	case sRtcTimeConfig:
		xTaskNotify(handle_rtc_task,(uint32_t)cmd,eSetValueWithOverwrite);
	    break;
	case SRtcDataConfig:
		xTaskNotify(handle_rtc_task,(uint32_t)cmd,eSetValueWithOverwrite);
	    break;
	case sRtcReport:
		xTaskNotify(handle_rtc_task,(uint32_t)cmd,eSetValueWithOverwrite);
	    break;
	}

}

int extract_command(command_t *cmd)
{
	BaseType_t status;
	uint8_t item;

	status= uxQueueMessagesWaiting(q_data);
	if (!status)
		return -1;

	uint8_t i=0;
	do{

	status= xQueueReceive(q_data, &item, 0);
	if (status==pdTRUE)
		cmd->payload[i++]=item;
	}
	while(item != '\n');

	cmd->payload[i-1]= '\0';
	cmd->Len=i-1;

	return 0;
}

void print_task(void *parameters)
{
	uint32_t *msg;
	while(1)
	{
		xQueueReceive(q_print, &msg, portMAX_DELAY);
		HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen((char*)msg), HAL_MAX_DELAY);

	}
}
void led_task(void *parameters)
{
	command_t *cmd;
	uint32_t cmd_addr;
	const char* msg_led= "=======================\n"
						"|      LED Effect      |\n"
						"========================\n"
						"  none ---------->0     \n"
						" Led effect1 ---->1     \n"
						" Led effect2 ---->2     \n"
						" Led effect3 ---->3     \n"
						" Led effect4 ---->4     \n"
						"Enter your choice here : ";
	while(1)
	{
		xTaskNotifyWait(0,0,NULL, portMAX_DELAY);
		xQueueSend(q_print,&msg_led,portMAX_DELAY);
		xTaskNotifyWait(0,0,&cmd_addr,portMAX_DELAY);

		cmd=(command_t*)cmd_addr;

		if(cmd->Len <=4)
		{
			if (! strcmp ((char*)cmd->payload, "none"))
				led_effect_stop();
			else if (! strcmp ((char*)cmd->payload, "e1"))
				led_effect(1);
			else if (! strcmp ((char*)cmd->payload, "e2"))
				led_effect(2);
			else if (! strcmp ((char*)cmd->payload, "e3"))
				led_effect(3);
			else if (! strcmp ((char*)cmd->payload, "e4"))
				led_effect(4);
			else
				xQueueSend(q_print,&msg_inv,portMAX_DELAY);
		}
		else
			xQueueSend(q_print,&msg_inv,portMAX_DELAY);

		current_state= sMainmenu;

		xTaskNotify(handle_menu_task,0,eNoAction);

	}
}

/*
void rtc_task(void *parameters)
{

}
*/
