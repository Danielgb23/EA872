#include "../include/controller/update.hpp"
using namespace std;
#define ENTITY_COLLISION_DIST 0.5

update::update(){
	state= SDL_GetKeyboardState(nullptr); // estado do teclado
	Map.init(Viewer.return_renderer());
//player
	spawns_entity(1, 2, 10, 10);

	//graves
	spawns_entity(10, -1, 20, 20);
	spawns_entity(10, -1, 21, 20);
	spawns_entity(10, -1, 22, 20);
	spawns_entity(10, -1, 23, 20);

	spawns_entity(10, -1, 5, 7);
	spawns_entity(10, -1, 4, 7);
	spawns_entity(10, -1, 3, 7);

	spawns_entity(10, -1, 40, 20);
	spawns_entity(10, -1, 41, 20);
	spawns_entity(10, -1, 42, 20);
	spawns_entity(10, -1, 43, 20);
	//zombies

	//cops
	spawns_entity(0, 0, 13, 5);
	spawns_entity(0, 0, 5, 5);
	spawns_entity(0, 0, 48, 5);
	spawns_entity(0, 0, 50, 5);
	spawns_entity(0, 0, 52, 5);

}

void update::step(float T){
	//entities movements
	move_player(Entities[0], T);

	for(shared_ptr<entity> zombie: Entities){
		if(zombie->rtype()==2)
			move_zombie(zombie, T);
	}

	//attacks
	for(shared_ptr<entity> ent: Entities){
		if(ent->rtype() != 1 )
			attack_closest(ent, T);
	}
	dig_grave(Entities[0], T);

	//kills the dead
	for (auto it = Entities.begin(); it != Entities.end(); ++it)
		if(*it)
			if((*it)->return_health() <= 0)
				Entities.erase(it);

	
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
	for(shared_ptr<entity> ent: Entities){
		render_entity(ent);
	}

	Viewer.present();

}



void update::render_entity(shared_ptr<entity> ent){
	SDL_Rect target;
	int h,w;
	string text;
	int render_factor=25;
	SDL_QueryTexture(ent->return_texture(), nullptr, nullptr, &w, &h);
	//renders the image taller than it's movement
	target.w=(int)(render_factor*ent->rwidth());
	target.h=(int)((float)h/(float)w*target.w);

	target.x = ent->rx()*render_factor;
	target.y = ent->ry()*render_factor-target.h;

	Viewer.render(ent->return_texture(), target);

	//renders text with health
	SDL_Rect Message_rect; 
	Message_rect.w = target.w; 
	Message_rect.h = target.w/2;
	Message_rect.x = target.x; 
	Message_rect.y = target.y-Message_rect.h;

	text=to_string(ent->return_health());
	if(text.length()==1)
		text="0"+text;
	if(text.length()==2)
		text="0"+text;
	Viewer.render_text(text, Message_rect);

}
void ::update::spawns_entity(int type, int team, float x, float  y){
	shared_ptr<entity> ent (new entity);
	ent->load( Viewer.return_renderer(), type, team );
	ent->update_pos(x,y);
	Entities.push_back(ent);
}

void update::move_player(shared_ptr<entity> player, float T){
	float speed=player->return_speed();
	float dist=speed*T;
	// Polling of events
	SDL_PumpEvents(); // update the keyboard state

	//if keyboard up is pressed
	if (state[SDL_SCANCODE_UP]) 
		player->addy(-dist*collision_up(player));
	else if (state[SDL_SCANCODE_DOWN]) 
		player->addy(dist*collision_down(player));

	//allows for simultaneous movement horizontal vertical
	if (state[SDL_SCANCODE_LEFT]) 
		player->addx(-dist*collision_left(player));
	else if (state[SDL_SCANCODE_RIGHT]) 
		player->addx(dist*collision_right(player));
} 

float update::distance(shared_ptr<entity> ent1,shared_ptr<entity> ent2){
	return sqrt(pow((ent1->rx()-ent2->rx()),2)+pow((ent1->ry()-ent2->ry()),2));
}
void update::move_zombie(shared_ptr<entity> zombie, float T){
	float speed=zombie->return_speed();
	float dist=speed*T;
	shared_ptr<entity>  closest=nullptr;
	float clst_dist=100000000;

	// Polling of events
	SDL_PumpEvents(); // update the keyboard state

	for (shared_ptr<entity> victim : Entities)
		//if of a different team
		if(victim->return_team() != zombie->return_team() &&  victim->return_team()!= -1)
			//if is closest
			if(distance(zombie,victim) < clst_dist){
				closest=victim;
				clst_dist=distance(zombie,victim);
			}

	if(closest==nullptr)
		return;
	//if keyboard up is pressed
	if (closest->ry() < zombie->ry()) 
		zombie->addy(-dist*collision_up(zombie));
	else if (closest->ry() > zombie->ry()) 
		zombie->addy(dist*collision_down(zombie));

	//allows for simultaneous movement horizontal vertical
	if (closest->rx() < zombie->rx()) 
		zombie->addx(-dist*collision_left(zombie));
	else if (closest->rx() > zombie->rx()) 
		zombie->addx(dist*collision_right(zombie));
}

