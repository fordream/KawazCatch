#include "MainScene.hpp"

USING_NS_CC;

// フルーツの画面上端からのマージン(px)
const int FRUIT_TOP_MARGIN = 40;

// フルーツの出現率
const int FRUIT_SPAWN_RATE = 20;

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
    
    //updateを毎フレーム実行するように登録する
    this->scheduleUpdate();
    
    return true;
}


Sprite* MainScene::addFruit(){
    //画面サイズを取り出す
    auto winSize = Director::getInstance()->getWinSize();
    //フルーツの種類を選択する
    int fruitType = rand() % static_cast<int>(FruitType::COUNT);
    //フルーツを作成する
    std::string filename = StringUtils::format("fruit%d.png", fruitType);
    auto fruit = Sprite::create(filename);
    //フルーツの種類をタグとして指定する
    fruit->setTag(fruitType);
    
    //フルーツのサイズを取り出す
    auto fruitSize = fruit->getContentSize();
    //x軸のランダムな位置
    float fruitXPos = rand() % static_cast<int>(winSize.width);
    fruit->setPosition(Vec2(fruitXPos,winSize.height - FRUIT_TOP_MARGIN - fruitSize.height / 2.0));
    this->addChild(fruit);
    //_fruitsベクターにフルーツを追加する
    _fruits.pushBack(fruit);
    
    /* ここまで出現 */
    
    
    /* フルーツに動きをつける*/
    //地面の座標
    auto ground = Vec2(fruitXPos, 0);
    
    // 3秒かけてgroundの位置まで落下させるアクション
    auto fall = EaseSineIn::create(MoveTo::create(3, ground));
    
    //removeFruitを即座に呼び出すアクション
    auto remove = CallFuncN::create([this](Node *node){
       //NodeをSpriteにダウンキャストする
        auto sprite = dynamic_cast<Sprite *>(node);
        
        //removeFruitを呼び出す
        this->removeFruit(sprite);
    });
    
    //fallとremoveを連続して実行させる
    auto sequence = Sequence::create(fall, remove, NULL);
    fruit->runAction(sequence);
    
    return fruit;
}


void MainScene::catchFruit(cocos2d::Sprite *fruit){
    //フルーツを削除する
    this->removeFruit(fruit);
}


bool MainScene::removeFruit(cocos2d::Sprite *fruit){
    //_fruitsにfruitが含まれているか確認する
    if(_fruits.contains(fruit)){
        //親ノードから削除する
        fruit->removeFromParent();
        //_fruits配列から削除する
        _fruits.eraseObject(fruit);
        return true;
    }
    return false;
}


void MainScene::update(float dt){
    //毎フレーム実行される
    int random = rand() % FRUIT_SPAWN_RATE;
    //適当な乱数が0の時
    if(random == 0){
        this->addFruit();
    }
    
    for(auto& fruit : _fruits){
        Vec2 busketPosition = _player->getPosition() - Vec2(0, 10);
        //フルーツの短形を取り出す
        Rect boundingBox = fruit->getBoundingBox();
        bool isHit = boundingBox.containsPoint(busketPosition);
        if(isHit){
            this->catchFruit(fruit);
        }
    }
}