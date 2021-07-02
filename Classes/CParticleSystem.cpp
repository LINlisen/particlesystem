#include "CParticleSystem.h"

#define NUMBER_PARTICLES 1000 // �w�]�@�����o 1000 �� Particles

USING_NS_CC;

CParticleSystem::CParticleSystem()
{
	_fGravity = 0;
	_bEmitterOn = false;
	_bChange = false;
	_bFirework = false;
	_fOpacity=255.0f;
	_fRed=255.0f;
	_fGreen=255.0f;
	_fBlue=255.0f;
	_bStore = false;
	_sStyle = "flare.png";
	_iEmitterType = 99;
	_bturnon = false;
}

void CParticleSystem::setEmitter(bool bEm)
{
	_bEmitterOn = bEm;
}
void CParticleSystem::setWind(bool bWd)
{
	_bWindOn = bWd;
}
void CParticleSystem::init(cocos2d::Scene &stage, std::string Style)
{
	_iFree = NUMBER_PARTICLES;
	_iInUsed = 0;
	_pParticles = new CParticle[NUMBER_PARTICLES]; // ���o�һݭn�� particle �Ŷ�
	 // Ū�J�x�s�h�i�Ϥ��� plist ��
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("click.plist");
	for (int i = 0; i < NUMBER_PARTICLES; i++) {
		_pParticles[i].setParticle(Style, stage);
		_FreeList.push_front(&_pParticles[i]);
	}
	
}

