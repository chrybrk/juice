#pragma once

extern juice::Application* juice::CreateApplication();

int main(int argc, char** argv)
{
    juice::Log::Init();
	JUICE_CORE_WARN("Initialized Log!");
    auto app = juice::CreateApplication();
    app->Run();
    delete app;
}
