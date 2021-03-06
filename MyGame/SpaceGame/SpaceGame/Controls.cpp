#include "Controls.h"

IND_Key Controls::getAdvance()
{
	return keyMap["advance"];
}

IND_Key Controls::getRotateLeft()
{
	return keyMap["rotateLeft"];
}

IND_Key Controls::getRotateRight()
{
	return keyMap["rotateRight"];
}

IND_Key Controls::getShoot()
{
	return keyMap["shoot"];
}

IND_Key Controls::getQuickSave()
{
	return keyMap["quickSave"];
}

IND_Key Controls::getQuickLoad()
{
	return keyMap["quickLoad"];
}

IND_Key Controls::getMenu()
{
	return keyMap["menu"];
}

void Controls::loadSettings()
{
	// key - action(advance, rotate, save etc) as char
	// value - key associated with action as char
	map<const char*,const char*> stringKeys;

	ifstream indKeys, customKeys;
	indKeys.open("../SpaceGame/Settings/IndieLib_Keys.txt", ios::in);
	customKeys.open("../SpaceGame/Settings/Custom_Keys.txt", ios::in);

	// read the custom keys and fill in stringKeys with keys and values, and keyMap only with heys
	if (indKeys.is_open() && customKeys.is_open())
	{
		string line = "";
		while (std::getline(customKeys, line))
		{
			if (line[0] != '#')
			{
				char* action = new char[40];
				strncpy(action, line.substr(line.find_first_of("[") + 1, line.find_first_of("]") - line.find_first_of("[") - 1).c_str(), 29);
				keyMap[action] = IND_0;
				char* key = new char[40];
				strncpy(key, line.substr(line.find_first_of(":") + 1).c_str(), 29);
				stringKeys[action] = key;
			}
		}

		// read the IND_Key enum to determine the numeric value of the keys
		int count = 0; // keeps the numeric value of the key that is currently read
		while (std::getline(indKeys, line))
		{
			char* indKey = new char[40];
			strncpy(indKey, line.substr(line.find_first_of("!") + 2).c_str(), 39);
			for (std::map<const char*, const char*>::iterator it = stringKeys.begin(); it != stringKeys.end(); ++it)
			{
				if (!strcmpi(indKey, it->second))
				{
					keyMap[it->first] = count;
				}
			}
			delete[] indKey;
			std::getline(indKeys, line);
			count++;
		}
	}

	// clean
	for (std::map<const char*, const char*>::iterator it = stringKeys.begin(); it != stringKeys.end(); ++it)
	{
		delete[] it->first;
		delete[] it->second;
	}
	indKeys.close();
	customKeys.close();
}

Controls::~Controls()
{
}