void CParticleSystem::update(float dt, cocos2d::Scene& stage)
{
	CParticle* get;
	list <CParticle*>::iterator it;
	if (_bWindOn) {
		_pwindDir = Point(sinf(10*dt), sinf(10*dt));
		Point d = _emitterPt - _windPt;
		Point s = Point(100,100);
		//_pwindDir = Point((_pwindDir.x) * (1000 +d.x) / 100, (_pwindDir.y) * (1000 - d.y) / 100);
		if (d.x > 0&&d.y>0) {
			_pwindDir = Point((_pwindDir.x) * (1000 - d.x) / 100, (_pwindDir.y) * (1000 - d.y) / 100);
		}
		else if (d.x < 0 && d.y > 0) {
			_pwindDir = Point((_pwindDir.x) * (-d.x-1000) / 100, (_pwindDir.y) * (1000 - d.y) / 100);
		}
		else if (d.x > 0 && d.y < 0) {
			_pwindDir = Point((_pwindDir.x) * (1000 - d.x) / 100, (_pwindDir.y) * (-d.y-1000) / 100);
		}
		else if(d.  x<0&&d.y<0){
			_pwindDir = Point((_pwindDir.x) * (-d.x - 1000) / 100, (_pwindDir.y) * (-d.y - 1000) / 100);
		}
		
		/*log("pwindDir.x:%f,_pwindDir.y:%f", _pwindDir.x, _pwindDir.y);*/
		_pParticles->setwindPos(_windPt);
		_pParticles->setbwind(_bWindOn);
		/*if (!_bturnon) {
			
			_bturnon = true;
		}*/
	}
	else {
		_pwindDir = Point(0,0);
		_pParticles->setwindPos(Point(0,0));
		//if (_bturnon) {
		_pParticles->setbwind(_bWindOn);
		//	_bturnon = false;
		//}
	}
	if (_bEmitterOn) { // �ھ� Emitter �]�w�������ѼơA���ͬ۹��������l
		// ���p��b�֥[
		int n = (int)(_fElpasedTime * _iNumParticles); // ��ثe�������Ӳ��ͪ����l�Ӽ�
		if (n > _iGenParticles) {  // ���ͪ����l�ӼƤ����A���ͨ� n �Ӥ��l
			for (int i = 0; i < n - _iGenParticles; i++) {
				// �ھ� Emitter �������ѼơA�]�w�Ҳ��ͤ��l���Ѽ�
				if (_iFree != 0) {
					get = _FreeList.front();
					if (_iEmitterType == 99) {
						log("99");
						get->setBehavior(EMITTER_DEFAULT);
						float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
						t = _fSpread - t * _fSpread * 2; //  ���ͪ����סA�ন����
						t = (_fDir + t) * M_PI / 180.0f;
						Vec2 vdir(cosf(t), sinf(t));
						get->setDirection(vdir+_pwindDir);
						get->setPosition(_emitterPt);

					}
					else if (_iEmitterType == 98) {
						log("98");
						get->setBehavior(EMITTER_ONE);
						float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
						float a = (rand() % 10);
						t = _fSpread - t * _fSpread * 2; //  ���ͪ����סA�ন����
						t = (_fDir + t) * M_PI / 180.0f;
						//Vec2 vdir(cosf(a*t) *cosf(a*t)*i*sinf(4/5), sinf(a*t)* sinf(t*a)*i)

						Vec2 vdir(0, 0);
						get->setPosition(_emitterPt);
					}
					else if (_iEmitterType == 97) {
						log("97");
						get->setBehavior(EMITTER_TWO);
						float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
						t = _fSpread - t * _fSpread * 2; //  ���ͪ����סA�ন����
						t = (_fDir + t) * M_PI / 180.0f;
						Vec2 vdir(0, 2);
						get->setDirection(vdir);
						get->setPosition(_emitterPt);
					}
					else if (_iEmitterType == 96) {
						log("96");

						Vec2 vdir(-5, 0);
						get->setDirection(vdir);
						get->setBehavior(EMITTER_THREE);
						get->setPosition(_emitterPt);
					}
					else {
						Vec2 vdir(0, 10);
						get->setDirection(vdir);
						get->setBehavior(EMITTER_FOUR);
						int x = rand() % (50 + 50 + 1) - 50;
						get->setPosition(Vec2(_emitterPt.x * dt * x, _emitterPt.y * dt * 2));
						log("95");
					}
					get->setVelocity(_fVelocity);
					get->setLifetime(_fLifeTime * 1.5);
					get->setGravity(_fGravity);
					get->setSpin(_fSpin);
					/*log("CParticleSystem:%f", _fSpin);*/
					get->setOpacity(_fOpacity);
					log("CParticleSystemOpacity:%f", _fOpacity); 
					get->setLifetime(_fLifeTime);
					get->setColor(Color3B(_fRed, _fGreen, _fBlue));
					get->setSize(0.125f);
					// �ھ� _fSpread �P _vDir ���ͤ�V
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--; _iInUsed++;
				}
			}
			_iGenParticles = n; // �ثe�w�g���� n �Ӥ��l

		}
		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= _iNumParticles) _iGenParticles -= _iNumParticles;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;
	}
	if (_bFirework) {
		
		_fFireworkTime += dt;
		_fFirePos = Point(0, 0);
		int n = (int)(_fElpasedTime * _iNumParticles); // ��ثe�������Ӳ��ͪ����l�Ӽ�
;
		if (n > _iGenParticles) {  // ���ͪ����l�ӼƤ����A���ͨ� n �Ӥ��l

			for (int i = 0; i < n - _iGenParticles; i++) {
				// �ھ� Emitter �������ѼơA�]�w�Ҳ��ͤ��l���Ѽ�
				if (_iFree != 0) {

					if(_iFireworkPart==1){
						get = _FreeList.front();
						Point pos = Point(float(800), float(_fFireworkTime*100+200));
						get->setBehavior(FIREWORK);
						get->setPosition(pos);
						float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
						t = _fSpread - t * _fSpread * 2; //  ���ͪ����סA�ন����
						t = (_fDir + t) * M_PI / 180.0f;
						Vec2 vdir(0, 10);
						get->setDirection(vdir);
						get->setVelocity(_fVelocity);
						get->setLifetime(0.5);
						get->setSpin(_fSpin);
						get->setOpacity(_fOpacity);
				
						get->setColor(Color3B(_fRed, _fGreen, _fBlue));
						get->setSize(0.125f);
						if (_fFireworkTime > 1.5) {
							_iFireworkPart = 2;
							_fFirePos = Vec2(pos.x,pos.y+10* _fFireworkTime);
						}
						_FreeList.pop_front();
						_InUsedList.push_front(get);
						_iFree--; _iInUsed++;
					}
					if (_iFireworkPart == 2&& _fFireworkTime>2) {
						
							if (_iFree > 100) {
								
									for (int i = 0; i < 100; i++) {
										get = _FreeList.front();
										get->setBehavior(EXPLOSION);
										get->setPosition(Vec2(800, 700));
										
										//get->setRot(i * 3.6f);
										get->setGravity(-10.0f);
										if (_fFireworkTime > 3) {
											_iFireworkPart = 3;
											_fFirePos = Vec2(800, 700);
										}
										_FreeList.pop_front();
										_InUsedList.push_front(get);
										_iFree--; _iInUsed++;

								}
							}
					}
					if (_iFireworkPart == 3 && _fFireworkTime > 5) {
						if (_iFree > 100) {
							for (int i = 0; i < 100; i++) {
								get = _FreeList.front();
								get->setBehavior(ALLSTART);
								/*get->setPosition(Vec2(rand() % (1000 - 200 + 1) + 200, rand() % (1000 - 200 + 1) + 200));*/
								get->setPosition(Vec2(800 + sinf(i) * (i + 100), 700 + cosf(i) * (i + 100)));
								get->setGravity(_fGravity);
								get->setStyle(_sStyle);
								//get->setParticle(_sStyle, stage);
								_FreeList.pop_front();
								_InUsedList.push_front(get);
								_iFree--; _iInUsed++;
							}
							_fFireworkTime = 0;
							_bFirework = false;
							_iFireworkPart = 4;
						}
					}
		
				}
			}
			_iGenParticles = n; // �ثe�w�g���� n �Ӥ��l

		}
		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= _iNumParticles) _iGenParticles -= _iNumParticles;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;

	}
	if (_iInUsed != 0) { // �����l�ݭn��s��
		for (it = _InUsedList.begin(); it != _InUsedList.end(); ) {
			if ((*it)->update(dt)) { // ���l�ͩR�g���w�g��F
									 // �N�ثe�o�@�Ӹ`�I�����e��^ _FreeList
				_FreeList.push_front((*it));
				it = _InUsedList.erase(it); // �����ثe�o�@��, 
				_iFree++; _iInUsed--;
			}
			else it++;
		}
	}


}
void CParticleSystem::setGravity(float fGravity)
{
	// �]�w�ثe particle �O�b inused �� gravity
	_fGravity = fGravity;
	list <CParticle *>::iterator it;
	if (_iInUsed != 0) { // �����l�ݭn��s��
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++) {
			(*it)->setGravity(_fGravity);
		}
	}
}
//void CParticleSystem::setSpin(float fSpin)
//{
//	// �]�w�ثe particle �O�b inused �� gravity
//	_fSpin = fSpin;
//	list <CParticle*>::iterator it;
//	if (_iInUsed != 0) { // �����l�ݭn��s��
//		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++) {
//			(*it)->setSpin(_fSpin);
//		}
//	}
//}
CParticleSystem::~CParticleSystem()
{
	if (_iInUsed != 0) _InUsedList.clear(); // �����Ҧ��� NODE
	if (_iFree != 0) _FreeList.clear();
	delete[] _pParticles; // ����Ҧ����o�귽
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("particletexture.plist");
}

