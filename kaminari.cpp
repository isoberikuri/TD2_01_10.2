#include "kaminari.h"

void Kaminari::Initialize(Model* model, Camera* camera) {
	assert(model);
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();

	worldTransform_.translation_ = {5.0f, 10.0f, 0.0f}; // X, Y, Z の位置
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};        // 大きさ
	worldTransform_.rotation_ = {300.0f, 300.0f, 0.0f};   // 回転

	// 行列をGPUに転送（初期化時）
	worldTransform_.TransferMatrix();
}

void Kaminari::Update() {

	if (isActive_) {
		// 落下してくる動き
		if (worldTransform_.translation_.y > 0.0f) {
			worldTransform_.translation_.y -= 0.8f;
		}

		// タイマー減少
		activeTimer_--;
		if (activeTimer_ <= 0) {
			isActive_ = false;
		}
	} else {
		// 上に戻す（待機位置）
		if (worldTransform_.translation_.y < 10.0f) {
			worldTransform_.translation_.y += 0.4f;
		}
	}


	// 行列を更新
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Kaminari::Draw() { 
	if (isActive_) {
		model_->Draw(worldTransform_, *camera_);
	}
}

void Kaminari::Start(const Vector3& enemyPos) {
	// 敵の上空に出現
	worldTransform_.translation_ = {enemyPos.x, 8.0f, enemyPos.z};
	isActive_ = true;
	activeTimer_ = 30; // 0.5秒ほど表示
}
