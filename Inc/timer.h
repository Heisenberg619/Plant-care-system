
#ifndef TIMER_H_
#define TIMER_H_
#define TIM2_EN      (1U << 0)
#define COUNT_EN     (1U << 0)
#define DIER_UIE     (1U << 0)
#define DIER_CC1IE   (1U << 1)
#define SR_UIF       (1U << 0)

void tim2_ms_interrupt_init(uint32_t ms);
#endif /* TIMER_H_ */
