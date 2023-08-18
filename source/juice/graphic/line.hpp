#pragma once

#include "renderer/graphics.hpp"
#include "renderer/renderer.hpp"

namespace juice {
    class Line
    {
        public:
            Line(const glm::vec2& a, const glm::vec2& b, float width, const glm::vec3& color);
            ~Line();

            void SetRotation(float _r);
            void move(const glm::vec2& position);

            void Draw(const ref<Shader>& shader);

        public:
            glm::vec2 a, b;
            float length, width, r;

        private:
            inline void CalculateModelViewMatrix()
            {
                m_model = glm::mat4(1.0f);

                m_model = glm::translate(m_model, glm::vec3(a.x, b.y, 0.0f));
                m_model = glm::translate(m_model, glm::vec3(0.5f * length, 0.5f * width, 0.0f));
                m_model = glm::rotate(m_model, r, glm::vec3(0.0f, 0.0f, 1.0f));
                m_model = glm::translate(m_model, glm::vec3(-0.5f * length, -0.5f * width, 0.0f));
                m_model = glm::scale(m_model, glm::vec3(length, width, 1.0f));
            }

        private:
            ref<juice::VertexArray> m_VertexArray;
            ref<juice::VertexBuffer> m_VertexBuffer;
            ref<juice::IndexBuffer> m_IndexBuffer;

            glm::vec3 m_color;
            glm::mat4 m_model;
    };
}
