#include "pch.hpp"
#include "timer.hpp"

#include <GLFW/glfw3.h>
#include "utils.hpp"

namespace juice {

	Timer::Timer()
		: m_DeltaTime(0.0f), m_LastFrame(0.0f)
	{
	}

	Timer::~Timer() {}

	void Timer::Init() 
	{
		JUICE_CORE_INFO("Timer Intialized!");
	}

	void Timer::Tick()
	{
		m_DeltaTime = glfwGetTime() - m_LastFrame;
		m_LastFrame = glfwGetTime();
	}

}
