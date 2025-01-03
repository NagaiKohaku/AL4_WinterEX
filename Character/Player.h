#pragma once

#include "Object3D.h"

#include "BulletManager.h"

class Player : public Object3D {

public:

	Player();

	void Update() override;

	void Draw() override;

	void DisplayImGui() override;

public:

	void SetBulletManager(BulletManager* ptr) { bulletManager_ = ptr; }

private:

	void Move();

	void Attack();

private:

	BulletManager* bulletManager_;

	float speed_;

	float coolTime_;

	float time_;
};