#include "Enemy.h"

#include "Bullet.h"

///=====================================================/// 
/// コンストラクタ
///=====================================================///
Enemy::Enemy() {

	//接近状態に設定
	state_ = Approach;

	//移動速度の設定
	speed_ = 0.2f;

	//離脱地点の設定
	leavePosZ_ = 10.0f;

	//死亡フラグをfalseで設定
	isDead = false;
}

///=====================================================/// 
/// 更新
///=====================================================///
void Enemy::Update() {

	//離脱地点に到達していたら
	if (transform_->GetTranslate().z <= leavePosZ_) {

		//離脱状態に設定する
		state_ = Leave;
	}

	//移動
	Move();

	//キャラクター基底の更新
	CharacterBase::Update();
}

///=====================================================/// 
/// 描画
///=====================================================///
void Enemy::Draw() {

	//キャラクター基底の描画
	CharacterBase::Draw();
}

///=====================================================/// 
/// ImGuiの描画
///=====================================================///
void Enemy::DisplayImGui() {

	//3DオブジェクトのImGui情報を表示
	Object3D::DisplayImGui();
}

///=====================================================/// 
/// 衝突時の処理
///=====================================================///
void Enemy::OnCollision(CharacterBase* character) {

	//衝突相手がバレットであれば
	if (dynamic_cast<Bullet*>(character)) {

		//死亡フラグをtrueに設定する
		isDead = true;
	}
}

///=====================================================/// 
/// 移動
///=====================================================///
void Enemy::Move() {

	switch (state_) {

	case Enemy::Approach:

		/// === 接近状態の場合 === ///

		//移動量の設定
		transform_->SetVelocity({ 0.0f,0.0f,-speed_ });
		break;

	case Enemy::Leave:

		/// === 離脱状態の場合 === ///

		//左側にいたら
		if (transform_->GetTranslate().x > 0) {

			//左にはけるように移動する
			transform_->SetVelocity({ speed_, 0.0f, 0.0f });
		} else {

			//右にはけるように移動する
			transform_->SetVelocity({ -speed_, 0.0f, 0.0f });
		}
		break;
	}
}
