#include "StartSceneReader.h"
#include "StartScene.hpp"

USING_NS_CC;

using namespace cocos2d::ui;

/*
#define X(a) READER_DEFINITION_FOR(a);
READERTYPES
#undef X

#define REGISTER_READER(readerClassName)\
CSLoader::getInstance()->registReaderObject(#readerClassName,(ObjectFactory::Instance)readerClassName::getInstance);

void registerCustomReaders(void)
{
	CCLOG("%s, line:%d, func:%s", __FILE__, __LINE__, __FUNCTION__);
#define X(a) REGISTER_READER(a##Reader);
	READERTYPES
#undef X
}
*/

StartScene* StartSceneReader::sm_pTmpNode = nullptr;
cocos2d::ccNodeLoadCallback StartSceneReader::sm_nodeLoadCallback = [](cocos2d::Ref * pRef) {
	if (StartSceneReader::sm_pTmpNode) {
		cocos2d::Node * pNode = dynamic_cast<cocos2d::Node *>(pRef);\
		if (!pNode) {
			return;
		}
		if (HelperFunctions::extractProperty(pNode, StartSceneReader::sm_pTmpNode, StartScene::sm_properties)) {
		}
	}
};

static StartSceneReader* _instanceStartSceneReader = nullptr;
StartSceneReader* StartSceneReader::getInstance()
{
	if (!_instanceStartSceneReader)
	{
		_instanceStartSceneReader = new StartSceneReader();
	}
	return _instanceStartSceneReader;
}

void StartSceneReader::purge()
{
	CC_SAFE_DELETE(_instanceStartSceneReader);
}

Node* StartSceneReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeStartScene)
{
	StartScene* node = StartScene::create();
	sm_pTmpNode = node;
	setPropsWithFlatBuffers(node, nodeStartScene);
	return node;
}
