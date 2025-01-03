#include "Bullet.h"

Bullet::Bullet() {

	speed_ = 1.5f;

	lifeTime_ = 5.0f;

	time_ = 0.0f;

	isDead_ = false;
}

void Bullet::Update() {

	time_ += 1.0f / 60.0f;

	if (time_ >= lifeTime_) {

		isDead_ = true;
	}

	Move();

	Object3D::Update();
}

void Bullet::Draw() {

	Object3D::Draw();
}

void Bullet::DisplayImGui() {

	Object3D::DisplayImGui();
}

void Bullet::Move() {

	transform_.SetVelocity({ 0.0f,0.0f,speed_ });
}