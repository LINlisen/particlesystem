#include "CButton.h"

USING_NS_CC;

void CButton::setProperty(const std::string& normalName, const std::string& touchedName, cocos2d::Scene& stage, const cocos2d::Point locPt, int zOrder)
{

	_normalPic = Sprite::createWithSpriteFrameName(normalName);
	_touchedPic = Sprite::createWithSpriteFrameName(touchedName);
	_BtnLoc = locPt;
	_normalPic->setPosition(_BtnLoc); // �]�w��m
	_touchedPic->setPosition(_BtnLoc); // �]�w��m
	_touchedPic->setVisible(false);
	_touchedPic->setScale(1.25f);
	stage.addChild(_normalPic, zOrder);  // �[�J�ثe�� Layer �� 1: Z �b���h���A�V�j�N���b�V�W�h
	stage.addChild(_touchedPic, zOrder); // �[�J�ثe�� Layer �� 1: Z �b���h���A�V�j�N���b�V�W�h

	// ���o�j�p
	_BtnSize = _normalPic->getContentSize();
	// �]�w�P�_�ϰ�
	_BtnRect.size = _BtnSize;
	_BtnRect.origin.x = _BtnLoc.x - _BtnSize.width * 0.5f;
	_BtnRect.origin.y = _BtnLoc.y - _BtnSize.height * 0.5f;
	_bTouched = false;
	_fScale = 1.0f;
	_bVisible = _bEnabled = true;
}


bool CButton::touchesBegin(cocos2d::Point inPos)
{
	if (_BtnRect.containsPoint(inPos) && _bVisible && _bEnabled)
	{
		_bTouched = true;
		_normalPic->setVisible(false);
		_touchedPic->setVisible(true);
		return(true); // �����b�W��
	}
	return(false);
}

bool CButton::touchesMoved(cocos2d::Point inPos)
{
	if (_bTouched) { // �u���Q�������ɭԤ~�B�z
		if (!_BtnRect.containsPoint(inPos)) { // ����Y��m���}���s
			_bTouched = false;
			_normalPic->setVisible(true);
			_touchedPic->setVisible(false);
			return(false);
		}
		else return(true);
	}
	return(false); // �ƫ�A������s�W�N�Q����
}

bool CButton::touchesEnded(cocos2d::Point inPos)
{
	if (_bTouched)
	{
		_bTouched = false;
		_normalPic->setVisible(true);
		_touchedPic->setVisible(false);
		if (_BtnRect.containsPoint(inPos)) return(true);  // ����Y��m���s�ɡA�٦b�ӫ��s�W
	}
	return false;
}

void CButton::setVisible(bool bVisible)
{
	_bVisible = bVisible;
	if (!_bVisible) _normalPic->setVisible(false);
	else _normalPic->setVisible(true);
}


void CButton::setEnabled(bool bEnable)
{
	_bEnabled = bEnable;
	if (_bEnabled) _normalPic->setColor(Color3B(255, 255, 255));
	else _normalPic->setColor(Color3B(50, 50, 50));
}