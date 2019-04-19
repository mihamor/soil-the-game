#pragma once
#include "AnimationManager.hpp"


//flyweight
class AnimationFactory {
	using Animations = std::map<std::string, const AnimationManager *>;
	Animations animations;
public:
	const AnimationManager * getAnimationManager(std::string fileName, Texture * texture = NULL);
};