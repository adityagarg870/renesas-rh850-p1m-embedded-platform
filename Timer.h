
#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/* Global millisecond tick counter, updated in timer ISR */
extern volatile unsigned long g_ms_tick;

void Timer_Init(void);
void Timer_DelayMs(unsigned short ms); /* Blocking delay in milliseconds */
#endif // TIMER_H

