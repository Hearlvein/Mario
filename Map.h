#pragma once

#include <vector>
#include "TileType.h"


class Map
{
public:
	Map();
	~Map();

	void load(const std::string& level_file);
	const TileType& at(unsigned int x, unsigned int y);

	void draw(const sf::RenderTarget& target, sf::RenderStates& states);

private:
	unsigned int m_width;
	unsigned int m_height;
	std::vector<std::vector<TileType>> m_grid;
	sf::VertexArray m_vertices;
};
