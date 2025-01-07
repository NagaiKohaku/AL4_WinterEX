#pragma once

#include "CharacterBase.h"

///=====================================================/// 
/// エネミー
///=====================================================///
class Enemy : public CharacterBase {

	///-------------------------------------------/// 
	/// 構造体
	///-------------------------------------------///
private:

	//状態
	enum STATE {
		Approach,
		Leave
	};

	///-------------------------------------------/// 
	/// メンバ関数
	///-------------------------------------------///
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy();

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

	///-------------------------------------------/// 
	/// ゲッター・セッター
	///-------------------------------------------///
public:

	/// <summary>
	/// 死亡フラグのゲッター
	/// </summary>
	/// <returns>死亡フラグ</returns>
	bool GetIsDead() { return isDead; }

	///-------------------------------------------/// 
	/// クラス内関数
	///-------------------------------------------///
private:

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	///-------------------------------------------/// 
	/// メンバ変数
	///-------------------------------------------///
private:

	//状態
	STATE state_;

	//移動速度
	float speed_;

	//離脱位置
	float leavePosZ_;

	//死亡フラグ
	bool isDead;

};