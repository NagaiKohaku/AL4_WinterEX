#include "Boss.h"

Boss::Boss() {

	core_ = std::make_unique<BossCore>();

	core_->SetModel("BossCore");

	for (int i = 0; i < 4; i++) {

		std::unique_ptr<BossPart> newPart = std::make_unique<BossPart>();

		newPart->SetModel("Sphere");

		newPart->GetWorldTransform()->SetParent(core_->GetWorldTransform());

		parts_.push_back(std::move(newPart));
	}

	parts_[0]->GetWorldTransform()->SetTranslate({ -3.0f,-3.0f,0.0f });
	parts_[1]->GetWorldTransform()->SetTranslate({ 3.0f,-3.0f,0.0f });
	parts_[2]->GetWorldTransform()->SetTranslate({ -3.0f,3.0f,0.0f });
	parts_[3]->GetWorldTransform()->SetTranslate({ 3.0f,3.0f,0.0f });

	state_ = FULL;

	revivalMaxTime_ = 6.0f;

	revivalTime_ = 0.0f;

	fireMaxTime_ = 3.0f;

	fireTime_ = fireMaxTime_;

	shotSE_ = Audio::GetInstance()->SoundLoad("Resource/Sound/SE/Shot.wav");

	for (int i = 0; i < 30; i++) {

		shotSEObject_[i] = Audio::GetInstance()->CreateSoundObject(shotSE_, false);
	}
}

void Boss::Update() {

	ChangeState();

	core_->Update();

	for (std::unique_ptr<BossPart>& part : parts_) {

		part->Update();
	}

	Fire();
}

void Boss::Draw() {

	core_->Draw();

	for (std::unique_ptr<BossPart>& part : parts_) {

		part->Draw();
	}
}

void Boss::DisplayImGui() {

	core_->DisplayImGui();

	for (std::unique_ptr<BossPart>& part : parts_) {

		part->DisplayImGui();
	}
}

std::list<CharacterBase*> Boss::GetPartsList() {

	std::list<CharacterBase*> result;

	for (std::unique_ptr<BossPart>& part : parts_) {

		result.push_back(part.get());
	}

	return result;
}

void Boss::ChangeState() {

	bool changeFlag = true;

	switch (state_) {
	case Boss::FULL:

		for (std::unique_ptr<BossPart>& part : parts_) {

			if (!part->GetIsDead()) {

				changeFlag = false;
			}
		}

		if (changeFlag) {

			state_ = DAMAGE;

			core_->SetIsInvincible(false);
		}

		break;
	case Boss::DAMAGE:

		revivalTime_ += 1.0f / 60.0f;

		if (revivalTime_ >= revivalMaxTime_) {

			state_ = FULL;

			core_->SetIsInvincible(true);

			for (std::unique_ptr<BossPart>& part : parts_) {

				part->SetIsDead(false);

				part->ResetHP();
			}

			revivalTime_ = 0.0f;
		}
		break;
	}
}

void Boss::Fire() {

	if (state_ == FULL) {

		fireTime_ += 1.0f / 60.0f;

		if (fireTime_ >= fireMaxTime_) {

			for (std::unique_ptr<BossPart>& part : parts_) {

				if (!part->GetIsDead()) {
					Vector3 partPos = part->GetWorldTransform()->GetWorldTranslate();

					Vector3 playerPos = player_->GetWorldTransform()->GetWorldTranslate();

					bulletManager_->AddBullet(
						partPos,
						playerPos,
						Bullet::TAG::Enemy
					);
				}

				for (int i = 0; i < 30; i++) {

					if (!Audio::GetInstance()->isPlayed(shotSEObject_[i])) {

						Audio::GetInstance()->StartSound(shotSEObject_[i]);

						break;
					}
				}
			}

			fireTime_ = 0.0f;
		}
	}
}