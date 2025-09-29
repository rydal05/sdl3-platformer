#ifndef PLAYER_H_
#define PLAYER_H_

#include <boost/shared_ptr.hpp>
#include <map>

#include "game.h"
#include "animatedSprite.h"
#include "graphics.h"
#include "map.h"
#include "rectangle.h"

struct Player{

	Player(int x, int y, SDL_Renderer* renderer, Graphics& graphics);
	
	void update(int elapsed_time_ms, const Map& map);
	void draw(Graphics& graphics);

	void startMovingLeft();
	void startMovingRight();
	void stopMoving();
	void startJump();
	void stopJump();

	void lookUp();
	void lookDown();
	void lookHorizontal();

	private:
	enum MotionType{
		FIRST_MOTION_TYPE,
		STANDING = FIRST_MOTION_TYPE,
		WALKING,
		JUMPING,
		FALLING,
		LAST_MOTION_TYPE
	};

	enum HorizontalFacing{
		FIRST_HORIZONTAL_FACING,
		LEFT = FIRST_HORIZONTAL_FACING,
		RIGHT,
		LAST_HORIZONTAL_FACING
	};

	enum VerticalFacing{
		FIRST_VERTICAL_FACING,
		UP = FIRST_VERTICAL_FACING,
		DOWN,
		HORIZONTAL,
		LAST_VERTICAL_FACING
	};

	friend inline MotionType& operator++(MotionType& v){
		v = static_cast<MotionType>(static_cast<int>(v) + 1);
		return v;
	}
	friend inline HorizontalFacing& operator++(HorizontalFacing& v){ //provides a way to do ++ operations on the 3 classes
		v = static_cast<HorizontalFacing>(static_cast<int>(v) + 1);
		return v;
	}
	friend inline VerticalFacing& operator++(VerticalFacing& v){
		v = static_cast<VerticalFacing>(static_cast<int>(v) + 1);
		return v;
	}

	struct SpriteState{
		SpriteState(MotionType motion_type = STANDING,
			HorizontalFacing horizontal_facing = LEFT,
			VerticalFacing vertical_facing = HORIZONTAL) :
			motion_type(motion_type),
			horizontal_facing(horizontal_facing),
			vertical_facing(vertical_facing){}

		MotionType motion_type;
		HorizontalFacing horizontal_facing;
		VerticalFacing vertical_facing;
	};

	friend bool operator<(const SpriteState& a, const SpriteState& b);

	struct Jump{
		Jump() : time_remaining_ms_(0), active_(false){}
		void reset();
		void reactivate(){ active_ = time_remaining_ms_ > 0; }
		void deactivate(){ active_ = false; }
		void update(int time_remaining_ms);
		bool active(){ return active_; }
		private:
		int time_remaining_ms_;
		bool active_;
	};

	void initializeSprites(Graphics& grapihcs);
	void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
	SpriteState getSpriteState();

	Rectangle leftCollision(int delta) const;
	Rectangle rightCollision(int delta) const;
	
	Rectangle bottomCollision(int delta) const;
	Rectangle topCollision(int delta) const;


	bool on_ground() const{ return on_ground_; }

	int x_, y_;
	float velocity_x_, velocity_y_;
	float acceleration_x_, acceleration_y_;
	HorizontalFacing horizontal_facing_;
	VerticalFacing vertical_facing_;
	bool on_ground_;
	Jump jump_;

	SDL_Renderer* m_renderer;

	std::map<SpriteState, boost::shared_ptr<Sprite> > sprites_;
};

#endif