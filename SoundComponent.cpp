#include "SoundComponent.h"
#include "ResourceManager.h"


SoundComponent::SoundComponent()
{
}

void SoundComponent::LoadSound(std::string const& filename)
{
	m_Sound.setBuffer(ResourceManager::GetSound(filename));
}

void SoundComponent::Play()
{
	m_Sound.play();
}
