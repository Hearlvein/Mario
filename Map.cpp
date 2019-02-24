#include "Map.h"
#include <iostream>


Map::Map()
{

}

Map::~Map()
{

}

void Map::load(const std::string& level_file)
{
	m_width = 20;
	m_height = 10;
	m_tileSize = 50;
	m_grid.resize(m_width);
	for (std::size_t i = 0; i < m_width; ++i)
	{
		m_grid[i].resize(m_height);

		for (std::size_t j = 0; j < m_height; ++j)
            m_grid[i][j] = Void;
	}

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(m_width * m_height * 4);
	for (std::size_t i = 0; i < m_width; ++i)
	{
		for (std::size_t j = 0; j < m_height; ++j)
		{
			sf::Vertex* quad = &m_vertices[(i + j * m_width) * 4];
			quad[0].position = m_tileSize * sf::Vector2f(i, j);
			quad[1].position = m_tileSize * sf::Vector2f(i+1, j);
			quad[2].position = m_tileSize * sf::Vector2f(i+1, j+1);
			quad[3].position = m_tileSize * sf::Vector2f(i, j+1);

			quad[0].texCoords = m_tileSize * sf::Vector2f((int)m_grid[i][j], 1);
			quad[1].texCoords = m_tileSize * sf::Vector2f((int)m_grid[i][j]+1, 1);
			quad[2].texCoords = m_tileSize * sf::Vector2f((int)m_grid[i][j]+1, 2);
			quad[3].texCoords = m_tileSize * sf::Vector2f((int)m_grid[i][j], 2);
		}
	}
}

const TileType& Map::at(unsigned int x, unsigned int y) const
{
	std::cout << "map::at read-only" << std::endl;
	return m_grid[x][y];
}

void Map::set(unsigned int x, unsigned int y, TileType type)
{
	m_grid[x][y] = type;

	// Actualize tile texture coords
	sf::Vertex* quad = &m_vertices[(x + y * m_width) * 4];
	quad[0].texCoords = m_tileSize * sf::Vector2f((int)type, 1);
	quad[1].texCoords = m_tileSize * sf::Vector2f((int)type+1, 1);
	quad[2].texCoords = m_tileSize * sf::Vector2f((int)type+1, 2);
	quad[3].texCoords = m_tileSize * sf::Vector2f((int)type, 2);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	target.draw(m_vertices, states);
}
