#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include "INIReader.h"

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

using namespace std;
class view{
	private:
		SDL_Window * window;
		SDL_Renderer * renderer; 
		int screen_width;
		int screen_height;
	public:

		void clear();
		void present();
		SDL_Renderer * return_renderer();
		void init_window ();
		void init_render ();
		void render(SDL_Texture * texture, SDL_Rect target);
		void  render_text(string text, SDL_Rect  Message_rect);
		~view();
		view();
		int rwidth();
		int rheight();
};

