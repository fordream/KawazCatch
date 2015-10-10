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
    void update(float dt);
    CREATE_FUNC(MainScene);
    
    //_player変数と、getPlauyer()、setPlayer(Script *)が自動的に実装される
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *, _player, Player);
    
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _fruits, Fruits);
    
private:
    // フルーツの種類を表す
    enum class FruitType{
        APPLE,
        GRAPE,
        ORANGE,
        BANANA,
        CHERRY,
        //最大値
        COUNT
    };
    
    /** 画面にフルーツを新たに配置して、それを返す
     * @return 新たに作成されたフルーツ
     */
    cocos2d::Sprite* addFruit();
    
    /** マップからフルーツを取り除く
     * @param fruit 削除するフルーツ
     * @return 正しく削除されたか
     */
    bool removeFruit(cocos2d::Sprite * fruit);
    
    /** フルーツを取得する
     * @param Sprite* 取得するフルーツ
     */
    void catchFruit(cocos2d::Sprite * fruit);
    
    
    
};



#endif /* defined(__KawazCatch__MainScene__) */
