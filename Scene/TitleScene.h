#pragma once

#include "BaseScene.h"

#include "Camera.h"
#include "Object2D.h"

#include "memory"

class TitleScene : public BaseScene {

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private:

	std::unique_ptr<Camera> camera_;

	std::unique_ptr<Object2D> titleSprite_;

};