
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/model/entity.hpp"
#include "../include/view/view.hpp"
#include "../include/controller/update.hpp"
#include <chrono>
#include <thread>
using namespace std::chrono; 

int main() {
	update controller;
	int duration_step;

	auto tempo = std::chrono::steady_clock::now();

	// Variaveis para verificar eventos

	SDL_Event evento; // eventos discretos
	bool rodando = true;

	while(rodando){
		auto start = high_resolution_clock::now(); 
		//runs a game step
		controller.step( ((float)duration_step)/1000 );

		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_QUIT) {
				rodando = false;
			}
		} 

		auto stop = high_resolution_clock::now(); 

		auto duration = duration_cast<milliseconds>(stop - start); 
		duration_step=duration.count()+4;

		//to reduce framerate to appropriate time
		if(!controller.is_spectator())
			std::this_thread::sleep_until(tempo + std::chrono::milliseconds(duration_step));
	}

	return 0;
}
