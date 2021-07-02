#include "CParticleSystem.h"

#define NUMBER_PARTICLES 1000 // 預設一次取得 1000 個 Particles

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
	_pParticles = new CParticle[NUMBER_PARTICLES]; // 取得所需要的 particle 空間
	 // 讀入儲存多張圖片的 plist 檔
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
	if (_bEmitterOn) { // 根據 Emitter 設定的相關參數，產生相對應的分子
		// 先計算在累加
		int n = (int)(_fElpasedTime * _iNumParticles); // 到目前為止應該產生的分子個數
		if (n > _iGenParticles) {  // 產生的分子個數不足，產生到 n 個分子
			for (int i = 0; i < n - _iGenParticles; i++) {
				// 根據 Emitter 的相關參數，設定所產生分子的參數
				if (_iFree != 0) {
					get = _FreeList.front();
					if (_iEmitterType == 99) {
						log("99");
						get->setBehavior(EMITTER_DEFAULT);
						float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
						t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
						t = (_fDir + t) * M_PI / 180.0f;
						Vec2 vdir(cosf(t), sinf(t));
						get->setDirection(vdir+_pwindDir);
						get->setPosition(_emitterPt);

					}
					else if (_iEmitterType == 98) {
						log("98");
						get->setBehavior(EMITTER_ONE);
						float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
						float a = (rand() % 10);
						t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
						t = (_fDir + t) * M_PI / 180.0f;
						//Vec2 vdir(cosf(a*t) *cosf(a*t)*i*sinf(4/5), sinf(a*t)* sinf(t*a)*i)

						Vec2 vdir(0, 0);
						get->setPosition(_emitterPt);
					}
					else if (_iEmitterType == 97) {
						log("97");
						get->setBehavior(EMITTER_TWO);
						float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
						t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
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
					// 根據 _fSpread 與 _vDir 產生方向
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--; _iInUsed++;
				}
			}
			_iGenParticles = n; // 目前已經產生 n 個分子

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
		int n = (int)(_fElpasedTime * _iNumParticles); // 到目前為止應該產生的分子個數
;
		if (n > _iGenParticles) {  // 產生的分子個數不足，產生到 n 個分子

			for (int i = 0; i < n - _iGenParticles; i++) {
				// 根據 Emitter 的相關參數，設定所產生分子的參數
				if (_iFree != 0) {

					if(_iFireworkPart==1){
						get = _FreeList.front();
						Point pos = Point(float(800), float(_fFireworkTime*100+200));
						get->setBehavior(FIREWORK);
						get->setPosition(pos);
						float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
						t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
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
			_iGenParticles = n; // 目前已經產生 n 個分子

		}
		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= _iNumParticles) _iGenParticles -= _iNumParticles;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;

	}
	if (_iInUsed != 0) { // 有分子需要更新時
		for (it = _InUsedList.begin(); it != _InUsedList.end(); ) {
			if ((*it)->update(dt)) { // 分子生命週期已經到達
									 // 將目前這一個節點的內容放回 _FreeList
				_FreeList.push_front((*it));
				it = _InUsedList.erase(it); // 移除目前這一個, 
				_iFree++; _iInUsed--;
			}
			else it++;
		}
	}


}
void CParticleSystem::setGravity(float fGravity)
{
	// 設定目前 particle 是在 inused 的 gravity
	_fGravity = fGravity;
	list <CParticle *>::iterator it;
	if (_iInUsed != 0) { // 有分子需要更新時
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++) {
			(*it)->setGravity(_fGravity);
		}
	}
}
//void CParticleSystem::setSpin(float fSpin)
//{
//	// 設定目前 particle 是在 inused 的 gravity
//	_fSpin = fSpin;
//	list <CParticle*>::iterator it;
//	if (_iInUsed != 0) { // 有分子需要更新時
//		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++) {
//			(*it)->setSpin(_fSpin);
//		}
//	}
//}
CParticleSystem::~CParticleSystem()
{
	if (_iInUsed != 0) _InUsedList.clear(); // 移除所有的 NODE
	if (_iFree != 0) _FreeList.clear();
	delete[] _pParticles; // 釋放所有取得資源
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("particletexture.plist");
}

void CParticleSystem::onTouchesBegan(const cocos2d::Point &touchPoint, cocos2d::Scene& stage)
{
	
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
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
		else return;// 沒有分子, 所以就不提供
		break;
	case FREE_FLY:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
		break;
	case EXPLOSION:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
		break;
	case HEARTSHAPE:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
		break;
	case BUTTERFLYSHAPE:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
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
			else return;// 沒有分子, 所以就不提供
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
		else return;// 沒有分子, 所以就不提供
		break;
	
	}

}

void CParticleSystem::onTouchesMoved(const cocos2d::Point &touchPoint,cocos2d::Scene& stage)
{
	
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
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
		else return;// 沒有分子, 所以就不提供
		break;
	case FREE_FLY:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
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
		else return;// 沒有分子, 所以就不提供
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