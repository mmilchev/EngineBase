#include "DestroyOnSoundEnd.h"
#include "SoundComponent.h"
#include "GameObject.h"

#include <SFML\Audio\SoundBuffer.hpp>

DestroyOnSoundEnd::DestroyOnSoundEnd()
{
}


void DestroyOnSoundEnd::Update()
{
	auto& sound = m_Sound->GetSound();
	if (m_Sound->WasSoundPlayed() && sound.getStatus() == sf::Sound::Stopped)
	{
		GameObject::Destroy(m_GameObject);
	}
}

void DestroyOnSoundEnd::Awake()
{
	m_Sound = m_GameObject->GetComponent<SoundComponent>();
}
