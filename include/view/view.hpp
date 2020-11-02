

#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;
class view{
	private:
		SDL_Window * window;
		SDL_Renderer * renderer; 
		SDL_Texture * player_texture;

	public:
		void init_window ();
		void init_render ();
		void render(SDL_Rect target);
		SDL_Texture * get_textura();
		~view();
		view();



};

