#pragma once

extern bbzl::Application* bbzl::CreateApplication();

int main(int argc, char** argv)
{
    bbzl::Log::Init();

    auto app = bbzl::CreateApplication();
    app->run();

    delete app;
}
