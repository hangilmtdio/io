#pragma once

#include "cockpit_enum.h"

#pragma pack(push, 1)

typedef struct CAUTION_LIGHTS_TYPE
{
	//data type change  2019.01.13
	int Program_Light;
	int Minimum_Light;
	int Chaff_Light;
	int Flare_Light;
	int Emer_Bst_On_Light;
	int Bst_Sys_Mal_Light;
	int Brk_Hld_Light;
	int Fuel_Low_Light;
	int Left_Gen_Light;
	int Right_Gen_Light;
	int Engine_Light;
	int Flt_Control_Light;
	int Hydraulic_Light;
	int Av_Bit_Light;
	int Dspl_Flo_Lo_Light;
	int Oxygen_Light;
	int Spare1_Light;
	int Spare2_Light;
	int Spare3_Light;
	int Spare4_Light;

}CAUTION_LIGHTS_TYPE;


typedef struct GROUND_TEST_LIGHTS_TYPE
{
	//data type change  2019.01.13
	int Left_Pump_Light;
	int Right_Pump_Light;
	int Util_A_Light;
	int Util_B_Light;
	int PC1_A_Light;
	int PC1_B_Light;
	int PC2_A_Light;
	int PC2_B_Light;
	int Xfer_Pump_Light;
	int Hook_Light;
	int Left_Bst_Pump_Light;
	int Right_Bst_Pump_Light;
	int Bingo_Fuel_Light;
	int Jfs_Low_Light;
	int Inlet_Ice_Light;
	int Ecs_Light;
	int Anti_Skid_Light;
	int Spd_Bk_Light;
	int Spare1_Light;
	int Spare2_Light;
}GROUND_TEST_LIGHTS_TYPE;


typedef struct FIRE_WARNING_LIGHTS_TYPE
{
	//data type change  2019.01.13
	int AMAD_Fire_Light;
	int Left_Engine_Fire_Light;
	int Right_Engine_Fire_Light;
	int Left_Burn_Thru_Light;
	int Right_Burn_Thru_Light;
}FIRE_WARNING_LIGHTS_TYPE;


typedef struct LANDING_GEAR_LIGHTS_TYPE
{
	//data type change  2019.01.13
	int Nose_Gear_Light;
	int Left_Gear_Light;
	int Right_Gear_Light;
	int Handle_Light; //added data
}LANDING_GEAR_LIGHTS_TYPE;

typedef struct FLAP_LIGHTS_TYPE
{
	//data type change  2019.01.13
	int Flap_Up_Light;
	int Flap_Down_Light;
}FLAP_LIGHTS_TYPE;

typedef struct MAIN_PANEL_LIGHTS_TYPE
{
	//ON_OFF_TYPE Lock_Shoot_Light; delete data  2019.01.13
	//ON_OFF_TYPE Ready_Light; delete data   2019.01.13

	//data type change  2019.01.13
	int Master_Caution_Light;
	int EMIS_LMT_Light;
	int Spare1_Light;
	int A1_SAM_Light;
	int Low_Alt_Light;
	int OBST_Light;
	int TF_Fail_Light;
	int Can_Unlkd_Light;
	int Spare2_Light;
	int Spare3_Light;
	int Laser_Armed_Light;
	int AP_Light;
	//int Test_Bit_Light; delete data  2019.01.13

}MAIN_PANEL_LIGHTS_TYPE;

typedef struct MASTER_MODE_LIGHTS_TYPE
{
	//data type change  2019.01.13
	int Air_to_Air_Light;
	int Air_to_Ground_Light;
	int Air_to_Nav_Light;
	int Air_to_Inst_Light;

}MASTER_MODE_LIGHTS_TYPE;

#pragma pack(pop)