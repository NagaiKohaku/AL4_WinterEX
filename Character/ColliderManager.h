#pragma once

#include "Collider.h"
#include "CharacterBase.h"

#include "list"

///=====================================================/// 
/// コライダーマネージャー
///=====================================================///
class ColliderManager {

	///=====================================================/// 
	/// メンバ関数
	///=====================================================///
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ColliderManager();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// コライダーの衝突判定チェック
	/// </summary>
	void CheckAllCollider();

	/// <summary>
	/// コライダーリストのリセット
	/// </summary>
	void ResetColliderList();

	/// <summary>
	/// コライダーリストに追加(キャラクター)
	/// </summary>
	/// <param name="character">キャラクター</param>
	void AddColliderList(CharacterBase* character);

	/// <summary>
	/// コライダーリストに追加(キャラクターリスト)
	/// </summary>
	/// <param name="characterList">キャラクターリスト</param>
	void AddColliderList(std::list<CharacterBase*> characterList);

	///-------------------------------------------/// 
	/// ゲッター・セッター
	///-------------------------------------------///
public:

	/// <summary>
	/// 描画フラグのセッター
	/// </summary>
	/// <param name="flag">フラグ</param>
	void SetIsDraw(bool flag) { isDraw_ = flag; }

	///-------------------------------------------/// 
	/// クラス内関数
	///-------------------------------------------///
private:

	/// <summary>
	/// 2つのキャラクターの衝突判定
	/// </summary>
	/// <param name="characterA">キャラクターA</param>
	/// <param name="characterB">キャラクターB</param>
	void CheckColliderPair(CharacterBase* characterA, CharacterBase* characterB);

	///-------------------------------------------/// 
	/// メンバ変数
	///-------------------------------------------///
private:

	//キャラクターリスト
	std::list<CharacterBase*> characterList_;

	//描画フラグ
	bool isDraw_;

	//色
	Vector4 color_;
};