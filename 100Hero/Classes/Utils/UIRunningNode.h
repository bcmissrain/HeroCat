#ifndef _RUNNING_NODE_H__
#define _RUNNING_NODE_H__
#include "cocos2d.h"

/************************************************************************/
/*How To Use                                                            */
/*	auto resultNode = UIRunningNode::create(2147483647, 3, "", 48);     */
/*	XXX->addChild(resultNode);											*/
/*	resultNode->beginRun();                                             */
/************************************************************************/
class UIRunningNode :public cocos2d::Node
{
public:
	static UIRunningNode* create(int target,float totalTime,std::string fontName,float fontSize);
	void beginRun();
	cocos2d::Size getContentSize();
private:
	bool init(int target, float totalTime, std::string fontName,float fontSize);

	UIRunningNode(){};
	~UIRunningNode(){};
private:
	float _totalTime = 1.0f;
	std::string _fontName = "";
	float _fontSize = 24;
	int _labelSize = 1;
	int _targetInt = 0;
	std::string _targetStr = "0";
};
#endif