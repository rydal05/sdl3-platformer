/*include "player.h"	

#include <cmath>

namespace{
	const float kSlowdownFactor = 0.8f;
	const float kWalkingAcceleration = 0.0012f; //(pixels / ms) / ms
	const float kMaxSpeedX = 0.325f; //(pixels / ms)

	const float kJumpSpeed = 0.325f; // pixels/ms
	const int kJumpTime = 275; // in ms
	const float kGravity = 0.0012f;
	const float kMaxSpeedY = 0.325f;

}



bool operator<(const Player::SpriteState& a, const Player::SpriteState& b){
	if(a.motion_type != b.motion_type){
		return a.motion_type < b.motion_type;
	}
	if(a.horizontal_facing != b.horizontal_facing){
		return a.horizontal_facing < b.horizontal_facing;
	}

	return false;
}

Player::Player(int x, int y, SDL_Renderer* renderer, Graphics& graphics) :
	x_(x),
	y_(y),
	velocity_x_(0.0f),
	acceleration_x_(0.0f),
	m_renderer(renderer),
	horizontal_facing(LEFT),
	on_ground_(false){
	initializeSprites(graphics);

}

void Player::update(int elapsed_time_ms){
	sprites_[getSpriteState()]->update(elapsed_time_ms);
	jump_.update(elapsed_time_ms);

	x_ += round(velocity_x_ * elapsed_time_ms);
	velocity_x_ += acceleration_x_ * elapsed_time_ms;
	if(acceleration_x_ < 0.0f){
		velocity_x_ = std::max(velocity_x_, -kMaxSpeedX);
	}
	else if(acceleration_x_ > 0.0f){
		velocity_x_ = std::min(velocity_x_, kMaxSpeedX);
	}
	else if(on_ground()){ // is 0
		velocity_x_ *= kSlowdownFactor;
	}

	y_ += round(velocity_y_ * elapsed_time_ms);
	if(!jump_.active()){
		velocity_y_ += std::min(velocity_y_ + kGravity * elapsed_time_ms, kMaxSpeedY);
	}

	//TODO: REMOVE THIS HACK
	if(y_ >= 320){
		y_ = 320;
		velocity_y_ = 0.0f;

	}
	on_ground_ = y_ + 320;
}

void Player::draw(Graphics& graphics){
	sprites_[getSpriteState()]->draw(graphics, x_, y_);
}

void Player::startMovingLeft(){
	horizontal_facing = LEFT;
	acceleration_x_ = -kWalkingAcceleration;
}
void Player::startMovingRight(){
	horizontal_facing = RIGHT;
	acceleration_x_ = kWalkingAcceleration;
}
void Player::stopMoving(){
	acceleration_x_ = 0.0f;
}


void Player::startJump(){
	if(on_ground()){
		jump_.reset();
		velocity_y_ = -kJumpSpeed;
		//give ourselves init velocity
	}
	//else if not on ground(falling)
	else if(velocity_y_ < 0.0f){
		jump_.reactivate();
	}

		//do nothing 
	//else if we are mid jump
}
void Player::stopJump(){
	jump_.deactivate();
}

void Player::initializeSprites(Graphics& graphics){
	sprites_[SpriteState(STANDING, LEFT)] =
		boost::shared_ptr<Sprite>(new Sprite(
			graphics,
			"sprites\\MyChar Minogame.bmp",
			0, 0, Game::kTileSize, Game::kTileSize, m_renderer));
	sprites_[SpriteState(WALKING, LEFT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
		"sprites\\MyChar Minogame.bmp",
		0, 0, Game::kTileSize, Game::kTileSize, m_renderer,
		15, 3));
	sprites_[SpriteState(WALKING, RIGHT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
		"sprites\\MyChar Minogame.bmp",
		0, Game::kTileSize, Game::kTileSize, Game::kTileSize, m_renderer,
		15, 3));
	sprites_[SpriteState(STANDING, RIGHT)] = boost::shared_ptr<Sprite>(new Sprite(graphics,
		"sprites\\MyChar Minogame.bmp",
		0, Game::kTileSize, Game::kTileSize, Game::kTileSize, m_renderer));
}

Player::SpriteState Player::getSpriteState(){
	return SpriteState(
		acceleration_x_ == 0.0f ? STANDING : WALKING,
		horizontal_facing);
}

void Player::Jump::reset(){
	time_remaining_ms_ = kJumpTime;
	reactivate();
}

void Player::Jump::update(int elapsed_time_ms){
	if(active_){
		time_remaining_ms_ -= elapsed_time_ms;
		if(time_remaining_ms_ <= 0){
			active_ = false;
		}
	}
}*/