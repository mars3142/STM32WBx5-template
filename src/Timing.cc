#include "Timing.hh"
#include "stm32wbxx_hal.h"

Timing::Timing() = default;
void Timing::delay(uint32_t ms) { HAL_Delay(ms); }