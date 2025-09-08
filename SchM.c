#include "SchM.h"
#include "Timer.h" // provides extern volatile uint32_t g_ms_tick
#include <string.h>

#define SCHM_MAX_TASKS  24

typedef struct {
    SchM_TaskFunc func;
    unsigned short period_ms;
    unsigned long last_run_ms;
    bool active;
} SchM_Task_t;

static SchM_Task_t tasks[SCHM_MAX_TASKS];

void SchM_Init(void)
{
    memset(tasks, 0, sizeof(tasks));
}

/* Register a periodic task. Returns false if no slot available. */
bool SchM_RegisterTask(SchM_TaskFunc func, unsigned short period_ms)
{
	int i;
    if (func == NULL || period_ms == 0) return false;

    for (i = 0; i < SCHM_MAX_TASKS; ++i) {
        if (!tasks[i].active) {
            tasks[i].func = func;
            tasks[i].period_ms = period_ms;
            tasks[i].last_run_ms = g_ms_tick;
            tasks[i].active = true;
            return true;
        }
    }
    return false;
}

void SchM_UnregisterTask(SchM_TaskFunc func)
{
	int i;
    for (i = 0; i < SCHM_MAX_TASKS; ++i) {
        if (tasks[i].active && tasks[i].func == func) {
            tasks[i].active = false;
            tasks[i].func = NULL;
        }
    }
}

/* Cooperative scheduler main function: call frequently from main loop. */
void SchM_MainFunction(void)
{
    unsigned long now = g_ms_tick;
    int i;
    for (i = 0; i < SCHM_MAX_TASKS; ++i) {
        if (!tasks[i].active) continue;
        if ((unsigned long)(now - tasks[i].last_run_ms) >= (unsigned long)tasks[i].period_ms) {
            tasks[i].last_run_ms = now;
            tasks[i].func();
        }
    }
}
