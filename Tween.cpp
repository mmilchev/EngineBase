#include "Tween.h"
#include <iostream>
#include "Utils.h"

Tween::Tween(bool isAngle)
: m_StartValue(0), m_TargetValue(0), m_Coef(1), 
m_Time(1), m_MaxTime(1), m_FinishedThisFrame(false), m_IsAngle(isAngle)
{
}

void Tween::Set( float from, float to, float time, TweenType type /*= TweenType::Linear*/ )
{
	switch (type)
	{
	case Tween::Linear:
		Set(from, to, time, new LinearTween());
		break;
	case Tween::SineWave:
		Set(from, to, time, new SineTween());
		break;
	case Tween::Logaritmic:
		Set(from, to, time, new LogTween());
		break;
	case Tween::Expo3:
		Set(from, to, time, new ExpoTween(3));
		break;
	case Tween::Expo5:
		Set(from, to, time, new ExpoTween(5));
		break;
	case Tween::Expo7:
		Set(from, to, time, new ExpoTween(7));
		break;
	default:
		break;
	}
}

void Tween::Set(float from, float to, float time, ITweenFunction* function)
{
	m_StartValue = from;
	m_TargetValue = to;
	m_Coef = 0;
	m_MaxTime = time;
	m_Time = 0;

	m_TweenFunction = std::unique_ptr<ITweenFunction>(function);

	m_FinishedThisFrame = false;
}

void Tween::Update( float dt )
{
	bool finishedBefore = Done();
	m_Time = Clamp(m_Time + dt, 0, m_MaxTime);
	
	m_Coef = m_TweenFunction->GetCoefValue(m_Time / m_MaxTime);

	if(Done())
		m_Coef = 1;

	m_FinishedThisFrame = finishedBefore != Done();
}

float Tween::GetValue() const
{
	return m_IsAngle ? LerpAngle(m_StartValue, m_TargetValue, m_Coef) : Lerp(m_StartValue, m_TargetValue, m_Coef);
}

bool Tween::Done() const
{
	return m_Coef > 0.9999f;
}

bool Tween::JustFinished() const
{
	return m_FinishedThisFrame;
}

float Tween::LinearTween::GetCoefValue(float timeCoef)
{
	return timeCoef;
}

float Tween::SineTween::GetCoefValue(float timeCoef)
{
	return (sin(PI * (timeCoef - 1 / 2.f)) + 1) * 0.5f;
}

float Tween::LogTween::GetCoefValue(float timeCoef)
{
	return log10(1 + timeCoef * 9); //log10
}

float Tween::ExpoTween::GetCoefValue(float timeCoef)
{
	return (powf(2 * timeCoef - 1, m_Power) + 1) * 0.5f;
}

Tween::ExpoTween::ExpoTween(float power)
	:m_Power(power)
{
}
