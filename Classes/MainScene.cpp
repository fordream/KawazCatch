#include "MainScene.hpp"


USING_NS_CC;

MainScene::MainScene() : _player(NULL){
    
}

MainScene::~MainScene(){
    //デストラクタ
    CC_SAFE_RELEASE_NULL(_player);
}

Scene* MainScene::createScene(){
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool MainScene::init(){
    if(!Layer::init()){
        return false;
    }
    
    // Directorを取り出す
    auto director = Director::getInstance();
    //画面サイズを取り出す
    auto size = director->getWinSize();
    //背景のスプライトを生成する
    auto background = Sprite::create("background.png");
    //スプライト表示位置を設定する
    background->setPosition(Vec2(size.width / 2.0, size.height / 2.0));
    //親ノードにスプライトする
    this->addChild(background);
    
    //Spriteを生成して_playerを格納
    this->setPlayer(Sprite::create("player.png"));
    //_playerの位置を設定
    _player->setPosition(Vec2(size.width / 2.0, size.height - 445));
    this->addChild(_player);
    
    /** タッチの取得 */
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event){
        //タッチされた時の処理
        return true;
    };
    
    listener->onTouchMoved = [this](Touch* touch, Event* event){
        /*タッチ中に動いた時の処理*/
        //前回とのタッチ位置との差wおベクトルで取得する
        Vec2 delta = touch->getDelta();
        
        //現在のプレイヤーの座標を取得する
        Vec2 position = _player->getPosition();
        
        //現在座標 + 移動量を新たに座標にする
        Vec2 newPosition = position + delta;
        
        //画面サイズを取り出す
        auto winSize = Director::getInstance()->getWinSize();
        
        newPosition = newPosition.getClampPoint(Vec2(0, position.y), Vec2(winSize.width, position.y));
        
        _player->setPosition(newPosition);
        
        return true;
    };
    
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    return true;
}