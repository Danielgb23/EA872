#include "../../include/view/assets.hpp"


using namespace boost::filesystem;
using namespace std;

void assets::load(SDL_Renderer * renderer){

//entity textures
	cop_standing= IMG_LoadTexture(renderer, "../assets/cop_standing.png");
	necromancer_standing= IMG_LoadTexture(renderer, "../assets/necromancer_standing.png");
	zombie_standing= IMG_LoadTexture(renderer, "../assets/zombie_standing.png");
	grave= IMG_LoadTexture(renderer, "../assets/grave.png");

	//this loads all arrows avaiable in the assets folder assets/arrows
	path p ("../assets/arrows");
	directory_iterator end_itr;
	SDL_Texture *arrow;
	// cycle through the directory
	for (directory_iterator itr(p); itr != end_itr; ++itr)
	{
		// If it's not a directory, list it. If you want to list directories too, just remove this check.
		if (is_regular_file(itr->path())) {
			// assign current file name to current_file and echo it out to the console.
			string current_file = itr->path().string();
			cout << current_file << endl;

			arrow= IMG_LoadTexture(renderer, current_file.c_str());
			arrows.push_back(arrow);
		}
	}
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

SDL_Texture * assets::return_arrow(int team){
	if(team<1 || team > arrows.size())
		return nullptr;
	else 
		return arrows[team-1];
}
