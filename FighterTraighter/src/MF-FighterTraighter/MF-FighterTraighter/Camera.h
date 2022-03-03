#pragma once
#include "Vector2D.h"
#include "Component.h"
#include "PhysicsTransform.h"
#include "UITimer.h"
#include "Shake.h"

class Camera:public Component
{
public:

	Camera(Transform*Target ) : Component(ecs::Camera),m_Target1(Target)
	{};
	Camera(Transform*Target, Transform* Target2) : Component(ecs::Camera),m_Target1(Target),m_Target2(Target2)
	{};
	void init()override
	{
		cam = entity_->getComponent<Transform>(ecs::Transform);
		m_shake = entity_->getComponent<Shake>(ecs::Shake)->shake();

		//1920+860*2+500
		cam->setWidthHeight(cam->getWidth() + m_Target1->getPosition().getX()*2 + m_Target2->getWidth(), cam->getHeight() + m_Target1->getPosition().getY());
		//m_ViewBox.w = app_->getWindowManager()->getCurResolution().w;
		//m_ViewBox.h= app_->getWindowManager()->getCurResolution().h +500;
		
	}
	~Camera() {
		delete m_shake;
	};
	virtual void update()override;
private:
	inline void CalculaPunto();
	Vector2D* m_shake=nullptr;
		SDL_Rect m_ViewBox;
		Transform* cam=nullptr;
		Transform* m_Target1=nullptr;
		Transform* m_Target2=nullptr;
};

