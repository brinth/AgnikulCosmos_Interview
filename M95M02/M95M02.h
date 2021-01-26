/*
	@brief    : C, C++ code to read and write EEPROM
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

#define WREN  0b00000110 //Write Enable 
#define WRDI  0b00000100 //Write Disable 
#define RDSR  0b00000101 //Read Status Register 
#define WRSR  0b00000001 //Write Status Register 
#define READ  0b00000011 //Read from Memory Array 
#define WRITE 0b00000010 //Write to Memory Array 
#define RDID  0b10000011 //Read Identification Page 
#define WRID  0b10000010 //Write Identification Page 
#define RDLS  0b10000011 //Reads the Identification Page lock status 
#define LID   0b10000010 //Locks the Identification page in read-only mode 

#define SUCCESS 1
#define FAIL 0

/*
	Function declarations
*/

#ifdef __cplusplus
extern "C" {
#endif
	static unsigned int _cs_pin = -1;
	void EEPROM_init(unsigned int cs_pin);
	unsigned char EEPROM_WriteByte (unsigned long address, unsigned char* txByte, unsigned char txByteLength);
	unsigned char EEPROM_ReadByte (unsigned long address, unsigned char* rxByte, unsigned char rxByteLength);

#ifdef __cplusplus
}
#endif