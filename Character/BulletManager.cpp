#include "BulletManager.h"

BulletManager::BulletManager() {

	//bulletList_.clear();
}

void BulletManager::Update() {

	bulletList_.remove_if([](std::unique_ptr<Bullet>& bullet) {

		if (bullet->GetIsDead()) {

			bullet.reset();
			return true;
		}

		return false;
		});

	for (std::unique_ptr<Bullet>& bullet : bulletList_) {

		bullet->Update();
	}
}

void BulletManager::Draw() {

	for (std::unique_ptr<Bullet>& bullet : bulletList_) {

		bullet->Draw();
	}
}

void BulletManager::AddBullet(Vector3 pos) {

	std::unique_ptr<Bullet> newBullet;

	newBullet = std::make_unique<Bullet>();

	newBullet->SetModel("Sphere");

	newBullet->GetWorldTransform().SetTranslate(pos);

	bulletList_.push_back(std::move(newBullet));
}