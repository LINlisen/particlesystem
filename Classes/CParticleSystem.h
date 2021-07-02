#ifndef __CPARTICLE_SYSTEM_H__
#define __CPARTICLE_SYSTEM_H__

#include "cocos2d.h"
#include "CParticle.h"
#include "ui/CocosGUI.h" // For Cocos Studio 控制項元件
#include "cocostudio/CocoStudio.h"
#include <list>

using namespace std;


class CParticleSystem
{
private:
	CParticle* _pParticles;
	list<CParticle*> _FreeList;
	list<CParticle*> _InUsedList;
	int _iFree;	// 可用的  Particle 個數
	int _iInUsed;  // 正在使用的 Particle 個數
	int _iType;  // 目前控制的分子運動模式是哪一種型態
	int _iEmitterType;

	int _iStyle;
	bool _bEmitterOn; // Emitter 是否顯示
	bool _bWindOn;
	bool _bChange;
	bool _bFirework;

public:
	// Emitter 設定的相關參數
	cocos2d::Point _emitterPt;// Emitter 的位置	
	cocos2d::Point _windPt;
	Point _pwindDir;
	float    _fDir; // Emitter 的噴射方向，0 到 360度，逆時針方向為正
	int		_iNumParticles;	// 每秒鐘產生的分子個數
	int     _iGenParticles; // 到目前為止所產生的分子個數(以每秒為單位)
	float	_fSpread;	 // 0 到 180 度，預設為 180 
	float   _fVelocity;	 // 分子的離開速度
	float   _fLifeTime;	 // 分子的存活時間
	float	_fSpin;		// 分子的旋轉量 degree/sec
	float   _fGravity;
	float   _fOpacity;
	int		_fParticle;
	float	_fRed;
	float	_fGreen;
	float	_fBlue;
	float   _fElpasedTime;	// 經過多少時間，以秒為單位，作為成生分子的計算依據
	int count;
	bool _bStore;
	//次數
	int _iTimes;
	int _iNowtimes;
	std::string _sStyle;
	cocos2d::Point _windDir;  // 風的方向，本範例沒有實作
	//firework
	float _fFireworkTime;
	Point _fFirePos;
	int _iFireworkPart;
	//bool 
	bool _bturnon;

	CParticleSystem();
	~CParticleSystem();
	void init(cocos2d::Scene &stage,std::string Style);
	void update(float dt,cocos2d::Scene& stage);
	void setEmitter(bool bEm);
	void setWind(bool bWd);
	void setType(int type) { _iType = type; }
	void setEmitterType(int emtype);
 //   void onTouchesEnded(const cocos2d::CCPoint &touchPoint);
    void onTouchesBegan(const cocos2d::Point &touchPoint, cocos2d::Scene& stage);
    void onTouchesMoved(const cocos2d::Point &touchPoint, cocos2d::Scene& stage);

	void setGravity(float fGravity);
	void setSpeed(float fSpeed) { _fVelocity = fSpeed; }
	void setSpin(float fSpin) { _fSpin = fSpin; }
	void setOpacity(float fOpacity) { _fOpacity = fOpacity;}
	void setParticleNum(int fParticle);
	void setLifetime(float fLifetime) { _fLifeTime = fLifetime; }
	void setRed(float fRed);
	void setGreen(float fGreen);
	void setBlue(float fBlue);
	void setStyle(const char* pngName,cocos2d::Scene& stage);
	void setChange();
	void setFirework(bool bFirework);
	bool getFirework();
	void setFireworkPart();
};

#endif