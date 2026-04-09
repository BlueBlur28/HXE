#include <stdint.h>



void LoadSectionHeaders(void);

void thunktable_decode(int type); // 0 is DEBUG, 1 is RETAIL

extern uint32_t ThunkTableAddr;

void LoadThunkTable(void);