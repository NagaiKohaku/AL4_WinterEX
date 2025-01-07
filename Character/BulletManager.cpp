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

		if (bullet->GetTag() == Bullet::TAG::Enemy) {

			bullet->SetSpeed(0.3f);
		}

		bullet->Update();
	}
}

void BulletManager::Draw() {

	for (std::unique_ptr<Bullet>& bullet : bulletList_) {

		bullet->Draw();
	}
}

void BulletManager::AddBullet(Vector3 pos, Vector3 targetPos, Bullet::TAG tag) {

	std::unique_ptr<Bullet> newBullet;

	newBullet = std::make_unique<Bullet>();

	newBullet->SetModel("Sphere");

	newBullet->GetWorldTransform()->SetTranslate(pos);

	newBullet->SetTag(tag);

	newBullet->SetTarget(targetPos);

	bulletList_.push_back(std::move(newBullet));
}

std::list<CharacterBase*> BulletManager::GetList() {

	std::list<CharacterBase*> result;

	for (std::unique_ptr<Bullet>& bullet : bulletList_) {

		result.push_back(bullet.get());
	}

	return result;
}