void CParticleSystem::onTouchesBegan(const cocos2d::Point &touchPoint, cocos2d::Scene& stage)
{
	
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			log("Opacity:%d", _fOpacity);
			get = _FreeList.front();
			get->setBehavior(STAY_FOR_TWOSECONDS);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setStyle(_sStyle);
			//get->setParticle(_sStyle, stage);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case RANDOMS_FALLING :
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(RANDOMS_FALLING);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setStyle(_sStyle);
			//get->setParticle(_sStyle, stage);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case FREE_FLY:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(FREE_FLY);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setStyle(_sStyle);
			//get->setParticle(_sStyle, stage);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case EXPLOSION:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree > 100) {
			for (int i = 0; i < 100; i++) {
				get = _FreeList.front();
				get->setBehavior(EXPLOSION);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				get->setStyle(_sStyle);
				//get->setParticle(_sStyle, stage);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case HEARTSHAPE:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setBehavior(HEARTSHAPE);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				get->setStyle(_sStyle);
				//get->setParticle(_sStyle, stage);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case BUTTERFLYSHAPE:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setBehavior(BUTTERFLYSHAPE);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				get->setStyle(_sStyle);
				//get->setParticle(_sStyle, stage);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case FLOWSTART:
		log("6");
			if (_iFree > 150) {
				for (int i = 0; i < 150; i++) {
					get = _FreeList.front();
					get->setBehavior(FLOWSTART);
					get->setPosition(touchPoint);
					get->setGravity(_fGravity);
					get->setStyle(_sStyle);
					//get->setParticle(_sStyle, stage);
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--; _iInUsed++;
				}
			}
			else return;// �S�����l, �ҥH�N������
			break;
	case ALLSTART:
		log("7");
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setBehavior(ALLSTART);
				/*get->setPosition(Vec2(rand() % (1000 - 200 + 1) + 200, rand() % (1000 - 200 + 1) + 200));*/
				get->setPosition(Vec2(touchPoint.x+sinf(i)*(i+100), touchPoint.y+cosf(i)*(i+100)));
				get->setGravity(_fGravity);
				get->setStyle(_sStyle);
				//get->setParticle(_sStyle, stage);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// �S�����l, �ҥH�N������
		break;
	
	}

}

