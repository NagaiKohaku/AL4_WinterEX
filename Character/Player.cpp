#include "Player.h"

#include "Input.h"

#include "WinApp.h"
#include "Sprite.h"
#include "Camera.h"

#include "MakeMatrixMath.h"

///=====================================================/// 
/// コンストラクタ
///=====================================================///
Player::Player() {

	bulletManager_ = nullptr;

	reticle3D_ = std::make_unique<Object3D>();

	reticle3D_->SetModel("Sphere");

	reticle3D_->GetWorldTransform()->SetParent(transform_.get());

	reticle3D_->GetWorldTransform()->SetTranslate({ 0.0f,0.0f,50.0f });

	reticle2D_ = std::make_unique<Object2D>();

	reticle2D_->SetSprite("Reticle");

	reticle2D_->SetSize({ 64.0f,64.0f });

	reticle2D_->GetSprite()->SetAnchorPoint({ 0.5f,0.5f });

	//移動速度の設定
	speed_ = 0.2f;

	//クールタイムの設定
	coolTime_ = 0.1f;

	//タイマーのリセット
	time_ = 0.0f;

	maxHP_ = 5.0f;

	HP_ = maxHP_;

	//3Dレティクルの描画フラグをtrueで設定
	isDrawReticle3D_ = true;

	isDead_ = false;

	damageSE_ = Audio::GetInstance()->SoundLoad("Resource/Sound/SE/PlayerDamage.wav");

	shotSE_ = Audio::GetInstance()->SoundLoad("Resource/Sound/SE/Shot.wav");

	for (int i = 0; i < 30; i++) {

		damageSEObject_[i] = Audio::GetInstance()->CreateSoundObject(damageSE_, false);
	}

	for (int i = 0; i < 30; i++) {

		shotSEObject_[i] = Audio::GetInstance()->CreateSoundObject(shotSE_, false);
	}

	transform_->SetIsClamp(true);

	transform_->SetMax({ 6.5f,3.0f,0.0f });

	transform_->SetMin({ -6.5f,-3.0f,0.0f });
}

///=====================================================/// 
/// 更新
///=====================================================///
void Player::Update() {

	//タイマーを進ませる
	time_ += 1.0f / 60.0f;

	if (HP_ <= 0.0f) {

		isDead_ = true;
	}

	//移動
	Move();

	//攻撃
	Attack();

	//キャラクター基底の更新
	CharacterBase::Update();

	reticle3D_->Update();

	Matrix4x4 matViewProjection = camera_->GetViewProjectionMatrix();

	Matrix4x4 matViewPort = MakeViewportMatrix(0.0f, 0.0f, WinApp::kClientWidth, WinApp::kClientHeight, 0.0f, 1.0f);

	Matrix4x4 matViewProjectionViewPort = matViewProjection * matViewPort;

	Vector3 reticlePos = reticle3D_->GetWorldTransform()->GetWorldTranslate();

	reticlePos = TransformCoord(reticlePos, matViewProjectionViewPort);

	reticle2D_->SetTranslate({ reticlePos.x,reticlePos.y });

	reticle2D_->Update();
}

///=====================================================/// 
/// 描画
///=====================================================///
void Player::Draw() {

	//キャラクター基底の描画
	CharacterBase::Draw();

	if (isDrawReticle3D_) {

		reticle3D_->Draw();
	}
}

void Player::Draw2D() {

	reticle2D_->Draw();
}

///=====================================================/// 
/// ImGuiの表示
///=====================================================///
void Player::DisplayImGui() {

	//3Dオブジェクトのデバッグ情報を表示
	Object3D::DisplayImGui();
}

///=====================================================/// 
/// 衝突時の処理
///=====================================================///
void Player::OnCollision(CharacterBase* character) {

	if (dynamic_cast<Bullet*>(character)) {

		Bullet* bullet = dynamic_cast<Bullet*>(character);

		if (bullet->GetTag() == Bullet::TAG::Enemy) {

			HP_--;

			bullet->SetIsDead(true);

			for (int i = 0; i < 30; i++) {

				if (!Audio::GetInstance()->isPlayed(damageSEObject_[i])) {

					Audio::GetInstance()->StartSound(damageSEObject_[i]);

					break;
				}
			}
		}
	}
}

///=====================================================/// 
/// 移動
///=====================================================///
void Player::Move() {

	//Wキーが押されたら
	if (Input::GetInstance()->isPushKey(DIK_W)) {

		//上に移動
		transform_->AddVelocity({ 0.0f,speed_,0.0f });
	}

	//Aキーが押されたら
	if (Input::GetInstance()->isPushKey(DIK_A)) {

		//左に移動
		transform_->AddVelocity({ -speed_,0.0f,0.0f });
	}

	//Sキーが押されたら
	if (Input::GetInstance()->isPushKey(DIK_S)) {

		//下に移動
		transform_->AddVelocity({ 0.0f,-speed_,0.0f });
	}

	//Dキーが押されたら
	if (Input::GetInstance()->isPushKey(DIK_D)) {

		//右に移動
		transform_->AddVelocity({ speed_,0.0f,0.0f });
	}
}

///=====================================================/// 
/// 攻撃
///=====================================================///
void Player::Attack() {

	//タイマーがクールタイムを越えていたら
	if (time_ >= coolTime_) {

		//Jキーが押されていたら
		if (Input::GetInstance()->isPushKey(DIK_J)) {

			//バレットの追加
			bulletManager_->AddBullet(
				transform_->GetTranslate(),
				reticle3D_->GetWorldTransform()->GetWorldTranslate(),
				Bullet::TAG::Player
			);

			//タイマーをリセット
			time_ = 0.0f;

			for (int i = 0; i < 30; i++) {

				if (!Audio::GetInstance()->isPlayed(shotSEObject_[i])) {

					Audio::GetInstance()->StartSound(shotSEObject_[i]);

					break;
				}
			}
		}
	}

}