#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "camera/orthographic_camera.hpp"
#include "graphics.hpp"
#include "shader/shader.hpp"

namespace juice {

	class RendererCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		inline static void Draw(const ref<VertexArray> vertexArray)
		{
			glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
	};

	class Renderer
	{
	public:
		static void Begin(OrthographicCamera& camera);
		static void Submit(const ref<VertexArray>& vertexArray, const ref<Shader>& shader);
	private:
		struct OrthographicCameraMatrix
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static OrthographicCameraMatrix* m_RendererElements;
	};
}
