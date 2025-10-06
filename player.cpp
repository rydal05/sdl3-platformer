#include "player.h"
#include <iostream>
#include <cmath>

namespace{
	//Horizontal Motion
	const float kSlowdownFactor = 0.8f;
	const float kWalkingAcceleration = 0.0012f; //(pixels / ms) / ms
	const float kMaxSpeedX = 0.325f; //(pixels / ms)
	//Vertical motion
	const float kGravity = 0.0012f;
	const float kJumpSpeed = 0.325f; // pixels/ms
	const float kMaxSpeedY = 0.425f;
	const int kJumpTime = 275; // in ms
	//Sprite directory
	const std::string kSpriteFilePath = "sprites/MyChar Minogame.bmp";
	//Sprite Frames
	const int kJumpFrame = 1;
	const int kFallFrame = 2;
	const int kCharacterFrame = 0;
	const int kWalkFrame = 0;
	const int kStandFrame = 0;
	//Vert Dir
	const int kUpFrameOffset = 3;
	const int kBackFrame = 7;
	const int kDownFrame = 6;
	//Frame timing
	const int kWalkFps = 15;
	const int kNumFrames = 3;

	//Collision Rect
	Rectangle kCollisionX(6, 10, 20, 12);
	Rectangle kCollisionY(10, 2, 12, 30);
}

bool operator<(const Player::SpriteState& a, const Player::SpriteState& b){
	if(a.motion_type != b.motion_type){
		return a.motion_type < b.motion_type;
	}
	if(a.horizontal_facing != b.horizontal_facing){
		return a.horizontal_facing < b.horizontal_facing;
	}
	if(a.vertical_facing != b.vertical_facing){
		return a.vertical_facing < b.vertical_facing;
	}

	return false;
}

Player::Player(int x, int y, SDL_Renderer* renderer, Graphics& graphics) :
	x_(x),
	y_(y),
	velocity_x_(0.0f),
	velocity_y_(0.0f),
	acceleration_x_(0.0f),
	m_renderer(renderer),
	on_ground_(false),
	horizontal_facing_(LEFT),
	vertical_facing_(HORIZONTAL){
	initializeSprites(graphics);
}

void Player::update(int elapsed_time_ms, const Map& map){
	sprites_[getSpriteState()]->update(elapsed_time_ms);
	jump_.update(elapsed_time_ms);

	Player::updateX(elapsed_time_ms, map);
	Player::updateY(elapsed_time_ms, map);
}

void Player::updateX(int elapsed_time_ms, const Map& map){
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
}

void Player::updateY(int elapsed_time_ms, const Map& map){
	//update velocity
	if(!jump_.active()){
		velocity_y_ = std::min(velocity_y_ + kGravity * elapsed_time_ms, kMaxSpeedY);
	}

	//calculate delta
	const int delta = (int)round(velocity_y_ * elapsed_time_ms);
	if(delta > 0){

		struct CollisionInfo{
			bool collided;
			int row, col;
		};

		//check collision in the direction of delta
		CollisionInfo info = {false, 0, 0};
		std::vector<Map::CollisionTile> tiles(map.getCollidingTiles(bottomCollision(delta)));
		for(size_t i = 0; i < tiles.size(); i++){
			if(tiles[i].tileType == Map::WALL_TILE){
				info = {true, tiles[i].row, tiles[i].col};
				break;
			}
		}

		//react to collision
		if(info.collided){
			y_ = info.row * Game::kTileSize - kCollisionY.height();
			velocity_y_ = 0.0f;
		}
		else{
			y_ += delta;
			on_ground_ = false;
		}
		//Check collision in other direction
		info = {false,0,0};
		tiles = map.getCollidingTiles(topCollision(0));
		for(size_t i = 0; i < tiles.size(); i++){
			if(tiles[i].tileType == Map::WALL_TILE){
				info = {true, tiles[i].row, tiles[i].col};
				break;
			}
		}

		if(info.collided){
			y_ = info.row * Game::kTileSize + kCollisionY.bottom();
			on_ground_ = true;
		}
	}
}

void Player::draw(Graphics& graphics){
	sprites_[getSpriteState()]->draw(graphics, x_, y_);
	//std::cout << y_ << std::endl;

}

void Player::startMovingLeft(){
	horizontal_facing_ = LEFT;
	acceleration_x_ = -kWalkingAcceleration;
}
void Player::startMovingRight(){
	horizontal_facing_ = RIGHT;
	acceleration_x_ = kWalkingAcceleration;
}
void Player::stopMoving(){
	acceleration_x_ = 0.0f;
}

