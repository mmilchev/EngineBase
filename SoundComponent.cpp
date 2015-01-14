#include "SoundComponent.h"
#include "ResourceManager.h"


SoundComponent::SoundComponent()
:m_WasPlayed(false)
{
}

void SoundComponent::LoadSound(std::string const& filename)
{
	m_Sound.setBuffer(ResourceManager::GetSound(filename));
}

void SoundComponent::Play()
{
	m_Sound.play();
	m_WasPlayed = true;
}

void SoundComponent::PlayOneShot(std::string const& filename)
{
	LoadSound(filename);
	Play();
}
