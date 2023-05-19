#include "rng.hpp"

#include <cstdint>
#include <random>

namespace Pixie
{
namespace RNG
{
namespace
{
static std::random_device rng;
static std::mt19937_64 engine(rng());
static std::uniform_int_distribution<uint64_t> distribution;

}; // Anonymous namespace
uint64_t generate() { return distribution(engine); }

}; // namespace RNG
}; // namespace Pixie
