#include "ItemReader.h"
#include "Item.hpp"

USING_NS_CC;

using namespace cocos2d::ui;

Item* ItemReader::sm_pTmpNode = nullptr;
cocos2d::ccNodeLoadCallback ItemReader::sm_nodeLoadCallback = [](cocos2d::Ref * pRef) {
	if (ItemReader::sm_pTmpNode) {
		cocos2d::Node * pNode = dynamic_cast<cocos2d::Node *>(pRef);
			if (!pNode) {
				return;
			}
		if (HelperFunctions::extractProperty(pNode, ItemReader::sm_pTmpNode, Item::sm_properties)) {
		}
	}
};

static ItemReader* _instanceItemReader = nullptr;
ItemReader* ItemReader::getInstance()
{
	if (!_instanceItemReader)
	{
		_instanceItemReader = new ItemReader();
	}
	return _instanceItemReader;
}

void ItemReader::purge()
{
	CC_SAFE_DELETE(_instanceItemReader);
}

Node* ItemReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeStartScene)
{
	Item* node = Item::create();
	sm_pTmpNode = node;
	setPropsWithFlatBuffers(node, nodeStartScene);
	return node;
}
