#include "line.hpp"

namespace juice {
    Line::Line(const glm::vec2& a, const glm::vec2& b, float width, const glm::vec3& color)
        : a(a), b(b), length(), width(width), m_color(color)
    {
        float vertices[] = {
             0.5f,  0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        m_VertexArray = MakeRef<VertexArray>();
        m_VertexBuffer = MakeRef<VertexBuffer>(vertices, sizeof(vertices));
        m_IndexBuffer = MakeRef<IndexBuffer>(indices, sizeof(indices));

        BufferLayout buff_layout = BufferLayout({
                    { ShaderDataType::Float3, "u_Position" }
                });

        m_VertexBuffer->SetLayout(buff_layout);

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        CalculateModelViewMatrix();
    }

    Line::~Line()
    {

    }

    void Line::SetRotation(float _r)
    {

    }

    void Line::move(const glm::vec2& position)
    {

    }

    void Line::Draw(const ref<Shader>& shader)
    {
        shader->SetMat4("u_ModalViewMatrix", m_model);
        shader->SetFloat3("u_Color", m_color);

        Renderer::Submit(m_VertexArray, shader);
    }
}
