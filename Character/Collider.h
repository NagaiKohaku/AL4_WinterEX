#pragma once

#include "Object3D.h"

///=====================================================/// 
/// コライダー
///=====================================================///
class Collider : public Object3D {

	///-------------------------------------------/// 
	/// メンバ関数
	///-------------------------------------------///
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Collider();

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	///-------------------------------------------/// 
	/// ゲッター・セッター
	///-------------------------------------------///
public:

	/// <summary>
	/// 半径のゲッター
	/// </summary>
	/// <returns>半径</returns>
	float GetRadius() { return radius_; }

	/// <summary>
	/// 衝突フラグのゲッター
	/// </summary>
	/// <returns>衝突フラグ</returns>
	bool GetIsCollision() { return isCollision_; }

	/// <summary>
	/// 衝突フラグのセッター
	/// </summary>
	/// <param name="flag">フラグ</param>
	void SetIsCollision(bool flag) { isCollision_ = flag; }

	///-------------------------------------------/// 
	/// メンバ変数
	///-------------------------------------------///
private:

	//半径
	float radius_;

	//衝突フラグ
	bool isCollision_;
};