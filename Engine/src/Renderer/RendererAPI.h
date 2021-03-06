#pragma once

#include <glm/glm.hpp>

#include "Renderer/VertexArray.h"

namespace stick2d {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		static API GetAPI() { return s_API; }
		static std::unique_ptr<RendererAPI> Create();
	private:
		static API s_API;
	};

}
