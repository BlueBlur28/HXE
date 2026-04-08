#include <stdio.h>
#include <stdint.h>



//CPU Init decrypts the XBE Entry Point
void cpu_init(int type); // 0 is DEBUG, 1 is RETAIL



void run_cpu(uint32_t entry); 
