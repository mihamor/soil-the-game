#pragma once
#include <SFML/Audio.hpp>
#include <map>
using namespace sf;
class SoundSystem
{
	std::map<std::string, SoundBuffer> map;
	Sound currSound;
	Sound additionalSound;
public:
	SoundSystem() {
		map["break_block"].loadFromFile("sounds/break_block.wav");
		map["player_jump"].loadFromFile("sounds/player_jump.ogg");
		map["place_block"].loadFromFile("sounds/place_block.wav");
		map["door_open"].loadFromFile("sounds/door_open.wav");
		map["bow_use"].loadFromFile("sounds/bow.wav");
		map["sword_use"].loadFromFile("sounds/sword_use.wav");
		map["stab_enemy"].loadFromFile("sounds/stab_enemy.wav");
		map["heal_up"].loadFromFile("sounds/heal_up.wav");
	}
	void play(std::string id) {
		if (currSound.getStatus() == sf::SoundSource::Playing) {
			additionalSound.setBuffer(map[id]);
			additionalSound.play();
		}
		else {
			currSound.setBuffer(map[id]);
			currSound.play();
		}
	}
	~SoundSystem();
};

