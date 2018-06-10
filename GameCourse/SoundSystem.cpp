#include "SoundSystem.hpp"
const int MAX_SOUNDS = 3;
SoundSystem::SoundSystem() {
	map["break_block"].loadFromFile("sounds/break_block.wav");
	map["player_jump"].loadFromFile("sounds/player_jump.ogg");
	map["place_block"].loadFromFile("sounds/place_block.wav");
	map["door_open"].loadFromFile("sounds/door_open.wav");
	map["bow_use"].loadFromFile("sounds/bow.wav");
	map["sword_use"].loadFromFile("sounds/sword_use.wav");
	map["stab_enemy"].loadFromFile("sounds/stab_enemy.wav");
	map["heal_up"].loadFromFile("sounds/heal_up.wav");
	map["craft"].loadFromFile("sounds/craft.wav");

	this->sounds.push_back(new Sound());
}
void SoundSystem::play(std::string id) {

	for (auto currSound : sounds) {
		if (currSound->getStatus() != sf::SoundSource::Playing) {
			currSound->setBuffer(map[id]);
			currSound->play();
			return;
		}
	}
	if (sounds.size() >= MAX_SOUNDS) return;
	Sound  * newSound = new Sound();
	newSound->setBuffer(map[id]);
	this->sounds.push_back(newSound);
	newSound->play();

}
SoundSystem::~SoundSystem()
{
	for (auto currSound : this->sounds) delete currSound;
}
