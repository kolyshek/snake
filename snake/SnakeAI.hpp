#ifndef SNAKE_AI_H
#define SNAKE_AI_H

#include "libraries.hpp"

#include "IBase.hpp"

namespace kp
{
	class Snake;

	class SnakeAI
		: public IBase
	{
	private:
	protected:
		kp::Snake* m_object;

		float m_dT;

		bool m_active;
	public:
		SnakeAI();

		void setSnakeObject(kp::Snake* object);
		void setActive(bool active);

		kp::Snake* getSnakeObject() const;
		bool isActive() const;

		virtual void update(float dT);
		virtual void render();

		~SnakeAI();
	};
}

#endif // !SNAKE_AI_H