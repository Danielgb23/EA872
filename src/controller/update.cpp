#include "../include/controller/update.hpp"

using namespace std;
#define ENTITY_COLLISION_DIST 0.5

update::update(){
	state= SDL_GetKeyboardState(&keyboard_vsize); // estado do teclado
	Map.init(Viewer.return_renderer());
	//player
	//spawns_entity(1, 2, 10, 10);

	//graves
	spawns_entity(10, -1, 20, 20);
	spawns_entity(10, -1, 21, 20);
	spawns_entity(10, -1, 22, 20);
	spawns_entity(10, -1, 23, 20);

	spawns_entity(10, -1, 5, 7);
	spawns_entity(10, -1, 4, 7);
	spawns_entity(10, -1, 3, 7);

	spawns_entity(10, 2, 40, 20);
	spawns_entity(10, 3, 41, 20);
	spawns_entity(10, 4, 42, 20);
	spawns_entity(10, 5, 43, 20);

	spawns_entity(10, -1, 52, 8);
	spawns_entity(10, -1, 51, 8);
	spawns_entity(10, -1, 50, 8);


	spawns_entity(10, -1, 49, 30);
	spawns_entity(10, -1, 48, 30);
	spawns_entity(10, -1, 47, 30);

	spawns_entity(10, -1, 5, 30);
	spawns_entity(10, -1, 4, 30);
	spawns_entity(10, -1, 3, 30);
	//zombies

	//cops
	spawns_entity(0, 0, 13, 5);
	spawns_entity(0, 0, 5, 5);
	spawns_entity(0, 0, 48, 5);
	spawns_entity(0, 0, 50, 5);
	spawns_entity(0, 0, 52, 5);

}

update::~update(){
	//sends a package to itself so the thread is receive_from method stops waiting for a package
	if(server)
		udp.send("", "127.0.0.1", 9001 );
	if(client)
		udp.send("", "127.0.0.1", 9002 );

	//flag that stops extra thread
	server=0;
	client=0;

	//waits for thread
	t.join();
}

int update::is_server(){
	return server;
}

void update::step(float T){


	SDL_PumpEvents(); // update the keyboard state

	//load save
	if (state[SDL_SCANCODE_S]) 
		save();

	if (state[SDL_SCANCODE_L]) 
		load();

	//server mode
	if (state[SDL_SCANCODE_E] && !server) {
		server=42;
		t=std::thread(&update::server_net, this);
		cout<< "Running server" << endl;
	}

	if (state[SDL_SCANCODE_R] && !client) {
		client=42;
		t=std::thread(&update::client_net, this);
		cout<< "Running client" << endl;
	}

	if(server){
		//thread to wait for udp messages from players
		//entities movements
		for (Player plr: Players){
			Uint8 * player_state;

			player_state=&plr.keyboard()[0];		

			//if the plr keyboard is not empty
			if(player_state){
				//finds the players correct entity
				for (entity & ent : Entities){
					//of type player
					if(ent.rtype() == 1)
						//team corresponding to ID
						if(ent.return_team() == plr.id()){
							//move and attack graves
							move_player(ent, T, player_state);
							dig_grave(ent, T, player_state);
						}
				}
			}
		}

		for(entity & zombie: Entities){
			if(zombie.rtype()==2)
				move_zombie(zombie, T);
		}

		//attacks
		for(entity  &ent: Entities){
			if(ent.rtype() != 1 )
				attack_closest(ent, T);
		}

		//kills the dead
		//copies the alive to a vector and it back to Entities
		vector <entity> copy;
		if(!Entities.empty())
			for(entity ent: Entities)
				//if alive
				if(ent.return_health() > 0)
					copy.push_back(ent);
		Entities=copy;

		//sends Entity data to all players
		json k, json_plr;
		std::string dump;
		k["Entities"]=Entities;

		for (Player plr: Players){
			json_plr=k;
			json_plr["player"]=plr.id();	
			//	udp.send(json_plr.dump(), plr.ip() );
			udp.send(json_plr.dump(), plr.ip(), 9002 );
		}

	}

	else if (client){
		//sends keyboard state
		json j;
		std::vector<Uint8> keyboard (state, &state[keyboard_vsize]);
		j["keyboard"]=keyboard;
		//player's id which is zero if the server didn't initialize him
		j["player"]=player_id;

		//udp.send(j.dump());
		udp.send(j.dump());


	}
	//rendering part
	if(client || server){
		//renderization part
		Viewer.clear();

		//background
		SDL_Rect target;
		target.w=Viewer.rwidth();
		target.h=Viewer.rheight();
		target.x=0;
		target.y=0;
		Viewer.render(Map.rbackground(), target);

		//entities
		//creates vector to sort by y	
		vector <entity> sorted(Entities);
		//sorts 'sorted' by the entities's y
		std::sort(sorted.begin(), sorted.end(), [](entity  a, entity b){ return a.ry() < b.ry(); });

		for(entity ent: sorted){
			render_entity(ent);
		}

		Viewer.present();
	}
}

