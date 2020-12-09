#include "../../include/view/assets.hpp"


 void assets::load(SDL_Renderer * renderer){
	cop_standing= IMG_LoadTexture(renderer, "../assets/cop_standing.png");
	necromancer_standing= IMG_LoadTexture(renderer, "../assets/necromancer_standing.png");
	zombie_standing= IMG_LoadTexture(renderer, "../assets/zombie_standing.png");
	grave= IMG_LoadTexture(renderer, "../assets/grave.png");
}

assets::~assets(){
SDL_DestroyTexture(cop_standing);
SDL_DestroyTexture(necromancer_standing);
SDL_DestroyTexture(zombie_standing);
SDL_DestroyTexture(grave);
}

SDL_Texture * assets::return_texture(int type){

	//type cop
	if(type==0){
		return cop_standing;
	}
	//player
	if(type==1){
		return necromancer_standing;
	}
	//zombie
	if(type==2){
		return zombie_standing;
	}
	//grave
	if(type==10){
		return grave;

	}



}

