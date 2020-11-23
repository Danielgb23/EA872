#pragma once
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "INIReader.h"
#include "../include/json.hpp"

using nlohmann::json;
//model
class entity{
	private:
		int type;
		float x;
		float y;
		int health;
		float speed;
		float dig_rate;
		float height;
		float width;
		int team;
		int facing;
		int attack_damage;
		float range;
		float attack_rate;
		float attack_cooldown;
		//SDL_Texture * standing;
		std::shared_ptr<SDL_Texture> standing;

	public:

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(entity, x, y ,health ,type, speed, height, width, team, facing, attack_damage, range, attack_rate );
		void load_team(int new_team);
		void load_texture(SDL_Renderer * renderer);
		int return_team();
		float rwidth();
		int attack(float time_step);
		SDL_Texture * return_texture();
		void load(SDL_Renderer * renderer, int get_type, int new_team);
		entity();
		~entity();
		void load();
		int return_health();

//the entity takes 'damage' amount of damage
		int take_damage(int damage);
		
//loads the variables x and y  with the entity current position
		void pos(float &x, float &y);

		//returns x and y
		float rx();
		float ry();
		
		void addx(float load_x);
		void addy(float load_y);

//updates the entity's position according to the fuction input
		void update_pos(float x, float y);

		float return_speed();
		int rtype();
		float rrange();
		int return_dig_rate();



};