void update::server_net(){
	int player, new_player_number;
	bool already_listed=false;

	//player input
	json j;
	std::string str, ip;
	std::vector<Uint8> keyboard;

	while(server){
		//str=udp.get(ip);
		str=udp.get(ip);
		if (!json::accept(str))
		{
			std::cerr << "parse error on player remote data or end of program" << std::endl;
			std::cerr << str<< std::endl;

		}
		else{
			j= json::parse(str);
			//player=j["player"].get<int>(); //this is supposed to convert to int
			player=j["player"].get<int>();

			//new player
			if(player==0){
				for(Player plr : Players){
					if(ip.compare(plr.ip()) ==0)	
						already_listed=true;
				}
				if(!already_listed){
					//send package with new player number
					//if it's lost the packages with the entities also contain the player numbers
					new_player_number=Players.size()+1;

					//creates the player entity in the game
					spawns_entity(1, new_player_number, 10, 10);

					//creates the player object
					Player new_player(new_player_number , ip);
					Players.push_back(new_player);
				}

			}

			else{
				keyboard=j["keyboard"].get<vector<Uint8>>();
				//updates keyboard according to received package
				Players[player-1].keyboard(keyboard);
			}

		}
	}
}

void update::client_net(){
	//receives entities states
	json j;
	std::string str;
	while(client){

		//str=udp.get();
		std::string ip;
		str=udp.get(ip, 9002);

		if (!json::accept(str))
		{
			std::cerr << "client remote data from server parse error or end of program" << std::endl;
			std::cerr << str<< std::endl;

		}
		else{
			j= json::parse(str);
			//get's player id from server which flags that it was initialized(nonzero)
			player_id=j["player"];
			Entities=j["Entities"].get<vector<entity>>();
		}
	}

}

void update::render_entity(entity &ent){
	SDL_Rect target, arrow_rec;
	int h,w;
	string text;
	int render_factor=25;


	SDL_QueryTexture(Viewer.entity_texture(ent.rtype()), nullptr, nullptr, &w, &h);
	//renders the image taller than it's movement
	target.w=(int)(render_factor*ent.rwidth());
	target.h=(int)((float)h/(float)w*target.w);

	target.x = ent.rx()*render_factor;
	target.y = ent.ry()*render_factor-target.h;

	Viewer.render(Viewer.entity_texture(ent.rtype()), target);

	//renders text with health
	SDL_Rect Message_rect; 
	Message_rect.w = target.w; 
	Message_rect.h = target.w/2;
	Message_rect.x = target.x; 
	Message_rect.y = target.y-Message_rect.h;

	text=to_string(ent.return_health());
	if(text.length()==1)
		text="0"+text;
	if(text.length()==2)
		text="0"+text;
	Viewer.render_text(text, Message_rect);

	//renders team arrow
	 arrow_rec.w= Message_rect.w; 

	SDL_QueryTexture(Viewer.arrow_texture(ent.return_team()), nullptr, nullptr, &w, &h);
	arrow_rec.h=(int)((float)h/(float)w*Message_rect.w);

	 arrow_rec.x= Message_rect.x; 
	 arrow_rec.y= Message_rect.y-arrow_rec.h;

	Viewer.render(Viewer.arrow_texture(ent.return_team()), arrow_rec);


}
//creates shared pointer to host an entity until it's out of scope
entity * update::spawns_entity(int type, int team, float x, float  y){
	entity ent;
	//	ent.load( Viewer.return_renderer(), type, team );
	//	ent.update_pos(x,y);
	Entities.push_back(std::move(ent));
	//sets up the entity in the last element in the vector
	Entities.back().load(type, team );
	Entities.back().update_pos(x,y);
	return &Entities.back();
}

void update::move_player(entity &player, float T, const Uint8* player_state){
	float speed=player.return_speed();
	float dist=speed*T;

	//if keyboard up is pressed
	if (player_state[SDL_SCANCODE_UP]) 
		player.addy(-dist*collision_up(player));
	else if (player_state[SDL_SCANCODE_DOWN]) 
		player.addy(dist*collision_down(player));

	//allows for simultaneous movement horizontal vertical
	if (player_state[SDL_SCANCODE_LEFT]) 
		player.addx(-dist*collision_left(player));
	else if (player_state[SDL_SCANCODE_RIGHT]) 
		player.addx(dist*collision_right(player));
} 

