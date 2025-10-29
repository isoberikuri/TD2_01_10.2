#include "beam.h"

void Beam::Initialize(Model* model, Camera* camera) {
	//assert(model);
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();

	worldTransform_.translation_ = {8.0f, 10.0f, 0.0f}; // X, Y, Z の位置
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};        // 大きさ
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};     // 回転

	isActive_ = false;
	timer_ = 0;

	// 行列をGPUに転送（初期化時）
	worldTransform_.TransferMatrix();
}

void Beam::Update() {

	if (!isActive_)
		return;

	// 表示タイマー
	timer_--;

	if (timer_ <= 0) {
		isActive_ = false;
	}


	// 行列を更新
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Beam::Draw() { 
	if (!isActive_)
		return; // 出してないなら描画しない
	model_->Draw(worldTransform_, *camera_);
}

void Beam::Activate(const Vector3& startPos) {
	worldTransform_.translation_ = startPos;
	isActive_ = true;
	timer_ = 20; // 表示フレーム
}
