#include "../include/model/player.hpp"

Player::Player(int id, std::string ip){
number_id=id;
ip_adr=ip;
}

//setters
void Player::id(int set_id){
	number_id=set_id;
}


void Player::ip(std::string set_ip){
	ip_adr=set_ip;
}

void Player::keyboard(std::vector<Uint8> data){
	player_keyboard=data;
}

//getters

int Player::id(){
	return number_id;
}


std::string Player::ip(){
	return ip_adr;
}


std::vector<Uint8> Player::keyboard(){
	return player_keyboard;
}
