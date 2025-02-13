#include "z80/RegisterFile.hpp"

namespace specbolt {

namespace {
bool is_high(RegisterFile::R8 reg) { return (static_cast<unsigned>(reg) & 1) == 0; }
} // namespace

std::uint8_t RegisterFile::get(const R8 reg) const {
  const auto &reg_pair = reg_for(reg);
  return is_high(reg) ? reg_pair.high() : reg_pair.low();
}
void RegisterFile::set(const R8 reg, const std::uint8_t value) {
  auto &reg_pair = reg_for(reg);
  if (is_high(reg))
    reg_pair.high(value);
  else
    reg_pair.low(value);
}
std::uint16_t RegisterFile::get(const R16 reg) const { return reg_for(reg).highlow(); }
void RegisterFile::set(const R16 reg, const std::uint16_t value) { reg_for(reg).highlow(value); }
std::uint16_t RegisterFile::ix() const { return ix_; }
void RegisterFile::ix(std::uint16_t ix) { ix_ = ix; }
std::uint16_t RegisterFile::iy() const { return iy_; }
void RegisterFile::iy(std::uint16_t iy) { iy_ = iy; }
std::uint16_t RegisterFile::sp() const { return sp_; }
void RegisterFile::sp(std::uint16_t sp) { sp_ = sp; }
std::uint16_t RegisterFile::pc() const { return pc_; }
void RegisterFile::pc(std::uint16_t pc) { pc_ = pc; }
std::uint8_t RegisterFile::r() const { return r_; }
void RegisterFile::r(std::uint8_t r) { r_ = r; }
std::uint8_t RegisterFile::i() const { return i_; }
void RegisterFile::i(std::uint8_t i) { i_ = i; }

void RegisterFile::exx() {
  std::swap(reg_for(R16::BC), reg_for(R16::BC_));
  std::swap(reg_for(R16::DE), reg_for(R16::DE_));
  std::swap(reg_for(R16::HL), reg_for(R16::HL_));
}

uint8_t RegisterFile::RegPair::high() const { return high_; }
void RegisterFile::RegPair::high(const uint8_t high) { high_ = high; }
uint8_t RegisterFile::RegPair::low() const { return low_; }
void RegisterFile::RegPair::low(const uint8_t low) { low_ = low; }
uint16_t RegisterFile::RegPair::highlow() const { return static_cast<uint16_t>(high_ << 8u) | low_; }
void RegisterFile::RegPair::highlow(const uint16_t highlow) {
  high_ = highlow >> 8 & 0xff;
  low_ = highlow & 0xff;
}

// The relationship between the various register numbers we rely on below is tested here explicit;y.
static_assert(static_cast<unsigned>(RegisterFile::R8::A) == static_cast<unsigned>(RegisterFile::R16::AF) << 1);
static_assert(static_cast<unsigned>(RegisterFile::R8::F) == (static_cast<unsigned>(RegisterFile::R16::AF) << 1) + 1);
static_assert(static_cast<unsigned>(RegisterFile::R8::A) + 8 == static_cast<unsigned>(RegisterFile::R8::A_));
static_assert(static_cast<unsigned>(RegisterFile::R16::AF) + 4 == static_cast<unsigned>(RegisterFile::R16::AF_));

RegisterFile::RegPair &RegisterFile::reg_for(R8 r8) { return regs_[static_cast<unsigned>(r8) / 2u]; }
const RegisterFile::RegPair &RegisterFile::reg_for(R8 r8) const { return regs_[static_cast<unsigned>(r8) / 2u]; }
RegisterFile::RegPair &RegisterFile::reg_for(R16 r16) { return regs_[static_cast<unsigned>(r16)]; }
const RegisterFile::RegPair &RegisterFile::reg_for(R16 r16) const { return regs_[static_cast<unsigned>(r16)]; }

} // namespace specbolt
