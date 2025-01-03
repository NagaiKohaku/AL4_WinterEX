#pragma once

#include "Object3D.h"

class Bullet : public Object3D {

public:

	Bullet();

	void Update() override;

	void Draw() override;

	void DisplayImGui() override;

public:

	bool GetIsDead() { return isDead_; }

private:

	void Move();

private:

	float speed_;

	float lifeTime_;

	float time_;

	bool isDead_;
};