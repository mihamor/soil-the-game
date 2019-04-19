#include "AnimationManager.hpp"

AnimationManager::AnimationManager() {}
AnimationManager::~AnimationManager() {}
void AnimationManager::create(String name, Texture &t, int x, int y, int w, int h, int count, float Speed, int step)
{
	animList[name] = Animation(t, x, y, w, h, count, Speed, step);
	currentAnim = name;
}


float AnimationManager::getFrameWidth(int index, const char * key) {
	return animList[key].frames[index].width;
}
float AnimationManager::getFrameHeight(int index, const char * key) {
	return animList[key].frames[index].height;
}
//загрузка из файла XML
void AnimationManager::loadFromXML(std::string fileName, Texture *t)
{
	animList.clear();
	this->fileName = fileName;
	TiXmlDocument animFile(fileName.c_str());

	if(!animFile.LoadFile()) abort();

	TiXmlElement * head = animFile.FirstChildElement("sprites");
	TiXmlElement *animElement;
	animElement = head->FirstChildElement("animation");
	while (animElement)
	{

		Animation anim;
		anim.frames.clear();
		anim.frames_flip.clear();
		currentAnim = "";
		anim.sprite.setTexture(*t);
		anim.currentFrame = 0;
		anim.isPlaying = true;
		anim.flip = false;

		currentAnim = animElement->Attribute("title");

		std::locale locale;
		std::string s1 = currentAnim.toAnsiString(locale);
		std::cout << s1 << " ";

		int delay = atoi(animElement->Attribute("delay"));
		anim.speed = 1.0 / delay;

		TiXmlElement *cut;
		cut = animElement->FirstChildElement("cut");
		while (cut)
		{

			int x = atoi(cut->Attribute("x")); std::cout << x << " ";
			int y = atoi(cut->Attribute("y")); std::cout << y << " ";
			int w = atoi(cut->Attribute("w")); std::cout << w << " ";
			int h = atoi(cut->Attribute("h")); std::cout << h << " ";

			anim.frames.push_back(IntRect(x, y, w, h));
			anim.frames_flip.push_back(IntRect(x + w, y, -w, h));
			cut = cut->NextSiblingElement("cut");
		}


		anim.sprite.setOrigin(0, anim.frames[0].height);
		animList.insert(std::pair<String, Animation>(currentAnim, anim));
		animList[currentAnim] = anim;
		std::cout << "\n";
		animElement = animElement->NextSiblingElement("animation");
	}
}

void AnimationManager::draw(RenderWindow &window, int x, int y)
{
	animList[currentAnim].sprite.setPosition(x, y + animList[currentAnim].frames[0].height);
	Vector2u a = window.getSize();
	if (x >= 0 && y >= 0 && x <= a.x && y <= a.y) {
		window.draw(animList[currentAnim].sprite);
	}
}
void AnimationManager::set(String name) { if(currentAnim != name) currentAnim = name; }
void AnimationManager::flip(bool b) { animList[currentAnim].flip = b; }
void AnimationManager::tick(float time) { animList[currentAnim].tick(time); }
void AnimationManager::pause() { animList[currentAnim].isPlaying = false; }
void AnimationManager::play() { animList[currentAnim].isPlaying = true; }

// Animation //

Animation::Animation()
{
}

Animation::Animation(Texture &t, int x, int y, int w, int h, int count, float Speed, int step)
{
	speed = Speed;
	sprite.setTexture(t);
	currentFrame = 0;
	isPlaying = true;
	flip = false;

	for (int i = 0; i < count; i++)
	{
		frames.push_back(IntRect(x + i * step, y, w, h));
		sprite.setTextureRect(frames[i]);
		frames_flip.push_back(IntRect(x + i * step + w, y, -w, h));
		sprite.setTextureRect(frames_flip[i]);
	}
}
void Animation::tick(float time)
{
	if (!isPlaying) return;

	currentFrame += speed * time;

	if (currentFrame > frames.size())
		currentFrame -= frames.size();

	int i = currentFrame;
	sprite.setTextureRect(frames[i]);
	if (flip) sprite.setTextureRect(frames_flip[i]);
};
Animation::~Animation() {}
