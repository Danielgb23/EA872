#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <vector>
#include <cmath>
#include "../include/model/entity.hpp"
#include "../include/model/mapa.hpp"
#include "../include/view/view.hpp"
#include <sstream>

using namespace std;

//controler
class update{
	public:
		//coord class with data and the size of time step
		void step(float T);
		update();
	private:
		void move_player(shared_ptr<entity> player, float T);
		void render_entity(shared_ptr<entity> ent);
		const Uint8* state; // estado do teclado 
		//scans the enviroment for collisions in the proper direction
		float collision_up(shared_ptr<entity> moved);
		float collision_down(shared_ptr<entity> moved);
		float collision_left(shared_ptr<entity> moved);
		float collision_right(shared_ptr<entity> moved);
		view Viewer;
		vector <shared_ptr<entity>> Entities;
		//terrain Map;
		float distance(shared_ptr<entity> ent1,shared_ptr<entity> ent2);
		void move_zombie(shared_ptr<entity> zombie, float T);
		void attack_closest(shared_ptr<entity> ent, float T);
		
};


