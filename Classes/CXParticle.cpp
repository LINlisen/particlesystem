//#include <cmath>
//#include "CXParticle.h"
//
//CXParticle::CXParticle()
//{
//	_Particle = nullptr;
//	_fGravity = 0;
//	_fVelocity=0;
//	_fLifeTime=0;	
//	_fIntensity=1;
//	_fOpacity=255;	
//	_fSize=1;		
//	_color = cocos2d::Color3B::WHITE;
//}
//void CXParticle::setParticle(const std::string& pngName, cocos2d::Scene& stage) 
//{
//	_Particle = Sprite::createWithSpriteFrameName(pngName);
//	_Particle->setPosition(Point(0,0));
//	_Particle->setOpacity(_fOpacity);
//	_Particle->setColor(Color3B::WHITE);
//	_Particle->setVisible(false);
//	BlendFunc blendfunc = { GL_SRC_ALPHA, GL_ONE };
//	_Particle->setBlendFunc(blendfunc);
//	stage.addChild(_Particle, 1);
//
//	_bVisible = false;
//	_iType = 0;
//	_color = cocos2d::Color3B::WHITE;
//};
//
//bool CXParticle::update(float dt)
//{
//	switch (_iType)
//	{
//		case STAY_FOR_TWOSECONDS:
//			if(_fTime==0)
//			{
//				_bVisible = true;
//				_Particle->setVisible(_bVisible);
//				_Particle->setColor(_color);
//				_Particle->setPosition(_Pos);
//				_fTime += dt;
//			}
//			if (_fTime <= _fLifeTime)
//			{
//
//				_fTime += dt;
//			}
//			else
//			{
//				return true;
//			}
//		break;
//
//	default:
//		break;
//	}
//};
//
//void CXParticle::setBehavior(int iType)
//{
//	float t;
//	switch (iType)
//	{
//	case STAY_FOR_TWOSECONDS:
//		_fVelocity = 0.25f;
//		t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
//		_Direction.x = cosf(t);
//		_Direction.y = sinf(t);
//		_fLifeTime = 2.0f;
//		_fIntensity = 1;
//		_fOpacity = 255;
//		_fSize = 1;
//		_color = Color3B(64 + rand() % 128, 64 + rand() % 128, 64 + rand() % 128);
//		_fTime = 0;
//		_fGravity = 0;
//		_Particle->setOpacity(255);
//		_Particle->setScale(_fSize);
//		_iType = STAY_FOR_TWOSECONDS;
//		break;
//
//	default:
//		break;
//	}
//};