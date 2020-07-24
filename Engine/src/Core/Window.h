#pragma once

#include "pch.h"

#include "Core/Logger.h"

#include <SDL.h>
#include <string>
#include <glm/vec2.hpp>

namespace stick2d {

	struct WindowProps
	{
		std::string title = "STICK2D ENGINE";
		std::string icon = "";
		glm::ivec2 resolution = { 1280, 720 };
		bool isFullscreen = false;
		bool isResizable = true;
		bool isVsync = true;
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		void onUpdate();

		SDL_Window* getWindowHandler() { return m_window; }
		SDL_GLContext* getGlContext() { return &m_gl_context; }
		int getWidth() { return m_props.resolution.x; }
		int getHeight() { return m_props.resolution.y; }
		bool isVSync() { return m_props.isVsync; }
		bool isResizable() { return m_props.isResizable; }
		bool isFullscreen() { return m_props.isFullscreen; }

		// Window attributes
		void setVSync(bool enabled);
		void setResizable(bool enabled);
		void setFullscreen(bool enabled);
		void setWindowTitle(std::string_view title);
		void setResolution(glm::ivec2 resolution);
		void setWindowIcon(std::string_view icon_filename);
		void clearScreen();
		void updateScreen();

	private:
		Window();
		~Window();

		SDL_Window* m_window;
		WindowProps m_props;
		SDL_GLContext m_gl_context;

		friend Window* theWindow();
	};

	extern Window* theWindow();
}