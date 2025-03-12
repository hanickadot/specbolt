#pragma once

#include <cstdint>

#include "z80/v2/Z80.hpp"

namespace specbolt::v2 {

constexpr void write(Z80 &z80, const std::uint16_t address, const std::uint8_t byte) {
  z80.pass_time(3);
  z80.memory().write(address, byte);
}

constexpr std::uint8_t read(Z80 &z80, const std::uint16_t address) {
  z80.pass_time(3);
  return z80.memory().read(address);
}

constexpr std::uint8_t pop8(Z80 &z80) {
  const auto value = read(z80, z80.regs().sp());
  z80.regs().sp(z80.regs().sp() + 1);
  return value;
}

constexpr std::uint16_t pop16(Z80 &z80) {
  const auto low = pop8(z80);
  const auto high = pop8(z80);
  return static_cast<std::uint16_t>(high << 8 | low);
}

constexpr void push8(Z80 &z80, const std::uint8_t value) {
  z80.regs().sp(z80.regs().sp() - 1);
  write(z80, z80.regs().sp(), value);
}

constexpr void push16(Z80 &z80, const std::uint16_t value) {
  push8(z80, static_cast<std::uint8_t>(value >> 8));
  push8(z80, static_cast<std::uint8_t>(value));
}

} // namespace specbolt::v2
