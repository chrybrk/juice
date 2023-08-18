#include "juice.hpp"

class Triangle : public juice::Layer
{
    public:
        Triangle()
            : camera(0.0f, 800.0f, 600.0f, 0.0f)
        {
        }

        void OnAttach() override
        {
            shader = juice::MakeRef<juice::Shader>("cmn", "./assets/glsl/main.vert", "./assets/glsl/main.frag");
            shader->Bind();

            rect = juice::MakeRef<juice::Rect>(100.0f, 100.0f, 100.0f, 100.0f, glm::vec3(0.0f, 0.3f, 0.3f));
            pent = juice::MakeRef<juice::Pent>(200.0f, 200.0f, 100.0f, 100.0f, glm::vec3(0.0f, 0.3f, 0.3f));
            line = juice::MakeRef<juice::Line>(glm::vec2(300.0f, 300.0f), glm::vec2(400.0f, 400.0f), 5.0f, glm::vec3(0.1f, 0.2f, 0.4f));

            juice::Renderer::Begin(camera);
        }

        void OnUpdate(float dt) override
        {
            rect->Draw(shader);
            pent->Draw(shader);
            line->Draw(shader);
        }

    private:
        juice::OrthographicCamera camera;
        juice::ref<juice::Shader> shader;
        juice::ref<juice::Rect> rect;
        juice::ref<juice::Pent> pent;
        juice::ref<juice::Line> line;
};

class Sandbox : public juice::Application
{
    public:
        Sandbox()
        {
            juice::Window::SetClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });
            PushLayer(new Triangle());
        }

        ~Sandbox()
        {
        }
};

juice::Application* juice::CreateApplication()
{
    Sandbox* app = new Sandbox();
    return app;
}
