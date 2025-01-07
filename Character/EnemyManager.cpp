#include "EnemyManager.h"

///=====================================================/// 
/// コンストラクタ
///=====================================================///
EnemyManager::EnemyManager() {
}

///=====================================================/// 
/// 更新
///=====================================================///
void EnemyManager::Update() {

	//エネミーリストの削除処理
	enemyList_.remove_if([](std::unique_ptr<Enemy>& enemy) {

		//エネミーの死亡フラグがtrueだったら
		if (enemy->GetIsDead()) {

			//エネミーの削除
			enemy.reset();

			return true;
		}

		return false;
		});

	//エネミー全要素の更新
	for (std::unique_ptr<Enemy>& enemy : enemyList_) {

		enemy->Update();
	}
}

///=====================================================/// 
/// 描画
///=====================================================///
void EnemyManager::Draw() {

	//エネミー全要素の描画
	for (std::unique_ptr<Enemy>& enemy : enemyList_) {

		enemy->Draw();
	}
}

///=====================================================/// 
/// エネミーの追加
///=====================================================///
void EnemyManager::AddEnemy(Vector3 pos) {

	//追加するエネミー
	std::unique_ptr<Enemy> newEnemy;

	//エネミーを生成
	newEnemy = std::make_unique<Enemy>();

	//モデルの設定
	newEnemy->SetModel("Sphere");

	//初期座標の設定
	newEnemy->GetWorldTransform()->SetTranslate(pos);

	//エネミーをリストに追加
	enemyList_.push_back(std::move(newEnemy));
}

///=====================================================/// 
/// リストのゲッター
///=====================================================///
std::list<CharacterBase*> EnemyManager::GetList() {

	//返り値のリスト
	std::list<CharacterBase*> result;

	//リストの全要素の参照
	for (std::unique_ptr<Enemy>& enemy : enemyList_) {

		//返り値のリストに情報を追加する
		result.push_back(enemy.get());
	}

	return result;
}