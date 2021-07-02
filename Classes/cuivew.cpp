#include "cuiview.h"

using namespace cocos2d::ui;

USING_NS_CC;

extern cocos2d::Size fSize;

CUIView::CUIView()
{
	_uiRoot = nullptr;
    _stage = nullptr;
    _ParticleControl = nullptr;
    _GravityBMValue = nullptr;
    _SpreadBMValue = nullptr;
    _DirectionBMValue = nullptr;
    _TypeBMValue = nullptr;
    _EmitterSprite = nullptr;
    _emitterSwitchBtn = nullptr;
    _bEmitterOn = false;
    _bfirework = false;
}

void CUIView::setModel(CParticleSystem& model)
{
    _ParticleControl = &model;
    _ParticleControl->init(*_stage,"flare.png");
    _ParticleControl->_emitterPt = _EmitterSprite->getLoc();
    _ParticleControl->_fDir = 90.0;
    _ParticleControl->_iNumParticles = 100;
    _ParticleControl->_iGenParticles = 0;
    _ParticleControl->_fSpread = 180.0f;
    _ParticleControl->_fVelocity = 2.5;	 // ���l�����}�t��
    _ParticleControl->_fLifeTime = 3.5f;	 // ���l���s���ɶ�
    _ParticleControl->_fSpin = 0;
    _ParticleControl->_fGravity = 0;
    _ParticleControl->_fElpasedTime = 0;
    _ParticleControl->setType(STAY_FOR_TWOSECONDS); // ���l�B�ʪ����A�A�w�]�� 0
    _ParticleControl->_windDir = Point(0, 0); // ���d�ҨS����@�����\��
    _ParticleControl->setFirework(_bfirework);
}

void CUIView::setProperty(std::string uicsbname, cocos2d::Size vsize, cocos2d::Scene& stage)
{
	_uiRoot = CSLoader::createNode(uicsbname);
	stage.addChild(_uiRoot);
	_uiRoot->setPosition(Vec2(0,0));
    _stage = &stage;
    _size = vsize;
    init();
}

