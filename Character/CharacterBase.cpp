#include "CharacterBase.h"

///=====================================================///
/// コンストラクタ
///=====================================================///
CharacterBase::CharacterBase() {

	//コライダーを生成
	collider_ = std::make_unique<Collider>();

	//コライダーのモデルを設定
	collider_->SetModel("ColliderSphere");
}

///=====================================================/// 
/// 更新
///=====================================================///
void CharacterBase::Update() {

	//3Dオブジェクトの更新
	Object3D::Update();

	Vector3 objectPos = transform_->GetWorldTranslate();

	//キャラクターの座標とコライダーの座標を一致させる
	collider_->GetWorldTransform()->SetTranslate(objectPos);

	//コライダーの更新
	collider_->Update();
}

///=====================================================/// 
/// 描画
///=====================================================///
void CharacterBase::Draw() {

	//3Dオブジェクトの描画
	Object3D::Draw();
}