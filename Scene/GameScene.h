#pragma once
#include "BaseScene.h"

#include "Camera.h"
#include "Object3D.h"
#include "Object2D.h"
#include "Audio.h"

#include "Player.h"
#include "Boss.h"
#include "BulletManager.h"
#include "ColliderManager.h"

#include "memory"

class GameScene : public BaseScene {

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private:

	void GameClear();

	void GameOver();

private:

	//カメラ
	std::unique_ptr<Camera> camera_;

	//バレットマネージャー
	std::unique_ptr<BulletManager> bulletManager_;

	//コライダーマネージャー
	std::unique_ptr<ColliderManager> colliderManager_;

	//プレイヤー
	std::unique_ptr<Player> player_;

	//ボス
	std::unique_ptr<Boss> boss_;

	//天球
	std::unique_ptr<Object3D> skyDome_;

	std::unique_ptr<Object2D> clearSprite_;

	std::unique_ptr<Object2D> gameOverSprite_;

	//音声データ
	SoundData BGM_;

	//SE
	SoundObject BGMObject_;

	bool isClear_;

	bool isGameOver_;

};