void CUIView::init() 
{
    //Bubble sytle
    auto rootNode = CSLoader::createNode("./MainScene.csb");
    auto loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("bubblepos"));
    loctag->setVisible(true);
    _Bubble = new (std::nothrow) CButton();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("click.plist");
    _Bubble->setProperty("bubble.png", "bubble_click.png", *_stage, loctag->getPosition());
    //Circle style
    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("circlepos"));
    loctag->setVisible(true);
    _Circle = new (std::nothrow) CButton();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("click.plist");
    _Circle->setProperty("circle.png", "circle_click.png", *_stage, loctag->getPosition());
    //Cloud style
    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("cloudpos"));
    loctag->setVisible(true);
    _Cloud = new (std::nothrow) CButton();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("click.plist");
    _Cloud->setProperty("cloud.png", "cloud_click.png", *_stage, loctag->getPosition());
    //Comet style
    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("cometpos"));
    loctag->setVisible(true);
    _Comet = new (std::nothrow) CButton();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("click.plist");
    _Comet->setProperty("comet.png", "comet_click.png", *_stage, loctag->getPosition());
    //Flare style
    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("flarepos"));
    loctag->setVisible(true);
    _Flare = new (std::nothrow) CButton();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("click.plist");
    _Flare->setProperty("flare.png", "flare_click.png", *_stage, loctag->getPosition());
    //Spark style
    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("sparkpos"));
    loctag->setVisible(true);
    _Spark = new (std::nothrow) CButton();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("click.plist");
    _Spark->setProperty("spark.png", "spark_click.png", *_stage, loctag->getPosition());
    //Raindrop style
    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("raindroppos"));
    loctag->setVisible(true);
    _Raindrop = new (std::nothrow) CButton();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("click.plist");
    _Raindrop->setProperty("raindrop.png", "raindrop.png", *_stage, loctag->getPosition());
    //Play1 Button
    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("play_one"));
    loctag->setVisible(true);
    _Play1 = new (std::nothrow) CButton();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("click.plist");
    _Play1->setProperty("sliderballnormal.png", "sliderballpressed.png", *_stage, loctag->getPosition());
    //Play2 Button
    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("play_two"));
    loctag->setVisible(true);
    _Play2 = new (std::nothrow) CButton();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("click.plist");
    _Play2->setProperty("sliderballnormal.png", "sliderballpressed.png", *_stage, loctag->getPosition());
    //Play3 Button
    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("play_three"));
    loctag->setVisible(true);
    _Play3 = new (std::nothrow) CButton();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("click.plist");
    _Play3->setProperty("sliderballnormal.png", "sliderballpressed.png", *_stage, loctag->getPosition());
    //FireWork Button
    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("play_four"));
    loctag->setVisible(true);
    _Play4 = new (std::nothrow) CButton();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("click.plist");
    _Play4->setProperty("sliderballnormal.png", "sliderballpressed.png", *_stage, loctag->getPosition());
    // For Emitter
    _EmitterSprite = CDraggableSprite::create();
    _EmitterSprite->setSpriteInfo("emittericon.png", Point(-125.0f + _size.width / 2.0f, _size.height / 2.0f));
    _EmitterSprite->setVisible(false);
    _bEmitterOn = false;
    _stage->addChild(_EmitterSprite, 5);

    auto emiterpos = dynamic_cast<Sprite*>(_uiRoot->getChildByName("emitterpos"));
    Point loc = emiterpos->getPosition();
    emiterpos->setVisible(false);
    _emitterSwitchBtn = CSwitchButton::create();
    _emitterSwitchBtn->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", loc);
    _stage->addChild(_emitterSwitchBtn, 2);
    //For Wind
    _WindSprite = CDraggableSprite::create();
    _WindSprite->setSpriteInfo("emittericon.png", Point(-125.0f + _size.width / 2.0f, _size.height / 2.0f));
    _WindSprite->setVisible(false);
    _bWindOn = false;
    _stage->addChild(_WindSprite, 5);

    auto windpos = dynamic_cast<Sprite*>(_uiRoot->getChildByName("windpos"));
    Point windloc = windpos->getPosition();
    windpos->setVisible(false);
    _windSwitchBtn = CSwitchButton::create();
    _windSwitchBtn->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", windloc);
    _stage->addChild(_windSwitchBtn, 2);
    // ���l���i�վ�Ѽƪ����ʶb
    auto* GravitySlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Gravity"));
    GravitySlider->addEventListener(CC_CALLBACK_2(CUIView::GravityEvent, this));
    GravitySlider->setMaxPercent(100); 	// �N 0 �� 100 ������ -10 �� 10 ����
    _GravityBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("GravityBMFont"));

    // Slider of Spread
    auto* SpreadSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Spread"));
    SpreadSlider->addEventListener(CC_CALLBACK_2(CUIView::SpreadEvent, this));
    SpreadSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 180 ����
    _SpreadBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SpreadBMFont"));

    // Slider of Direction
    auto* DirectionSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Direction"));
    DirectionSlider->addEventListener(CC_CALLBACK_2(CUIView::DirectionEvent, this));
    DirectionSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
    _DirectionBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("DirectionBMFont"));

    // Slider of Type
    auto* TypeSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Type"));
    TypeSlider->addEventListener(CC_CALLBACK_2(CUIView::TypeEvent, this));
    TypeSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
    _TypeBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("TypeBMFont"));
    // Slider of Type
    auto* EmitterTypeSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_EmitterType"));
    EmitterTypeSlider->addEventListener(CC_CALLBACK_2(CUIView::EmitterTypeEvent, this));
    EmitterTypeSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
    _EmitterTypeBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("EmitterTypeBMFont"));

    //Slider of Speed
    auto* SpeedSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Speed"));
    SpeedSlider->addEventListener(CC_CALLBACK_2(CUIView::SpeedEvent, this));
    SpeedSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
    _SpeedBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SpeedBMFont"));
    //Slider of Spin
    auto* SpinSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Spin"));
    SpinSlider->addEventListener(CC_CALLBACK_2(CUIView::SpinEvent, this));
    SpinSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
    _SpinBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SpinBMFont"));
    //Slider of Opacity
    auto* OpacitySlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Opacity"));
    OpacitySlider->addEventListener(CC_CALLBACK_2(CUIView::OpacityEvent, this));
    OpacitySlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
    _OpacityBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("OpacityBMFont"));
    //Slider of Particle
    auto* ParticleSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Particles"));
    ParticleSlider->addEventListener(CC_CALLBACK_2(CUIView::ParticleEvent, this));
    ParticleSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
    _ParticleBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("ParticlesBMFont"));
    //Slider of Lifetime
    auto* LifetimeSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Lifetime"));
    LifetimeSlider->addEventListener(CC_CALLBACK_2(CUIView::LifetimeEvent, this));
    LifetimeSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
    _LifetimeBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("LifetimeBMFont"));
    //Slider of Red
    auto* RedSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Red"));
    RedSlider->addEventListener(CC_CALLBACK_2(CUIView::RedEvent, this));
    RedSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
    _RedBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("RedBMFont"));
    //Slider of Green
    auto* GreenSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Green"));
    GreenSlider->addEventListener(CC_CALLBACK_2(CUIView::GreenEvent, this));
    GreenSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
    _GreenBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("GreenBMFont"));
    //Slider of Blue
    auto* BlueSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Blue"));
    BlueSlider->addEventListener(CC_CALLBACK_2(CUIView::BlueEvent, this));
    BlueSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
    _BlueBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("BlueBMFont"));
}


