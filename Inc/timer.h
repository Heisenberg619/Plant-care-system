
#ifndef TIMER_H_
#define TIMER_H_
#define TIM2_EN      (1U << 0)
#define COUNT_EN     (1U << 0)
#define DIER_UIE     (1U << 0)
#define DIER_CC1IE   (1U << 1)
#define SR_UIF       (1U << 0)
#define TIM2EN (1U << 0)
#define CR1CEN (1U << 0)
#define GPIOAEN (1U << 0)
#define GPIOCEN (1U << 2)
#define CC1E (1U << 0)

void tim2_ms_interrupt_init(uint32_t ms);
void pwm_init(void);
void set_duty_cycle(uint32_t duty_cycle);
#endif /* TIMER_H_ */
