#ifndef __KawazCatch__MainScene__
#define __KawazCatch__MainScene__

#include "cocos2d.h"


class MainScene :public cocos2d::Layer{
  
protected:
    MainScene();
    virtual ~MainScene();
    bool init() override;
    
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(MainScene);
    
};



#endif /* defined(__KawazCatch__MainScene__) */
