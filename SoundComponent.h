#ifndef SOUND_COMPONENT_H
#define SOUND_COMPONENT_H

#include "Component.h"
#include <SFML/Audio/Sound.hpp>

class SoundComponent :
	public Component
{
public:
	SoundComponent();

	void LoadSound(std::string const& filename);
	void Play();

	inline sf::Sound& GetSound() { return m_Sound; }
private:
	sf::Sound m_Sound;
};

#endif // ifndef AUDIO_SOURCE_H

