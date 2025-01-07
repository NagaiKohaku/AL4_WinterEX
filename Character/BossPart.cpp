#include "BossPart.h"

#include "Bullet.h"

BossPart::BossPart() {

	maxHP_ = 20.0f;

	HP_ = maxHP_;

	isDead_ = false;

	damageSE_ = Audio::GetInstance()->SoundLoad("Resource/Sound/SE/PlayerDamage.wav");

	for (int i = 0; i < 30; i++) {

		damageSEObject_[i] = Audio::GetInstance()->CreateSoundObject(damageSE_, false);
	}

}

void BossPart::Update() {

	if (HP_ <= 0.0f) {

		isDead_ = true;
	}

	CharacterBase::Update();
}

void BossPart::Draw() {

	if (!isDead_) {

		CharacterBase::Draw();
	}
}

void BossPart::DisplayImGui() {

	Object3D::DisplayImGui();
}

void BossPart::OnCollision(CharacterBase* character) {

	if (!isDead_) {
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