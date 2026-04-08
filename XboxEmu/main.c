#include "memory.h"
#include "xbe.h"
#include "cpu.h"


int main(void)
{
	InitVirtualMem(); //Init Memory
	
	LoadXBE("C:/Projects/XboxEmu/XboxEmu/default.xbe"); //Load a xbe file
	
	ReadByte(0x00010000); //Just reading some bytes for fun
	ReadByte(0x00010001);
	ReadByte(0x00010002);
	ReadByte(0x00010003);
	ReadByte(0x00010004);
	LoadSectionHeaders();
	
	entry_decode(1); //Decode entry point
	
	thunktable_decode(1); //Decode the kernel thunktable

	LoadThunkTable();
	
	return 0;
}