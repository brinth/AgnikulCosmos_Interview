/*
	@brief    : C, C++ code to read and write EEPROM
	@author   : Brinth
	@date     : 26 Jan 2021
	@platfrom : STM32F103C8T6
	
	*** PLEASE NOTE THAT THE FOLLOWING CODE IS **NOT TESTED** 
	USER DISCRETION IS REQUIRED BEFORE FLASHING THE CODE ****

*/

#include <M95M02.h>

/*
	@brief   : Initialize EEPROM device
	@param   : GPIO Pin from Port A **** USE GPIO PIN MACRO ***
	@return  : None
*/

void EEPROM_init(unsigned int cs_pin){
	//Setting CS Pin
	_cs_pin = cs_pin;
	GPIO_InitTypeDef GPIO_InitStruct;
	__GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = _cs_pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_SET);
	// Assuming this sets the given SPI pheripheral in SPI Mode 0 or Mode 3
	SPI_Init();
}


/*
	@brief   : Write a byte to EEPROM
	@param   : Start Address, data, length of data
	@return  : 1 on success 0 on failure
*/

unsigned char EEPROM_WriteByte(unsigned long address, unsigned char* txByte, unsigned char txByteLength){
	/*
	Checking Write Enable Latch and Setting WEL bit
	*/
	unsigned char EEPROM_St_Reg;
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_RESET);
	EEPROM_St_Reg = SPI_ReadAndWriteByte(RDSR,1); //RDSR Instruction
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_SET);
	if(((EEPROM_St_Reg >> 0x01) & 1) == 0){
	//Set WEL bit
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_RESET);
	SPI_ReadAndWriteByte(WREN,1);	//WREN Instruction
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_SET);
	}
	/*
	Checking WIL bit and Sending the byte to EEPROM
	*/
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_RESET);
	EEPROM_St_Reg = SPI_ReadAndWriteByte(RDSR,1); //RDSR Instruction
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_SET);
	while((EEPROM_St_Reg & 0x01) == 1) // Wait until the device write operation is complete
	{
		for(int i=100; i>0; --i){
			HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_RESET);
			EEPROM_St_Reg = SPI_ReadAndWriteByte(RDSR,1); //RDSR Instruction
			HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_SET);
			HAL_Delay(5);
		}//timeout
		return FAIL;
	}
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_RESET);
	SPI_ReadAndWriteByte(WRITE,1);		//Write Instruction
	SPI_ReadAndWriteByte(address,1);		//Address
	for(int i=0; i<txByteLength; i++){
	 SPI_ReadAndWriteByte(*(txByte+i),1);//Data
	}
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_SET);
	return SUCCESS;
}



/*
	@brief   : Read a byte from EEPROM to variable
	@param   : Start Address, variable pointer, length of data
	@return  : 1 on success 0 on failure
*/
unsigned char EEPROM_ReadByte(unsigned long address, unsigned char* rxByte, unsigned char rxByteLength){
	unsigned char EEPROM_St_Reg;
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_RESET);
	EEPROM_St_Reg = SPI_ReadAndWriteByte(RDSR,1); //RDSR Instruction
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_SET);
	while((EEPROM_St_Reg & 0x01) == 1) // Wait until the device write operation is complete
	{
		for(int i=100; i>0; --i){
			HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_RESET);
			EEPROM_St_Reg = SPI_ReadAndWriteByte(RDSR,1); //RDSR Instruction
			HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_SET);
			HAL_Delay(5);
		}//timeout
		return FAIL;
	}
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_RESET);
	SPI_ReadAndWriteByte(READ,1);		//READ Instruction
	SPI_ReadAndWriteByte(address,1);  //Address 
	for(int i=0; i<rxByteLength; i++){
		*(rxByte + i) =  SPI_ReadAndWriteByte(0x00,1); //Send dummy bytes to generate SPI clock
	}
	HAL_GPIO_WritePin(GPIOA, _cs_pin, GPIO_PIN_SET);
	return SUCCESS;
}