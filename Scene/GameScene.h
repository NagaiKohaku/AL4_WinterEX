#pragma once
#include "BaseScene.h"

#include "Camera.h"
#include "Object3D.h"
#include "Object2D.h"
#include "Audio.h"

#include "Player.h"
#include "Enemy.h"
#include "BulletManager.h"

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

	//カメラ
	std::unique_ptr<Camera> camera_;

	//音声データ
	SoundData soundData_;

	//バレットマネージャー
	std::unique_ptr<BulletManager> bulletManager_;

	//プレイヤー
	std::unique_ptr<Player> player_;

	//エネミー
	std::unique_ptr<Enemy> enemy_;

	//SE
	SoundObject soundObject_;

};