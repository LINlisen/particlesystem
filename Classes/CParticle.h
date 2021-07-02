#ifndef __CPARTICLE_H__
#define __CPARTICLE_H__

#define STAY_FOR_TWOSECONDS 0	// �b����ƹL���a�貣�� particle
#define RANDOMS_FALLING     1	// �b����ƹL���a�詹�U���� particle
#define FREE_FLY 2				// �b����ƹL���a����N�V�|�貣�� particle
#define EXPLOSION 3				// �Q�g�X��Ϊ��Ϥ�
#define HEARTSHAPE 4			// �Q�g�X�߫����Ϥ�
#define BUTTERFLYSHAPE	5		// �Q�g�X�����~�����Ϥ�
#define FLOWSTART 6
#define ALLSTART 7
#define SHAPE 8

#define EMITTER_DEFAULT 99
#define EMITTER_ONE 98
#define EMITTER_TWO 97
#define EMITTER_THREE 96
#define EMITTER_FOUR 95
#define FIREWORK 94
#include "cocos2d.h"


USING_NS_CC;

class CParticle
{
private:
	cocos2d::Sprite *_Particle;	// ���l����
	cocos2d::Point  _OldPos;		// ���l�e�@�Ӧ�m
	cocos2d::Point  _Pos;			// ���l�ثe����m
	cocos2d::Point  _Direction;	// ���l�ثe���B�ʤ�V�A���V�q
	cocos2d::Scene* _stage;
	cocos2d::Point _pwindPos;
	cocos2d::Point _pwindDir;
	float _fVelocity;	// ���l���t��
	float _fLifeTime;	// �ͩR�g��
	float _fIntensity;// ���l��q���̤j�ȡA�q�`�Ω���ܤ��l���C��
	float _fOpacity;	// �ثe���l���z����
	float _fSpin;		// ���l������q
	float _fSize;		// ���l���j�p
	float _fGravity;	// ���l�����쪺���O�j�p
	float _fSpeed;
	std::string _sStyle;
	cocos2d::Color3B _color;	// ���l���C��
	// �ɶ�
	float _fElapsedTime; // ���l�q��ܨ�ثe����ɶ�
	float _fDelayTime;	 // ���l��ܫe������ɶ�

	// �欰�Ҧ�
	int _iType;
	// ��ܻP�_
	bool _bVisible;
	//wind
	bool _bwind;
	
	
public:
	CParticle();

	void setParticle(const std::string &pngName, cocos2d::Scene &stage);
	bool update(float dt);
	void setPosition(const cocos2d::Point &inPos);
	void setColor(const cocos2d::Color3B& color);
	void setBehavior(int iType); // �]�w���l���ͪ��_�l�欰�Ҧ�
	void setVisible();
	void setGravity(const float fGravity);
	void setSpeed(const float fSpeed);
	void setSpin(const float fSpin);
	void setOpacity(const float fOpacity) { _fOpacity = fOpacity;}
	void setVelocity(const float v) { _fVelocity = v; }
	void setLifetime(const float lt);
	void setDirection(const cocos2d::Point pt) { _Direction = pt; }
	void setSize(float s) { _fSize = s; _Particle->setScale(_fSize); }
	void setStyle(std::string Style);
	void setStage(cocos2d::Scene& stage);
	void changeParticle(const char* pngName, cocos2d::Scene& stage);
	void setwindPos(cocos2d::Point pw);
	void setwindDir(cocos2d::Point w);
	void setbwind(bool bw);
};

#endif