void Player::lookUp(){
	vertical_facing_ = UP;
}

void Player::lookDown(){
	vertical_facing_ = DOWN;
}

void Player::lookHorizontal(){
	vertical_facing_ = HORIZONTAL;
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
	// for every motion type
	for(MotionType motion_type = FIRST_MOTION_TYPE;
		motion_type < LAST_MOTION_TYPE;
		++motion_type){
		// for every horizontal facing
		for(HorizontalFacing horizontal_facing = FIRST_HORIZONTAL_FACING;
			horizontal_facing < LAST_HORIZONTAL_FACING;
			++horizontal_facing){
			// for every vertical facing
			for(VerticalFacing vertical_facing = FIRST_VERTICAL_FACING;
				vertical_facing < LAST_VERTICAL_FACING;
				++vertical_facing)
				// create a sprite state
				// call initializesprite with spritestate
				initializeSprite(graphics, SpriteState(motion_type, horizontal_facing, vertical_facing));
		}
	}
}

Player::SpriteState Player::getSpriteState(){
	MotionType motion;
	if(on_ground()){
		motion = acceleration_x_ == 0.0f ? STANDING : WALKING;
	}
	else{
		motion = velocity_y_ < 0.0f ? JUMPING : FALLING;
	}
	return SpriteState(motion,
		horizontal_facing_,
		vertical_facing_);
}

void Player::initializeSprite(Graphics& graphics, const SpriteState& sprite_state){
	int source_y = sprite_state.horizontal_facing == LEFT ?
		kCharacterFrame * Game::kTileSize :
		(1 + kCharacterFrame) * Game::kTileSize;
	int source_x;
	switch(sprite_state.motion_type){
		case WALKING:
			source_x = kWalkFrame * Game::kTileSize;
			break;
		case STANDING:
			source_x = kStandFrame * Game::kTileSize;
			break;
		case JUMPING:
			source_x = kJumpFrame * Game::kTileSize;
			break;
		case FALLING:
			source_x = kFallFrame * Game::kTileSize;
			break;
		case LAST_MOTION_TYPE:
			break;
	}
	source_x = sprite_state.vertical_facing == UP ?
		source_x + kUpFrameOffset * Game::kTileSize :
		source_x;

	if(sprite_state.motion_type == WALKING){
		//create animated sprite
		sprites_[sprite_state] =
			boost::shared_ptr<Sprite>(new AnimatedSprite(
				graphics,
				kSpriteFilePath,
				source_x, source_y,
				Game::kTileSize, Game::kTileSize,
				m_renderer, kWalkFps, kNumFrames));
	}
	else{
		if(sprite_state.vertical_facing == DOWN){
			source_x = sprite_state.motion_type == STANDING ?
				kBackFrame * Game::kTileSize :
				kDownFrame * Game::kTileSize;
		}
		//create static
		sprites_[sprite_state] =
			boost::shared_ptr<Sprite>(new Sprite(
				graphics,
				kSpriteFilePath,
				source_x, source_y,
				Game::kTileSize, Game::kTileSize,
				m_renderer));
	}
	// characterFrame*kTileSize if we are going left
	// otherwise (characterFrame+1)*kTileSize
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
}

Rectangle Player::leftCollision(int delta) const{
	assert(delta <= 0);
	return Rectangle(
		x_ + kCollisionX.left() + delta,
		y_ + kCollisionX.top(),
		kCollisionX.width() / 2 - delta,
		kCollisionX.height()
	);
}

Rectangle Player::rightCollision(int delta) const{
	assert(delta >= 0);
	return Rectangle(
		x_ + kCollisionX.left() + kCollisionX.width() / 2,
		y_ + kCollisionX.top(),
		kCollisionX.width() / 2 + delta,
		kCollisionX.height()
	);
}

Rectangle Player::topCollision(int delta) const{
	assert(delta <= 0);
	return Rectangle(
		x_ + kCollisionY.left(),
		y_ + kCollisionY.top() + delta,
		kCollisionY.width(),
		kCollisionY.height() / 2 - delta
	);
}

Rectangle Player::bottomCollision(int delta) const{
	assert(delta >= 0);
	return Rectangle(
		x_ + kCollisionY.left(),
		y_ + kCollisionY.top() + kCollisionY.height() / 2,
		kCollisionY.width(),
		kCollisionY.height() / 2 + delta
	);
}