#pragma once

#include "ILED.hh"
#include "ITiming.hh"

#include <memory>

class Module {
public:
  Module(const std::shared_ptr<ILED> &led1, const std::shared_ptr<ILED> &led2,
         const std::shared_ptr<ILED> &led3,
         const std::shared_ptr<ITiming> &timing);

  void blink(const std::shared_ptr<ILED> &led, uint32_t ms);

private:
  std::shared_ptr<ILED> led1_;
  std::shared_ptr<ILED> led2_;
  std::shared_ptr<ILED> led3_;
  std::shared_ptr<ITiming> timing_;
};