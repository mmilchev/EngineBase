#include "Application.h"
#include <SFML/Window/Event.hpp>

#include <iostream>
#include "Input.h"

Application* Application::sInstance = nullptr;

Application::Application(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style, const sf::ContextSettings& settings )
: m_Window(mode, title, style, settings)
{
	sInstance = this;
}

void Application::Initialize()
{
	m_ResourceManager.PreloadResources();

	m_GraphicsModule.Initialize(m_Window.getSize());
}

void Application::Run()
{
	while (m_Window.isOpen())
	{
		//Update the time
		m_GameTime.Update();

		HandleInput();

		UpdateFrame();

		RenderFrame();
	}
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
	//Instantiate new objects
	m_SceneModule.SignalQueuedObjects();
	m_PhysicsModule.InitQueuedBodies();

	//Initial update
	m_SceneModule.Update();

	//Update physics
	m_PhysicsModule.StepWorld();

	//Late update after everything else
	m_SceneModule.LateUpdate();
	
	//Remove destroyed obejcts
	m_SceneModule.DestroyRemovedObjects();
}

void Application::RenderFrame()
{
	/* Workaround over a bug in SFML. Render textures won't clear properly on some graphics cards 
	if this isn't called */
	m_Window.resetGLStates();

	m_Window.clear(); //Clear the backbuffer

	m_GraphicsModule.Render();

	m_Window.draw(m_GraphicsModule.GetSprite());

	m_Window.display();
}