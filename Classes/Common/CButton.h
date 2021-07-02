#pragma once
#ifndef __CBUTTON_H__
#define __CBUTTON_H__

#include "cocos2d.h"

USING_NS_CC;

class CButton
{
private:
	cocos2d::Sprite* _normalPic;
	cocos2d::Sprite* _touchedPic;

	cocos2d::Size  _BtnSize;
	cocos2d::Point _BtnLoc;
	cocos2d::Rect  _BtnRect;

	float _fScale;	// �Ϥ��Y�񪺤j�p
	bool _bTouched; // �O�_�Q���U
	bool _bEnabled; // �O�_���@��
	bool _bVisible; // �O�_���

public:
	void setProperty(const std::string& normalName, const std::string& touchedName,
		cocos2d::Scene& stage, const cocos2d::Point locPt, int zOrder = 11);
	bool touchesBegin(cocos2d::Point inPos);
	bool touchesMoved(cocos2d::Point inPos);
	bool touchesEnded(cocos2d::Point inPos);
	void setVisible(bool bVis);
	void setEnabled(bool bEnable);

};


#endif