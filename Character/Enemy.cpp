#include "Enemy.h"

Enemy::Enemy() {

	state_ = Approach;

	speed_ = 0.2f;

	leavePosY_ = 10.0f;
}

void Enemy::Update() {

	if (transform_.GetTranslate().z <= leavePosY_) {

		state_ = Leave;
	}

	Move();

	Object3D::Update();
}

void Enemy::Draw() {

	Object3D::Draw();
}

void Enemy::DisplayImGui() {

	Object3D::DisplayImGui();
}

void Enemy::Move() {

	Vector3 newPosition = transform_.GetTranslate();

	switch (state_) {
	case Enemy::Approach:

		transform_.SetVelocity({ 0.0f,0.0f,-speed_ });
		break;
	case Enemy::Leave:

		if (transform_.GetTranslate().x > 0) {

			transform_.SetVelocity({ speed_, 0.0f, 0.0f });
		} else {

			transform_.SetVelocity({ -speed_, 0.0f, 0.0f });
		}
		break;
	}
}