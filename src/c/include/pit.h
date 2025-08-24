#ifndef PIT_H
#define PIT_H

extern int total_ticks;

void timer_sleep(int ticks);
void timer_sleep_seconds(int seconds);
void timer_sleep_ms(int seconds);
void timer_init();

#endif