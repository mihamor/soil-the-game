#pragma once

#include <SFML/Graphics.hpp>
#include "tinystr.h"
#include <iostream>
#include "tinyxml.h"

using namespace sf;

class Animation
{
public:
	std::vector<IntRect> frames, frames_flip;
	float currentFrame, speed;
	bool flip, isPlaying;
	Sprite sprite;
	
	Animation();
	Animation(Texture &t, int x, int y, int w, int h, int count, float Speed, int step);
	void tick(float time);
	~Animation();
};

class AnimationManager
{
	String currentAnim;
	std::map<String, Animation> animList;
public:
	AnimationManager();
	~AnimationManager();
	void create(String name, Texture &t, int x, int y, int w, int h, int count, float Speed, int step);
	float getFrameWidth(int index, const char * key);
	float getFrameHeight(int index, const char * key);
	void loadFromXML(std::string fileName, Texture *t);
	void draw(RenderWindow &window, int x, int y);
	void set(String name);
	void flip(bool b);
	void tick(float time);
	void pause();
	void play();
	const Texture * getTexture() {
		return animList["stay"].sprite.getTexture();
	}
	const IntRect getRect() {
		return animList["stay"].sprite.getTextureRect();
	}
	bool isOver() {
		return (int)this->animList[currentAnim].currentFrame == ((int)(this->animList[currentAnim].frames.size())- 1);
	}
};