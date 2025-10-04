#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <boost/shared_ptr.hpp>

#include "sprite.h"
#include "rectangle.h"
#include "graphics.h"
#include "game.h"


struct Map{
	enum TileType{
		AIR_TILE,
		WALL_TILE
	}; //good

	struct CollisionTile{
		CollisionTile(int row, int col, TileType tileType) :
			row(row),
			col(col),
			tileType(tileType){}
		int row, col;
		TileType tileType;
	};
	static Map* createTestMap(Graphics& graphics);

	std::vector<CollisionTile> getCollidingTiles(Rectangle& rectangle) ;

	void update(int elapsed_time_ms);
	void draw(Graphics& graphics) const;

	private:

	struct Tile{
		Tile(TileType tile_type = AIR_TILE,
			boost::shared_ptr<Sprite> sprite = boost::shared_ptr<Sprite>()) :
			tile_type(tile_type),
			sprite(sprite){}

		TileType tile_type;
		boost::shared_ptr<Sprite> sprite;
	};

	std::vector<std::vector<Tile>> tiles_;

};

#endif