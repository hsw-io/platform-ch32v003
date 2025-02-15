#if defined(CH32V00X)
#include <ch32v00x.h>
#elif defined(CH32V10X)
#include <ch32v10x.h>
#elif defined(CH32V20X)
#include <ch32v20x.h>
#elif defined(CH32V30X)
#include <ch32v30x.h>
#endif
#include <debug.h>

#define BLINKY_GPIO_PORT GPIOC
#define BLINKY_GPIO_PIN GPIO_Pin_1
#define BLINKY_CLOCK_ENABLE RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE)

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void Delay_Init(void);
void delay_ms(uint32_t n);

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();

	GPIO_PinConfig GPIO_InitStructure = {0};

	BLINKY_CLOCK_ENABLE;
	GPIO_InitStructure.GPIO_Pin = BLINKY_GPIO_PIN;
	GPIO_InitStructure.mode = GPIO_MODE_out_push_pull;
	GPIO_InitStructure.speed = GPIO_SPEED_50MHz;
	gpio_init(BLINKY_GPIO_PORT, &GPIO_InitStructure);

	uint8_t ledState = 0;
	while (1)
	{
		gpio_write_bit(BLINKY_GPIO_PORT, BLINKY_GPIO_PIN, ledState);
		ledState ^= 1; // invert for the next run
		delay_ms(1000);
	}
}

void NMI_Handler(void) {}
void HardFault_Handler(void)
{
	while (1)
	{
	}
}
