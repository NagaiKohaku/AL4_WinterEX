#include "GameScene.h"

#include "DirectXCommon.h"
#include "Object3DCommon.h"
#include "Object2DCommon.h"
#include "ModelManager.h"
#include "SpriteManager.h"
#include "ParticleManager.h"

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

	//タイトル画面のスプライトをロード
	SpriteManager::GetInstance()->LoadSprite("Sprite","RockShotTitle");

	SpriteManager::GetInstance()->LoadSprite("Reticle", "Reticle");

	/// === オブジェクトの生成 === ///

	/// === バレットマネージャーの生成 === ///

	bulletManager_ = std::make_unique<BulletManager>();

	/// === コライダーマネージャーの生成 === ///

	colliderManager_ = std::make_unique<ColliderManager>();

	//コライダー描画を有効化
	colliderManager_->SetIsDraw(true);

	/// === エネミーマネージャーの生成 === ///

	enemyManager_ = std::make_unique<EnemyManager>();

	/// === プレイヤーの生成 === ///

	player_ = std::make_unique<Player>();

	//モデルを設定
	player_->SetModel("Sphere");

	//バレットマネージャーの設定
	player_->SetBulletManager(bulletManager_.get());

	//初期座標を設定
	player_->GetWorldTransform()->SetTranslate({ 0.0f,0.0f,0.0f });

	/// === エネミーの生成 === ///

	//エネミーを1体生成
	enemyManager_->AddEnemy({ -1.0f,-1.0f,50.0f });

	/// === 天球の生成 === ///

	skyDome_ = std::make_unique<Object3D>();

	skyDome_->SetModel("SkyDome");
}

void GameScene::Finalize() {

	//音声データの解放
	Audio::GetInstance()->SoundUnLoad(&soundData_);
}

void GameScene::Update() {

	//カメラをデバッグ状態で更新
	camera_->Update();

	/// === 3Dオブジェクトの更新 === ///

	//プレイヤーの更新
	player_->Update();

	//エネミーマネージャーの更新
	enemyManager_->Update();

	//バレットマネージャーの更新
	bulletManager_->Update();

	skyDome_->Update();

	/// === 衝突判定の更新 === ///

	//コライダーリストをリセット
	colliderManager_->ResetColliderList();

	//プレイヤーをコライダーリストにセット
	colliderManager_->AddColliderList(player_.get());

	//エネミー情報をコライダーリストにセット
	colliderManager_->AddColliderList(enemyManager_->GetList());

	//バレット情報をコライダーリストにセット
	colliderManager_->AddColliderList(bulletManager_->GetList());

	//コライダーリストの全要素の当たり判定を取る
	colliderManager_->CheckAllCollider();

	/// === ImGuiの更新 === ///

	//ImGuiを起動
	ImGui::Begin("Scene");

	//モデルのImGui
	if (ImGui::TreeNode("Player")) {

		player_->DisplayImGui();

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Camera")) {

		camera_->DisplayImGui();

		ImGui::TreePop();
	}

	ImGui::Text("Shift + LeftClick : Move Camera");
	ImGui::Text("Shift + RightClick : Rotate Camera");
	ImGui::Text("Shift + MiddleWheel : Move Offset Camera");

	//ImGuiの終了
	ImGui::End();

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

	//エネミーマネージャーの描画
	enemyManager_->Draw();

	//バレットマネージャーの描画
	bulletManager_->Draw();

	//コライダーマネージャーの描画
	colliderManager_->Draw();

	/// === 前景Spriteの描画 === ///

	Object2DCommon::GetInstance()->CommonDrawSetting();

	player_->Draw2D();
}