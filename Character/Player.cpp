#include "Player.h"

#include "Input.h"

Player::Player() {

	speed_ = 0.2f;

	coolTime_ = 0.1f;

	time_ = 0.0f;
}

void Player::Update() {

	time_ += 1.0f / 60.0f;

	Move();

	Attack();

	Object3D::Update();
}

void Player::Draw() {

	Object3D::Draw();
}

void Player::DisplayImGui() {

	Object3D::DisplayImGui();
}

void Player::Move() {

	if (Input::GetInstance()->isPushKey(DIK_W)) {

		transform_.AddVelocity({ 0.0f,speed_,0.0f });
	}
	if (Input::GetInstance()->isPushKey(DIK_A)) {

		transform_.AddVelocity({ -speed_,0.0f,0.0f });
	}
	if (Input::GetInstance()->isPushKey(DIK_S)) {

		transform_.AddVelocity({ 0.0f,-speed_,0.0f });
	}
	if (Input::GetInstance()->isPushKey(DIK_D)) {

		transform_.AddVelocity({ speed_,0.0f,0.0f });
	}
}

void Player::Attack() {

	if (time_ >= coolTime_) {

		if (Input::GetInstance()->isPushKey(DIK_J)) {

			bulletManager_->AddBullet(transform_.GetTranslate());

			time_ = 0.0f;
		}
	}

}