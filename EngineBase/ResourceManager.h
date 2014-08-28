#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <SFML\Audio.hpp>
#include <system_error>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <memory>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	//Getters for resources
	static sf::Font& GetFont(const std::string& filename);
	static sf::Texture& GetTexture(const std::string& filename);
	static sf::SoundBuffer& GetSound(const std::string& filePath);
	static sf::Music& GetMusic(const std::string& filename);
	static sf::Shader& GetShader(const std::string& vShader, const std::string& fShader);
	
	//Preloads assets in a current directory
	void PreloadResources(const std::string& dirPath);
	//Preloads assets in default directories
	void PreloadResources();
	
	//Releases all assets fron chache
	void ReleaseResources();

	//Folders holding the assets
	static std::string sWorkingDir;
	
	static const std::string ksResourceFolder;
	static const std::string ksLevelFolder;
	static const std::string ksShaderFolder;
	static const std::string ksSoundsFolder;
	static const std::string ksMusicFolder;
	static const std::string ksGraphicsFolder;
	static const std::string ksFontFolder;

	//Shortcut for getting the right path for the file
	static std::string GetResourceFilePath(const std::string& subDir, const std::string& filename);
private:
	//Chached resources
	std::map<std::string, sf::Font>						m_Fonts;
	std::map<std::string, sf::Texture>					m_Textures;
	std::map<std::string, sf::SoundBuffer>				m_Sounds;
	std::map<std::string, std::unique_ptr<sf::Shader>>	m_Shaders;
	std::map<std::string, std::unique_ptr<sf::Music>>	m_MusicTracks;

	//Singleton
	static ResourceManager* m_Instance;
};

#endif