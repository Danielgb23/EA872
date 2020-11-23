
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

	auto tempo = std::chrono::steady_clock::now();

	// Variaveis para verificar eventos

	SDL_Event evento; // eventos discretos
	bool rodando = true;

	int i=0;
	int avg=0;
	while(rodando){

		controller.step(0.017);
		i++;

		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_QUIT) {
				rodando = false;
			}
		} 

		//to reduce framerate to appropriate time
		std::this_thread::sleep_until(tempo + std::chrono::milliseconds(17));
	}

	return 0;
}
