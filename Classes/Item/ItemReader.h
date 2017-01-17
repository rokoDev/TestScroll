#ifndef _ItemReader_hpp_
#define _ItemReader_hpp_

#include <stdio.h>
#include "editor-support/cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/WidgetReader/NodeReader/NodeReader.h"

class Item;
class ItemReader
	: public cocostudio::NodeReader
{
	public:
		static Item* sm_pTmpNode;
		static cocos2d::ccNodeLoadCallback sm_nodeLoadCallback;
		ItemReader() {};
		~ItemReader() {};
		static ItemReader* getInstance();
		static void purge();
		cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeItem);
};

#endif /* _ItemReader_hpp_ */