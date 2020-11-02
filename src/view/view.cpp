

#include "../../include/view/view.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

SDL_Renderer * view::return_renderer(){
return renderer;
}
view::view(){

	// Inicializando o subsistema de video do SDL
	if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
		std::cout << SDL_GetError();
		exit( 1 );
	}
	this->init_window();
	this->init_render();

}
void view::init_window(){

	// Criando uma janela
	window = nullptr;
	window = SDL_CreateWindow("Madrugada dos mortos",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (window==nullptr) { // Em caso de erro...
		std::cout << SDL_GetError();
		SDL_Quit();
		exit( 1 );
	}

}

void view::init_render(){
	// Inicializando o renderizador
	renderer = SDL_CreateRenderer(
			window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer==nullptr) { // Em caso de erro...
		SDL_DestroyWindow(window);
		std::cout << SDL_GetError();
		SDL_Quit();
		exit( 1 );
	}

}

void view::render(SDL_Texture * texture, SDL_Rect target){
  //Draws the target element 
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, &target);
    SDL_RenderPresent(renderer);
  }


view::~view(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
