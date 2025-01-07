#include "GameScene.h"

#include "SceneManager.h"
#include "DirectXCommon.h"
#include "Object3DCommon.h"
#include "Object2DCommon.h"
#include "ModelManager.h"
#include "SpriteManager.h"
#include "ParticleManager.h"
#include "Input.h"

#include "imgui.h"

#include "numbers"

void GameScene::Initialize() {

	/// === カメラの設定 === ///

	//カメラを生成
	camera_ = std::make_unique<Camera>();

	camera_->SetDebugCameraFlag(true);

	//カメラの座標
	camera_->GetWorldTransform().SetTranslate({ 0.0f,0.0f,-5.0f });

	//3Dオブジェクト基底のデフォルトカメラを設定
	Object3DCommon::GetInstance()->SetDefaultCamera(camera_.get());

	//パーティく売るマネージャーのデフォルトカメラを設定
	ParticleManager::GetInstance()->SetDefaultCamera(camera_.get());

	/// === リソースの読み込み === ///

	ModelManager::GetInstance()->LoadModel("SkyDome", "skyDome");

	ModelManager::GetInstance()->LoadModel("BossCore", "Sphere");

	ModelManager::GetInstance()->FindModel("BossCore")->SetColor({ 1.0f,0.0f,0.0f,1.0f });

	//タイトル画面のスプライトをロード
	SpriteManager::GetInstance()->LoadSprite("GameOver", "GameOver");

	SpriteManager::GetInstance()->LoadSprite("GameClear", "GameClear");

	SpriteManager::GetInstance()->LoadSprite("Reticle", "Reticle");

	SpriteManager::GetInstance()->LoadSprite("Tutorial", "Tutorial");

	BGM_ = Audio::GetInstance()->SoundLoad("Resource/Sound/BGM/BGM.wav");

	/// === オブジェクトの生成 === ///

	/// === バレットマネージャーの生成 === ///

	bulletManager_ = std::make_unique<BulletManager>();

	/// === コライダーマネージャーの生成 === ///

	colliderManager_ = std::make_unique<ColliderManager>();

	/// === プレイヤーの生成 === ///

	player_ = std::make_unique<Player>();

	//モデルを設定
	player_->SetModel("Sphere");

	//バレットマネージャーの設定
	player_->SetBulletManager(bulletManager_.get());

	//初期座標を設定
	player_->GetWorldTransform()->SetTranslate({ 0.0f,0.0f,0.0f });

	/// === ボスの生成 === ///

	boss_ = std::make_unique<Boss>();

	boss_->SetPos({ 0.0f,0.0f,40.0f });

	boss_->SetPlayer(player_.get());

	boss_->SetBulletManager(bulletManager_.get());

	/// === 天球の生成 === ///

	skyDome_ = std::make_unique<Object3D>();

	skyDome_->SetModel("SkyDome");

	clearSprite_ = std::make_unique<Object2D>();

	clearSprite_->SetSprite("GameClear");

	clearSprite_->SetSize({ 1280.0f,720.0f });

	gameOverSprite_ = std::make_unique<Object2D>();

	gameOverSprite_->SetSprite("GameOver");

	gameOverSprite_->SetSize({ 1280.0f,720.0f });

	tutorialSprite_ = std::make_unique<Object2D>();

	tutorialSprite_->SetSprite("Tutorial");

	tutorialSprite_->SetSize({ 1280.0f,720.0f });

	BGMObject_ = Audio::GetInstance()->CreateSoundObject(BGM_, true);

	Audio::GetInstance()->StartSound(BGMObject_);

	isClear_ = false;

	isGameOver_ = false;
}

void GameScene::Finalize() {

	//音声データの解放
	Audio::GetInstance()->SoundUnLoad(&BGM_);
}

void GameScene::Update() {

	//カメラをデバッグ状態で更新
	camera_->Update();

	GameClear();

	GameOver();

	/// === 3Dオブジェクトの更新 === ///

	if (!isClear_ && !isGameOver_) {

		//プレイヤーの更新
		player_->Update();

		boss_->Update();

		//バレットマネージャーの更新
		bulletManager_->Update();

		skyDome_->Update();

		/// === 衝突判定の更新 === ///

		//コライダーリストをリセット
		colliderManager_->ResetColliderList();

		//プレイヤーをコライダーリストにセット
		colliderManager_->AddColliderList(player_.get());

		colliderManager_->AddColliderList(boss_->GetCore());

		colliderManager_->AddColliderList(boss_->GetPartsList());

		//バレット情報をコライダーリストにセット
		colliderManager_->AddColliderList(bulletManager_->GetList());

		//コライダーリストの全要素の当たり判定を取る
		colliderManager_->CheckAllCollider();
	}

	clearSprite_->Update();

	gameOverSprite_->Update();

	tutorialSprite_->Update();

	if (isClear_ || isGameOver_) {

		if (Input::GetInstance()->IsTriggerPushKey(DIK_SPACE)) {

			Audio::GetInstance()->StopSound(BGMObject_);

			sceneManager_->ChangeScene(SceneManager::SceneType::kTitle);
		}
	}
}

void GameScene::Draw() {

	/// === 背景Spriteの描画 === ///

	//Spriteの描画準備
	Object2DCommon::GetInstance()->CommonDrawSetting();

	//深度情報のリセット
	DirectXCommon::GetInstance()->ClearDepthBuffer();

	/// === 3DObjectの描画 === ///

	//3DObjectの描画準備
	Object3DCommon::GetInstance()->CommonDrawSetting();

	skyDome_->Draw();

	//プレイヤーの描画
	player_->Draw();

	boss_->Draw();

	//バレットマネージャーの描画
	bulletManager_->Draw();

	//コライダーマネージャーの描画
	colliderManager_->Draw();

	/// === 前景Spriteの描画 === ///

	Object2DCommon::GetInstance()->CommonDrawSetting();

	player_->Draw2D();

	tutorialSprite_->Draw();

	if (isClear_) {

		clearSprite_->Draw();
	}

	if (isGameOver_) {

		gameOverSprite_->Draw();
	}

}

void GameScene::GameClear() {

	if (boss_->GetCore()->GetIsDead()) {

		isClear_ = true;
	}

}

void GameScene::GameOver() {

	if (player_->GetIsDead()) {

		isGameOver_ = true;
	}
}