#include "LightHandler.hpp"

LightShapePair * LightHandler::getPair(Vector2i coords) {
	for (LightShapePair * pair : this->pairs)
		if (pair->coords == coords) return pair;
	return nullptr;
}

LightPointPair * LightHandler::getPairPoint(Vector2i coords) {
	for (LightPointPair * pair : this->pairsPoint)
		if (pair->coords == coords) return pair;
	return nullptr;
}
bool LightHandler::isContains(LightShapePair * pair, std::vector<LightShapePair *> added) {
	for (auto pairTo : added) {
		if (pairTo->coords == pair->coords) return true;
	}
	return false;
}
bool LightHandler::isContains(Vector2i coords, std::vector<LightShapePair *> added) {
	for (auto pairTo : added) {
		if (pairTo->coords == coords) return true;
	}
	return false;
}

LightHandler::LightHandler(std::list<AbstractBlock *> & list, String * TileMap, RenderWindow & window, int vmodey, int vmodex) {

	this->TileMap = TileMap;
	this->vmodex = vmodex;
	this->vmodey = vmodey;
	penumbraTexture.loadFromFile("data/penumbraTexture.png");
	//penumbraTexture.setSmooth(true);

	pointLightTexture.loadFromFile("data/pointLightTexture.png");
	//pointLightTexture.setSmooth(true);

	ConeLightTexture.loadFromFile("data/spotLightTexture.png");
	//ConeLightTexture.setSmooth(true);

	unshadowShader.loadFromFile("data/unshadowShader.vert", "data/unshadowShader.frag");
	lightOverShapeShader.loadFromFile("data/lightOverShapeShader.vert", "data/lightOverShapeShader.frag");

	ls.create(ltbl::rectFromBounds(sf::Vector2f(-1000.0f, -1000.0f), sf::Vector2f(1000.0f, 1000.0f)), Vector2u(vmodex, vmodey), penumbraTexture, unshadowShader, lightOverShapeShader);

	std::shared_ptr<ltbl::LightDirectionEmission> sun = std::make_shared<ltbl::LightDirectionEmission>();// Глобальный источник света что-то вроде солнца.
	sun->_castDirection = ltbl::vectorNormalize(sf::Vector2f(-0.1f, 0.8f));//Вектор падения тени.
																		   //ls.addLight(sun);

	playerLight = std::make_shared<ltbl::LightPointEmission>();
	playerLight->_emissionSprite.setOrigin(sf::Vector2f(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f));
	playerLight->_emissionSprite.setTexture(pointLightTexture);
	playerLight->_emissionSprite.setScale(sf::Vector2f(2, 2));
	playerLight->_emissionSprite.setColor(sf::Color(255, 255, 255));
	playerLight->_sourceRadius = 1;
	ls.addLight(playerLight);


	for (int y = 0; y < H; y++)
		for (int x = 0; x < W; x++) {
			AbstractBlock * block = AbstractBlock::getBlock(list, TileMap, y, x);
			if (!block) continue;
			if (block->getCollision() && block->interact() != spriticType) this->addPair(Vector2i(x, y));
			else if (block->getCollision()) this->addLight(Vector2i(x, y));
		}
	Lsprite.setTexture(ls.getLightingTexture());
}

void LightHandler::removePair(Vector2i pairCoord) {
	for (auto it = pairs.begin(); it != pairs.end(); it++)
	{
		LightShapePair * pair = *it;
		if (pair->coords.x == pairCoord.x && pairCoord.y == pair->coords.y) {
			it = pairs.erase(it);
			//this->ls.removeShape(pair->lightShape);
			delete pair;
			break;
		}
	}
}
void LightHandler::removeLight(Vector2i pairCoord) {
	for (auto it = pairsPoint.begin(); it != pairsPoint.end(); it++)
	{
		LightPointPair * pair = *it;
		if (pair->coords.x == pairCoord.x && pairCoord.y == pair->coords.y) {
			it = pairsPoint.erase(it);
			this->ls.removeLight(pair->newLight);
			delete pair;
			break;
		}
	}
}

