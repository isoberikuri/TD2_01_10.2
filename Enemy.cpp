#include "MyMath.h"
#include "Enemy.h"
#include "input/Input.h"
using namespace KamataEngine;

void Enemy::Initialize(Model* model,Camera* camera) {
	//assert(model);
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();

	worldTransform_.translation_ = {5.5f, 0.0f, 0.0f};   // X, Y, Z の位置
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};       // 大きさ
	worldTransform_.rotation_ = {0.0f, 600.0f, 0.0f};   // 回転

	// 行列をGPUに転送（初期化時）
	worldTransform_.TransferMatrix();
}

void Enemy::Update() {

	if (isDamaged_) {
		// ノックバック（Z軸方向に後ろへ下がる）
		/*worldtransform_.translation_.x += knockbackPower_*/;

		 // 縦揺れ：sin波を利用して上下にブルッと動く
		float shakeAmplitude = 0.15f; // 揺れの大きさ
		float shakeSpeed = 0.6f;      // 揺れる速さ
		worldTransform_.translation_.y = sinf(damageTimer_ * shakeSpeed) * shakeAmplitude;

		damageTimer_--;

		// ノックバック終了
		if (damageTimer_ <= 0) {
			isDamaged_ = false;
			worldTransform_.translation_.x = 5.5f; // 元の位置に戻す
		}
	}


	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Enemy::Draw() {

	// ダメージ中は点滅
	if (damageTimer_ > 0 && (damageTimer_ / 3) % 2 == 0)
		return;

	model_->Draw(worldTransform_, *camera_);

}

void Enemy::OnDamage() {
	isDamaged_ = true;
	damageTimer_ = 20; // 約20フレームノックバック＋点滅
}
