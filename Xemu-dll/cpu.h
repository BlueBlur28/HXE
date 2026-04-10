#include <stdio.h>
#include <stdint.h>
#include <windows.h>



//decrypts the XBE Entry Point
uint32_t entry_decode(int type); // 0 is DEBUG, 1 is RETAIL



void run_cpu(uint32_t entry); 


LONG CALLBACK ExceptionHandler(EXCEPTION_POINTERS* ep);
