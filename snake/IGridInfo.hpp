#ifndef I_GRID_INFO_H
#define I_GRID_INFO_H

#include "libraries.hpp"

namespace kp
{
	using tilePositions_t = std::vector<std::vector<sf::Vector2f*>>;

	class IGridInfo
	{
	protected:
		sf::Vector2u m_gridSize;
		kp::tilePositions_t m_tilePositions;
	public:
		virtual void setGridSize(sf::Vector2u gridSize) = 0;
		virtual void setTilePositions(kp::tilePositions_t tilePositions) = 0;

		virtual sf::Vector2u getGridSize() const = 0;
		virtual kp::tilePositions_t getTilePositions() const = 0;
	};
}

#endif // !I_GRID_INFO_H