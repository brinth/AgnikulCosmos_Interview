/*
	@brief    : C, C++ code to Send payload over LoRa
	@author   : Brinth
	@date     : 26 Jan 2021
	@platfrom : STM32F103C8T6
	
	*** PLEASE NOTE THAT THE FOLLOWING CODE IS **NOT TESTED** 
	USER DISCRETION IS REQUIRED BEFORE FLASHING THE CODE ****

*/

#include <SX1272.h>

//Assuming the Freq of oscillator Fosc = 8 MHz
#define __OSC_FREQ 8000000

bool LoRa_Init(unsigned char _mode, unsigned int _freq,
				RegOpMode_Typedef RegOpMode_Val,
				RegModemConfig1_Typedef RegModemConfig1_Val,
				RegModemConfig2_Typedef RegModemConfig2_Val
				)
{
	/*
	MODE Settings
	*/
	
	//Put Module in Sleep Mode to set Module in LoRa Mode
	unsigned char mode = RegOpMode_Val.Mode
	RegOpMode_Val.Mode = SLEEP_MODE;
	SPI_ReadAndWriteByte(RegOpMode_Val,0);
	RegOpMode_Val.Mode = mode;
	SPI_ReadAndWriteByte(RegOpMode_Val,0);
	SPI_ReadAndWriteByte(RegModemConfig1_Val,0);
	SPI_ReadAndWriteByte(RegModemConfig2_Val,0);
}

/*
	Sample Implementation:
	
	#include<SX1272.h>
	RegOpMode_Typedef RegOpMode_Val,
	RegModemConfig1_Typedef RegModemConfig1_Val,
	RegModemConfig2_Typedef RegModemConfig2_Val
	RegOpMode_Val.LongRangeMode = LORA_MODE;
	RegOpMode_Val.AccessSharedReg = ACCESS_LORA_REG;
	RegModemConfig1_Val.Bw ...
	RegModemConfig1_Val.CodingRate ...
	RegModemConfig1_Val.ImplicitHeaderModeOn ...
	RegModemConfig1_Val.RxPayloadCrcOn ...
	RegModemConfig1_Val.LowDataRateOptimize ...
	void main(){
		LoRa_Init( ...
	}
*/