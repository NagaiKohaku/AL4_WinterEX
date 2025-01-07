#include "BossCore.h"

#include "Bullet.h"

BossCore::BossCore() {

	maxHP_ = 50.0f;

	HP_ = maxHP_;

	isDead_ = false;

	isInvincible_ = true;

	damageSE_ = Audio::GetInstance()->SoundLoad("Resource/Sound/SE/PlayerDamage.wav");

	for (int i = 0; i < 30; i++) {

		damageSEObject_[i] = Audio::GetInstance()->CreateSoundObject(damageSE_, false);
	}

}

void BossCore::Update() {

	if (HP_ <= 0.0f) {

		isDead_ = true;
	}

	CharacterBase::Update();
}

void BossCore::Draw() {

	if (!isDead_) {

		CharacterBase::Draw();
	}
}

void BossCore::DisplayImGui() {

	Object3D::DisplayImGui();
}

void BossCore::OnCollision(CharacterBase* character) {

	if (!isInvincible_) {
		if (dynamic_cast<Bullet*>(character)) {

			Bullet* bullet = dynamic_cast<Bullet*>(character);

			if (bullet->GetTag() == Bullet::TAG::Player) {

				HP_--;

				bullet->SetIsDead(true);
			}

			for (int i = 0; i < 30; i++) {

				if (!Audio::GetInstance()->isPlayed(damageSEObject_[i])) {

					Audio::GetInstance()->StartSound(damageSEObject_[i]);

					break;
				}
			}
		}
	}
}