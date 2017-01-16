//
//  Item.hpp
//  TestScroll
//
//  Created by roko on 1/16/17.
//
//

#ifndef Item_hpp
#define Item_hpp

#include "CSNodeIncludes.hpp"

#include "Helper.hpp"

class Item:
public cocos2d::ui::Layout,
public cocostudio::WidgetCallBackHandlerProtocol
{
    
    friend class ItemReader;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Item);
    
protected:
    Item();
    bool init() override;
    
    //synthesize properties from Cocos Studio 2
    ///////////////////////////////////////////
    //static const PropertyMap sm_properties;
public:
    bool unusedVar;
#define PROPERTY_TYPE_NAME           \
X(Button, SuperButton)\
X(Layout, ContentPanel)

#include "SYNTHESIZE_PROPERTIES.hpp"
    ///////////////////////////////////////////
    
public:
    virtual ~Item();
    
    CREATE_FUNC(Item)
    
    static Item * createDefault();
    
#pragma mark WidgetCallBackHandlerProtocol methods
    cocos2d::ui::Widget::ccWidgetTouchCallback onLocateTouchCallback(const std::string &callBackName) override;
    
#pragma mark Button' callbacks
    void onSuperButton(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif /* Item_hpp */