void update::attack_closest(shared_ptr<entity> ent, float T){
	shared_ptr<entity>  closest;
	float clst_dist=100000000;

	for (shared_ptr<entity> victim : Entities)
		//if of a different team
		if(victim->return_team() != ent->return_team() &&  victim->return_team()!= -1)
			//if is closest
			if(distance(ent,victim) < clst_dist){
				closest=victim;
				clst_dist=distance(ent,victim);
			}

	if(closest==nullptr)
		return;
	if(clst_dist<=ent->rrange()){
		closest->take_damage(ent->attack(T));

	}
}
//digs closest grave to the player if within range
void update::dig_grave(shared_ptr<entity> player, float T){
	shared_ptr<entity>  closest;
	float clst_dist=100000000;
	SDL_PumpEvents(); // update the keyboard state

	//if keyboard up is pressed
	if (state[SDL_SCANCODE_SPACE]) {
		for (shared_ptr<entity> grave : Entities)
			//if is a grave (type 10) 
			if(grave->rtype()==10 )
				//if is closest
				if(distance(player,grave) < clst_dist){
					closest=grave;
					clst_dist=distance(player,grave);
				}

		if(closest==nullptr)
			return;
		//within range
		if(clst_dist<=player->rrange()){
			closest->take_damage(player->attack(T));
			//if the grave is fully dug raise the dead
			if(closest->return_health()<=0){
				//zombie, player team, grave location
				spawns_entity(2, player->return_team(), closest->rx(), closest->ry());
			}
		}
	}
}


//detects collisions between entities and objects for a given entity in a given direction
float update::collision_down(shared_ptr<entity> moved){
	//scans the entities near for collision
	for (shared_ptr<entity> collided : Entities)
		//if they have the same horizontal position within 1m
		if (collided->rx()-moved->rx()<ENTITY_COLLISION_DIST && collided->rx()-moved->rx()>-ENTITY_COLLISION_DIST) 
			//if they are near enough collide
			if (collided->ry() <= moved->ry()+ENTITY_COLLISION_DIST && collided->ry() >moved->ry()) 
				return 0;

	//here goes the map object collision code

	return 1;
}

float update::collision_up(shared_ptr<entity> moved){
	//scans the entities near for collision
	for (shared_ptr<entity> collided : Entities)
		//if they have the same horizontal position within 1m
		if (collided->rx()-moved->rx()<ENTITY_COLLISION_DIST && collided->rx()-moved->rx()>-ENTITY_COLLISION_DIST) 
			//if they are near enough collide
			if (collided->ry() >= moved->ry()-ENTITY_COLLISION_DIST && collided->ry() <moved->ry()) 
				return 0;

	//here goes the map object collision code

	return 1;
}

float update::collision_left(shared_ptr<entity> moved){
	//scans the entities near for collision
	for (shared_ptr<entity> collided : Entities)
		//if they have the same horizontal position within 1m
		if (collided->ry()-moved->ry()<ENTITY_COLLISION_DIST && collided->ry()-moved->ry()>-ENTITY_COLLISION_DIST) 
			//if they are near enough collide
			if (collided->rx() >= moved->rx()-ENTITY_COLLISION_DIST && collided->rx() <moved->rx()) 
				return 0;

	//here goes the map object collision code

	return 1;
}
float update::collision_right(shared_ptr<entity> moved){
	//scans the entities near for collision
	for (shared_ptr<entity> collided : Entities)
		//if they have the same horizontal position within 1m
		if (collided->ry()-moved->ry()<ENTITY_COLLISION_DIST && collided->ry()-moved->ry()>-ENTITY_COLLISION_DIST) 
			//if they are near enough collide
			if (collided->rx() <= moved->rx() + ENTITY_COLLISION_DIST && collided->rx() >moved->rx()) 
				return 0;

	//here goes the map object collision code

	return 1;
}
