#include "pch.hpp"
#include "renderer.hpp"

namespace juice {

	Renderer::OrthographicCameraMatrix* Renderer::m_RendererElements = new Renderer::OrthographicCameraMatrix;

	void Renderer::Begin(OrthographicCamera& camera) 
	{
		m_RendererElements->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(const ref<VertexArray>& vertexArray, const ref<Shader>& shader)
	{
		shader->Bind();
		vertexArray->Bind();
		shader->SetMat4("u_ViewPorjectionMatrix", m_RendererElements->ViewProjectionMatrix);

		RendererCommand::Draw(vertexArray);
	}

}
