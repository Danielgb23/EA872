#include "../include/controller/update.hpp"
using namespace std;
#define ENTITY_COLLISION_DIST 1

update::update(){
	state= SDL_GetKeyboardState(nullptr); // estado do teclado

	shared_ptr<entity> player1 (new entity);
	player1->load( Viewer.return_renderer(), 1, 2 );
	player1->update_pos(10,10);
	Entities.push_back(player1);


	shared_ptr<entity> zombie1 (new entity);
	shared_ptr<entity> cop (new entity);

	zombie1->load( Viewer.return_renderer(), 2, 1 );
	cop->load( Viewer.return_renderer(), 0, 0 );

	zombie1->update_pos(20,10);
	cop->update_pos(10,5);

	Entities.push_back(zombie1);
	Entities.push_back(cop);
}

void update::step(float T){
	move_player(Entities[0], T);
	move_zombie(Entities[1], T);

	//renderization part
	Viewer.clear();
	for(shared_ptr<entity> ent: Entities){
		render_entity(ent);
	}

	Viewer.present();

}

void update::render_entity(shared_ptr<entity> ent){
	SDL_Rect target;
	target.x = ent->rx()*50;
	target.y = ent->ry()*50;
	//SDL_QueryTexture(ent.return_texture(), nullptr, nullptr, &target.w, &target.h);
	target.w=50;
	target.h=50;

	Viewer.render(ent->return_texture(), target);

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
	shared_ptr<entity>  closest;
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
