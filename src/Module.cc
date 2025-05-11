#include "Module.hh"

Module::Module(const std::shared_ptr<ILED> &led1,
               const std::shared_ptr<ILED> &led2,
               const std::shared_ptr<ILED> &led3,
               const std::shared_ptr<ITiming> &timing)
    : led1_(led1), led2_(led2), led3_(led3), timing_(timing) {}

void Module::blink(const std::shared_ptr<ILED> &led, uint32_t ms) {
  led->on();
  timing_->delay(ms);
  led->off();
  timing_->delay(ms);
}
