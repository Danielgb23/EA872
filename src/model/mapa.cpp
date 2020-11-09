#include "../include/model/mapa.hpp"

terrain::terrain(){
}

void terrain::init(SDL_Renderer * renderer){

	background = IMG_LoadTexture(renderer, "../assets/background.jpg");

}

SDL_Texture * terrain::rbackground(){

	return background;
}
