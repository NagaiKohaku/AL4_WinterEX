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

	//デフォルトカメラを設定
	Object3DCommon::GetInstance()->SetDefaultCamera(camera_.get());

	ParticleManager::GetInstance()->SetDefaultCamera(camera_.get());

	/// === リソースの読み込み === ///

	SpriteManager::GetInstance()->LoadSprite("Sprite","RockShotTitle");

	/// === オブジェクトの生成 === ///

	/// === バレットマネージャーの生成 === ///

	bulletManager_ = std::make_unique<BulletManager>();

	/// === プレイヤーの生成 === ///

	player_ = std::make_unique<Player>();

	player_->SetModel("Sphere");

	player_->SetBulletManager(bulletManager_.get());

	player_->GetWorldTransform().SetTranslate({ 0.0f,0.0f,0.0f });

	/// === エネミーの生成 === ///

	enemy_ = std::make_unique<Enemy>();

	enemy_->SetModel("Sphere");

	enemy_->GetWorldTransform().SetTranslate({ -1.0f,-1.0f,50.0f });

}

void GameScene::Finalize() {

	//音声データの解放
	Audio::GetInstance()->SoundUnLoad(&soundData_);
}

void GameScene::Update() {

	//カメラをデバッグ状態で更新
	camera_->Update();

	//3Dオブジェクトの更新
	player_->Update();

	enemy_->Update();

	bulletManager_->Update();

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

	//Object3Dの描画
	player_->Draw();

	enemy_->Draw();

	bulletManager_->Draw();

	/// === 前景Spriteの描画 === ///

	Object2DCommon::GetInstance()->CommonDrawSetting();

}