#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <vector>
using namespace sf;
class SoundSystem
{
	std::map<std::string, SoundBuffer> map;
	std::vector<Sound *> sounds;
public:
	SoundSystem();
	void play(std::string id);
	~SoundSystem();
};

