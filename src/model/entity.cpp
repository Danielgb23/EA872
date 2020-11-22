#include "../include/model/entity.hpp"
using namespace std;

entity::entity(){
}

int entity::return_team(){
	return team;
}

void entity::load_team(int new_team){
	team=new_team;
}

//loads the entity texture
void entity::load(SDL_Renderer * renderer, int get_type, int new_team){
	type=get_type;
	team=new_team;
	//type cop
	if(type==0){
		standing = IMG_LoadTexture(renderer, "../assets/cop_standing.png");

		INIReader reader("../config/cop.ini");
		if (reader.ParseError() < 0) {
			std::cout << "Can't load 'cop.ini'\n";
			exit( 1 );
		}
		health = reader.GetInteger("stats", "health", -1);
		speed = reader.GetReal("stats", "speed", -1);
		attack_damage = reader.GetReal("stats", "attack", -1);
		attack_rate = reader.GetReal("stats", "attack_rate", -1);
		height = reader.GetReal("stats", "height", -1);
		width = reader.GetReal("stats", "width", -1);
		range = reader.GetReal("stats", "range", -1);

	}
	//player
	if(type==1){
		standing = IMG_LoadTexture(renderer, "../assets/necromancer_standing.png");
		INIReader reader("../config/player.ini");
		if (reader.ParseError() < 0) {
			std::cout << "Can't load 'player.ini'\n";
			exit( 1 );
		}
		health = reader.GetInteger("stats", "health", -1);
		speed = reader.GetReal("stats", "speed", -1);
		attack_damage = reader.GetReal("stats", "attack", -1);
		attack_rate = reader.GetReal("stats", "attack_rate", -1);
		height = reader.GetReal("stats", "height", -1);
		width = reader.GetReal("stats", "width", -1);
		range = reader.GetReal("stats", "range", -1);

	}
	//zombie
	if(type==2){
		standing = IMG_LoadTexture(renderer, "../assets/zombie_standing.png");
		INIReader reader("../config/zombie.ini");
		if (reader.ParseError() < 0) {
			std::cout << "Can't load 'zombie.ini'\n";
			exit( 1 );
		}
		health = reader.GetInteger("stats", "health", -1);
		speed = reader.GetReal("stats", "speed", -1);
		attack_damage = reader.GetReal("stats", "attack", -1);
		attack_rate = reader.GetReal("stats", "attack_rate", -1);
		height = reader.GetReal("stats", "height", -1);
		width = reader.GetReal("stats", "width", -1);
		range = reader.GetReal("stats", "range", -1);

	}
	if(type==10){

		standing = IMG_LoadTexture(renderer, "../assets/grave.png");
		INIReader reader("../config/grave.ini");
		if (reader.ParseError() < 0) {
			std::cout << "Can't load 'grave.ini'\n";
			exit( 1 );
		}
		health = reader.GetInteger("stats", "health", -1);
		height = reader.GetReal("stats", "height", -1);
		width = reader.GetReal("stats", "width", -1);

	}



}

void entity::load_texture(SDL_Renderer * renderer){

	if(type==0)
		standing = IMG_LoadTexture(renderer, "../assets/cop_standing.png");
	if(type==1)
		standing = IMG_LoadTexture(renderer, "../assets/necromancer_standing.png");
	if(type==2)
		standing = IMG_LoadTexture(renderer, "../assets/zombie_standing.png");
	if(type==10)
		standing = IMG_LoadTexture(renderer, "../assets/grave.png");
}

float entity::rwidth(){
	return width;
}

int entity::rtype(){
	return type;
}
float entity::rx(){
	return x;
}

float entity::ry(){
	return y;
}


void entity::addx(float load_x){
	x+=load_x;
}
void entity::addy(float load_y){
	y+=load_y;
}

SDL_Texture * entity::return_texture(){
	return standing;
}

int	entity::return_health(){
	return health;
}

int	entity::attack(float time_step){
	if(attack_cooldown <=0){
		attack_cooldown=1/attack_rate;
		return attack_damage;
	}
	attack_cooldown-=time_step;
	return 0;
}

float entity::rrange(){
	return range;
}
//the entity takes 'damage' amount of damage
int	entity::take_damage(int damage){
	health-=damage;
}
//loads the variables x and y  with the entity current position
void	entity::pos(float &pos_x, float &pos_y){
	pos_x=x;
	pos_y=y;
}

int	entity::return_speed(){
	return speed;
}

int	entity::return_dig_rate(){
	return dig_rate;
}
//updates the entitys position according to the fuction input
void	entity::update_pos(float pos_x, float pos_y){
	x=pos_x;
	y=pos_y;
}


entity::~entity(){
	//cout<<"entity destroyed\n";
	SDL_DestroyTexture(standing);

}
