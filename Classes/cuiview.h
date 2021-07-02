#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h" // For Cocos Studio 控制項元件
#include "cocostudio/CocoStudio.h"
#include "Common/CSwitchButton.h"
#include "Common/CDraggableSprite.h"
#include "CParticleSystem.h"
#include "Common/CButton.h"
class CUIView
{
private:
	// 建立控制 particle system 所需的操作介面
	cocos2d::Node* _uiRoot;
	cocos2d::Scene* _stage;
	cocos2d::Size _size; //開啟的視窗大小

	// 分子的可提整不同參數的顯示
	cocos2d::ui::TextBMFont* _GravityBMValue;
	cocos2d::ui::TextBMFont* _SpreadBMValue;
	cocos2d::ui::TextBMFont* _DirectionBMValue;
	cocos2d::ui::TextBMFont* _SpeedBMValue;
	cocos2d::ui::TextBMFont* _SpinBMValue;
	cocos2d::ui::TextBMFont* _OpacityBMValue;
	cocos2d::ui::TextBMFont* _ParticleBMValue;
	cocos2d::ui::TextBMFont* _LifetimeBMValue;
	cocos2d::ui::TextBMFont* _RedBMValue;
	cocos2d::ui::TextBMFont* _GreenBMValue;
	cocos2d::ui::TextBMFont* _BlueBMValue;
	// 選擇不同的分子型態，用在 Emitter 沒有開啟的狀態
	cocos2d::ui::TextBMFont* _TypeBMValue;
	cocos2d::ui::TextBMFont* _EmitterTypeBMValue;
	// For Emitter
	CDraggableSprite* _EmitterSprite;
	CSwitchButton* _emitterSwitchBtn;
	bool _bEmitterOn;
	//For Wind
	CDraggableSprite* _WindSprite;
	CSwitchButton* _windSwitchBtn;
	bool _bWindOn;
	// 指向 Particle System 的指標物件
	CParticleSystem* _ParticleControl;
	//Style Button
	CButton* _Bubble,*_Circle,*_Cloud,*_Comet,*_Flare,*_Spark,*_Raindrop;
	//Play Button
	CButton* _Play1, * _Play2, * _Play3,* _Play4;
	//For Firework
	bool _bfirework;
public:
	CUIView();

	void setProperty(std::string uicsbname, cocos2d::Size vsize, cocos2d::Scene& stage);
	void setModel(CParticleSystem &model);
	void init();
	void update();
	// 定義 Callback function
	void GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void EmitterTypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void ParticleEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void LifetimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void RedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void GreenEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void BlueEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	// touch 事件
	void onTouchBegan(const cocos2d::Point& tPoint, cocos2d::Scene& stage);
	void onTouchMoved(const cocos2d::Point& tPoint, cocos2d::Scene& stage); //觸碰移動事件
	void onTouchEnded(const cocos2d::Point& tPoint, cocos2d::Scene& stage); //觸碰結束事件 

};