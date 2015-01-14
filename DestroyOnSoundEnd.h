#pragma once
#include "DynamicBehaviour.h"

class SoundComponent;

class DestroyOnSoundEnd :
	public DynamicBehaviour
{
public:
	DestroyOnSoundEnd();

	void Awake() override;

	void Update() override;

private:
	SoundComponent* m_Sound;
};

