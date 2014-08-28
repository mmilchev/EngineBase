#include "ConfigManager.h"

#include <fstream>

std::map<std::string, float>		ConfigManager::sFloatConsts;
std::map<std::string, int>			ConfigManager::sIntConsts;
std::map<std::string, bool>			ConfigManager::sBoolConsts;
std::map<std::string, std::string>	ConfigManager::sStringConsts;
std::map<std::string, sf::Vector2f>	ConfigManager::sVectorConsts;

void ConfigManager::LoadFile(const std::string& filename)
{
	std::fstream fin(filename);

	std::string category = "";
	while (!fin.eof())
	{
		std::string key;
		char separator;
		while (fin >> key)
		{
			char identifier = key[0];
			switch (identifier)
			{
			case 'i':
				int iValue;

				//Format: iName = *value*
				fin >> separator >> iValue;
				sIntConsts[category + key] = iValue;
				break;
			case 'b':
				bool bValue;

				//Format: bName = true
				fin >> separator >> std::boolalpha >> bValue;
				sBoolConsts[category + key] = bValue;
				break;
			case 'f':
				float fValue;

				//Format: fName = *value*
				fin >> separator >> fValue;
				sFloatConsts[category + key] = fValue;
				break;
			case 'v':
				float x, y;

				//Format: vName = ( x ; y ) 
				fin >> separator >> separator >> x >> separator >> y >> separator;
				sVectorConsts[category + key] = sf::Vector2f(x, y);
				break;
			case 's':
			{
				//Format: sName = String Value
				fin >> separator;

				char lineBuffer[256];
				fin.getline(lineBuffer, sizeof(lineBuffer));
				std::string sValue = std::string(lineBuffer);

				sStringConsts[category + key] = sValue;
				break;
			}
			case '[':
			{
				//Format: [Category Name]
				char lineBuffer[256];
				fin.getline(lineBuffer, sizeof(lineBuffer));
				category = std::string(key + lineBuffer);
				break;
			}
			default:
			{
				//Ignore the line if not recongnized
				char lineBuffer[256];
				fin.getline(lineBuffer, sizeof(lineBuffer));
				break;
			}
			}
		}
	}
}

int ConfigManager::GetInt(std::string const& key)
{
	return sIntConsts[key];
}

float ConfigManager::GetFloat(std::string const& key)
{
	return sFloatConsts[key];
}

bool ConfigManager::GetBool(std::string const& key)
{
	return sBoolConsts[key];
}

std::string const& ConfigManager::GetString(std::string const& key)
{
	return sStringConsts[key];
}

sf::Vector2f const& ConfigManager::GetVector(std::string const& key)
{
	return sVectorConsts[key];
}