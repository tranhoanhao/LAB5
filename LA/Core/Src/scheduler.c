/*
 * scheduler.c
 *
 *  Created on: Nov 26, 2023
 *      Author: haoha
 */


#include "scheduler.h"

 sTask SCH_tasks_G[SCH_MAX_TASKS];
//static uint8_t array_Of_Task_ID[SCH_MAX_TASKS];
//static uint32_t newTaskID = 0;
//static uint32_t rearQueue = 0;
//static uint32_t count_SCH_Update = 0;
uint8_t current_index_task=0;

void SCH_Init(void){

}
uint32_t SCH_Add_Task(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task<SCH_MAX_TASKS){
		SCH_tasks_G[current_index_task].pTask=p_function;
		SCH_tasks_G[current_index_task].Delay=DELAY;
		SCH_tasks_G[current_index_task].Period=PERIOD;
		SCH_tasks_G[current_index_task].RunMe=0;
		SCH_tasks_G[current_index_task].TaskID=current_index_task;
	}
	return SCH_tasks_G[current_index_task].TaskID;
}
void SCH_Update(void){
	for(int i=0;i<current_index_task;i++){
		if (SCH_tasks_G[i].Delay>0){
			SCH_tasks_G[i].Delay--;
		}else {
			SCH_tasks_G[i].Delay=SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe+=1;
		}

	}
}

void SCH_Dispactch_Tasks(void){
	for(int i=0;i<current_index_task;i++){
		if(SCH_tasks_G[i].RunMe>0){
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();
		}
	}
}
