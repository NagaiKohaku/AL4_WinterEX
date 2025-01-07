#pragma once

#include "CharacterBase.h"

#include "BulletManager.h"
#include "Collider.h"
#include "Object2D.h"
#include "Audio.h"

#include "memory"

///=====================================================/// 
/// プレイヤー
///=====================================================///
class Player : public CharacterBase {

	///-------------------------------------------/// 
	/// メンバ関数
	///-------------------------------------------///
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 2Dの描画
	/// </summary>
	void Draw2D();

	/// <summary>
	/// ImGuiの表示
	/// </summary>
	void DisplayImGui() override;

	/// <summary>
	/// 衝突時の処理
	/// </summary>
	/// <param name="character">衝突相手</param>
	void OnCollision(CharacterBase* character) override;

	///-------------------------------------------/// 
	/// ゲッター・セッター
	///-------------------------------------------///
public:

	bool GetIsDead() { return isDead_; }

	/// <summary>
	/// バレットマネージャーのセッター
	/// </summary>
	/// <param name="ptr">バレットマネージャーのポインター</param>
	void SetBulletManager(BulletManager* ptr) { bulletManager_ = ptr; }

	///-------------------------------------------/// 
	/// クラス内関数
	///-------------------------------------------///
private:

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	///-------------------------------------------/// 
	/// メンバ変数
	///-------------------------------------------///
private:

	//バレットマネージャー
	BulletManager* bulletManager_;

	//3Dレティクル
	std::unique_ptr<Object3D> reticle3D_;

	//2Dレティクル
	std::unique_ptr<Object2D> reticle2D_;

	//移動速度
	float speed_;

	//攻撃のクールタイム
	float coolTime_;

	//タイマー
	float time_;

	float maxHP_;

	float HP_;

	//3Dレティクルの描画フラグ
	bool isDrawReticle3D_;

	bool isDead_;

	SoundData damageSE_;

	SoundData shotSE_;

	SoundObject damageSEObject_[30];

	SoundObject shotSEObject_[30];
};