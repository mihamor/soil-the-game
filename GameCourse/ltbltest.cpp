#pragma warning(disable : 4996)
#include <SFML/Graphics.hpp>
#include <ltbl/lighting/LightSystem.h>
using namespace sf;
int main1()
{
	RenderWindow window;
	ContextSettings contextSettings;
	Event event;
	Texture backgroundImage;
	sf::RenderStates lightRenderStates;
	Sprite backgroundSprite(backgroundImage);// Фон.
	sf::Sprite Lsprite;//Спрайт света.
	Texture pointLightTexture, ConeLightTexture;// Текстура света.
	Texture  penumbraTexture;// Текстура полутени.
	Shader unshadowShader, lightOverShapeShader;// Шейдеры для рендера света.
	RectangleShape shape1, shape2, shape3;// Фигуры для визуализации.
	ltbl::LightSystem ls;//Глобальная система света и тени.
	//ls._ambientColor(Color::Black); //Цвет глобальной тени.
	ls._ambientColor = Color::Black;
	contextSettings.antialiasingLevel = 8;// Включить сглаживание.
	window.create(sf::VideoMode(1280, 720), "LTBL2", sf::Style::Default, contextSettings);

	penumbraTexture.loadFromFile("data/penumbraTexture.png");
	penumbraTexture.setSmooth(true);

	pointLightTexture.loadFromFile("data/pointLightTexture.png");
	pointLightTexture.setSmooth(true);

	ConeLightTexture.loadFromFile("data/spotLightTexture.png");
	ConeLightTexture.setSmooth(true);

	backgroundImage.loadFromFile("data/background.png");
	backgroundImage.setRepeated(true);

	backgroundSprite.setTextureRect(sf::IntRect(0, 0, 1280 * 2, 720 * 2));
	backgroundSprite.setPosition(-400.0f, -400.0f);

	unshadowShader.loadFromFile("data/unshadowShader.vert", "data/unshadowShader.frag");
	lightOverShapeShader.loadFromFile("data/lightOverShapeShader.vert", "data/lightOverShapeShader.frag");

	ls.create(ltbl::rectFromBounds(sf::Vector2f(-1000.0f, -1000.0f), sf::Vector2f(1000.0f, 1000.0f)), window.getSize(), penumbraTexture, unshadowShader, lightOverShapeShader);
	/*ls.create(ltbl::rectFromBounds(Исходный регион для дерева квадрантов(Может подстроиться автоматически).,Размер области рендеринга., Розмер окна.,Загрузка ефектов); */

	std::shared_ptr<ltbl::LightPointEmission> light = std::make_shared<ltbl::LightPointEmission>();//LightPointEmission-> точечное свечение, фонарь, костёр, прожектор.
	light->_emissionSprite.setOrigin(sf::Vector2f(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f));//Устанавливаем источник света в середину текстуры свечения.
	light->_emissionSprite.setTexture(pointLightTexture);// Сама текстура свечения.
	light->_emissionSprite.setScale(sf::Vector2f(10, 10));// Размер области свечения.
	light->_emissionSprite.setColor(sf::Color(255, 255, 255));// Цвет света.
	light->_emissionSprite.setPosition(sf::Vector2f(50, 50));//Позиция света.
	light->_sourceRadius = 10;//Радиус источника света.По умолчанию 1.
	light->_shadowOverExtendMultiplier = 1;// Умножитель отбрасываемой тени(в столько раз увеличиться тень). 
	ls.addLight(light);// Добавляем свет в систему.

	std::shared_ptr<ltbl::LightPointEmission> light2 = std::make_shared<ltbl::LightPointEmission>();
	light2->_emissionSprite.setOrigin(sf::Vector2f(ConeLightTexture.getSize().x * 0.5f, ConeLightTexture.getSize().y * 0.5f));
	light2->_emissionSprite.setTexture(ConeLightTexture);//Текстура свечения как у фонаря.
	light2->_emissionSprite.setScale(sf::Vector2f(13, 10));
	light2->_emissionSprite.setColor(sf::Color(255, 255, 255));
	light2->_emissionSprite.setPosition(sf::Vector2f(440, 50));
	light2->_emissionSprite.setRotation(90);// Угол поворота света.
	light2->_sourceRadius = 10;
	ls.addLight(light2);

	std::shared_ptr<ltbl::LightPointEmission> light1 = std::make_shared<ltbl::LightPointEmission>();
	light1->_emissionSprite.setOrigin(sf::Vector2f(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f));
	light1->_emissionSprite.setTexture(pointLightTexture);
	light1->_emissionSprite.setScale(sf::Vector2f(5, 5));
	light1->_emissionSprite.setColor(sf::Color(255, 255, 255));
	light1->_sourceRadius = 10;
	ls.addLight(light1);

	std::shared_ptr<ltbl::LightDirectionEmission> light3 = std::make_shared<ltbl::LightDirectionEmission>();// Глобальный источник света что-то вроде солнца.
	light3->_castDirection = ltbl::vectorNormalize(sf::Vector2f(-0.1f, 0.8f));//Вектор падения тени.
	ls.addLight(light3);

	std::shared_ptr<ltbl::LightShape> lightShape = std::make_shared<ltbl::LightShape>();//Препятствие для света.Представляет из себя обычный ConvexShape(выпуклая фигура). Подробней ищите здесь: <a href="http://progressor-blog.ru/sfml/figury/" rel="nofollow">http://progressor-blog.ru/sfml/figury/</a> .
	lightShape->_shape.setPointCount(4);
	lightShape->_shape.setPoint(0, Vector2f(0, 0));// Что бы избажать глюков с тенью строить фигуру нужно опираясь на координаты 0,0.
	lightShape->_shape.setPoint(1, Vector2f(80, 0));
	lightShape->_shape.setPoint(2, Vector2f(80, 80));
	lightShape->_shape.setPoint(3, Vector2f(0, 80));
	lightShape->_renderLightOverShape = true;//Рендерить свет сквозь фигуру.По умолчанию false.
	lightShape->_shape.setPosition(100, 100);
	ls.addShape(lightShape);

	std::shared_ptr<ltbl::LightShape> lightShape1 = std::make_shared<ltbl::LightShape>();
	lightShape1->_shape.setPointCount(4);

	lightShape1->_shape.setPoint(0, Vector2f(0, 0));
	lightShape1->_shape.setPoint(1, Vector2f(200, 0));
	lightShape1->_shape.setPoint(2, Vector2f(200, 80));
	lightShape1->_shape.setPoint(3, Vector2f(0, 80));
	lightShape1->_renderLightOverShape = true;
	lightShape1->_shape.setPosition(300, 400);
	ls.addShape(lightShape1);

	std::shared_ptr<ltbl::LightShape> lightShape2 = std::make_shared<ltbl::LightShape>();
	lightShape2->_shape.setPointCount(4);
	lightShape2->_shape.setPoint(0, Vector2f(0, 0));
	lightShape2->_shape.setPoint(1, Vector2f(80, 0));
	lightShape2->_shape.setPoint(2, Vector2f(80, 80));
	lightShape2->_shape.setPoint(3, Vector2f(0, 80));
	lightShape2->_renderLightOverShape = true;
	lightShape2->_shape.setPosition(400, 200);
	ls.addShape(lightShape2);
	//Визуализация фигур.
	Texture * t = new Texture();
	t->loadFromFile("blocks/rock.png");
	shape1.setTexture(t);
	shape1.setSize(Vector2f(80, 80));
	/*shape1.setPointCount(4);
	shape1.setPoint(0, Vector2f(0, 0));
	shape1.setPoint(1, Vector2f(80, 0));
	shape1.setPoint(2, Vector2f(80, 80));
	shape1.setPoint(3, Vector2f(0, 80));*/
	shape1.setPosition(100, 100);
	//shape1.setFillColor(Color::Green);

	
	shape2.setTexture(t);
	shape2.setSize(Vector2f(80, 80));
	/*shape2.setPoint(0, Vector2f(0, 0));
	shape2.setPoint(1, Vector2f(80, 0));
	shape2.setPoint(2, Vector2f(80, 80));
	shape2.setPoint(3, Vector2f(0, 80));*/
	shape2.setPosition(400, 200);
	//shape2.setFillColor(Color::Green);

	shape3.setTexture(t);
	shape3.setSize(Vector2f(80, 80));
	/*shape3.setPoint(0, Vector2f(0, 0));
	shape3.setPoint(1, Vector2f(200, 0));
	shape3.setPoint(2, Vector2f(200, 80));
	shape3.setPoint(3, Vector2f(0, 80));*/
	shape3.setPosition(300, 400);
	//shape3.setFillColor(Color::Green);

	sf::View view = window.getDefaultView();

	view.setCenter(sf::Vector2f(1280 * 0.5f, 720 * 0.5f));
	while (window.isOpen())
	{
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		light1->_emissionSprite.setPosition(pos);
		window.clear(sf::Color::White);

		window.draw(backgroundSprite);
		window.draw(shape1);
		window.draw(shape2);
		window.draw(shape3);
		//-----------------------------Рендер света-----------------------------------
		ls.render(view, unshadowShader, lightOverShapeShader);
		Lsprite.setTexture(ls.getLightingTexture());
		lightRenderStates.blendMode = sf::BlendMultiply;
		window.setView(window.getDefaultView());
		window.draw(Lsprite, lightRenderStates);
		window.setView(view);
		// ---------------------------------------------------------------------------
		
		window.display();
	}
}