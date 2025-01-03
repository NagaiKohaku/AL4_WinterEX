#pragma once

#include "Object3D.h"

class Enemy : public Object3D {

private:

	enum STATE {
		Approach,
		Leave
	};

public:

	Enemy();

	void Update() override;

	void Draw() override;

	void DisplayImGui() override;

private:

	void Move();

private:

	STATE state_;

	float speed_;

	float leavePosY_;

};