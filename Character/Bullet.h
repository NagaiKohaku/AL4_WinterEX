#pragma once

#include "CharacterBase.h"

///=====================================================/// 
/// バレット
///=====================================================///
class Bullet : public CharacterBase {

public:

	enum TAG {
		Player,
		Enemy
	};

	///-------------------------------------------/// 
	/// メンバ関数
	///-------------------------------------------///
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Bullet();

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ImGuiの表示
	/// </summary>
	void DisplayImGui() override;

	/// <summary>
	/// 衝突時の判定
	/// </summary>
	/// <param name="character">衝突相手</param>
	void OnCollision(CharacterBase* character) override;

	///-------------------------------------------/// 
	/// ゲッター・セッター
	///-------------------------------------------///
public:

	/// <summary>
	/// 死亡フラグのゲッター
	/// </summary>
	/// <returns>死亡フラグ</returns>
	bool GetIsDead() { return isDead_; }

	TAG GetTag() { return tag_; }

	void SetIsDead(bool flag) { isDead_ = flag; }

	void SetTag(TAG tag) { tag_ = tag; }

	void SetSpeed(float speed) { speed_ = speed; }

	/// <summary>
	/// 攻撃目標のセッター
	/// </summary>
	/// <param name="ptr">攻撃目標のポインター</param>
	void SetTarget(Vector3 pos);

	///-------------------------------------------/// 
	/// クラス内関数
	///-------------------------------------------///
private:

	//移動
	void Move();

	///-------------------------------------------/// 
	/// メンバ変数
	///-------------------------------------------///
private:

	TAG tag_;

	//移動速度
	float speed_;

	//生存時間
	float lifeTime_;

	//タイマー
	float time_;

	//死亡フラグ
	bool isDead_;

	//目標への方向
	Vector3 toTarget_;
};