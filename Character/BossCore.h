#pragma once

#include "CharacterBase.h"

#include "Audio.h"

class BossCore : public CharacterBase {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BossCore();

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// デバッグ情報の表示
	/// </summary>
	void DisplayImGui() override;

	/// <summary>
	/// 衝突時の処理
	/// </summary>
	/// <param name="character">衝突相手</param>
	void OnCollision(CharacterBase* character) override;

public:

	bool GetIsDead() { return isDead_; }

	bool GetIsInvincible() { return isInvincible_; }

	void SetIsDead(bool flag) { isDead_ = flag; }

	void SetIsInvincible(bool flag) { isInvincible_ = flag; }

private:

	float maxHP_;

	float HP_;

	bool isDead_;

	bool isInvincible_;

	SoundData damageSE_;

	SoundObject damageSEObject_[30];

};