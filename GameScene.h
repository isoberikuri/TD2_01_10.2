#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class GameScene
{

public:
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// デストラクタ
	~GameScene();

private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// スプライトを複数持つ
	std::vector<Sprite*> hearts_;

};