void CUIView::onTouchBegan(const cocos2d::Point& tPoint, cocos2d::Scene& stage)
{
    const char* pngName;
    //��� Emitter �ɡA�i�즲�ӹϦ�
    if (_bEmitterOn) _EmitterSprite->touchesBegan(tPoint);

    // �S����� Emitter�A�ӥB�S�����b Emitter �������s�W�A�~�� touch �i�H�I����ܤ��l
    if (!_emitterSwitchBtn->touchesBegan(tPoint) && !_bEmitterOn && !(_ParticleControl->getFirework())) { _ParticleControl->onTouchesBegan(tPoint, stage); log("clickshow"); }
    
    //��� Wind �ɡA�i�즲�ӹϦ�
    if (_bWindOn) _WindSprite->touchesBegan(tPoint);

    // �S����� Wind�A�ӥB�S�����b Wind �������s�W�A�~�� touch �i�H�I����ܤ��l
    if (!_windSwitchBtn->touchesBegan(tPoint) && !_bEmitterOn && !(_ParticleControl->getFirework()))  _ParticleControl->onTouchesBegan(tPoint, stage);
    if (_Bubble->touchesBegin(tPoint))
    {
        pngName = "bubble.png";
        _ParticleControl->setStyle(pngName,*_stage);
        _ParticleControl->setChange();
        _Circle->touchesEnded(tPoint);
        _Cloud->touchesEnded(tPoint);
        _Comet->touchesEnded(tPoint);
        _Flare->touchesEnded(tPoint);
        _Spark->touchesEnded(tPoint);
        _Raindrop->touchesEnded(tPoint);
    }
    else if(_Circle->touchesBegin(tPoint)) {
        pngName = "circle.png";
        _ParticleControl->setStyle(pngName, *_stage);
        _ParticleControl->setChange();
        _Bubble->touchesEnded(tPoint);
        _Cloud->touchesEnded(tPoint);
        _Comet->touchesEnded(tPoint);
        _Flare->touchesEnded(tPoint);
        _Spark->touchesEnded(tPoint);
        _Raindrop->touchesEnded(tPoint);
    }
    else if (_Cloud->touchesBegin(tPoint)) {
        pngName = "cloud.png";
        _ParticleControl->setStyle(pngName, *_stage);
        _ParticleControl->setChange();
        _Bubble->touchesEnded(tPoint);
        _Circle->touchesEnded(tPoint);
        _Comet->touchesEnded(tPoint);
        _Flare->touchesEnded(tPoint);
        _Spark->touchesEnded(tPoint);
        _Raindrop->touchesEnded(tPoint);
    }
    else if (_Comet->touchesBegin(tPoint)) {
        pngName = "comet.png";
        _ParticleControl->setStyle(pngName, *_stage);
        _ParticleControl->setChange();
        _Bubble->touchesEnded(tPoint);
        _Circle->touchesEnded(tPoint);
        _Cloud->touchesEnded(tPoint);
        _Flare->touchesEnded(tPoint);
        _Spark->touchesEnded(tPoint);
        _Raindrop->touchesEnded(tPoint);
    }
    else if (_Flare->touchesBegin(tPoint)) {
        pngName = "flare.png";
        _ParticleControl->setStyle(pngName, *_stage);
        _ParticleControl->setChange();
        _Bubble->touchesEnded(tPoint);
        _Circle->touchesEnded(tPoint);
        _Comet->touchesEnded(tPoint);
        _Cloud->touchesEnded(tPoint);
        _Spark->touchesEnded(tPoint);
        _Raindrop->touchesEnded(tPoint);
    }
    else if (_Spark->touchesBegin(tPoint)) {
        pngName = "spark.png";
        _ParticleControl->setStyle(pngName, *_stage);
        _ParticleControl->setChange();
        _Bubble->touchesEnded(tPoint);
        _Circle->touchesEnded(tPoint);
        _Comet->touchesEnded(tPoint);
        _Cloud->touchesEnded(tPoint);
        _Flare->touchesEnded(tPoint);
        _Raindrop->touchesEnded(tPoint);
    }
    else if (_Raindrop->touchesBegin(tPoint)) {
        pngName = "raindrop.png";
        _ParticleControl->setStyle(pngName, *_stage);
        _ParticleControl->setChange();
        _Bubble->touchesEnded(tPoint);
        _Circle->touchesEnded(tPoint);
        _Comet->touchesEnded(tPoint);
        _Cloud->touchesEnded(tPoint);
        _Flare->touchesEnded(tPoint);
        _Spark->touchesEnded(tPoint);
    }
    if (_Play1->touchesBegin(tPoint)) {
        log("clickpaly1");
        _ParticleControl->setType(6);
        /*_ParticleControl->onTouchesBegan(tPoint, stage);*/
    }
    if (_Play2->touchesBegin(tPoint)) {
        log("clickpaly2");
        _ParticleControl->setType(7);
        /*_ParticleControl->onTouchesBegan(tPoint, stage);*/
    }
    if (_Play3->touchesBegin(tPoint)) {
        _ParticleControl->setType(8);
    }
    if (_Play4->touchesBegin(tPoint)) {
        _bfirework = true;
        _ParticleControl->setFirework(_bfirework);
        _ParticleControl->setFireworkPart();
    }
    
}

