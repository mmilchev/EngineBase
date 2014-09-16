#pragma once

#include <memory>

class Tween
{
public:
	class ITweenFunction
	{
	public:
		virtual ~ITweenFunction(){ }
		virtual float GetCoefValue(float timeCoef) = 0;
	};
	enum TweenType
	{
		Linear,
		SineWave,
		Logaritmic,
		Expo3,
		Expo5,
		Expo7
	};

	explicit Tween(bool isAngle = false);

	void Set(float from, float to, float time, TweenType type = TweenType::Linear);
	void Set(float from, float to, float time, ITweenFunction* function);

	void Update(float dt);
	float GetValue() const;

	bool Done() const;
	bool JustFinished() const;
private:
	class LinearTween
		: public ITweenFunction
	{
		virtual float GetCoefValue(float timeCoef) override;
	};
	class SineTween
		: public ITweenFunction
	{
		virtual float GetCoefValue(float timeCoef) override;
	};
	class LogTween
		: public ITweenFunction
	{
		virtual float GetCoefValue(float timeCoef) override;
	};
	class ExpoTween
		: public ITweenFunction
	{
	public:
		ExpoTween(float power);

		virtual float GetCoefValue(float timeCoef) override;
	
	private:
		float m_Power;
	};

	std::unique_ptr<ITweenFunction> m_TweenFunction;
	float m_StartValue;
	float m_TargetValue;
	float m_Coef;
	float m_MaxTime;
	float m_Time;
	bool m_FinishedThisFrame;
	bool m_IsAngle;
};