
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/model/entity.hpp"
#include "../include/view/view.hpp"
#include "../include/controller/update.hpp"
#include <chrono>
#include <thread>

using std::chrono::system_clock;

int main() {
	update controller;
	
	auto tempo = std::chrono::steady_clock::now()
		
	// Variaveis para verificar eventos
	
	SDL_Event evento; // eventos discretos
	// Controlador:
	bool rodando = true;

	while(rodando){
	//	viewer.render(player1.return_texture(), target);
		controller.step(0.005);
		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_QUIT) {
				rodando = false;
			}
		} 

		// Delay para diminuir o framerate
		//SDL_Delay(0.01);

		std::this_thread::sleep_until(tempo + std::chrono::milliseconds(5));
	}

	return 0;
}
