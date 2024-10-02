#pragma once

#include <cctype>

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
	
	void Eat(uint32_t data)
	{
		accumulator += data * primeC;
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

	operator uint32_t() const
	{
		return accumulator;
	}
};