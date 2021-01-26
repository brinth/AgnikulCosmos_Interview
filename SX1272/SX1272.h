/*
	@brief    : C, C++ code to Send payload over LoRa
	@author   : Brinth
	@date     : 26 Jan 2021
	@platfrom : STM32F103C8T6
	
	*** PLEASE NOTE THAT THE FOLLOWING CODE IS **NOT TESTED** 
	USER DISCRETION IS REQUIRED BEFORE FLASHING THE CODE ****

*/
/*
	Assuming all the SPI_Init() and other SPI supporting functions are declared in SPI header file
*/

#include <SPI.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
	bool LoRa_Init(void); 
	unsigned char LoRa_Send(unsigned char* data, unsigned char length);
	unsigned char LoRa_Receive(unsigned char* pData, unsigned char* pLength);
	
#ifdef __cplusplus
}
#endif