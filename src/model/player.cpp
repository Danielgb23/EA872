#include "../include/model/player.hpp"
using namespace std;

player::player(){
	INIReader reader("../config/player.ini");
	//INIReader reader("../../config/player.ini");
	if (reader.ParseError() < 0) {
		std::cout << "Can't load 'player.ini'\n";
		exit( 1 );
	}
	 health = reader.GetInteger("stats", "health", -1);
	 speed = reader.GetReal("stats", "speed", -1);
	 dig_rate = reader.GetReal("stats", "digrate", -1);
	 height = reader.GetReal("stats", "height", -1);
	 width = reader.GetReal("stats", "width", -1);
}

int player::return_team(){
return team;
}

void player::load_team(int new_team){
	 team=new_team;
}

//loads the player texture
void player::load_texture(SDL_Renderer * renderer){
	player_texture = IMG_LoadTexture(renderer, "../assets/capi.png");
}

SDL_Texture * player::return_texture(){
	return player_texture;
}

int	player::return_health(){
	return health;
}
//the player takes 'damage' amount of damage
int	player::take_damage(int damage){
	health-=damage;
}
//loads the variables x and y  with the player current position
void	player::pos(float &pos_x, float &pos_y){
	pos_x=x;
	pos_y=y;
}

int	player::return_speed(){
	return speed;
}

int	player::return_dig_rate(){
	return dig_rate;
}
//updates the players position according to the fuction input
void	player::update_pos(float pos_x, float pos_y){
	x=pos_x;
	y=pos_y;
}


	player::~player(){
	SDL_DestroyTexture(player_texture);

	}
