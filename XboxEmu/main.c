#include "memory.h"
#include "xbe.h"
#include "cpu.h"


int main(void)
{
	InitVirtualMem();
	LoadXBE("C:/Projects/XboxEmu/XboxEmu/default.xbe");
	ReadByte(0x00010000);
	ReadByte(0x00010001);
	ReadByte(0x00010002);
	ReadByte(0x00010003);
	ReadByte(0x00010004);
	LoadSectionHeaders();

	cpu_init(1);
	run_cpu(0x00043160);
	
	return 0;
}