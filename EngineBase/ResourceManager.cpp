#include "ResourceManager.h"
#include "Utils.h"

ResourceManager* ResourceManager::m_Instance = nullptr;

std::string			ResourceManager::sWorkingDir;
const std::string	ResourceManager::ksResourceFolder = "Resources/";
const std::string	ResourceManager::ksLevelFolder = "Levels/";
const std::string	ResourceManager::ksShaderFolder = "Shaders/";
const std::string	ResourceManager::ksSoundsFolder = "Sounds/";
const std::string	ResourceManager::ksMusicFolder = "Music/";
const std::string	ResourceManager::ksGraphicsFolder = "Graphics/";
const std::string	ResourceManager::ksFontFolder = "Fonts/";

ResourceManager::ResourceManager() 
{
	assert(m_Instance == nullptr);
	m_Instance = this;
	sWorkingDir = GetWorkingDirectory();
}

ResourceManager::~ResourceManager()
{

}

using namespace std;

string ResourceManager::GetResourceFilePath(const std::string& subDir, const std::string& filename)
{
	std::string filePath;
	filePath.append(ksResourceFolder);
	filePath.append(subDir);
	filePath.append(filename);
	return filePath;
}

sf::Font& ResourceManager::GetFont( const std::string& filename )
{
	auto& fonts = m_Instance->m_Fonts;
	std::string filePath = m_Instance->GetResourceFilePath(ksFontFolder, filename);
	if (fonts.find(filePath) == fonts.end())
	{
		sf::Font font;
		font.loadFromFile(filePath);
		fonts[filePath] = font;
	}

	return fonts[filePath];
}

sf::Texture& ResourceManager::GetTexture(const std::string& filename)
{
	auto& textures = m_Instance->m_Textures;
	string filePath = m_Instance->GetResourceFilePath(ksGraphicsFolder, filename);
	if (textures.find(filePath) == textures.end())
	{
		sf::Texture texture;
		texture.loadFromFile(filePath);
		texture.setSmooth(true);
		textures[filePath] = texture;
	}

	return textures[filePath];
}

sf::SoundBuffer& ResourceManager::GetSound( const std::string& filename )
{
	auto& sBuffers = m_Instance->m_Sounds;
	string filePath = m_Instance->GetResourceFilePath(ksSoundsFolder, filename);
	if (sBuffers.find(filePath) == sBuffers.end())
	{
		sf::SoundBuffer buffer;
		buffer.loadFromFile(filePath);
		sBuffers[filePath] = buffer;
	}

	return sBuffers[filePath];
}

sf::Shader& ResourceManager::GetShader(const std::string& vShader, const std::string& fShader)
{
	const std::string vertexPath = m_Instance->GetResourceFilePath(ksShaderFolder, vShader);
	const std::string fragmentPath = m_Instance->GetResourceFilePath(ksShaderFolder, fShader);
	const std::string combined = vertexPath + fragmentPath;
	auto& shaders = m_Instance->m_Shaders;
	if (shaders.find(combined) == shaders.end())
	{
		shaders[combined] = std::unique_ptr<sf::Shader>(new sf::Shader());
		shaders[combined]->loadFromFile(vertexPath, fragmentPath);
	}

	return *shaders[combined];
}


sf::Music& ResourceManager::GetMusic(const std::string& filename)
{
	string filePath = m_Instance->GetResourceFilePath(ksMusicFolder, filename);
	auto& mTracks = m_Instance->m_MusicTracks;
	if (mTracks.find(filePath) == mTracks.end())
	{
		mTracks[filePath] = std::unique_ptr<sf::Music>(new sf::Music());
		mTracks[filePath]->openFromFile(filePath);
	}

	return *mTracks[filePath];
}

//Preloads resrouces from all folders
void ResourceManager::PreloadResources()
{
	PreloadResources(sWorkingDir + "/" + ksResourceFolder);
	PreloadResources(sWorkingDir + "/" + ksResourceFolder + "/" + ksGraphicsFolder);
	PreloadResources(sWorkingDir + "/" + ksResourceFolder + "/" + ksMusicFolder);
	PreloadResources(sWorkingDir + "/" + ksResourceFolder + "/" + ksSoundsFolder);
	PreloadResources(sWorkingDir + "/" + ksResourceFolder + "/" + ksFontFolder);
}

void ResourceManager::PreloadResources(const std::string& dirPath)
{
	std::vector<std::string> files = GetDirFiles(dirPath);
	for(auto& file : files)
	{
		auto ext = GetFileExtension(file);
		
		if(ext == "png" || ext == "jpg")
			GetTexture(file);
		else if(ext == "flac" || ext == "ogg")
			GetSound(file);
		else if(ext == "tff")
			GetFont(file);
	}
}

void ResourceManager::ReleaseResources()
{
	m_Textures.clear();
	m_Fonts.clear();
	m_Sounds.clear();
	m_MusicTracks.clear();
}
