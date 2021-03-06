#include "pch.h"
#include "types.hpp"
#include <iostream>


FIELD field_from_int(const int i)
{
	return static_cast<FIELD>(i);
}

int field_value(const FIELD& f)
{
	switch(f) 
	{
		case FIELD::CANNIBALS:
		  return -2;
		  break;
		case FIELD::DESERT:
		  return 0;
		  break;
		case FIELD::FOREST:
		  return 3;
		  break;
		case FIELD::GOLD_MINE:
		  return 5;
		  break;
		case FIELD::GRASSLAND:
		  return 2;
		  break;
		case FIELD::IRON:
		  return 2;
		  break;
		case FIELD::LAKE:
		  return 3;
		  break;
		case FIELD::SEA:
		  return 1;
		  break;
		case FIELD::SWAMP:
		  return 1;
		  break;
		case FIELD::VILLAGE:
		  return 6;
		  break;
		case FIELD::WHEAT:
		  return 3;
		  break;
    }
}

int tile_value(const Tile& f)
{
	return field_value(std::get<1>(f));
}

bool operator<(const Coordinate& a, const Coordinate& b)
{
	if(a.x < b.x) {
		return true;
    } else if(a.x > b.x) {
		return false;
	} else if(a.y < b.y) {
		return true;
    } else {
		return false;
	}
}

/*
std::ostream& operator<<(std::ostream& s, const FIELD& f)
{
    return s;
}

std::ostream& operator<<(std::ostream& s, const DIRECTION& d)
{
    return s;
}

std::ostream& operator<<(std::ostream& s, const Coordinate& p)
{
    return s;
}
std::istream& operator>>(std::istream& s, Coordinate& p)
{
    return s;
}

std::ostream& operator<<(std::ostream& s, const Tile& t)
{
    return s;
}
*/
std::istream& operator>>(std::istream& s, Map& m)
{
	int row, col;
	s >> row;
	s >> col;
	Map map(row, col);
	m.map_ = map.map_;
	m.rows_ = row;
	m.cols_ = col;
	for(int i=0; i<row; i++) {
		for(int j=0; j<col; j++) {
			int val;
			s >> val;
			m.set_tile(i,j, field_from_int(val));
		}
    }
	
    return s;
}

Map::Map(): rows_(0), cols_(0)
{
}

Map::Map(const int r, const int c)
{
	if (r >= 0 && c >= 0) {
		rows_ = r;
		cols_ = c;
		for (int i = 0; i < r; i++) {
			std::vector<FIELD> row(c, FIELD::SEA);
			map_.push_back(row);
		}
	}
	Map();
}
    
int Map::rows() const
{
    return rows_;
}

int Map::cols() const
{
    return cols_;
}

bool Map::in_range(const int x, const int y) const
{
	return (x >= 0 && x < rows_ && y >= 0 && y < cols_) ? true : false;
}

Tile Map::tile_at(const int i,const int j) const
{
	return (in_range(i, j)) ? std::make_pair(Coordinate(i, j), map_.at(i).at(j)) : std::make_pair(Coordinate(i, j), FIELD::SEA);
}

void Map::set_tile(const int i, const int j, const FIELD f)
{
    if(in_range(i, j)) {
		map_.at(i).at(j) = f;
    }
}

bool isOdd(const int x) {
	return (x % 2 != 0);		
}

Tile Map::tile_in_direction(int x, int y, const DIRECTION d) const
{
	switch(d) {
		case DIRECTION::NORTH_WEST:
		  if(isOdd(y)) {
			return tile_at(x, y-1); 
		  } else {
			return tile_at(x-1, y-1); 
		  }
		  break;
		case DIRECTION::NORTH: 
		  return tile_at(x-1, y); 
		  break;
		case DIRECTION::NORTH_EAST: 
		  if(isOdd(y)) {
			return tile_at(x, y+1); 
		  } else {
			return tile_at(x-1, y+1); 
		  }
		  break;
		case DIRECTION::SOUTH_EAST: 
		  if(isOdd(y)) {
			return tile_at(x+1, y+1); 
		  } else {
			return tile_at(x, y+1); 
		  }
		  break;
		case DIRECTION::SOUTH:
		  return tile_at(x+1, y); 		
		  break;
		case DIRECTION::SOUTH_WEST: 
		  if(isOdd(y)) {
			return tile_at(x+1, y-1); 
		  } else {
			return tile_at(x, y-1); 
		  }
		  break;
	}
}

std::set<Tile> Map::get_tiles_in_radius(const int i, const int j, const int r) const
{
	int act_i, act_j;
    std::set<Tile> s;
	s.insert(tile_at(i, j));

	for (int q = 1; q <= r; q++) {
		act_i = i + q;
		act_j = j;
		s.insert(tile_at(act_i, act_j));

		// SOUTH_EAST
		for (int p = 0; p < i; p++) {
			Tile t = tile_in_direction(act_i, act_j, DIRECTION::SOUTH_EAST);
			s.insert(t);
			Coordinate c = std::get<0>(t);
			act_i = c.x;
			act_j = c.y;
		}

		// SOUTH
		for (int p = 0; p < i; p++) {
			Tile t = tile_in_direction(act_i, act_j, DIRECTION::SOUTH);
			s.insert(t);
			Coordinate c = std::get<0>(t);
			act_i = c.x;
			act_j = c.y;
		}

		// SOUTH_WEST
		for (int p = 0; p < i; p++) {
			Tile t = tile_in_direction(act_i, act_j, DIRECTION::SOUTH_WEST);
			s.insert(t);
			Coordinate c = std::get<0>(t);
			act_i = c.x;
			act_j = c.y;
		}

		// NORTH_WEST
		for (int p = 0; p < i; p++) {
			Tile t = tile_in_direction(act_i, act_j, DIRECTION::NORTH_WEST);
			s.insert(t);
			Coordinate c = std::get<0>(t);
			act_i = c.x;
			act_j = c.y;
		}

		// NORTH
		for (int p = 0; p < i; p++) {
			Tile t = tile_in_direction(act_i, act_j, DIRECTION::NORTH);
			s.insert(t);
			Coordinate c = std::get<0>(t);
			act_i = c.x;
			act_j = c.y;
		}

		// NORTH_EAST
		for (int p = 0; p < i; p++) {
			Tile t = tile_in_direction(act_i, act_j, DIRECTION::NORTH_EAST);
			s.insert(t);
			Coordinate c = std::get<0>(t);
			act_i = c.x;
			act_j = c.y;
		}
	}

    return s;
}