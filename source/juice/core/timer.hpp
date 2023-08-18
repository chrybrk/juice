#pragma once

namespace juice {
	
	class Timer {
	public:
		~Timer();

		void Init();
		void Tick();

		static Timer& GetInstance() {
			static Timer ref;
			return ref;
		}

		inline float DeltaTime() { return m_DeltaTime; }
		inline float GetSeconds() const { return m_DeltaTime; }
		inline float GetMilliseconds() const { return m_DeltaTime * 1000.0f; }

	private:
		float m_LastFrame, m_DeltaTime;

	private:
		Timer();
	};

	static Timer& timer = Timer::GetInstance();

}