void LightHandler::addLight(Vector2i pairCord) {
	LightPointPair * pair = new LightPointPair();
	pair->coords = pairCord;
	pair->newLight = std::make_shared<ltbl::LightPointEmission>();
	pair->newLight->_emissionSprite.setOrigin(sf::Vector2f(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f));
	pair->newLight->_emissionSprite.setTexture(pointLightTexture);
	pair->newLight->_emissionSprite.setScale(sf::Vector2f(5, 5));
	pair->newLight->_emissionSprite.setColor(sf::Color(255, 255, 255));
	pair->newLight->_sourceRadius = 4;
	pair->newLight->_emissionSprite.setPosition(Vector2f(pairCord.x, pairCord.y));

	pairsPoint.push_back(pair);
	ls.addLight(pair->newLight);
}


void LightHandler::addPair(Vector2i pairCord) {
	//if (isContains(pairCord, pairs)) return;
	LightShapePair * pair = new LightShapePair();
	pair->coords = Vector2i(pairCord.x, pairCord.y);
	pair->lightShape = std::make_shared<ltbl::LightShape>();
	pair->lightShape->_shape.setPointCount(4);
	pair->lightShape->_shape.setPoint(0, Vector2f(0, 0));// Что бы избажать глюков с тенью строить фигуру нужно опираясь на координаты 0,0.
	pair->lightShape->_shape.setPoint(1, Vector2f(BLOCK_SIZE, 0));
	pair->lightShape->_shape.setPoint(2, Vector2f(BLOCK_SIZE, BLOCK_SIZE));
	pair->lightShape->_shape.setPoint(3, Vector2f(0, BLOCK_SIZE));
	pair->lightShape->_renderLightOverShape = true;//Рендерить свет сквозь фигуру.По умолчанию false.
	pair->lightShape->_shape.setPosition(0, 0);
	pairs.push_back(pair);
}

void LightHandler::render(float offsetX, float offsetY, float px, float py, RenderWindow & window, bool drawRendered) {

	Vector2u size = Vector2u(vmodex, vmodey);
	std::vector<LightShapePair *> added;
	for (LightShapePair * pair : this->pairs) {

		float posx = (float)(pair->coords.x * 32 - offsetX);
		float posy = (float)(pair->coords.y * 32 - offsetY);
		float reserve = 0.9 *BLOCK_SIZE;
		if (posy > size.y || posx > size.x || posx < 0 - reserve || posy < 0 - reserve || isContains(pair, added)) continue;
		pair->lightShape->_shape.setPosition(posx, posy);
		ls.addShape(pair->lightShape);
		added.push_back(pair);
	}

	View view = window.getDefaultView();
	float centerx = size.x / 2;
	float centery = size.y / 2;
	if (px > size.x / 2 && px  <  W*(32) - size.x / 2) centerx = px - offsetX;
	if (py > size.y / 2 && py  < H*(32) - size.y / 2)  centery = py - offsetY;
	for (auto pair : pairsPoint) {
		Vector2i posL = pair->coords;
		pair->newLight->_emissionSprite.setPosition(posL.x * BLOCK_SIZE - offsetX, posL.y * BLOCK_SIZE - offsetY);
	}
	playerLight->_emissionSprite.setPosition(px - offsetX, py - offsetY);
	view.setCenter(Vector2f(centerx, centery));
	//view.setSize(Vector2f(size.x, size.y));
	if(!drawRendered) ls.render(view, unshadowShader, lightOverShapeShader);
	//Lsprite.setTexture(ls.getLightingTexture());
	lightRenderStates.blendMode = sf::BlendMultiply;
	window.draw(Lsprite, lightRenderStates);
	for (LightShapePair * pair : added)
		ls.removeShape(pair->lightShape);
	//added.clear();
}

LightHandler::~LightHandler() {
	for (auto it = pairsPoint.begin(); it != pairsPoint.end(); it++)
	{
		LightPointPair * pair = *it;
		this->ls.removeLight(pair->newLight);
		delete pair;
	}
	for (auto it = pairs.begin(); it != pairs.end(); it++)
	{
		LightShapePair * pair = *it;
		delete pair;
	}
}