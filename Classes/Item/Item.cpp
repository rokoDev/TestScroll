//
//  Item.cpp
//  TestScroll
//
//  Created by roko on 1/16/17.
//
//

#include "Item.hpp"

//#include "RegisterCustomReaders.hpp"
#include "ItemReader.h"

USING_NS_CC;

using namespace cocos2d::ui;

#define ROOT_CLASS  Item
#include "PROPERTY_MAP_MACRO.hpp"

Item::~Item()
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
}

Item::Item():
#include "INITIALIZE_PROPERTIES.hpp"
unusedVar(false)
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
}

Item * Item::createDefault()
{
    static cocos2d::Data data;
    if (0 == data.getSize()) {
        const std::string fileName = MY_STRINGIFY(ROOT_CLASS)+std::string(".csb");
        data = FileUtils::getInstance()->getDataFromFile(fileName);
    }
    auto rootNode = static_cast<Item*>(CSLoader::createNode(data, ItemReader::sm_nodeLoadCallback));
    
    //rootNode->setContentSize(Director::getInstance()->getWinSize());
    ui::Helper::doLayout(rootNode);
    
    rootNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    return (Item*)rootNode;
}

bool Item::init()
{
    if (Layout::init()) {
        return true;
    }
    return false;
}

#pragma mark WidgetCallBackHandlerProtocol methods
cocos2d::ui::Widget::ccWidgetTouchCallback Item::onLocateTouchCallback(const std::string &callBackName)
{
    if (callBackName == "onSuperButton")
    {
        return CC_CALLBACK_2(Item::onSuperButton, this);
    }
    return nullptr;
}

#pragma mark Button' callbacks
void Item::onSuperButton(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
    //CCLOG("%d, %s", __LINE__, __FUNCTION__);
    switch (type) {
        case Widget::TouchEventType::BEGAN:
        {
            CCLOG("onSuperButton::BEGAN");
            break;
        }
        case Widget::TouchEventType::MOVED:
        {
            break;
        }
        case Widget::TouchEventType::ENDED:
        {
            CCLOG("onSuperButton::ENDED");
            break;
        }
        case Widget::TouchEventType::CANCELED:
        {
            CCLOG("onSuperButton::CANCELED");
            break;
        }
            
        default:
            break;
    }
}
