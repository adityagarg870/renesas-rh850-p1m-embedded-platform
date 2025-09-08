#ifndef SCHM_H
#define SCHM_H
#ifndef BOOL_TYPEDEF
#define BOOL_TYPEDEF
typedef unsigned char bool;
#define true  1
#define false 0
#endif

#include <stdint.h>
#include <stdbool.h>

typedef void (*SchM_TaskFunc)(void);

extern volatile unsigned long g_ms_tick;

void SchM_Init(void);
bool SchM_RegisterTask(SchM_TaskFunc func, unsigned short period_ms); // period_ms: run every N ms
void SchM_UnregisterTask(SchM_TaskFunc func);
void SchM_MainFunction(void); // call in while(1) loop

#endif // SCHM_H
