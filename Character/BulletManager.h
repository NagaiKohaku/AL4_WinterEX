#pragma once

#include "Bullet.h"

#include "list"
#include "memory"

class BulletManager {

public:

	BulletManager();

	void Update();

	void Draw();

	void AddBullet(Vector3 pos);

public:

private:

	std::list<std::unique_ptr<Bullet>> bulletList_;
};