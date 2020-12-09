
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class assets{
	private:

		SDL_Texture * 	cop_standing;
		SDL_Texture *   necromancer_standing;
		SDL_Texture * 	zombie_standing;
		SDL_Texture * 	grave;
	public:

		SDL_Texture * return_texture(int type);
 		void load(SDL_Renderer * renderer);
		~assets();


};
