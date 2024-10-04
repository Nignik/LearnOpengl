#pragma once

#include <string>
#include <functional>

class Slider
{
public:
	virtual ~Slider() = default;
	virtual void Render() = 0;
};

template<typename T>
class TypedSlider : public Slider
{
public:
	TypedSlider(std::string&& label, std::function<void(T)> func, T value, T minValue, T maxValue)
		: m_label(label),
		m_func(func),
		m_value(value),
		m_minValue(minValue),
		m_maxValue(maxValue)
	{
	}

	void Render() override
	{
		if constexpr (std::is_same_v<T, float>)
		{
			if (ImGui::SliderFloat(m_label.c_str(), &m_value, m_minValue, m_maxValue))
			{
				m_func(m_value);
			}
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			if (ImGui::SliderInt(m_label.c_str(), &m_value, m_minValue, m_maxValue))
			{
				m_func(m_value);
			}
		}
		else
		{
			static_assert(sizeof(T) == 0, "Unsupported slider type");
		}
	}

private:
	std::string m_label;
	std::function<void(T)> m_func{};
	T m_value;
	T m_minValue;
	T m_maxValue;

};