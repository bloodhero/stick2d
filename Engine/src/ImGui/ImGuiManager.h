#pragma once

#include "Core/Layer.h"
#include "Core/Event.h"


namespace stick2d {

	class ImGuiManager
	{
	public:
		friend ImGuiManager* theImGuiManager();

		void onAttach();
		void onDetach();

		void begin();
		void end();
		void onEvent(Event& e);

	private:
		ImGuiManager() = default;
		~ImGuiManager() = default;
		bool m_block_events = true;
	};

	extern ImGuiManager* theImGuiManager();
}