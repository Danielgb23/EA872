#include "../include/controller/update.hpp"
using namespace std;
#define ENTITY_COLLISION_DIST 0.5

update::update(){
	state= SDL_GetKeyboardState(nullptr); // estado do teclado

	shared_ptr<entity> player1 (new entity);
	player1->load( Viewer.return_renderer(), 1, 2 );
	player1->update_pos(10,10);
	Entities.push_back(player1);


	shared_ptr<entity> zombie1 (new entity);
	zombie1->load( Viewer.return_renderer(), 2, 2 );
	zombie1->update_pos(20,10);
	Entities.push_back(zombie1);

	shared_ptr<entity> zombie2 (new entity);
	zombie2->load( Viewer.return_renderer(), 2, 2 );
	zombie2->update_pos(20,5);
	Entities.push_back(zombie2);


	shared_ptr<entity> cop (new entity);
	cop->load( Viewer.return_renderer(), 0, 0 );
	cop->update_pos(10,5);
	Entities.push_back(cop);

	shared_ptr<entity> cop2 (new entity);
	cop2->load( Viewer.return_renderer(), 0, 0 );
	cop2->update_pos(5,5);
	Entities.push_back(cop2);

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
		if(ent->rtype() != 1)
			attack_closest(ent, T);
	}

	//kills the dead

for (auto it = Entities.begin(); it != Entities.end(); ++it)
		if((*it)->return_health() <= 0)
			Entities.erase(it);


	//renderization part
	Viewer.clear();
	for(shared_ptr<entity> ent: Entities){
		render_entity(ent);
	}

	Viewer.present();

}



void update::render_entity(shared_ptr<entity> ent){
	SDL_Rect target;
	int h,w;
	string text;
	std::ostringstream ss;
	SDL_QueryTexture(ent->return_texture(), nullptr, nullptr, &w, &h);
	//renders the image taller than it's movement
	target.h=(int)((float)h/(float)w*50);
	target.w=50;

	target.x = ent->rx()*50;
	target.y = ent->ry()*50-target.h;

	Viewer.render(ent->return_texture(), target);

//renders text with health
	SDL_Rect Message_rect; 
	Message_rect.w = target.w/2; 
	Message_rect.h = target.w/4;
	Message_rect.x = target.x+target.w/4; 
	Message_rect.y = target.y-Message_rect.h;

	text=to_string(ent->return_health());
	if(text.length()==1)
		text="0"+text;
	if(text.length()==2)
		text="0"+text;
	Viewer.render_text(text, Message_rect);

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
		if(victim->return_team() != zombie->return_team())
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
		if(victim->return_team() != ent->return_team())
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
