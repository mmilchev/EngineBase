#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <Box2D/Common/b2Math.h>
#include <SFML/System/Vector2.hpp>

#define PI 3.14159265f

std::vector<std::string> GetDirFiles(std::string const& path);
std::string GetFileExtension(std::string const& file);
std::string GetWorkingDirectory();

b2Vec2 ToBox2DWorld(b2Vec2 const& vec);
b2Vec2 FromBox2DWorld(b2Vec2 const& vec);

sf::Vector2f ToBox2DWorld(sf::Vector2f const& vec);
sf::Vector2f FromBox2DWorld(sf::Vector2f const& vec);

float ToBox2DWorld(float n);
float FromBox2DWorld(float n);

sf::Vector2f BoxToSf(b2Vec2 const& vec);
b2Vec2 SfToBox(sf::Vector2f const& vec);

sf::Vector2f ToVecf(sf::Vector2u const& vec);
sf::Vector2f ToVecf(sf::Vector2i const& vec);

float RadToDeg(float angle);
float DegToRad(float angle);

float GetRotationAngle(sf::Vector2f const& direction);
bool AreAnglesEqual(float lhsAngle, float rhsAngle, float epsilon);

float Lerp(float from, float to, float coef);
sf::Vector2f Lerp(sf::Vector2f const& from, sf::Vector2f const& to, float coef);
float LerpAngle(float from, float to, float coef);

float Randf();
float Randf(float minNum, float maxNum);
int RandInt(int minNum, int maxNum);

float Clamp(float val, float bottom, float top);
float ClampTop(float val, float top);
float ClampBottom(float val, float bottom);

std::string ReplaceAll(std::string const& str, std::string const& replaceInstance, std::string const& replaceStr);
void SplitString(std::string const& str, std::string const& separator, std::vector<std::string>& outVec);

template<class VecType>
sf::Vector2<VecType> Normalize(sf::Vector2<VecType> const& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (fabs(length) > 0.00000001)
		return sf::Vector2<VecType>(source.x / length, source.y / length);

	return source;
}

template<class VecType>
float Length(sf::Vector2<VecType> const& source)
{
	return sqrtf((source.x * source.x) + (source.y * source.y));
}

template<class VecType>
float Dot(sf::Vector2<VecType> const& lhs, sf::Vector2<VecType> const& rhs)
{
	return static_cast<float>(lhs.x * rhs.x + lhs.y * rhs.y);
}

#endif