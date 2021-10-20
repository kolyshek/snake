#ifndef I_TILE_INFO_H
#define I_TILE_INFO_H

#include "libraries.hpp"

namespace kp
{
	class ITileInfo
	{
	protected:
		sf::Vector2u m_tileIndex;
		sf::Vector2f m_tileSize;
	public:
		virtual void chooseRandomIndex() = 0;
		
		virtual void setTileSize(sf::Vector2f tileSize) = 0;
		virtual void setTileIndex(sf::Vector2u tileIndex) = 0;

		virtual sf::Vector2f getTileSize() const = 0;
		virtual sf::Vector2u getTileIndex() const = 0;
	};
}

#endif // !I_TILE_INFO_H