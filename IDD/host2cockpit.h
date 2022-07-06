#pragma once

#include "host_interface.h"

#pragma pack(push, 1)

/*typedef struct ENGINE_DATA_TYPE
{
	int Engine_RPM;
	int Engine_Temp;
	int Fuel_Flow_PPH;
	int NOZ_Pos;
	int Oil_PSI;
}ENGINE_DATA_TYPE;*/
//delete  2019.01.13

typedef struct SETTING_DATA_TYPE
{
	int Bright;
	int Contrast;
}SETTING_DATA_TYPE;


typedef struct MPCD_LIGHTS_TYPE
{
	ON_OFF_TYPE L_LIGHT; // name change  2019.01.14 by KAI
	ON_OFF_TYPE LC_LIGHT;  // name change  2019.01.14 by KAI
	ON_OFF_TYPE C_LIGHT; // name change  2019.01.14 by KAI
	ON_OFF_TYPE RC_LIGHT; // name change  2019.01.14 by KAI
	ON_OFF_TYPE R_LIGHT; // name change  2019.01.14 by KAI

}MPCD_LIGHTS_TYPE;

//added struct   2019.01.13
typedef struct CONTROLSTICK_TRIM_TYPE
{
	ON_OFF_TYPE CONTROLSTICK_INIT;
	ON_OFF_TYPE CONTROLSTICK_Forward_TRIM;
	ON_OFF_TYPE CONTROLSTICK_Backward_TRIM;
	ON_OFF_TYPE CONTROLSTICK_Left_TRIM;
	ON_OFF_TYPE CONTROLSTICK_Right_TRIM;

}CONTROLSTICK_TRIM_TYPE;

//added struct  2019.01.13
typedef struct RUDDERPEDAL_TRIM_TYPE
{
	ON_OFF_TYPE RUDDER_INIT;
	ON_OFF_TYPE RUDDER_RH_TRIM;
	ON_OFF_TYPE RUDDER_LH_TRIM;

}RUDDERPEDAL_TRIM_TYPE;

typedef struct HOST_TO_COCKPIT_TYPE
{

	//ON_OFF_TYPE CAS_Bit_Light; delete data  2019.01.13
//	ON_OFF_TYPE TO_Trim_Light;
	int TO_Trim_Light; //data type change  2019.01.13
	int Replay_Light; //data type change  2019.01.13

	int OXY_Bit_Light; //data type change  2019.01.13
	int Starter_Light; //data type change  2019.01.13

	CAUTION_LIGHTS_TYPE Caution_Lights; //data type change  2019.01.13
	GROUND_TEST_LIGHTS_TYPE Ground_Test_Lights; //data type change  2019.01.13
	FIRE_WARNING_LIGHTS_TYPE Fire_Warning; //data type change  2019.01.13
	LANDING_GEAR_LIGHTS_TYPE Landing_Gear_Light; //data type change and added data  2019.01.13
	MAIN_PANEL_LIGHTS_TYPE Main_Panel_Light;//data type change and delete data  2019.01.13
	FLAP_LIGHTS_TYPE Flap_Light;//data type change  2019.01.13
	MASTER_MODE_LIGHTS_TYPE Master_Mode_Lights;//data type change  2019.01.13

	//ENGINE_DATA_TYPE Left_Engine_Data; delete data  2019.01.13
	//ENGINE_DATA_TYPE Right_Engine_Data; delete data  2019.01.13

	int HYD_Pressure_Util;
	int HYD_Pressure_PC1;
	int HYD_Pressure_PC2;

	int Pitch_Ratio;

	int Console_Backlight; //data name change  2019.01.13
	int Inst_Backlight; //data name change  2019.01.13
	int UFC_Backlight; //data name change  2019.01.13
	//int Chart_Light_Knob; delete data  2019.01.13
	//int Caution_Light_Knob; delete data  2019.01.13
	int Storm_Flood_Light; //data name change  2019.01.13

	SETTING_DATA_TYPE Left_MPD_Data;
	SETTING_DATA_TYPE Right_MPD_Data;
	SETTING_DATA_TYPE MPCD_Data;

	SETTING_DATA_TYPE HUD_Data;

	MPCD_LIGHTS_TYPE MPCD_Lights;	//add 2019.01.02

	CONTROLSTICK_TRIM_TYPE Controlstick_Trim;
	RUDDERPEDAL_TRIM_TYPE Rudderpedal_Trim;

	int OXYGEN; // add oxygen indicator in oxygen regulator panel 2019.01.13
	ON_OFF_TYPE FLOW; // add Flow indicator in oxygen regulator panel 2019.01.13

	ON_OFF_TYPE Solenoid_Coil_OFF[SOLENOIDE_COIL_END];
	bool Training_Status;   // true 이면 해당 절차
	bool Ext_Pwr_Reset;	 // true 이면 A/A Switch 로 변경

}HOST_TO_COCKPIT_TYPE;


typedef struct Host_To_Cockpit_Data_Type
{
	
	unsigned long			TIMETAG;

	int						HOST2COCK_SIZE;
	int						COCK2HOST_SIZE;
	int						INST_TIMETAG;
	MTD_MODE_TYPE			MTD_MODE;
	F_16_COCKPIT_TO_HOST_TYPE	HOST2IO;
	

} Host_To_Cockpit_Data_Type;

#pragma pack(pop)