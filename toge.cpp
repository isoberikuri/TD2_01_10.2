#include "toge.h"

void Toge::Initialize(Model* model, Camera* camera) {
	assert(model);
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();

	worldTransform_.translation_ = {5.0f, -3.0f, 0.0f}; // X, Y, Z の位置
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};        // 大きさ
	worldTransform_.rotation_ = {0.0f, 850.0f, 0.0f};   // 回転

	// 行列をGPUに転送（初期化時）
	worldTransform_.TransferMatrix();
}

void Toge::Update() {

	if (isActive_) {
		// 徐々に上がる
		if (worldTransform_.translation_.y < 0.5f) {
			worldTransform_.translation_.y += 0.2f;
		}

		// タイマー減少
		activeTimer_--;
		if (activeTimer_ <= 0) {
			isActive_ = false;
		}
	} else {
		// 徐々に下へ戻る
		if (worldTransform_.translation_.y > -5.0f) {
			worldTransform_.translation_.y -= 0.2f;
		}
	}

	// 行列を更新
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Toge::Draw() {
	if (isActive_) {
		model_->Draw(worldTransform_, *camera_);
	}
}

void Toge::Start(const Vector3& enemyPos) {
	// 敵の下に出現
	worldTransform_.translation_ = {enemyPos.x, -2.0f, enemyPos.z};
	isActive_ = true;
	activeTimer_ = 30; // 約0.5秒出現
}
