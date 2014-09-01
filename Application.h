#ifndef SCENE_WINDOW_H
#define SCENE_WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "GraphicsModule.h"
#include "PhysicsModule.h"
#include "SceneModule.h"
#include "GameTime.h"
#include "ResourceManager.h"

class Application
{
public:
	Application(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style, const sf::ContextSettings& settings);

	void Initialize(bool useRenderTexture);

	void Run();

	static sf::RenderTarget* GetDefaultRenderTarget();
	static sf::RenderWindow& GetWindow();
	static SceneModule& GetSceneModule();
	static PhysicsModule& GetPhysicsModule();
	static GraphicsModule& GetGraphicsModule();
private:
	GraphicsModule m_GraphicsModule;
	PhysicsModule m_PhysicsModule;
	SceneModule	m_SceneModule;

	//Chaches resources for reuse
	ResourceManager m_ResourceManager;

	//Holds time info: dt, fps etc..
	GameTime m_GameTime;

	sf::RenderWindow m_Window;

	bool m_UseRenderTexture;

	static Application* sInstance;

	void HandleInput();
	void UpdateFrame();
	void RenderFrame();
};

#endif