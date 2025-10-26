#pragma once
#include "KamataEngine.h"
#include "MyMath.h"

using namespace KamataEngine;

class Kaminari {
public:
	// 初期化
	void Initialize(Model* model, Camera* camera);
	// 更新
	void Update();
	// 描画
	void Draw();

	 // 出現（敵の上に雷を落とす）
	void Start(const Vector3& enemyPos);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

	// カメラ
	Camera* camera_ = nullptr;

	// 出現中フラグ
	bool isActive_ = false;
	// 出現時間
	int activeTimer_ = 0;
};
