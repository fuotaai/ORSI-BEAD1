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
    return false;
}

Tile Map::tile_at(const int i,const int j) const
{
    return std::make_pair(Coordinate(-1,-1), FIELD::SEA);
}

void Map::set_tile(const int i, const int j, const FIELD f)
{
    
}

Tile Map::tile_in_direction(int x, int y, const DIRECTION d) const
{
    return tile_at(0,0);
}

std::set<Tile> Map::get_tiles_in_radius(const int i, const int j, const int r) const
{
    std::set<Tile> s;
    return s;
}

