#ifndef TIMER_H
#define TIMER_H
void init_timer(unsigned int freq);
void sleep(unsigned int timer_ticks);
unsigned int get_uptime();
#endif
