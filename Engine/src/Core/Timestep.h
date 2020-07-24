#pragma once

namespace stick2d {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{
		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time / 1000.0f; }
		float GetMilliseconds() const { return m_Time; }
	private:
		float m_Time;
	};

}