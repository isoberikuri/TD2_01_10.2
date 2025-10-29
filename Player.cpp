#include "Player.h"

using namespace KamataEngine;

void Player::Initialize(Model* model, Camera* camera) {
	//assert(model);
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();

	worldTransform_.translation_ = {-2.0f, 0.0f, 0.0f}; // X, Y, Z の位置
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};// 大きさ
	worldTransform_.rotation_ = {0.0f, 850.0f, 0.0f};// 回転

	// 行列をGPUに転送（初期化時）
	worldTransform_.TransferMatrix();
}

void Player::Update() {

	  // 攻撃中の処理
	if (isAttacking_) {
		// 少し前に出る（Z軸マイナス方向に前進）
		worldTransform_.translation_.z += attackPower_;

		attackTimer_--;

		if (attackTimer_ <= 0) {
			isAttacking_ = false;
			worldTransform_.translation_.z = -2.0f; // 元の位置に戻す
		}
	}


	 // ダメージ中の処理
	if (isDamaged_) {
		// ノックバック（Z軸方向に少し後ろへ）
		worldTransform_.translation_.z -= knockbackPower_;

		// だんだん小さく揺れる（スケールを小さくして戻す）
		float scaleShake = 1.0f - 0.1f * sinf(static_cast<float>(damageTimer_) * 0.5f);
		worldTransform_.scale_ = {scaleShake, scaleShake, scaleShake};

		// タイマーを減らす
		damageTimer_--;

		// 終わったら元に戻す
		if (damageTimer_ <= 0) {
			isDamaged_ = false;
			worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
			worldTransform_.translation_.z = -2.0f; // 元の位置に戻す
		}
	}

	 // 行列を更新
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw() {
	// ダメージ中は3フレームごとに非表示
	if (damageTimer_ > 0 && (damageTimer_ / 3) % 2 == 0)
		return;

	model_->Draw(worldTransform_, *camera_);

}

//--------------------------------------
// ダメージを受けたとき呼ばれる関数
//--------------------------------------
void Player::SetDamage() {
	damageTimer_ = 30; // 約0.5秒くらい拡大表示（60FPS基準）
}

void Player::OnDamage() {
	isDamaged_ = true;
	damageTimer_ = 20; // ダメージ演出を20フレーム続ける
}

void Player::OnAttack() {
	isAttacking_ = true;
	attackTimer_ = 8; // 攻撃演出を15フレーム続ける
}
