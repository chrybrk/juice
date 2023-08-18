#include "pent.hpp"

namespace juice {

    Pent::Pent(float x, float y, float w, float h, glm::vec3 color)
        : x(x), y(y), w(w), h(h), r(0.0f), m_color(color)
    {
        float vertices[] = {
             0.0f, -1.0f, 0.0f,
             1.0f,  0.0f, 0.0f,
            -1.0f,  0.0f, 0.0f,
             0.5f,  1.0f, 0.0f,
            -0.5f,  1.0f, 0.0f,
             0.0f,  0.0f, 0.0f
        };
        unsigned int indices[] = {
            0, 1, 2,
            1, 5, 3,
            3, 5, 4,
            4, 5, 2
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

    Pent::~Pent()
    {

    }

    void Pent::SetRotation(float _r)
    {
        r = _r;
        CalculateModelViewMatrix();
    }
    
    void Pent::move(const glm::vec2& position)
    {
        x += position.x;
        y += position.y;
        CalculateModelViewMatrix();
    }

    void Pent::Draw(const ref<Shader>& shader)
    {
        shader->SetMat4("u_ModalViewMatrix", m_model);
        shader->SetFloat3("u_Color", m_color);

        Renderer::Submit(m_VertexArray, shader);
    }

}
