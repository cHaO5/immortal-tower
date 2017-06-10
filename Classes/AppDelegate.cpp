#include "AppDelegate.h"
#include "Scene\LoadingScene.h"

USING_NS_CC;

<<<<<<< HEAD
=======
//static cocos2d::Size designResolutionSize = cocos2d::Size(480*4, 320*4);
//static cocos2d::Size smallResolutionSize = cocos2d::Size(480*4, 320*4);
//static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024*4, 768*4);
//static cocos2d::Size largeResolutionSize = cocos2d::Size(2048*4, 1536*4);

>>>>>>> origin/develop
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

bool AppDelegate::applicationDidFinishLaunching() {
<<<<<<< HEAD
=======


>>>>>>> origin/develop
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
<<<<<<< HEAD
		glview = GLViewImpl::createWithRect("ImmortalTower", Rect(0, 0, 960, 640));
		glview->setFrameSize(1200, 640);
		director->setOpenGLView(glview);
	}
	//director->setDisplayStats(true);
	director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::FIXED_HEIGHT);
	// create a scene. it's an autorelease object
	auto scene = LoadingScene::createScene();
=======
		glview = GLViewImpl::createWithRect("OriginalImmortalTower", Rect(0, 0, 960, 640));//设计分辨率
		glview->setFrameSize(1200, 640);//屏幕分辨率就是外面的框
		director->setOpenGLView(glview);
	}

	//缩放？感觉有没有都一样
	//director->setContentScaleFactor();//资源分辨率把中间运行的部分缩放了整个缩放了

	//director->setDisplayStats(true);
	director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::FIXED_HEIGHT);

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
   // director->setAnimationInterval(1.0f / 60);


	/*
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect(, cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("OriginalImmortalTower");
#endif
        director->setOpenGLView(glview);
    }

    // Set the design resolution
    //glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	//director->setContentScaleFactor(smallResolutionSize.height / designResolutionSize.height);
	/*
	auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();
*/
    // create a scene. it's an autorelease object
    //为了创造一个指针可以不是运行scene，而是运行create以后运行startscene	

	SceneManager* manager = new SceneManager();
	manager->createScene();
>>>>>>> origin/develop
	// run
	director->runWithScene(scene);

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
