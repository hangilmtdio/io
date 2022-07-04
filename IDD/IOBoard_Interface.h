#pragma once

#define MAX_IOBOARD 50
#define MAX_IOBOARD_IO 64
#define DI_HIGH 1
#define DI_LOW 0
#define AOFREQ_28V  3400
#define AOFREQ_24V  3400
#define AOFREQ_5V  3400
#define AOFREQ_DIMMER	3400


#pragma pack(push, 1)


typedef struct IOBOARD_to_IOSW
{
	////////////////Board Number 0~23
	unsigned char Board_No; 	// USING 0x00~0x17 

	//////////////// Built in Test Result 
	//HIGH = PASS
	//LOW = FAIL
	unsigned char BIT_RESULT;

	////////////////Digital Input 32 bit 
	unsigned short DI_CH_LOW; //0~15 
	unsigned short DI_CH_HIGH; //16~31

							////////////////Analog Input 16bit x 8ch
	unsigned short AI_CH_0; //16bit ADC
	unsigned short AI_CH_1;
	unsigned short AI_CH_2;
	unsigned short AI_CH_3;
	unsigned short AI_CH_4;
	unsigned short AI_CH_5;
	unsigned short AI_CH_6;
	unsigned short AI_CH_7;

	////////////////Rudder Pedal Position
	// Encorder sensor data
	// -100.00 ~ 100.00
	float YAW;

	// PEDAL Brake signal 
	// 1 = off
	// 0 = on

	unsigned char BRAKE_LH;
	unsigned char BRAKE_RH;
	
	// TRIM COMPLETE
	unsigned char RUDDER_TRIM_COMPLETE;

	////////////////Control Stick Position
	// AHRS sensor data
	//PITCH = -180.00 ~ 180.00
	//ROLL = -90.00 ~ 90.00
	float AHRS_PITCH;
	float AHRS_ROLL;

	// TRIM COMPLETE
	unsigned char STICK_TRIM_COMPLETE;

	////////////////Spare Data
	int SPARE0;
	int SPARE1;
	int SPARE2;

} IOBOARD_to_IOSW;


#pragma pack(pop) 

#pragma pack(push, 1)


typedef struct IOSW_to_IOBOARD
{
	////////////////Board Number 0~23
	unsigned char Board_No; 	// USING 0x00~0x17 

								//////////////// Built in Test command
								//HIGH = run
								//LOW = normal mode
	unsigned char BIT_COMMAND;

	//////////////// Shut down
	unsigned char SHUTDOWN_COMMAND;

	//////////////// reboot
	unsigned char REBOOT_COMMAND;

	////////////////Digital Output 
	//HIGH = ON
	//LOW = OFF
	//28vdc 0~7ch
	unsigned char DO_28V; //8bit
						  //24vdc 0~4ch
	unsigned char DO_24V;//5bit
						 //5vdc 0~2ch
	unsigned char DO_5V;//3bit

						////////////////Analog Output
						//28vdc 0~12ch
	unsigned short CH0_FREQ_28V;
	unsigned short CH0_WIDTH_28V;
	unsigned short CH1_FREQ_28V;
	unsigned short CH1_WIDTH_28V;
	unsigned short CH2_FREQ_28V;
	unsigned short CH2_WIDTH_28V;
	unsigned short CH3_FREQ_28V;
	unsigned short CH3_WIDTH_28V;
	unsigned short CH4_FREQ_28V;
	unsigned short CH4_WIDTH_28V;
	unsigned short CH5_FREQ_28V;
	unsigned short CH5_WIDTH_28V;
	unsigned short CH6_FREQ_28V;
	unsigned short CH6_WIDTH_28V;
	unsigned short CH7_FREQ_28V;
	unsigned short CH7_WIDTH_28V;
	unsigned short CH8_FREQ_28V;
	unsigned short CH8_WIDTH_28V;
	unsigned short CH9_FREQ_28V;
	unsigned short CH9_WIDTH_28V;
	unsigned short CH10_FREQ_28V;
	unsigned short CH10_WIDTH_28V;
	unsigned short CH11_FREQ_28V;
	unsigned short CH11_WIDTH_28V;
	unsigned short CH12_FREQ_28V;
	unsigned short CH12_WIDTH_28V;

	//24vdc 0~4ch
	unsigned short CH0_FREQ_24V;
	unsigned short CH0_WIDTH_24V;
	unsigned short CH1_FREQ_24V;
	unsigned short CH1_WIDTH_24V;
	unsigned short CH2_FREQ_24V;
	unsigned short CH2_WIDTH_24V;
	unsigned short CH3_FREQ_24V;
	unsigned short CH3_WIDTH_24V;
	unsigned short CH4_FREQ_24V;
	unsigned short CH4_WIDTH_24V;

	//5vdc 0~1ch
	unsigned short CH0_FREQ_5V;
	unsigned short CH0_WIDTH_5V;
	unsigned short CH1_FREQ_5V;
	unsigned short CH1_WIDTH_5V;

	////////////////Dimming Out 0~1ch
	unsigned short DIMM_CH0_FREQ;
	unsigned short DIMM_CH0_WIDTH;
	unsigned short DIMM_CH1_FREQ;
	unsigned short DIMM_CH1_WIDTH;

	////////////////HYD UTIL Indicator
	unsigned short UTIL_GAUGE; //0~1000

							   ////////////////HYD PC1 Indicator
	unsigned short PC1_GAUGE; //0~1000

							  ////////////////HYD PC2 Indicator
	unsigned short PC2_GAUGE;//0~1000

							 ////////////////PITCH RATIO Indicator
	unsigned short PITCH_RATIO_GAUGE; //0~1000

									  ////////////////OXYGEN Indicator
	unsigned short OXYGEN_GAUGE; //0~1000

								 ////////////////OXYGEN FLOW Indicator
								 //HIGH = WHITE
								 //LOW = BLACK
	unsigned char OXYGEN_FLOW;

	////////////////CONTROL STICK TRIM
	// left positive right negative
	// rear positive front negative
	// -100 ~ 100 
	unsigned char STICK_TRIM_LEFT;
	unsigned char STICK_TRIM_RIGHT;
	unsigned char STICK_TRIM_FRONT;
	unsigned char STICK_TRIM_REAR;
	unsigned char STICK_INIT;
				////////////////RUDDER PEDAL TRIM
				// turn clockwise positive 
				// turn counterclockwise negative
				// -100 ~ 100
	unsigned char RUDDER_INIT;
	unsigned char RUDDER_LH_TRIM;
	unsigned char RUDDER_RH_TRIM;

	// CAUTION LIGHT 20ch add (40byte )
	// 2019.01.11 ¼öÁ¤ 
	unsigned short CAUTION_CH0;
	unsigned short CAUTION_CH1;
	unsigned short CAUTION_CH2;
	unsigned short CAUTION_CH3;
	unsigned short CAUTION_CH4;
	unsigned short CAUTION_CH5;
	unsigned short CAUTION_CH6;
	unsigned short CAUTION_CH7;
	unsigned short CAUTION_CH8;
	unsigned short CAUTION_CH9;
	unsigned short CAUTION_CH10;
	unsigned short CAUTION_CH11;
	unsigned short CAUTION_CH12;
	unsigned short CAUTION_CH13;
	unsigned short CAUTION_CH14;
	unsigned short CAUTION_CH15;
	unsigned short CAUTION_CH16;
	unsigned short CAUTION_CH17;
	unsigned short CAUTION_CH18;
	unsigned short CAUTION_CH19;

}IOSW_to_IOBOARD;



#pragma pack(pop) 
