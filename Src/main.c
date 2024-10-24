#include <stdint.h>
#include "miros.h"

uint32_t task1Visualizer=0;
uint32_t task2Visualizer=0;
uint32_t task3Visualizer=0;

uint32_t stackTask1[40];
uint32_t stackTask2[40];
uint32_t stackTask3[40];

uint32_t stack_idleThread[40];

OSThread task1Thread;
OSThread task2Thread;
OSThread task3Thread;

void task1();
void task2();
void task3();

int main() {
    OS_init(stack_idleThread, sizeof(stack_idleThread));

    OSThread_start(&task1Thread, 5U, &task1, stackTask1, sizeof(stackTask1),
				   3 * TICKS_PER_SEC, 5 * TICKS_PER_SEC);

    OSThread_start(&task2Thread, 2U, &task2, stackTask2, sizeof(stackTask2),
				   1 * TICKS_PER_SEC, 8 * TICKS_PER_SEC);

    OSThread_start(&task3Thread, 1U, &task3, stackTask3, sizeof(stackTask3),
				   1 * TICKS_PER_SEC, 10 * TICKS_PER_SEC);

    OS_run();
}

void task1() {
    while (1) {
    	task1Visualizer++;
        TaskAction(&task1Thread, task1Thread.remainingTime);
    }
}

void task2() {
    while (1) {
    	task2Visualizer++;
        TaskAction(&task2Thread, task2Thread.remainingTime);
    }
}

void task3() {
    while (1) {
    	task3Visualizer++;
        TaskAction(&task3Thread, task3Thread.remainingTime);
    }
}
