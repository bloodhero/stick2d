#pragma once

#include "Core/Layer.h"
#include "Core/Event.h"


namespace stick2d {

	class ImGuiManager
	{
	public:
		ImGuiManager() = default;
		~ImGuiManager() = default;

		void onAttach();
		void onDetach();

		void begin();
		void end();
		void onEvent(Event& e);

	private:
		bool m_block_events = true;
	};
}