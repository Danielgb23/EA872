#include <string>

#include "../include/model/entity.hpp"

class Player {
	public:
		Player(int id, std::string ip);
		//setters
		void id(int set_id);
		void ip(std::string set_ip);
		void keyboard(std::vector<Uint8> data);

		//getters

		int id();
		std::string ip();
		std::vector<Uint8> keyboard();

	private:
		std::vector<Uint8> player_keyboard;
		int number_id;
		std::string ip_adr;




};
