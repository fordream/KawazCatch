#include "MainScene.hpp"


USING_NS_CC;

MainScene::MainScene(){
    
}

MainScene::~MainScene(){
    
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
    
    return true;
}