
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>
#include <regex>

class assets{
	private:

		SDL_Texture * 	cop_standing;
		SDL_Texture *   necromancer_standing;
		SDL_Texture * 	zombie_standing;
		SDL_Texture * 	grave;
		std::vector<SDL_Texture *> arrows; 
	public:

		SDL_Texture * return_arrow(int team);
		SDL_Texture * return_texture(int type);
 		void load(SDL_Renderer * renderer);
		~assets();


};
