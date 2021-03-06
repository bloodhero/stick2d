#pragma once

#include <string>

namespace stick2d {
	class Timestep;
	class Event;

	class Layer
	{
	public:
		Layer(const std::string_view name = "Layer"):
			m_name(name)
		{}
		virtual ~Layer() = default;

		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onDraw() = 0;
		virtual void onUpdate(Timestep& ts) = 0;
		virtual void onEvent(Event& event) = 0;

		const std::string& getName() const { return m_name; }
	protected:
		std::string m_name;
	};

}