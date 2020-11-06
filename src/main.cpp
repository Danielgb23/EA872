
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/model/entity.hpp"
#include "../include/view/view.hpp"
#include "../include/controller/update.hpp"




int main() {
	update controller;
/*	
	   view viewer;
	   entity player1;

	   player1.load_type( viewer.return_renderer(), 1 );
	// Quadrado onde a textura sera desenhada
	SDL_Rect target;
	target.x = SCREEN_WIDTH/2;
	target.y = SCREEN_HEIGHT/2;
	SDL_QueryTexture(player1.return_texture(), nullptr, nullptr, &target.w, &target.h);
	target.w/=4;
	target.h/=4;

	target.w=50;
	target.h=50;
	*/
	// Variaveis para verificar eventos
	
	SDL_Event evento; // eventos discretos
	// Controlador:
	bool rodando = true;

	while(rodando){
	//	viewer.render(player1.return_texture(), target);
		controller.step(0.01);
		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_QUIT) {
				rodando = false;
			}
		} 

		// Delay para diminuir o framerate
		SDL_Delay(0.01);


	}

	return 0;
}
