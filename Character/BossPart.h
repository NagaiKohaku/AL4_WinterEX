#pragma once

#include "CharacterBase.h"

#include "Audio.h"

class BossPart : public CharacterBase {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BossPart();

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

	void ResetHP() { HP_ = maxHP_; }

public:

	bool GetIsDead() { return isDead_; }

	void SetIsDead(bool flag) { isDead_ = flag; }

private:

	float maxHP_;

	float HP_;

	bool isDead_;

	SoundData damageSE_;

	SoundObject damageSEObject_[30];

};