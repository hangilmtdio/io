#pragma once

//
// Device NO	Device Name								Device IP		Receive Port(넥스웨어)	Send Port(IOSW - ANTOS)
//	200			HEAD UP DISPLAY COMBINING GLASS			192.168.0.200	10200					11200					Not Used
//  201			UPFRONT CONTROL PANEL					192.168.0.201	10201					11201
//  202			MULTI - PURPOSE DISPLAY(MPD) - Left		192.168.0.202	10202					11202					Not Used
//  203			MULTI - PURPOSE DISPLAY(MPD) - Right	192.168.0.203	10203					11203					Not Used
//  204			MULTI - PURPOSE COLOR DISPLAY(MPCD)		192.168.0.204	10204					11204					Not Used
//  205			HEAD UP DISPLAY CONTROL PANEL			192.168.0.205	10205					11205 
//  206			STANDBY AIRSPEED INDICATOR				192.168.0.206	10206					11206
//  207			ANGLE OF ATTACK INDICATOR				192.168.0.207	10207					11207
//  208			VERTICAL VELOCITY INDICATOR				192.168.0.208	10208					11208
//  209			CABIN PRESSURE ALTIMETER				192.168.0.209	10209					11209
//  210			ALTIMETER								192.168.0.210	10210					11210
//  211			STANDBY ATTITUDE INDICATOR				192.168.0.211	10211					11211
//  212			EIGHT DAY CLOCK							192.168.0.212	10212					11212
//  213			ENHANCED ENGINE MONITOR DISPLAY			192.168.0.213	10213					11213
//  214			FUEL QUANTITY INDICATOR					192.168.0.214	10214					11214
// 
#define NEXWARE_UFC_ID		201
#define NEXWARE_HCP_ID		205
#define NEXWARE_SAI_ID		206
#define NEXWARE_AOA_ID		207
#define NEXWARE_VVI_ID		208
#define NEXWARE_CPA_ID		209
#define NEXWARE_ALT_ID		210
#define NEXWARE_SA_ID		211
#define NEXWARE_CLOCK_ID	212
#define NEXWARE_EEMD_ID		213
#define NEXWARE_FQI_ID		214

#define IOBOARD_UFC_ID		4
#define IOBOARD_HCP_ID		5
#define IOBOARD_SAI_ID		6
#define IOBOARD_AOA_ID		7
#define IOBOARD_VVI_ID		8
#define IOBOARD_CPA_ID		9
#define IOBOARD_ALT_ID		11
#define IOBOARD_SA_ID		12
#define IOBOARD_CLOCK_ID	13
#define IOBOARD_EEMD_ID		14
#define IOBOARD_FQI_ID		21

#pragma pack(push, 1)

typedef struct Nexware_to_IOSW
{
	int Timetag;					// 증가값 (0 ~ integer 범위까지,,, 범위 넘어가면 0 부터 다시 증가)
	unsigned char Device_No;		// 0x64 ~ 0x74  해당 장비 No
	unsigned char BIT_Result;		// 0x01 = Pass , 0x00 = Fail
	unsigned short DI_1;			// DI 0 ~ 15 Ch
	unsigned short DI_2;			// DI 16 ~ 31 Ch
	unsigned short DI_3;			// DI 32 ~ 47 Ch
	unsigned short DI_4;			// DI 48 ~ 63 Ch
	unsigned short AI_0;			// AI 0 Ch
	unsigned short AI_1;			// AI 1 Ch
	unsigned short AI_2;			// AI 2 Ch
	unsigned short AI_3;			// AI 3 Ch
	unsigned short AI_4;			// AI 4 Ch
	unsigned short AI_5;			// AI 5 Ch
	unsigned short AI_6;			// AI 6 Ch
	unsigned short AI_7;			// AI 7 Ch
	int spare_0;					// Spare 1
	int spare_1;					// Spare 2
	int spare_2;					// Spare 3
}Nexware_to_IOSW;

#pragma pack(pop) 


#pragma pack(push, 1)

typedef struct IOSW_to_Nexware
{
	unsigned char Device_No;		// 0x64 ~ 0x74  해당 장비 No
	unsigned char BIT_Command;		// 0x01 = BIT Run , 0x00 = Normal Mode
	unsigned char Shutdown_Command;	// 0x01 = Shutdown run , 0x00 = Normal mode
	unsigned char Reboot_Command;	// 0x01 = Reboot run , 0x00 = Normal mode
	unsigned short DO_1;			// DO 0 ~ 15 Ch
	unsigned short DO_2;			// DO 16 ~ 31 Ch
	unsigned short DO_3;			// DO 32 ~ 47 Ch
	unsigned short DO_4;			// DO 48 ~ 63 Ch
	unsigned short AO_0;			// AO 0 Ch
	unsigned short AO_1;			// AO 1 Ch
	unsigned short AO_2;			// AO 2 Ch
	unsigned short AO_3;			// AO 3 Ch
	unsigned short AO_4;			// AO 4 Ch
	unsigned short AO_5;			// AO 5 Ch
	unsigned short AO_6;			// AO 6 Ch
	unsigned short AO_7;			// AO 7 Ch
	int spare_0;					// Spare 1
	int spare_1;					// Spare 2
	int spare_2;					// Spare 3
}IOSW_to_Nexware;

#pragma pack(pop) 
