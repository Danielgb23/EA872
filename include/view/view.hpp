#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <SDL2/SDL_ttf.h>

#include "INIReader.h"
#include "../include/view/assets.hpp"

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

using namespace std;
class view{
	private:
		SDL_Window * window;
		SDL_Renderer * renderer; 
		int screen_width;
		int screen_height;
		assets Assets;
	public:

		void clear();
		void present();
		SDL_Renderer * return_renderer();
		void init_window ();
		void init_render ();
		SDL_Texture * entity_texture(int type);
		SDL_Texture * arrow_texture(int team);
		void render(SDL_Texture * texture, SDL_Rect target);
		void  render_text(string text, SDL_Rect  Message_rect);
		~view();
		view();
		int rwidth();
		int rheight();
};

