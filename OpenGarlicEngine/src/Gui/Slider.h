#pragma once

#include <string>
#include <functional>
#include <type_traits>

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
				m_func(m_value);
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			if (ImGui::SliderInt(m_label.c_str(), &m_value, m_minValue, m_maxValue))
				m_func(m_value);
		}
		else if constexpr (std::is_same<T, glm::vec3>::value)
		{
			ImGui::Text(m_label.c_str());

			ImGui::PushItemWidth(200);
			if (ImGui::SliderFloat(("X ##" + m_label).c_str(), &m_value.x, m_minValue.x, m_maxValue.x))
				m_func(m_value);

			ImGui::SameLine(0, 10);
			if (ImGui::SliderFloat(("Y ##" + m_label).c_str(), &m_value.y, m_minValue.y, m_maxValue.y))
				m_func(m_value);

			ImGui::SameLine(0, 10);
			if (ImGui::SliderFloat(("Z ##" + m_label).c_str(), &m_value.z, m_minValue.z, m_maxValue.z))
				m_func(m_value);

			ImGui::PopItemWidth();
		}
		else if constexpr (std::is_same<T, glm::ivec3>::value)
		{
			ImGui::Text(m_label.c_str());

			ImGui::PushItemWidth(200);
			if (ImGui::SliderInt(("X ##" + m_label).c_str(), &m_value.x, m_minValue.x, m_maxValue.x))
				m_func(m_value);

			ImGui::SameLine(0, 10);
			if (ImGui::SliderInt(("Y ##" + m_label).c_str(), &m_value.y, m_minValue.y, m_maxValue.y))
				m_func(m_value);

			ImGui::SameLine(0, 10);
			if (ImGui::SliderInt(("Z ##" + m_label).c_str(), &m_value.z, m_minValue.z, m_maxValue.z))
				m_func(m_value);

			ImGui::PopItemWidth();
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