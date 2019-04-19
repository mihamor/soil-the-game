#include "AnimationFactory.hpp"


const AnimationManager * AnimationFactory::getAnimationManager(std::string fileName, Texture * texture)
{
	// Uses "lazy initialization"
	const AnimationManager * founded = animations[fileName];
	if (!founded) {
		std::cout << "Not founded manager" << std::endl;
		AnimationManager * manager = new AnimationManager();
		manager->loadFromXML(fileName, texture ? texture : new Texture());
		animations[fileName] = manager;
		return animations[fileName];
	}
	return founded;
}