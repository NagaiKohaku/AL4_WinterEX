#pragma once

#include "BossCore.h"
#include "BossPart.h"
#include "Player.h"
#include "BulletManager.h"

#include "memory"
#include "vector"

class Boss {

private:

	enum STATE {
		FULL,
		DAMAGE
	};

public:

	Boss();

	void Update();

	void Draw();

	void DisplayImGui();

public:

	BossCore* GetCore() { return core_.get(); }

	std::list<CharacterBase*> GetPartsList();

	void SetPos(Vector3 pos) { core_->GetWorldTransform()->SetTranslate(pos); }

	void SetPlayer(Player* ptr) { player_ = ptr; }

	void SetBulletManager(BulletManager* ptr) { bulletManager_ = ptr; }

private:

	void ChangeState();

	void Fire();

private:

	Player* player_;

	BulletManager* bulletManager_;

	std::unique_ptr<BossCore> core_;

	std::vector<std::unique_ptr<BossPart>> parts_;

	STATE state_;

	float revivalTime_;

	float revivalMaxTime_;

	float fireTime_;

	float fireMaxTime_;

	SoundData shotSE_;

	SoundObject shotSEObject_[30];
};