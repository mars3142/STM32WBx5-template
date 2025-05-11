#include "LED.hh"
#include "Module.hh"
#include "Timing.hh"
#include "stm32wbxx_hal.h"

extern "C" {
// HAL needs the SysTick handler for timing.
void SysTick_Handler(void) { HAL_IncTick(); }
}

int main() {

  HAL_Init();
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();

  auto led1 = std::make_shared<LED>(GPIOB, GPIO_PIN_5);
  auto led2 = std::make_shared<LED>(GPIOB, GPIO_PIN_0);
  auto led3 = std::make_shared<LED>(GPIOB, GPIO_PIN_1);
  auto timing = std::make_shared<Timing>();

  Module module(led1, led2, led3, timing);
  uint16_t count = 0;

  while (1) {
    module.blink(led1, 100);

    module.blink(led2, 200);

    module.blink(led3, 300);

    timing->delay(1000);

    count++;
  }
}
