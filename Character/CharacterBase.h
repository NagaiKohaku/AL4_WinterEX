#pragma once

#include "Object3D.h"
#include "Collider.h"

#include "memory"

///=====================================================/// 
/// キャラクター基底
///=====================================================///
class CharacterBase : public Object3D {

	///-------------------------------------------/// 
	/// メンバ関数
	///-------------------------------------------///
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	CharacterBase();

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 衝突時の処理
	/// </summary>
	/// <param name="character">衝突相手</param>
	virtual void OnCollision(CharacterBase* character) = 0;

	///-------------------------------------------/// 
	/// ゲッター・セッター
	///-------------------------------------------///
public:

	/// <summary>
	/// コライダーのゲッター
	/// </summary>
	/// <returns>コライダー</returns>
	Collider* GetCollider() { return collider_.get(); }

	///-------------------------------------------/// 
	/// メンバ変数
	///-------------------------------------------///
protected:

	//コライダー
	std::unique_ptr<Collider> collider_;
};