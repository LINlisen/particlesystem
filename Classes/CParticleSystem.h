#ifndef __CPARTICLE_SYSTEM_H__
#define __CPARTICLE_SYSTEM_H__

#include "cocos2d.h"
#include "CParticle.h"
#include "ui/CocosGUI.h" // For Cocos Studio �������
#include "cocostudio/CocoStudio.h"
#include <list>

using namespace std;


class CParticleSystem
{
private:
	CParticle* _pParticles;
	list<CParticle*> _FreeList;
	list<CParticle*> _InUsedList;
	int _iFree;	// �i�Ϊ�  Particle �Ӽ�
	int _iInUsed;  // ���b�ϥΪ� Particle �Ӽ�
	int _iType;  // �ثe������l�B�ʼҦ��O���@�ث��A
	int _iEmitterType;

	int _iStyle;
	bool _bEmitterOn; // Emitter �O�_���
	bool _bWindOn;
	bool _bChange;
	bool _bFirework;

public:
	// Emitter �]�w�������Ѽ�
	cocos2d::Point _emitterPt;// Emitter ����m	
	cocos2d::Point _windPt;
	Point _pwindDir;
	float    _fDir; // Emitter ���Q�g��V�A0 �� 360�סA�f�ɰw��V����
	int		_iNumParticles;	// �C�������ͪ����l�Ӽ�
	int     _iGenParticles; // ��ثe����Ҳ��ͪ����l�Ӽ�(�H�C�����)
	float	_fSpread;	 // 0 �� 180 �סA�w�]�� 180 
	float   _fVelocity;	 // ���l�����}�t��
	float   _fLifeTime;	 // ���l���s���ɶ�
	float	_fSpin;		// ���l������q degree/sec
	float   _fGravity;
	float   _fOpacity;
	int		_fParticle;
	float	_fRed;
	float	_fGreen;
	float	_fBlue;
	float   _fElpasedTime;	// �g�L�h�֮ɶ��A�H�����A�@�����ͤ��l���p��̾�
	int count;
	bool _bStore;
	//����
	int _iTimes;
	int _iNowtimes;
	std::string _sStyle;
	cocos2d::Point _windDir;  // ������V�A���d�ҨS����@
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