void CUIView::onTouchMoved(const cocos2d::Point& tPoint, cocos2d::Scene& stage)
{
    if (_bEmitterOn) {
        if (_EmitterSprite->touchesMoved(tPoint)) { // ���ʨç�s Emitter ����m
            _ParticleControl->_emitterPt = _EmitterSprite->getLoc();
        }
    }
    // �S����� Emitter�A�ӥB�S�����b Emitter �������s�W�A�~�� touch �i�H�I����ܤ��l
    if (!_emitterSwitchBtn->touchesMoved(tPoint) && !_bEmitterOn  && !(_ParticleControl->getFirework())) _ParticleControl->onTouchesMoved(tPoint, stage);

    if (_bWindOn) {
        if (_WindSprite->touchesMoved(tPoint)) { // ���ʨç�s Emitter ����m
            _ParticleControl->_windPt = _WindSprite->getLoc();
        }
    }
    // �S����� Emitter�A�ӥB�S�����b Emitter �������s�W�A�~�� touch �i�H�I����ܤ��l
    if (!_windSwitchBtn->touchesMoved(tPoint)  && !_bEmitterOn && !(_ParticleControl->getFirework())) _ParticleControl->onTouchesMoved(tPoint, stage);
}

void CUIView::onTouchEnded(const cocos2d::Point& tPoint, cocos2d::Scene& stage)
{
    if (_bEmitterOn) {
        if (_EmitterSprite->touchesEnded(tPoint)) {
            _ParticleControl->_emitterPt = _EmitterSprite->getLoc();
        }
    }
     // �I�b Emitter �������ϥܤW�A�i�楲�n�����A����
    if (_emitterSwitchBtn->touchesEnded(tPoint))
    {
        _bEmitterOn = _emitterSwitchBtn->getStatus();
        if (_bEmitterOn) { // ��� Emitter �ϥ�
            _EmitterSprite->setVisible(true);
        }
        else { // ���� Emitter �ϥ�
            _EmitterSprite->setVisible(false);
        }
        _ParticleControl->setEmitter(_bEmitterOn); // ��s����t�Τ��� Emitter ���A
    }

    if (_bWindOn) {
        if (_WindSprite->touchesEnded(tPoint)) {
            _ParticleControl->_windPt = _WindSprite->getLoc();
        }
    }
    // �I�b Emitter �������ϥܤW�A�i�楲�n�����A����
    if (_windSwitchBtn->touchesEnded(tPoint))
    {
        _bWindOn = _windSwitchBtn->getStatus();
        if (_bWindOn) { // ��� Emitter �ϥ�
            _WindSprite->setVisible(true);
        }
        else { // ���� Emitter �ϥ�
            _WindSprite->setVisible(false);
        }
        _ParticleControl->setWind(_bWindOn); // ��s����t�Τ��� Emitter ���A
    }
    else if (_Play1->touchesEnded(tPoint)) {
   
    }
    else if (_Play2->touchesEnded(tPoint)) {

    }
    else if (_Play3->touchesEnded(tPoint)) {

    }
    else if (_Play4->touchesEnded(tPoint)) {

    }

}

