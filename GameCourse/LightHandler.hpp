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
}LightPair;

class LightHandler
{

	String * TileMap;
	int vmodey, vmodex;

	ltbl::LightSystem ls;
	std::vector<LightPair *> pairs;
	std::shared_ptr<ltbl::LightPointEmission> playerLight;

	sf::Sprite Lsprite;//������ �����.
	Texture  pointLightTexture, ConeLightTexture;// �������� �����.
	Texture  penumbraTexture;// �������� ��������.
	Shader unshadowShader, lightOverShapeShader;// ������� ��� ������� �����.
	sf::RenderStates lightRenderStates;

	LightPair * getPair(Vector2i coords) {
		for (LightPair * pair : this->pairs)
			if (pair->coords == coords) return pair;
		return nullptr;
	}

	static bool isNeighoorsShapes() {}

public:
	LightHandler(std::list<AbstractBlock *> & list, String * TileMap, RenderWindow & window, int vmodey, int vmodex) {

		this->TileMap = TileMap;
		this->vmodex = vmodex;
		this->vmodey = vmodey;
		penumbraTexture.loadFromFile("data/penumbraTexture.png");
		penumbraTexture.setSmooth(true);

		pointLightTexture.loadFromFile("data/pointLightTexture.png");
		pointLightTexture.setSmooth(true);

		ConeLightTexture.loadFromFile("data/spotLightTexture.png");
		ConeLightTexture.setSmooth(true);

		unshadowShader.loadFromFile("data/unshadowShader.vert", "data/unshadowShader.frag");
		lightOverShapeShader.loadFromFile("data/lightOverShapeShader.vert", "data/lightOverShapeShader.frag");

		ls.create(ltbl::rectFromBounds(sf::Vector2f(-1000.0f, -1000.0f), sf::Vector2f(1000.0f, 1000.0f)), Vector2u(vmodex, vmodey), penumbraTexture, unshadowShader, lightOverShapeShader);

		std::shared_ptr<ltbl::LightDirectionEmission> sun = std::make_shared<ltbl::LightDirectionEmission>();// ���������� �������� ����� ���-�� ����� ������.
		sun->_castDirection = ltbl::vectorNormalize(sf::Vector2f(-0.1f, 0.8f));//������ ������� ����.
		//ls.addLight(sun);

		playerLight = std::make_shared<ltbl::LightPointEmission>();
		playerLight->_emissionSprite.setOrigin(sf::Vector2f(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f));
		playerLight->_emissionSprite.setTexture(pointLightTexture);
		playerLight->_emissionSprite.setScale(sf::Vector2f(5, 5));
		playerLight->_emissionSprite.setColor(sf::Color(255, 255, 255));
		playerLight->_sourceRadius = 4;
		ls.addLight(playerLight);


			for(int y = 0; y < H; y++)
				for (int x = 0; x < W; x++) {
					AbstractBlock * block = AbstractBlock::getBlock(list, TileMap, y, x);
					if (!block) continue;
					if (block->getCollision())
					{
						LightPair * pair = new LightPair();
						pair->coords = Vector2i(x, y);
						pair->lightShape = std::make_shared<ltbl::LightShape>();
						pair->lightShape->_shape.setPointCount(4);
						pair->lightShape->_shape.setPoint(0, Vector2f(0, 0));// ��� �� �������� ������ � ����� ������� ������ ����� �������� �� ���������� 0,0.
						pair->lightShape->_shape.setPoint(1, Vector2f(BLOCK_SIZE, 0));
						pair->lightShape->_shape.setPoint(2, Vector2f(BLOCK_SIZE, BLOCK_SIZE));
						pair->lightShape->_shape.setPoint(3, Vector2f(0, BLOCK_SIZE));
						pair->lightShape->_renderLightOverShape = true;//��������� ���� ������ ������.�� ��������� false.
						pair->lightShape->_shape.setPosition(0, 0);
						pairs.push_back(pair);
						//ls.addShape(pair->lightShape);
					}
				}
	}

	void removePair(Vector2i pairCoord) {
		for (auto it = pairs.begin(); it != pairs.end(); it++)
		{
			LightPair * pair = *it;
			if (pair->coords.x == pairCoord.x && pairCoord.y == pair->coords.y) {
				it = pairs.erase(it);
				//this->ls.removeShape(pair->lightShape);
				delete pair;
				break;
			}
		}
	}

	void addPair(Vector2i pairCord) {
		LightPair * pair = new LightPair();
		pair->coords = Vector2i(pairCord.x, pairCord.y);
		pair->lightShape = std::make_shared<ltbl::LightShape>();
		pair->lightShape->_shape.setPointCount(4);
		pair->lightShape->_shape.setPoint(0, Vector2f(0, 0));// ��� �� �������� ������ � ����� ������� ������ ����� �������� �� ���������� 0,0.
		pair->lightShape->_shape.setPoint(1, Vector2f(BLOCK_SIZE, 0));
		pair->lightShape->_shape.setPoint(2, Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		pair->lightShape->_shape.setPoint(3, Vector2f(0, BLOCK_SIZE));
		pair->lightShape->_renderLightOverShape = true;//��������� ���� ������ ������.�� ��������� false.
		pair->lightShape->_shape.setPosition(0, 0);
		pairs.push_back(pair);
	}
	void render(float offsetX, float offsetY, float px, float py, RenderWindow & window) {

		Vector2u size = Vector2u(vmodex, vmodey);
		std::vector<LightPair *> added;
		for (LightPair * pair : this->pairs) {
			
			float posx = (float)(pair->coords.x * 32 - offsetX);
			float posy = (float)(pair->coords.y * 32 - offsetY);
			float reserve = BLOCK_SIZE * 2;
			if (posy > size.y || posx > size.x || posx < 0 - reserve || posy < 0 - reserve) continue;
			//if (AbstractBlock::hasBlockNeigh(pair->coords.y, pair->coords.y, TileMap, DEFAULT_BG_SINGNATURE)) {
				pair->lightShape->_shape.setPosition(posx, posy);
				ls.addShape(pair->lightShape);
				added.push_back(pair);
			//}
			//	if (!AbstractBlock::hasBlockNeigh(pair->coords.y, pair->coords.y, TileMap, DEFAULT_BG_SINGNATURE)) {
				//	pair->lightShape->_shape.
		
				//}

		}
		
		View view = window.getDefaultView();
		float centerx = size.x/2;
		float centery = size.y/2;
		if (px > size.x / 2 && px  <  W*(32) - size.x / 2) centerx = px - offsetX;
		if (py > size.y / 2 && py  < H*(32) - size.y / 2)  centery = py - offsetY;
		playerLight->_emissionSprite.setPosition(px - offsetX, py - offsetY);
		view.setCenter(Vector2f(centerx, centery));
		//view.setSize(Vector2f(size.x, size.y));
		
		ls.render(view, unshadowShader, lightOverShapeShader);
		Lsprite.setTexture(ls.getLightingTexture());
		lightRenderStates.blendMode = sf::BlendMultiply;
		window.draw(Lsprite, lightRenderStates);

		for(LightPair * pair : added) 
			ls.removeShape(pair->lightShape);
	}
};
