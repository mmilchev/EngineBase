#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <map>
#include <string>
#include <SFML/System/Vector2.hpp>

class ConfigManager
{
public:

	static void LoadFile(const std::string& filename);

	static int GetInt(const std::string& key);
	static float GetFloat(const std::string& key);
	static bool GetBool(const std::string& key);
	static const std::string& GetString(const std::string& key);
	static const sf::Vector2f& GetVector(const std::string& key);
private:
	static std::map<std::string, float>			sFloatConsts;
	static std::map<std::string, int>			sIntConsts;
	static std::map<std::string, bool>			sBoolConsts;
	static std::map<std::string, std::string>	sStringConsts;
	static std::map<std::string, sf::Vector2f>	sVectorConsts;
};

#endif