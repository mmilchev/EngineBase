#pragma once

class Tween
{
public:
	enum TweenType
	{
		Linear,
		SineWave,
		Logaritmic
	};

	explicit Tween(bool isAngle = false);

	void Set(float from, float to, float time, TweenType type = TweenType::Linear);

	void Update(float dt);
	float GetValue() const;

	bool Done() const;
	bool JustFinished() const;
private:
	TweenType m_Type;
	float m_StartValue;
	float m_TargetValue;
	float m_Coef;
	float m_MaxTime;
	float m_Time;
	bool m_FinishedThisFrame;
	bool m_IsAngle;
};