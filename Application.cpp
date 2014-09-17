#include "Application.h"
#include <SFML/Window/Event.hpp>

#include <iostream>
#include "Input.h"

Application* Application::sInstance = nullptr;

Application::Application(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style, const sf::ContextSettings& settings)
: m_Window(mode, title, style, settings)
{
	sInstance = this;
}

void Application::Initialize(bool useRenderTexture)
{
	m_ResourceManager.PreloadResources();

	m_UseRenderTexture = useRenderTexture;

	m_GraphicsModule.Initialize(m_Window.getSize());
}

void Application::Run()
{
	m_GameTime.Reset();

	while (m_Window.isOpen())
	{
		//Update the time
		m_GameTime.Update();

		HandleInput();

		UpdateFrame();

		RenderFrame();
	}
}

sf::RenderTarget* Application::GetDefaultRenderTarget()
{
	if (sInstance->m_UseRenderTexture)
		return GetGraphicsModule().GetRenderTexture();

	return &sInstance->m_Window;
}

sf::RenderWindow& Application::GetWindow()
{
	return sInstance->m_Window;
}

SceneModule& Application::GetSceneModule()
{
	return sInstance->m_SceneModule;
}

PhysicsModule& Application::GetPhysicsModule()
{
	return sInstance->m_PhysicsModule;
}

GraphicsModule& Application::GetGraphicsModule()
{
	return sInstance->m_GraphicsModule;
}

void Application::HandleInput()
{
	Input::ClearCurrentStates();

	sf::Event ev;
	while (m_Window.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			m_Window.close();
			break;
		}
		Input::HandleEvent(ev);
	}

	Input::Update();
}

void Application::UpdateFrame()
{
	//Instantiate new objects and delete old objects
	m_SceneModule.ProcessQueuedObjects();

	//Initial update
	m_SceneModule.Update();

	//Update physics
	m_PhysicsModule.StepWorld();

	//Late update after everything else
	m_SceneModule.LateUpdate();
}

void Application::RenderFrame()
{
	/* Workaround over a bug in SFML. Render textures won't clear properly on some graphics cards
	if this isn't called */
	m_Window.resetGLStates();

	m_Window.clear(); //Clear the backbuffer

	m_GraphicsModule.Render();

	if (m_UseRenderTexture)
	{
		m_Window.draw(m_GraphicsModule.GetSprite());
	}
	
	m_Window.display();
}

void Application::ClearScene()
{
	sInstance->m_SceneModule.DeleteAllObjects();
}

void Application::OnNewLevelLoaded()
{
	sInstance->m_GameTime.Reset();
}

void Application::ProcessQeuedObjectsInModules()
{
	sInstance->m_PhysicsModule.ProcessQueuedObjects();
	sInstance->m_GraphicsModule.ProcessQueuedObjects();
}
