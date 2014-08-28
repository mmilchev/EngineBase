#ifndef FPS_METER_H
#define FPS_METER_H

#include <string>
#include <SFML/System/Clock.hpp>
#include <vector>

class GameTime
{
public:
	GameTime();
	~GameTime();
	static int CalculateFramesPerSecond();
	static float DeltaTime();
	static float Time();
	static float AverageFrameTime();
	static int FramesPerSecond();
	static std::string GetTextInfo();
	void Update();
	
private:
	float m_LastFrameTime;
	float m_CurrentFrameTime;
	sf::Clock m_Clock;
	std::vector<float> m_FrameTimeSamples;

	static GameTime* sInstance;

	void AddSample(float sample);
};

#endif