#pragma once
#include "SingletonBase.h"

class GameNode;
class SceneManager : public SingletonBase<SceneManager>
{
private:
	typedef map<string, GameNode*>mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLoadingScene(string loadingSceneName, GameNode* scene);
	
	HRESULT changeScene(string SceneName);

	//로딩만 하는 누군가.
	//콜백이 곧 델리게이트다...
	//LPVOID : void* 어떤 타입으로도 변환 가능
	//friend 단방향참조
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	SceneManager() {};
	~SceneManager() {};
};