void CUIView::GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        float fGravity = (-50.0f + percent) / 5.0f; // �N 0 �� 100 ������ -10 �� 10 ����
        _GravityBMValue->setString(StringUtils::format("%2.1f", fGravity)); // �z�L _GravityBMValue ��ܦb�e���W
        _ParticleControl->setGravity(fGravity);
    }
}

void CUIView::SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        float fSpread = percent * 1.8f; // 0 �� 180 ����
        _SpreadBMValue->setString(StringUtils::format("%2.1f", fSpread));
        _ParticleControl->_fSpread = fSpread;
    }
}

void CUIView::DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        float fDir = percent * 3.6f; // 0 �� 360 ����
        _DirectionBMValue->setString(StringUtils::format("%2.1f", fDir));
        _ParticleControl->_fDir = fDir;
    }
}
void CUIView::SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // ���ʶs�ثe����m 0 ~ 100
        // �N 0 �� 100 ������ 0 �� 40 ����
        float fSpeed = percent / 2.5f;
        // �z�L _SpreadBMValue ��ܦb�e���W
        _SpeedBMValue->setString(StringUtils::format("%2.1f", fSpeed));
        _ParticleControl->setSpeed(fSpeed);
    }
}
void CUIView::SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // ���ʶs�ثe����m 0 ~ 100
        // �N 0 �� 100 ������ 0 �� 360 ����
        float fSpin = percent *3.6f;
        // �z�L _SpinBMValue ��ܦb�e���W
        _SpinBMValue->setString(StringUtils::format("%2.1f", fSpin));
        _ParticleControl->setSpin(fSpin);
    }
}
void CUIView::OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // ���ʶs�ثe����m 0 ~ 100
        // �N 0 �� 100 ������ 0 �� 360 ����
        float fOpacity = percent * 2.25f;
        // �z�L _SpinBMValue ��ܦb�e���W
        _OpacityBMValue->setString(StringUtils::format("%2.1f", fOpacity));
        _ParticleControl->setOpacity(fOpacity);
    }
}
void CUIView::ParticleEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // ���ʶs�ثe����m 0 ~ 100
        // �N 0 �� 100 ������ 0 �� 360 ����
        float fParticle = percent * 10.0f;
        // �z�L _SpinBMValue ��ܦb�e���W
        _ParticleBMValue->setString(StringUtils::format("%2.1f", fParticle));
        _ParticleControl->setParticleNum(fParticle);
    }
}
void CUIView::LifetimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // ���ʶs�ثe����m 0 ~ 100
        // �N 0 �� 100 ������ 0 �� 360 ����
        float fLifetime = percent * 0.1f;
        // �z�L _SpinBMValue ��ܦb�e���W
        _LifetimeBMValue->setString(StringUtils::format("%2.1f", fLifetime));
        _ParticleControl->setLifetime(fLifetime);
    }
}
void CUIView::RedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // ���ʶs�ثe����m 0 ~ 100
        // �N 0 �� 100 ������ 0 �� 360 ����
        float fRed = percent * 2.25f;
        // �z�L _SpinBMValue ��ܦb�e���W
        _RedBMValue->setString(StringUtils::format("%2.1f", fRed));
        _ParticleControl->setRed(fRed);
    }
}
void CUIView::GreenEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // ���ʶs�ثe����m 0 ~ 100
        // �N 0 �� 100 ������ 0 �� 360 ����
        float fGreen = percent * 2.25f;
        // �z�L _SpinBMValue ��ܦb�e���W
        _GreenBMValue->setString(StringUtils::format("%2.1f", fGreen));
        _ParticleControl->setGreen(fGreen);
    }
}
void CUIView::BlueEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // ���ʶs�ثe����m 0 ~ 100
        // �N 0 �� 100 ������ 0 �� 360 ����
        float fBlue = percent * 2.25f;
        // �z�L _SpinBMValue ��ܦb�e���W
        _BlueBMValue->setString(StringUtils::format("%2.1f", fBlue));
        _ParticleControl->setBlue(fBlue);
    }
}

void CUIView::TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        int iType = percent / 20; 
        _TypeBMValue->setString(StringUtils::format("%2d", iType));
        _ParticleControl->setType(iType);
       
    }
}

void CUIView::EmitterTypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        int iEmitterType = percent / 25;
        _EmitterTypeBMValue->setString(StringUtils::format("%2d", iEmitterType));
        _ParticleControl->setEmitterType(99-iEmitterType);

    }
}

void CUIView::update() {
    log("update%b",_bfirework);
    _bfirework = _ParticleControl->getFirework();
}