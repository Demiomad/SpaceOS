#include <pit.h>
#include <system.h>
#include <irq.h>
#include <printf.h>

int total_ticks = 0;
int F = 100;

void timer_phase(int hz)
{
    int divisor = 1193180 / hz;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
}

void timer_handler(struct regs *r) {
    total_ticks++;
}

void timer_sleep(int ticks) {
    int eticks = total_ticks + ticks;

    while (total_ticks < eticks);
}

void timer_sleep_seconds(int seconds) {
    timer_sleep(seconds * F);
}

void timer_sleep_ms(int ms) {
    timer_sleep((ms * F) / 1000);
}

void timer_init() {
    timer_phase(F);
    irq_set_handler(0, timer_handler);
}