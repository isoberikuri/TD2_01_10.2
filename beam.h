#pragma once
#include "KamataEngine.h"
#include "MyMath.h"

using namespace KamataEngine;

class Beam {
public:
	// 初期化
	void Initialize(Model* model, Camera* camera);
	// 更新
	void Update();
	// 描画
	void Draw();

	 // ★ 弱攻撃で呼び出す関数
	void Activate(const Vector3& startPos);

	// 表示してるか確認用（必要なら）
	bool IsActive() const { return isActive_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

	// カメラ
	Camera* camera_ = nullptr;

	// ★追加
	bool isActive_ = false;
	int timer_ = 0;
};
