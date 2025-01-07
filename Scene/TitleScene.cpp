#include "TitleScene.h"

#include "SceneManager.h"
#include "SpriteManager.h"
#include "Object2DCommon.h"
#include "Object3DCommon.h"
#include "ParticleManager.h"
#include "Input.h"

void TitleScene::Initialize() {

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

	SpriteManager::GetInstance()->LoadSprite("Title", "Title");

	titleSprite_ = std::make_unique<Object2D>();

	titleSprite_->SetSprite("Title");

	titleSprite_->SetSize({ 1280.0f,720.0f });
}

void TitleScene::Finalize() {
}

void TitleScene::Update() {

	titleSprite_->Update();

	if (Input::GetInstance()->IsTriggerPushKey(DIK_SPACE)) {

		sceneManager_->ChangeScene(SceneManager::SceneType::kGame);
	}
}

void TitleScene::Draw() {

	Object2DCommon::GetInstance()->CommonDrawSetting();

	titleSprite_->Draw();
}