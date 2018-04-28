#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.hpp"
#include <list>
#include "Windows.h"
#include <Math.h>
#include "PLAYER.hpp"
#include "tilemap.h"
#include <assert.h>
#include "Bullet.hpp"
#include "Inventory.hpp"
#include "Block.hpp"
#include "Environment.hpp"
#include "Cursor.hpp"
#define SFML_DYNAMIC

#pragma comment(lib, "sfml-graphics-s-d.lib")

using namespace sf;

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}
//const int ground = 32 * 18;
int vmodex = 600;
int vmodey = 32 * 12;

int main(){


	RenderWindow window(VideoMode(vmodex, vmodey), "Miha game");
	bool gameOver = false;
	bool Resized = false;

	Clock clock;
	View view;

	Environment e(vmodex, vmodey);

	RectangleShape rectangle;
	sf::Vector2i a(0, 0);
	while (window.isOpen() && e.player()->life) {
		float time = clock.getElapsedTime().asMicroseconds(); // ��� ����
		clock.restart();
		time = time / 400; // �������� ~  �������� �����������
		if (!Resized)
		{
			a = Mouse::getPosition(window);
		}
		else
			a = Mouse::getPosition();
		// �������� ������� ������
		if (!e.isInvGui()) {
			if (Keyboard::isKeyPressed(Keyboard::A))
				e.player()->key["L"] = true;
			if (Keyboard::isKeyPressed(Keyboard::D))
				e.player()->key["R"] = true;
			if (Keyboard::isKeyPressed(Keyboard::W))
				e.player()->key["Up"] = true;
			if (Keyboard::isKeyPressed(Keyboard::S))
				e.player()->key["Down"] = true;
			if (Keyboard::isKeyPressed(Keyboard::Space))
				e.player()->key["Space"] = true;
			if (Keyboard::isKeyPressed(Keyboard::E) && a.x <= vmodex && a.y <= vmodey) // ����� ����
			{
				e.addBlock(a);
			}
		}
		// call inventory
		if (Keyboard::isKeyPressed(Keyboard::I))
			e.setGui(true);

		// �������� ������� �������� �� ������ ����
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return EXIT_SUCCESS;
			}
			if (event.type == Event::Resized)
			{
				//vmodex = event.size.width;
				//vmodey = event.size.height;
				//window.create(sf::VideoMode(vmodex, vmodey, 32), "SFML Window");
			}
			if (event.type == Event::KeyPressed && !e.isInvGui())
				switch (event.key.code)
				{
				case Keyboard::Space :{
					e.addBullet();
					break;
				}
				default:
					break;
				}
			if(event.type == Event::MouseButtonPressed && !e.isInvGui())
				switch (event.key.code)
				{
				case Mouse::Right: { // ��������� ����
					e.setBlock(a);
					break;
				}
				case Mouse::Left: { // ������� ����
					e.removeBlock(a);
					break;
				}
				default:
					break;
				}
				
		}

		e.update(time, window, a);

		window.display();
		if (e.player()->life == false)
		{

			// ���� ��� ������ ����� (����������� ���� ������ � ������������)
			window.close();
			return EXIT_SUCCESS;
		}
	}
	return EXIT_SUCCESS;
}

