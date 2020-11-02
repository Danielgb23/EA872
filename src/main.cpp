
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/model/player.hpp"
#include "../include/view/view.hpp"




int main() {
	view viewer;
	player player1;

	player1.load_texture( viewer.return_renderer() );
	// Quadrado onde a textura sera desenhada
	SDL_Rect target;
	target.x = SCREEN_WIDTH/2;
	target.y = SCREEN_HEIGHT/2;
	SDL_QueryTexture(player1.return_texture(), nullptr, nullptr, &target.w, &target.h);

	// Variaveis para verificar eventos
	SDL_Event evento; // eventos discretos
	// Controlador:
	bool rodando = true;

	while(rodando){
		viewer.render(player1.return_texture(), target);

		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_QUIT) {
				rodando = false;
			}
		} 


	}

	return 0;
}
