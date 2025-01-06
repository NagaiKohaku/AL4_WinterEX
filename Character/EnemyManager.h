#pragma once

#include "Enemy.h"

#include "list"
#include "memory"

///=====================================================/// 
/// エネミーマネージャー
///=====================================================///
class EnemyManager {

	///-------------------------------------------/// 
	/// メンバ関数
	///-------------------------------------------///
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyManager();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// エネミーの追加
	/// </summary>
	/// <param name="pos">初期座標</param>
	void AddEnemy(Vector3 pos);

	///-------------------------------------------/// 
	/// ゲッター・セッター
	///-------------------------------------------///
public:

	/// <summary>
	/// エネミーリストのゲッター
	/// </summary>
	/// <returns>エネミーリスト</returns>
	std::list<CharacterBase*> GetList();

	///-------------------------------------------/// 
	/// メンバ変数
	///-------------------------------------------///
private:

	//エネミーリスト
	std::list<std::unique_ptr<Enemy>> enemyList_;
};