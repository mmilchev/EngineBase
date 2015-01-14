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
	void PlayOneShot(std::string const& filename);

	inline sf::Sound& GetSound() { return m_Sound; }
	inline bool WasSoundPlayed() const { return m_WasPlayed; }
private:
	bool m_WasPlayed;
	sf::Sound m_Sound;
};

#endif // ifndef AUDIO_SOURCE_H

