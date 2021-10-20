#include "SnakeAI.hpp"

kp::SnakeAI::SnakeAI()
{
}

void kp::SnakeAI::setSnakeObject(kp::Snake* object)
{
	m_object = object;
}

void kp::SnakeAI::setActive(bool active)
{
	m_active = active;
}

kp::Snake* kp::SnakeAI::getSnakeObject() const
{
	return m_object;
}

bool kp::SnakeAI::isActive() const
{
	return m_active;
}

void kp::SnakeAI::update(float dT)
{
	m_dT = dT;

	if (m_active)
	{
	}
}

void kp::SnakeAI::render()
{
}

kp::SnakeAI::~SnakeAI()
{
}