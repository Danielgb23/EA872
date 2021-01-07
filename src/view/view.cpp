#include "../../include/view/view.hpp"

using namespace std;

SDL_Renderer * view::return_renderer(){
	return renderer;
}

view::view(){
	INIReader reader("../config/view.ini");
	if (reader.ParseError() < 0) {
		std::cout << "Can't load 'view.ini'\n";
		exit( 1 );
	}
	screen_width = reader.GetInteger("screen", "width", -1);
	screen_height = reader.GetInteger("screen", "height", -1);
	
	if (TTF_Init() < 0) {
	   cout << "error initializing SDL_ttf" << endl;
	}
	// Inicializando o subsistema de video do SDL
	if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
		std::cout << SDL_GetError();
		exit( 1 );
	}
	this->init_window();
	this->init_render();

	Assets.load(renderer);
	// Select the color for drawing. It is set to red here.
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

}
void view::init_window(){

	// Criando uma janela
	window = nullptr;
	window = SDL_CreateWindow("Madrugada dos mortos",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			screen_width,
			screen_height,
			SDL_WINDOW_SHOWN);
	if (window==nullptr) { // Em caso de erro...
		std::cout << SDL_GetError();
		SDL_Quit();
		exit( 1 );
	}

}

void view::init_render(){
	// Inicializando o renderizador
	renderer = SDL_CreateRenderer(
			window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer==nullptr) { // Em caso de erro...
		SDL_DestroyWindow(window);
		std::cout << SDL_GetError();
		SDL_Quit();
		exit( 1 );
	}

}
void  view::render_text(string text, SDL_Rect Message_rect){
	TTF_Font* Font = TTF_OpenFont("../assets/Arial.ttf", 80); 
	SDL_Color Color = {0, 0, 0};  

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, text.c_str(), Color); 
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 

	render(Message, Message_rect);

	//Don't forget to free your surface and texture
	TTF_CloseFont( Font );
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}


void view::clear(){
	SDL_RenderClear(renderer);
}
void view::present(){
	SDL_RenderPresent(renderer);
}
SDL_Texture * view::entity_texture(int type){
	return Assets.return_texture(type);
}

SDL_Texture * view::arrow_texture(int team){
	return	Assets.return_arrow(team);
}

void view::render(SDL_Texture * texture, SDL_Rect target){
	//Draws the target element 
	SDL_RenderCopy(renderer, texture, nullptr, &target);
}

int view::rwidth(){
	return screen_width;
}

int view::rheight(){
	return screen_height;
}
view::~view(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
