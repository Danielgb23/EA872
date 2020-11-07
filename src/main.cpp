
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/model/entity.hpp"
#include "../include/view/view.hpp"
#include "../include/controller/update.hpp"




int main() {
	update controller;

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
