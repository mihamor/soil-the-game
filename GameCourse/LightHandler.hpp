#pragma once
#include <SFML/Graphics.hpp>
#include <ltbl/lighting/LightSystem.h>
#include "AbstractBlock.hpp"
#include "WorldDef.h"

using namespace sf;

typedef struct {
public:
	std::shared_ptr<ltbl::LightShape>  lightShape;
	Vector2i coords;
}LightShapePair;

typedef struct {
public:
	std::shared_ptr<ltbl::LightPointEmission>  newLight;
	Vector2i coords;
}LightPointPair;



// Facade
class LightHandler
{

	String * TileMap;
	int vmodey, vmodex;

	int bufferRenderCounts;

	ltbl::LightSystem ls;
	std::vector<LightShapePair *> pairs;
	std::vector<LightPointPair *> pairsPoint;
	std::shared_ptr<ltbl::LightPointEmission> playerLight;

	sf::Sprite Lsprite;//Спрайт света.
	Texture  pointLightTexture, ConeLightTexture;// Текстура света.
	Texture  penumbraTexture;// Текстура полутени.
	Shader unshadowShader, lightOverShapeShader;// Шейдеры для рендера света.
	sf::RenderStates lightRenderStates;

	LightShapePair * getPair(Vector2i coords);

	LightPointPair * getPairPoint(Vector2i coords);
	static bool isContains(LightShapePair * pair, std::vector<LightShapePair *> added);
	static bool isContains(Vector2i coords, std::vector<LightShapePair *> added);

public:
	LightHandler(std::list<AbstractBlock *> & list, String * TileMap, RenderWindow & window, int vmodey, int vmodex);
	void removePair(Vector2i pairCoord);
	void removeLight(Vector2i pairCoord);
	void addLight(Vector2i pairCord);
	void addPair(Vector2i pairCord);
	void render(float offsetX, float offsetY, float px, float py, RenderWindow & window, bool drawRendered = false);
	~LightHandler();
};