void CParticleSystem::onTouchesMoved(const cocos2d::Point &touchPoint,cocos2d::Scene& stage)
{
	
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(STAY_FOR_TWOSECONDS);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setStyle(_sStyle);
			//get->setParticle(_sStyle, stage);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case RANDOMS_FALLING:
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(RANDOMS_FALLING);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setStyle(_sStyle);
			//get->setParticle(_sStyle, stage);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case FREE_FLY:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(FREE_FLY);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setStyle(_sStyle);
			//get->setParticle(_sStyle, stage);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case SHAPE:
		if (_iFree > 50) {
			for (int i = 0; i < 50; i++) {
				get = _FreeList.front();
				get->setBehavior(SHAPE);
				/*get->setPosition(Vec2(rand() % (1000 - 200 + 1) + 200, rand() % (1000 - 200 + 1) + 200));*/
				get->setPosition(Vec2(touchPoint.x , touchPoint.y));
				get->setGravity(_fGravity);
				get->setStyle(_sStyle);
				
				//get->setParticle(_sStyle, stage);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// �S�����l, �ҥH�N������
		break;
	}
}
void CParticleSystem::setParticleNum(int fParticle) {
	_iNumParticles = fParticle;
}
void CParticleSystem::setRed(float fRed) {
	_fRed = fRed;
}
void CParticleSystem::setGreen(float fGreen) {
	_fGreen = fGreen;
}
void CParticleSystem::setBlue(float fBlue) {
	_fBlue = fBlue;
}
void CParticleSystem::setChange() {
	_bChange = true;
}
void CParticleSystem::setStyle(const char* pngName, cocos2d::Scene& stage) {
		for (int i = 0; i < NUMBER_PARTICLES; i++)
		{
			_pParticles[i].changeParticle(pngName,stage);
		}
}
void CParticleSystem::setEmitterType(int emtype) {
	_iEmitterType = emtype;
}
void CParticleSystem::setFirework(bool bFirework) {
	_bFirework = bFirework;
}
bool CParticleSystem::getFirework() {
	
	return _bFirework;
}
void CParticleSystem::setFireworkPart() {
	_iFireworkPart = 1;
}