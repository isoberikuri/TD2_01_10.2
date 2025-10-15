#include "MyMath.h"
#include "Enemy.h"
#include "input/Input.h"
using namespace KamataEngine;

void Enemy::Initialize(Model* model,Camera* camera) {
	assert(model);
	model_ = model;
	camera_ = camera;
	worldtransform_.Initialize();

	worldtransform_.translation_ = {5.5f, 0.0f, 0.0f}; // X, Y, Z の位置
	worldtransform_.scale_ = {1.0f, 1.0f, 1.0f};        // 大きさ
	worldtransform_.rotation_ = {0.0f, -900.0f, 0.0f};   // 回転

	// 行列をGPUに転送（初期化時）
	worldtransform_.TransferMatrix();
}

void Enemy::Update() {

	worldtransform_.matWorld_ = MakeAffineMatrix(worldtransform_.scale_, worldtransform_.rotation_, worldtransform_.translation_);
	// 行列を定数バッファに転送
	worldtransform_.TransferMatrix();
}

void Enemy::Draw() { model_->Draw(worldtransform_, *camera_); }
