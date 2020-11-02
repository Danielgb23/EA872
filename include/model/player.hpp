#pragma once
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "INIReader.h"



//model
class player{
	private:
		//posicao e velocidade
		float x;
		float y;
		int health;
		float speed;
		float dig_rate;
		int height;
		int width;
		float team;
		float facing;
		



	public:
		player();
		void load();
		int show_health();
		int take_damage(int damage);
		void pos(float &x, float &y);
		int show_speed();
		int show_dig_rate();
		void update_pos(float x, float y);


};

