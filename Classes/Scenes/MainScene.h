#ifndef SCENES_MAIN_SCENE_H
#define SCENES_MAIN_SCENE_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

class MainScene : public cocos2d::Scene
{
public:
	virtual bool init();

	virtual void update(float delta);

	CREATE_FUNC(MainScene);

	virtual ~MainScene();
private:
	cocos2d::Node *mainNode;
	cocos2d::Node *gameObjects;

	void initBackGround();
	void initNodes();
	void initPhysics();
	void initDeleteCheck();
	void initWaterRenderer();
	void initSlimeRenderer();
	void initItems();
	void initTiles();
	void initMap();
	void initPlayer();
	void initSlimes();
	void initShop();
};

#endif // !SCENES_MAIN_SCENE_H
