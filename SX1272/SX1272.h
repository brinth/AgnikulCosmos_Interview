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

/*
	MACROS
*/
//LongRangeMode 
#define LORA_MODE 1
#define FSK_OOK_MODE 0
//Access Shared RegOpMode
#define ACCESS_LORA_REG 0
#define ACCESS_FSK_REG 1
//LoRa Modes
#define SLEEP_MODE		0
#define STDBY_MODE		1
#define FSTX_MODE		2
#define TX_MODE			3
#define FSRX_MODE		4
#define RX_CONT_MODE	5
#define RX_SING_MODE    6
#define CAD_MODE		7

enum EN_REGISTERS_BASE_ADDRESS{
	RegOpMode      		= 0x01;
	RegFrMsb       		= 0x06;
	RegFrMib       		= 0x07;
	RegFrLsb       		= 0x08;
	RegPaConfig    		= 0x09;
	RegPaRamp	   		= 0x0A;
	RegOcp		      	= 0x0B;
	RegLna            	= 0x0C;
	RegFifoAddrPtr    	= 0x0D;
	RegFifoTxBaseAddr 	= 0x0E;
	RegFifoRxBaseAddr	= 0x0F;
	RegFifoRxCurrent	= 0x10;
	RegIrqFlagMask		= 0x11;
	RegIrqFlag			= 0x12;
	RegRxNbBytes		= 0x13;
	RegRxHeaderCntVMsb  = 0x14;
	RegRxHeaderCntVLsb  = 0x15;
	RegRxPacketCntVMsb  = 0x16;
	RegRxPacketCntVLsb  = 0x17;
	RegModemStat		= 0x18;
	RegPktSnrValue 		= 0x19;
	RegPktRssiValue		= 0x1A;
	RegRssiValue		= 0x1B;
	RegHopChannel		= 0x1C;
	RegModemConfig1		= 0x1D;
	RegModemConfig2		= 0x1E;
	RegSymbTimeOutLsb	= 0x1F;
	RegPreambleMsb		= 0x20;
	RegPreambleLsb		= 0x21;
	RegPayloadLength	= 0x22;
	RegMaxPayloadLength = 0x23;
	RegHopPeriod		= 0x24;
	RegFifoRxByteAdd	= 0x25;
	RegFeiMsb			= 0x28;
	RegFeiMid			= 0x29;
	RegFeiLsb			= 0x2A;
	RegRssiWideband		= 0x2C;
	RegDetectOptimize	= 0x31;
	RegInvertIQ			= 0x33;
	RegDetectionThresld = 0x37;
	RegSyncWord			= 0x39;
}Reg_Base_Addr;


#ifdef __cplusplus
extern "C" {
#endif
	/*
		STRUCTURES
	*/
	typedef struct St_RegOpMode{
		unsigned char LongRangeMode : 1;
		unsigned char AccessSharedReg : 1;
		unsigned char unused : 3;
		unsigned char Mode : 3;
	} RegOpMode_Typedef;
	typedef struct St_RegModemConfig1{
		unsigned char Bw : 2;
		unsigned char CodingRate : 3;
		unsigned char ImplicitHeaderModeOn : 1;
		unsigned char RxPayloadCrcOn : 1;
		unsigned char LowDataRateOptimize : 1;
	} RegModemConfig1_Typedef;
	typedef struct St_RegModemConfig2{
		unsigned char SpreadingFactor : 4;
		unsigned char TxContinuousMode : 1;
		unsigned char AgcAutoOn : 1;
		unsigned char SymbTimeout : 2;
	} RegModemConfig2_Typedef;
	
	
	/*
	FUNCTION DECLARATION
	*/
	bool LoRa_Init(unsigned int freq, unsigned char mode); 
	unsigned char LoRa_Send(unsigned char* data, unsigned char length);
	unsigned char LoRa_Receive(unsigned char* pData, unsigned char* pLength);
	
#ifdef __cplusplus
}
#endif