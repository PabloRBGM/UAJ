#include "Camera.h"

inline void Camera::CalculaPunto()
{
	if (m_Target2!=nullptr)
	{
		m_ViewBox.y =-(m_Target1->getPosition().getY() + m_Target2->getPosition().getY())/2   + m_shake->getY()+ m_Target2->getHeight()/2;
		m_ViewBox.x = -(m_Target1->getPosition().getX() + m_Target2->getPosition().getX())/2  + m_shake->getX();
	}
	else if(m_Target1!= nullptr)
	{
		m_ViewBox.x = -m_Target1->getPosition().getX();
	     m_ViewBox.y = - m_Target1->getPosition().getY();

	}
}
void Camera::update()
{
	CalculaPunto();
	cam->setPosition(Vector2D(m_ViewBox.x, m_ViewBox.y));
}

