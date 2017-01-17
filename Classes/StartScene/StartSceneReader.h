#ifndef _StartSceneReader_hpp_
#define _StartSceneReader_hpp_

#include <stdio.h>
#include "editor-support/cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/WidgetReader/NodeReader/NodeReader.h"

class StartScene;
class StartSceneReader 
	: public cocostudio::NodeReader
{
	public:
		static StartScene * sm_pTmpNode;
		static cocos2d::ccNodeLoadCallback sm_nodeLoadCallback;
		StartSceneReader() {};
		~StartSceneReader() {};
		static StartSceneReader* getInstance();
		static void purge();
		cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeStartScene);
};

#endif /* _StartSceneReader_hpp_ */
