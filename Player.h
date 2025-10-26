#pragma once
#include "KamataEngine.h"
#include "MyMath.h"
#include "input/Input.h"

using namespace KamataEngine;

class Player {
public:
	// 初期化
	void Initialize(Model* model, Camera* camera);
	// 更新
	void Update();
	// 描画
	void Draw();

	// ダメージを受けたときの処理
	void SetDamage();

	 // ダメージを受けたときに呼ばれる関数
	void OnDamage();

	// 攻撃をしたときに呼ばれる関数
	void OnAttack();

	// ワールド変換データ
	WorldTransform worldTransform_;

	WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	
	// モデル
	Model* model_ = nullptr;
	// カメラ
	Camera* camera_ = nullptr;


	 // ダメージ中かどうか
	bool isDamaged_ = false;

	// ダメージ演出の時間（フレーム数）
	int damageTimer_ = 0;

	// ノックバックの強さ
	float knockbackPower_ = 0.1f;

	 // 攻撃中かどうか
	bool isAttacking_ = false;

	// 攻撃演出タイマー
	int attackTimer_ = 0;

	// 攻撃の押し出し強さ
	float attackPower_ = 0.25f;
};