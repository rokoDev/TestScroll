#include "AppDelegate.h"
#include "StartScene.hpp"
#include "RegisterCustomReaders.hpp"
//#include "StartSceneReader.h"
//#include "ItemReader.h"

USING_NS_CC;

static const cocos2d::Size iPhoneLogicSize = cocos2d::Size(480, 320);
static const cocos2d::Size iPhone5LogicSize = cocos2d::Size(1136, 640);
static const cocos2d::Size iPadLogicSize = cocos2d::Size(1024, 768);

typedef struct tagResource
{
    std::string name;
    cocos2d::Size logicalSize;
    cocos2d::Size physicalSize;
    std::vector<std::string> folders;
    
} Resource;

// landscape
static Resource iPhoneRes       =   { "iPhone",     iPhoneLogicSize,  cocos2d::Size(480,  320),     {"iPhone", "common_csb_files"} };
static Resource iPhoneHDRes     =   { "iPhoneHD",   iPhoneLogicSize,  cocos2d::Size(960,  640),     {"iPhoneHD", "iPhone", "iPad", "common_csb_files"} };
static Resource iPadRes         =   { "iPad",       iPadLogicSize,    cocos2d::Size(1024,  768),    {"iPad", "iPhoneHD", "iPhone", "common_csb_files"} };
static Resource iPhone5Res      =   { "iPhone5",    iPhone5LogicSize, cocos2d::Size(1136,  640),    {"iPhone5", "iPhoneHD", "iPhone", "common_csb_files"} };
static Resource iPhone6Res      =   { "iPhone6",    iPhone5LogicSize, cocos2d::Size(1334, 750),     {"iPhone6", "iPad", "iPhoneHD", "iPhone", "common_csb_files"} };
static Resource iPhone6PlusRes  =   { "iPhone6+",   iPhone5LogicSize, cocos2d::Size(2208, 1242),    {"iPhone6Plus", "iPhone6", "iPad", "iPhoneHD", "iPhone", "common_csb_files"} };
static Resource iPadHDRes       =   { "iPadHD",     iPadLogicSize,    cocos2d::Size(2048, 1536),    {"iPadHD", "iPhone6Plus", "iPhone6", "iPad", "iPhoneHD", "iPhone", "common_csb_files"} };
static Resource iPadProRes       =  { "iPadPro",    iPadLogicSize,    cocos2d::Size(2732, 2048),    {"iPadPro", "iPadHDRes", "iPad", "common_csb_files"} };

void setupResolutionPolicy()
{
    const std::set<Resource *> availableResources = {&iPhoneRes};//, &iPhoneHDRes, &iPhone5Res, &iPhone6Res, &iPhone6PlusRes, &iPadRes, &iPadHDRes, &iPadProRes};
    
    auto calcScaleDistFunc = [](const cocos2d::Size & targetSize, const cocos2d::Size & candidateSize, float & scaleFactor) -> double
    {
        scaleFactor = MIN(targetSize.width/candidateSize.width, targetSize.height/candidateSize.height);
        const auto scaledCandidateSize = candidateSize*scaleFactor;
        return fabs(scaledCandidateSize.width*scaledCandidateSize.height-candidateSize.width*candidateSize.height);
    };
    
    auto director = Director::getInstance();
    const Size targetSize = director->getOpenGLView()->getFrameSize();
    double minScaleDist = std::numeric_limits<double>::max();
    Resource * resForLoad = &iPadRes;//assign some defaul resource
    float scaleFactor = 1.f;
    for (auto res : availableResources) {
        auto tmpScale = scaleFactor;
        auto scaleDist = calcScaleDistFunc(targetSize, res->physicalSize, tmpScale);
        if (scaleDist < minScaleDist) {
            resForLoad = res;
            minScaleDist = scaleDist;
            scaleFactor = tmpScale;
        }
    }
    
    
    auto designSize = targetSize/scaleFactor*resForLoad->logicalSize.width/resForLoad->physicalSize.width;
    designSize.width = std::roundf(designSize.width);
    designSize.height = std::roundf(designSize.height);
    
    CCLOG("resForLoad >> %s\n", resForLoad->name.c_str());
    //CCLOG("designRes >> %f x %f\n", designSize.width, designSize.height);
    
    FileUtils::getInstance()->setSearchPaths(resForLoad->folders);
    
    director->setContentScaleFactor(resForLoad->physicalSize.height/resForLoad->logicalSize.height);
    
    //uncomment first line and comment out second if you want "black strips" to be shown when screen size don't match resource size
    //director->getOpenGLView()->setDesignResolutionSize(resForLoad->logicalSize.width, resForLoad->logicalSize.height, ResolutionPolicy::SHOW_ALL);
    director->getOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
}

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        glview = GLViewImpl::createWithRect("TestScroll", Rect(0,0, 320, 480));
#else
        glview = GLViewImpl::create("TestScroll");
#endif
        //glview = GLViewImpl::createWithRect("HelloCpp", Rect(0, 0, 960, 640));
        //glview = GLViewImpl::create("TestScroll");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // Set the design resolution
    setupResolutionPolicy();
    
    //register reader' classes for cocostudio
    registerCustomReaders();
    //CSLoader::getInstance()->registReaderObject("StartSceneReader",(ObjectFactory::Instance)StartSceneReader::getInstance);
    //CSLoader::getInstance()->registReaderObject("ItemReader",(ObjectFactory::Instance)ItemReader::getInstance);
    
    
    // create scene
    auto startSceneNode = StartScene::createDefault();
    auto scene = Scene::create();
    scene->addChild(startSceneNode);
    
    // run
    Director::getInstance()->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
