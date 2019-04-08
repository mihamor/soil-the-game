#include "AnimationFactory.hpp"


const AnimationManager * AnimationFactory::getAnimationManager(std::string fileName, Texture * texture)
{
	// Uses "lazy initialization"
	Animations::const_iterator it = animations.find(fileName);
	if (animations.end() == it) {
		AnimationManager * manager = new AnimationManager();
		manager->loadFromXML(fileName, texture ? texture : new Texture());
		animations[fileName] = manager;
		return animations[fileName];
	}
	else {
		return it->second;
	}
}