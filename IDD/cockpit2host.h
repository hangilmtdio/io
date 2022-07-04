#pragma once

#include "cockpit_interface.h"

#pragma pack(push, 1)

typedef struct COCKPIT_TO_HOST_TYPE
{
	LEFT_PANEL_TYPE Left_Panel;
	MAIN_PANEL_TYPE Main_Panel;
	RIGHT_PANEL_TYPE Right_Panel;

}COCKPIT_TO_HOST_TYPE;

typedef struct Cockpit_To_Host_Data_Type
{

	unsigned long TIMETAG;
	int HOST2COCK_SIZE;
	int	COCK2HOST_SIZE;

	//COCKPIT_TO_HOST_TYPE IO2HOST;
	F_16_COCKPIT_TO_HOST_TYPE	IO2HOST;


} Cockpit_To_Host_Data_Type;

#pragma pack(pop)