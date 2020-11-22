#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include "../include/model/entity.hpp"
#include "../include/view/view.hpp"
#include <vector>

using namespace std;

class terrain{
	public:
		~terrain();
		terrain();
		int rwidth();
		int rheight();
		void init(SDL_Renderer * renderer);
		SDL_Texture * rbackground();
	private:
		SDL_Texture * background;
		int width;
		int height;

};