float update::distance(entity &ent1,entity &ent2){
	return sqrt(pow((ent1.rx()-ent2.rx()),2)+pow((ent1.ry()-ent2.ry()),2));
}
void update::move_zombie(entity &zombie, float T){
	float speed=zombie.return_speed();
	float dist=speed*T;
	entity * closest=nullptr;
	float clst_dist=100000000;

	for (entity & victim : Entities)
		//if of a different team
		if(victim.return_team() != zombie.return_team() &&  victim.return_team()!= -1)
			//if is closest
			if(distance(zombie,victim) < clst_dist){
				closest=&victim;
				clst_dist=distance(zombie,victim);
			}

	if(closest==nullptr)
		return;
	//if keyboard up is pressed
	if (closest->ry() < zombie.ry()) 
		zombie.addy(-dist*collision_up(zombie));
	else if (closest->ry() > zombie.ry()) 
		zombie.addy(dist*collision_down(zombie));

	//allows for simultaneous movement horizontal vertical
	if (closest->rx() < zombie.rx()) 
		zombie.addx(-dist*collision_left(zombie));
	else if (closest->rx() > zombie.rx()) 
		zombie.addx(dist*collision_right(zombie));
}

void update::attack_closest(entity &ent, float T){
	float clst_dist=100000000;
	entity * closest=nullptr;

	for (auto & victim : Entities)
		//if of a different team and not grave or unanimate
		if(victim.return_team() != ent.return_team() &&  victim.return_team()!= -1)
			//if is closest
			if(distance(ent,victim) < clst_dist){
				closest=&victim;
				clst_dist=distance(ent,victim);
			}

	if(closest==nullptr)
		return;
	if(clst_dist<=ent.rrange()){

		int golpe=ent.attack(T);
		closest->take_damage(golpe);

	}
}
//digs closest grave to the player if within range
void update::dig_grave(entity &player, float T, const Uint8 * plr_state){
	entity * closest=nullptr;
	float clst_dist=100000000;

	//if keyboard up is pressed
	if (plr_state[SDL_SCANCODE_SPACE]) {
		for (entity & grave : Entities)
			//if is a grave (type 10) 
			if(grave.rtype()==10 )
				//if is closest
				if(distance(player,grave) < clst_dist){
					closest=&grave;
					clst_dist=distance(player,grave);
				}

		if(closest==nullptr)
			return;
		//within range
		if(clst_dist<=player.rrange()){
			closest->take_damage(player.attack(T));
			//if the grave is fully dug raise the dead
			if(closest->return_health()<=0){
				//zombie, player team, grave location
				spawns_entity(2, player.return_team(), closest->rx(), closest->ry());
			}
		}
	}
}


//detects collisions between entities and objects for a given entity in a given direction
float update::collision_down(entity &moved){
	//scans the entities near for collision
	for (entity collided : Entities)
		//if they have the same horizontal position within 1m
		if (collided.rx()-moved.rx()<ENTITY_COLLISION_DIST && collided.rx()-moved.rx()>-ENTITY_COLLISION_DIST) 
			//if they are near enough collide
			if (collided.ry() <= moved.ry()+ENTITY_COLLISION_DIST && collided.ry() >moved.ry()) 
				return 0;

	//here goes the map object collision code

	return 1;
}

float update::collision_up(entity& moved){
	//scans the entities near for collision
	for (entity collided : Entities)
		//if they have the same horizontal position within 1m
		if (collided.rx()-moved.rx()<ENTITY_COLLISION_DIST && collided.rx()-moved.rx()>-ENTITY_COLLISION_DIST) 
			//if they are near enough collide
			if (collided.ry() >= moved.ry()-ENTITY_COLLISION_DIST && collided.ry() <moved.ry()) 
				return 0;

	//here goes the map object collision code

	return 1;
}

float update::collision_left(entity& moved){
	//scans the entities near for collision
	for (entity collided : Entities)
		//if they have the same horizontal position within 1m
		if (collided.ry()-moved.ry()<ENTITY_COLLISION_DIST && collided.ry()-moved.ry()>-ENTITY_COLLISION_DIST) 
			//if they are near enough collide
			if (collided.rx() >= moved.rx()-ENTITY_COLLISION_DIST && collided.rx() <moved.rx()) 
				return 0;

	//here goes the map object collision code

	return 1;
}
float update::collision_right(entity &moved){
	//scans the entities near for collision
	for (entity collided : Entities)
		//if they have the same horizontal position within 1m
		if (collided.ry()-moved.ry()<ENTITY_COLLISION_DIST && collided.ry()-moved.ry()>-ENTITY_COLLISION_DIST) 
			//if they are near enough collide
			if (collided.rx() <= moved.rx() + ENTITY_COLLISION_DIST && collided.rx() >moved.rx()) 
				return 0;

	//here goes the map object collision code

	return 1;
}



void update::save(){
	json j;
	std::string str;
	std::ofstream arquivo1;

	//transforms class update object into json object
	j["Entities"]=Entities;
	//saves to a file
	str = j.dump(); 
	arquivo1.open("save.json");
	arquivo1 << str;
	arquivo1.close();

}
void update::load(){
	std::stringstream s;
	json j;
	std::ifstream arquivo;

	arquivo.open("save.json");
	if (arquivo.is_open() ) {
		s << arquivo.rdbuf();
		j= json::parse(s.str());
		arquivo.close();
		//converts to vector and assigns
		Entities=j["Entities"].get<vector<entity>>();
	} else {
		std::cout << "Error reading save file" << std::endl;
	}

}

