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
	m_StartValue = from;
	m_TargetValue = to;
	m_Coef = 0;
	m_MaxTime = time;
	m_Time = 0;
	m_Type = type;
	m_FinishedThisFrame = false;
}

void Tween::Update( float dt )
{
	bool finishedBefore = Done();
	m_Time = Clamp(m_Time + dt, 0, m_MaxTime);
	if(m_Type == Linear)
	{
		m_Coef = m_Time / m_MaxTime;
	}
	else if (m_Type == SineWave)
	{
		m_Coef = (sin(PI * (m_Time / m_MaxTime - 1 / 2.f)) + 1) / 2.f;
	}
	else if (m_Type == Logaritmic)
	{
		m_Coef = log10(1 + (m_Time / m_MaxTime) * 9); //log10
	}

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
