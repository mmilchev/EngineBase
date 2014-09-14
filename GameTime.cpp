#include "GameTime.h"
#include <assert.h>

GameTime* GameTime::sInstance = nullptr;

GameTime::GameTime()
	:m_LastFrameTime(0), m_CurrentFrameTime(0), m_TimeScale(1)
{
	//Only one instance of GameTime is allowed
	assert(sInstance == nullptr);
	sInstance = this;

	m_FrameTimeSamples.push_back(0); //initial
}

float GameTime::DeltaTime()
{
	return DeltaTimeUnscaled() * sInstance->m_TimeScale;
}

float GameTime::DeltaTimeUnscaled()
{
	return sInstance->m_CurrentFrameTime - sInstance->m_LastFrameTime;
}


float GameTime::Time()
{
	return sInstance->m_Clock.getElapsedTime().asSeconds();
}

int GameTime::FramesPerSecond()
{
	return int(1 / AverageFrameTime());
}

void GameTime::Update()
{
	m_LastFrameTime = m_CurrentFrameTime;
	m_CurrentFrameTime = m_Clock.getElapsedTime().asSeconds();
	AddSample(DeltaTime());
}

void GameTime::Reset()
{
	m_LastFrameTime = 0;
	m_CurrentFrameTime = 0;
	m_FrameTimeSamples.clear();
	m_FrameTimeSamples.push_back(0);

	m_Clock.restart();
}

std::string GameTime::GetTextInfo()
{
	std::string s;
	s.append("Fps: " + std::to_string(long double(FramesPerSecond())) + "\nFrametime: " + 
		std::to_string(static_cast<long double>(AverageFrameTime()) * 1000) + "ms");
	return s;
}

int GameTime::CalculateFramesPerSecond()
{
	return static_cast<int>(1 / DeltaTime());
}

void GameTime::AddSample( float sample )
{
	m_FrameTimeSamples.push_back(sample);
	int const MAX_FRAME_SAMPLES = 60;
	if(m_FrameTimeSamples.size() > MAX_FRAME_SAMPLES)
	{
		m_FrameTimeSamples.erase(m_FrameTimeSamples.begin(), m_FrameTimeSamples.begin() + 5); //remove oldest
	}
}

float GameTime::AverageFrameTime()
{
	float sum = 0;
	int count = 0;
	for (auto it = sInstance->m_FrameTimeSamples.begin(); it != sInstance->m_FrameTimeSamples.end(); ++it)
	{
		sum += *it;
		count++;
	}

	return sum / count;
}

void GameTime::SetScale(float scale)
{
	sInstance->m_TimeScale = scale;
}

float GameTime::GetScale()
{
	return sInstance->m_TimeScale;
}