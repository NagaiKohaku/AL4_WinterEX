#include "ColliderManager.h"
#include "ModelManager.h"

///=====================================================/// 
/// コンストラクタ
///=====================================================///
ColliderManager::ColliderManager() {

	//描画フラグをfalseで設定
	isDraw_ = false;

	//色の設定
	color_ = { 1.0f,0.0f,0.0f,0.3f };

	//コライダーの球体モデルの読み込み
	ModelManager::GetInstance()->LoadModel("ColliderSphere", "sphere");

	ModelManager::GetInstance()->FindModel("ColliderSphere")->SetColor(color_);

	//コライダーの正方形モデルの読み込み
	ModelManager::GetInstance()->LoadModel("ColliderCube", "cube");

	ModelManager::GetInstance()->FindModel("ColliderCube")->SetColor(color_);

}

///=====================================================/// 
/// 描画
///=====================================================///
void ColliderManager::Draw() {

	//描画フラグがtrueであれば
	if (isDraw_) {

		//キャラクターリスト全要素のコライダーを描画
		for (CharacterBase* character : characterList_) {

			character->GetCollider()->Draw();
		}
	}
}

///=====================================================/// 
/// コライダーの衝突判定チェック
///=====================================================///
void ColliderManager::CheckAllCollider() {

	//キャラクターリストの先頭要素を取得
	std::list<CharacterBase*>::iterator itrA = characterList_.begin();

	for (; itrA != characterList_.end(); ++itrA) {

		//キャラクター情報を取得
		CharacterBase* characterA = *itrA;

		//イテレータAのとなりの要素
		std::list<CharacterBase*>::iterator itrB = itrA;

		itrB++;

		for (; itrB != characterList_.end(); ++itrB) {

			//キャラクター情報を取得
			CharacterBase* characterB = *itrB;

			//キャラクターAとキャラクターBで衝突判定
			CheckColliderPair(characterA, characterB);
		}
	}
}

///=====================================================/// 
/// コライダーリストのリセット
///=====================================================///
void ColliderManager::ResetColliderList() {

	//コライダーリストのリセット
	characterList_.clear();
}

///=====================================================/// 
/// コライダーリストに追加(キャラクター)
///=====================================================///
void ColliderManager::AddColliderList(CharacterBase* character) {

	//キャラクター情報をリストに追加
	characterList_.push_back(character);
}

///=====================================================/// 
/// コライダーリストに追加(キャラクターリスト)
///=====================================================///
void ColliderManager::AddColliderList(std::list<CharacterBase*> characterList) {

	//キャラクターリストの全要素をリストに追加
	for (CharacterBase* character : characterList) {

		characterList_.push_back(character);
	}
}

///=====================================================/// 
/// 2つのキャラクターの衝突判定
///=====================================================///
void ColliderManager::CheckColliderPair(CharacterBase* characterA, CharacterBase* characterB) {

	/// === キャラクターAの情報を取得 === ///

	//座標を取得
	Vector3 posA = characterA->GetCollider()->GetWorldTransform()->GetTranslate();

	//半径を取得
	float radiusA = characterA->GetCollider()->GetRadius();

	/// === キャラクターBの情報を取得 === ///

	//座標を取得
	Vector3 posB = characterB->GetCollider()->GetWorldTransform()->GetTranslate();

	//半径を取得
	float radiusB = characterB->GetCollider()->GetRadius();

	//差分ベクトルを計算
	Vector3 subtract = posB - posA;

	//距離を計算
	float distance = Length(subtract);

	//2つのキャラクターが重なっていたら
	if (distance <= (radiusA + radiusB)) {

		//キャラクターAの衝突時の処理を呼び出す
		characterA->OnCollision(characterB);

		//キャラクターBの衝突時の処理を呼び出す
		characterB->OnCollision(characterA);
	}

}