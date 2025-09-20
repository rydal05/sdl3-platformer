#include "map.h"

#include "sprite.h"
#include "graphics.h"
#include "game.h"

using boost::shared_ptr;
using std::vector;

Map* Map::createTestMap(Graphics& graphics){
	Map* map = new Map();

	const int num_rows = 15;
	const int num_cols = 20;
	//ensure foreground sprites is num rows x unm cols in size
	map->tiles_ = vector<vector<Tile>>(num_rows, vector<Tile>(num_cols, Tile()));

	shared_ptr<Sprite> sprite(new Sprite(
		graphics, "sprites/PrtCave.png",
		16, 0, 16,
		16, graphics.getRenderer()));

	Tile tile(WALL_TILE, sprite);

	const int row = 11;
	for(int col = 0; col < num_cols; ++col){
		map->tiles_[row][col] = tile;
	}

	return map;
}

void Map::update(int elapsed_time_ms){
	for(size_t row = 0; row < tiles_.size(); ++row){
		for(size_t col = 0; col < tiles_[row].size(); ++col){
			if(tiles_[row][col].sprite){
				tiles_[row][col].sprite->update(elapsed_time_ms);
			}
		}
	}
}

void Map::draw(Graphics& graphics) const{
	for(size_t row = 0; row < tiles_.size(); ++row){
		for(size_t col = 0; col < tiles_[row].size(); ++col){
			if(tiles_[row][col].sprite){
				tiles_[row][col].sprite->scaled_draw(graphics, col * Game::kTileSize, row * Game::kTileSize, 2);
			}
		}
	}
}