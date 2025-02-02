#include "Bullet.h"

#include "Enemy.h"

#include "Easing.h"

///=====================================================/// 
/// コンストラクタ
///=====================================================///
Bullet::Bullet() {

	//移動速度の設定
	speed_ = 1.0f;

	//生存時間の設定
	lifeTime_ = 5.0f;

	//タイマーの初期化
	time_ = 0.0f;

	//死亡フラグをtrueで設定
	isDead_ = false;
}

///=====================================================/// 
/// 更新
///=====================================================///
void Bullet::Update() {

	//タイマーを進ませる
	time_ += 1.0f / 60.0f;

	//タイマーが生存時間を越えていたら
	if (time_ >= lifeTime_) {

		//死亡フラグをtrueにする
		isDead_ = true;
	}

	//移動
	Move();

	//キャラクター基底の更新
	CharacterBase::Update();
}

///=====================================================/// 
/// 描画
///=====================================================///
void Bullet::Draw() {

	//キャラクター基底の描画
	CharacterBase::Draw();
}

///=====================================================/// 
/// ImGuiの表示
///=====================================================///
void Bullet::DisplayImGui() {

	//3Dオブジェクトのデバッグ情報の表示
	Object3D::DisplayImGui();
}

///=====================================================/// 
/// 衝突時の処理
///=====================================================///
void Bullet::OnCollision(CharacterBase* character) {
	character;
}

void Bullet::SetTarget(Vector3 pos) {

	toTarget_ = Normalize(pos - transform_->GetTranslate());
}

///=====================================================/// 
/// 移動
///=====================================================///
void Bullet::Move() {

	//移動量を設定
	transform_->SetVelocity(toTarget_ * speed_);
}