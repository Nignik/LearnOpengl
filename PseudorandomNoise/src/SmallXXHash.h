#pragma once

#include <cstddef>
#include <bit>

struct SmallXXHash
{
	static constexpr uint32_t primeA = 0b10011110001101110111100110110001;
	static constexpr uint32_t primeB = 0b10000101111010111100101001110111;
	static constexpr uint32_t primeC = 0b11000010101100101010111000111101;
	static constexpr uint32_t primeD = 0b00100111110101001110101100101111;
	static constexpr uint32_t primeE = 0b00010110010101100110011110110001;

	uint32_t accumulator = 0;

	SmallXXHash() : accumulator(0) {}
	SmallXXHash(uint32_t seed) : accumulator(seed + primeE) {}

	void Seed(uint32_t seed)
	{
		accumulator = seed + primeE;
	}
	
	SmallXXHash& Eat(uint32_t data)
	{
		accumulator = std::rotl(accumulator + data * primeC, 17) * primeD;
		return *this;
	}

	SmallXXHash& Eat(uint8_t data)
	{
		accumulator = std::rotl(accumulator + data * primeE, 11) * primeA;
		return *this;
	}

	operator uint32_t() const
	{
		uint32_t avalanche = accumulator;
		avalanche ^= avalanche >> 15;
		avalanche *= primeB;
		avalanche ^= avalanche >> 13;
		avalanche *= primeC;
		avalanche ^= avalanche >> 16;
		return avalanche;
	}

	SmallXXHash operator+(const SmallXXHash& other) const
	{
		return SmallXXHash(this->accumulator + other.accumulator);
	}

	SmallXXHash operator-(const SmallXXHash& other) const
	{
		return SmallXXHash(this->accumulator - other.accumulator);
	}

	SmallXXHash operator*(const SmallXXHash& other) const
	{
		return SmallXXHash(this->accumulator * other.accumulator);
	}

	SmallXXHash operator/(const SmallXXHash& other) const
	{
		return SmallXXHash(this->accumulator / other.accumulator);
	}

	SmallXXHash& operator+=(const SmallXXHash& other)
	{
		this->accumulator += other.accumulator;
		return *this;
	}

	SmallXXHash& operator-=(const SmallXXHash& other)
	{
		this->accumulator -= other.accumulator;
		return *this;
	}
};