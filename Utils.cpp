#include "Utils.h"
#include <algorithm>
#include <string>
#include <vector>

#include <dirent.h>
#include <sys/types.h>

#ifdef _WIN32 
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define PI 3.14159265f
#define B2_SCALE_COEF 0.02f

//Source: http://www.cplusplus.com/forum/unices/3548/
//Return an ASCII-sorted vector of filename entries in a given directory.
std::vector <std::string> GetDirFiles(std::string const& path)
{
	std::vector<std::string> result;
	dirent* de;
	DIR* dp;
	errno = NULL;
	dp = opendir(path.empty() ? "." : path.c_str());
	if (dp)
	{
		while (true)
		{
			errno = NULL;
			de = readdir(dp);
			if (de == NULL) break;
			result.push_back(std::string(de->d_name));
		}
		closedir(dp);
		std::sort(result.begin(), result.end());
	}

	return result;
}

std::string GetFileExtension(std::string const& filename)
{
	auto dotIndex = filename.find_last_of(".");
	if (dotIndex != std::string::npos)
		return filename.substr(dotIndex + 1);
	return "";
}

std::string GetWorkingDirectory()
{
	char filePath[256];

	if (GetCurrentDir(filePath, sizeof(filePath)))
		return std::string(filePath);

	return "";
}

b2Vec2 ToBox2DWorld(b2Vec2 const& vec)
{
	return b2Vec2(vec.x * B2_SCALE_COEF, vec.y * B2_SCALE_COEF);
}

b2Vec2 FromBox2DWorld(b2Vec2 const& vec)
{
	return b2Vec2(vec.x / B2_SCALE_COEF, vec.y / B2_SCALE_COEF);
}

sf::Vector2f ToBox2DWorld(sf::Vector2f const& vec)
{
	return sf::Vector2f(vec.x * B2_SCALE_COEF, vec.y * B2_SCALE_COEF);
}

sf::Vector2f FromBox2DWorld(sf::Vector2f const& vec)
{
	return sf::Vector2f(vec.x / B2_SCALE_COEF, vec.y / B2_SCALE_COEF);
}

float ToBox2DWorld(float n)
{
	return n*B2_SCALE_COEF;
}

float FromBox2DWorld(float n)
{
	return n / B2_SCALE_COEF;
}

sf::Vector2f BoxToSf(b2Vec2 const& vec)
{
	return sf::Vector2f(vec.x, vec.y);
}

b2Vec2 SfToBox(sf::Vector2f const& vec)
{
	return b2Vec2(vec.x, vec.y);
}

float RadToDeg(float angle)
{
	return (angle * 180 / PI);
}

float DegToRad(float angle)
{
	return (angle * PI / 180);
}

float GetRotationAngle(sf::Vector2f const& direction)
{
	float angle = RadToDeg(atan2(direction.y, direction.x));
	return (angle < 0) ? (angle + 360) : angle;
}

bool AreAnglesEqual(float lhsAngle, float rhsAngle, float epsilon)
{
	float delta = fabs(lhsAngle - rhsAngle);
	return (delta >= -epsilon && delta <= epsilon) || 
		(delta >= 360 - epsilon && delta <= 360 + epsilon);
}

float ClampBottom(float val, float bottom)
{
	if (val < bottom)
		return bottom;
	return val;
}

float ClampTop(float val, float top)
{
	if (val > top)
		return top;
	return val;
}

float Clamp(float val, float bottom, float top)
{
	if (val > top)
		return top;
	else if (val < bottom)
		return bottom;
	return val;
}

float Lerp(float from, float to, float coef)
{
	return from + (to - from) * coef;
}

sf::Vector2f Lerp(sf::Vector2f const& from, sf::Vector2f const& to, float coef)
{
	return sf::Vector2f(Lerp(from.x, to.x, coef), Lerp(from.y, to.y, coef));
}

float LerpAngle(float start, float end, float coef)
{
	float difference = fabs(end - start);
	if (difference > 180)
	{
		// We need to add on to one of the values.
		auto& val = (end > start) ? start : end;
		val += 360;
	}

	float value = (start + ((end - start) * coef));

	// Wrap it..
	float rangeZero = 360;

	if (value >= 0 && value <= 360)
		return value;

	return fmod(value, rangeZero); 
	
	/*
	float mod360 = 360;
	float shortest_angle = modff(modff(to - from, &mod360) + 540, &mod360) - 180;
	return shortest_angle * coef;*/
}

float Randf()
{
	return (static_cast<float>(rand()) / RAND_MAX);
}

float Randf(float minNum, float maxNum)
{
	assert(maxNum >= minNum);

	return minNum + (static_cast<float>(rand()) / RAND_MAX) * (maxNum - minNum);
}

int RandInt(int minNum, int maxNum)
{
	assert(maxNum >= minNum);

	return minNum + rand() % (maxNum - minNum);
}

sf::Vector2f ToVecf(sf::Vector2u const& vec)
{
	return sf::Vector2f(static_cast<float>(vec.x), static_cast<float>(vec.y));
}

sf::Vector2f ToVecf(sf::Vector2i const& vec)
{
	return sf::Vector2f(static_cast<float>(vec.x), static_cast<float>(vec.y));
}