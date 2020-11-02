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
		int team;
		int facing;
		SDL_Texture * player_texture;
		



	public:
		void load_team(int new_team);
		int return_team();
		SDL_Texture * return_texture();
		void load_texture(SDL_Renderer * renderer);
		player();
		~player();
		void load();
		int return_health();

//the player takes 'damage' amount of damage
		int take_damage(int damage);
		
//loads the variables x and y  with the player current position
		void pos(float &x, float &y);

		int return_speed();
		int return_dig_rate();

//updates the players position according to the fuction input
		void update_pos(float x, float y);


};

