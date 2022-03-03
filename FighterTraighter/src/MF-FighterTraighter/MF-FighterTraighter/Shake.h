#pragma once
#include "Vector2D.h"
#include "Component.h"
#include "PhysicsTransform.h"
class Shake :public Component
{
   
public:

    Shake(uint32 shakeTime,float shakeOffset) : Component(ecs::Shake) ,SHAKE_TIME_MS(shakeTime),SHAKE_OFFSET(shakeOffset){};
    Shake(uint32 shakeTime) : Component(ecs::Shake) ,SHAKE_TIME_MS(shakeTime),SHAKE_OFFSET(20.0){};
    Shake() : Component(ecs::Shake) ,SHAKE_TIME_MS(2000),SHAKE_OFFSET(20.0){};
	~Shake() {  }

    //Shaking will take 200ms
    uint32 SHAKE_TIME_MS ;

    //The screen will be moved 20 pixels forth and back
    float SHAKE_OFFSET ;

    //Indicates the shake move direction
    bool shakeDirection = false;

    //Indicates if the screen is currently shaking
    bool  shaking=false;
    bool getShake()
    {
        return shaking;
    }
    void playShake()
    {
        shaking = true;
        timeStart_ = SDL_GetTicks();

    }

    //delta is the ms passed since last update
    virtual void update()override;
    void init()override
    {
        //cam = entity_->getComponent<Transform>(ecs::Transform);
        xOffset = 0;
        yOffset = 0;
        m_shake = new Vector2D();
        m_shake->setX(0);
        m_shake->setY(0);
    }
    Vector2D* shake() { return m_shake; }
private:
    void updateShake();
    void applyScreenShake();

    Vector2D* m_shake=nullptr;
  //  Transform* cam;
    Uint32 timeStart_=0;
    Uint32 delta=0;
    float xOffset = 0;
    float yOffset = 0;


};