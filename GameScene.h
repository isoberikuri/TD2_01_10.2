#pragma once
#include "Enemy.h"
#include "KamataEngine.h"
#include "MyMath.h"
#include "Player.h"
#include "beam.h"
#include "input/Input.h"
#include "kaminari.h"
#include "toge.h"
#include <algorithm>
#include <array>
#include <numbers>

using namespace KamataEngine;
using namespace MathUtility;

//==================================================
// ゲームのメインシーンを管理するクラス
// プレイヤー、敵、HP、攻撃ゲージ、カメラなどを統括する
//==================================================
class GameScene {

public:
	//--------------------------------------------------
	// メイン処理（ゲームループの中で呼ばれる）
	//--------------------------------------------------

	// 初期化処理（ゲーム開始時に1回だけ呼ばれる）
	void Initialize();

	// 更新処理（毎フレーム呼ばれる：入力や動きの処理など）
	void Update();

	// 描画処理（毎フレーム呼ばれる：画面に描く）
	void Draw();

	// デストラクタ（終了時にメモリを解放）
	~GameScene();

	void StartCameraShake();

private:
	//==================================================
	// ▼ 自機（プレイヤー）関連
	//==================================================

	// 自機のハート画像（テクスチャ）ハンドル
	uint32_t hatoHandle_ = 0;

	// 敵のハート画像（テクスチャ）ハンドル
	uint32_t ehatoHadle_ = 0;

	// 自機のハートスプライト（HP表示用）を複数管理
	std::vector<Sprite*> hearts_;

	// 敵のハートスプライト（HP表示用）を複数管理
	std::vector<Sprite*> enemyHearts_;

	// タイトル
	uint32_t gameTitleHandle_ = 0;
	Sprite* gameTitleSprite_ = nullptr;

	// ルール説明
	uint32_t gameRuruHandle_ = 0;
	Sprite* gameRuruSprite_ = nullptr;

	// ゲームクリア
	uint32_t gameClearHandle_ = 0;
	Sprite* gameClearSprite_ = nullptr;

	// ゲームオーバ
	uint32_t gameOverHandle_ = 0;
	Sprite* gameOverSprite_ = nullptr;

	// HP管理
	int playerHPPoint_ = 5;

	int enemyHPPoint_ = 5;

	// プレイヤーのHP（ハート数で決まる）
	int playerHP_ = playerHPPoint_;

	// 敵のHP（ハート数で決まる）
	int enemyHP_ = enemyHPPoint_;

	// プレイヤーの画像ハンドル
	uint32_t playerHandle_ = 0;

	// プレイヤーの3Dモデルデータ
	Model* modelPlayer_ = nullptr;

	// プレイヤーキャラクター本体
	Player* player_ = nullptr;

	// 敵キャラクター本体
	Enemy* enemy_ = nullptr;

	// 敵の3Dモデルデータ
	Model* modelEnemy_ = nullptr;

	Model* enemyModel1_ = nullptr;
	Model* enemyModel2_ = nullptr;
	Model* enemyModel3_ = nullptr;

	// とげ攻撃本体
	Toge* toge_ = nullptr;

	// とげ攻撃の3Dモデルデータ
	Model* modelToge_ = nullptr;

	// 雷攻撃本体
	Kaminari* kami_ = nullptr;

	// 雷攻撃の3Dモデルデータ
	Model* modelKami_ = nullptr;

	// ビーム攻撃本体
	Beam* beam_ = nullptr;

	// ビーム攻撃の3Dモデルデータ
	Model* modelBeam_ = nullptr;

	////Playerから発射する位置
	// Vector3 playerPos = player_->worldTransform_.translation_;

	//==================================================
	// ▼ 攻撃ゲージ関連
	//==================================================

	// 攻撃ゲージ本体の画像ハンドル
	uint32_t attackHandle_ = 0;

	// 攻撃ゲージスプライト
	Sprite* attackSprite_ = nullptr;

	// 攻撃ゲージの矢印画像ハンドル
	uint32_t attackArrowHandle_ = 0;

	// 攻撃ゲージの矢印スプライト
	Sprite* attackArrowSprite_ = nullptr;

	// 矢印の現在の座標（X位置は固定、Yが上下移動）
	float attackArrowX = 75;
	float attackArrowY = 576 - 32;

	// プレイヤーが攻撃できる残り回数
	int playerAttackTurn = 3;

	// 攻撃判定ライン（矢印の位置を判定用に保存）
	float attackGaugeLain = attackArrowY - 32;

	// 矢印の移動方向（-5 = 上へ、+5 = 下へ）
	float arrowDirection = -5;

	// 攻撃倍率（中攻撃）
	int attackGauge2 = 2;

	// 攻撃倍率（強攻撃）
	int attackGauge3 = 3;

	// シーン切り替え
	bool titleScene = false;
	bool gameRuruScene = false;
	bool stageEnemy1 = false;
	bool stageEnemy2 = false;
	bool stageEnemy3 = false;
	bool gameOver = false;
	bool gameClear = false;

	//遅延タイマー
	int delayTimerPoint = false;
	int delayTimer = 150;

	//==================================================
	// ▼ カメラ関連
	//==================================================

	// 通常カメラ
	Camera camera_;

	// デバッグカメラ（※現在は未使用。必要に応じて有効化可能）
	// DebugCamera* debugCamera_ = nullptr;

	// デバッグカメラ使用フラグ
	bool isDebugCameraActive_ = false;

	// カメラの揺れ
	bool isCameraShaking_ = false;
	int cameraShakeTimer_ = 0;
	float cameraShakePower_ = 0.05f;

	// カメラの元位置を保存
	Vector3 defaultCameraPos_ = {0.0f, 1.0f, -10.0f};

	// 音声//

	// 音声ファイル
	uint32_t soundTitleHandle_ = 0;
	uint32_t soundGameHandle_ = 0;
	uint32_t soundClearHandle_ = 0;
	uint32_t soundOverHandle_ = 0;

	// 攻撃効果音
	uint32_t soundBotanHandle_ = 0;
	uint32_t soundTogeHandle_ = 0;
	uint32_t soundBeamHandle_ = 0;
	uint32_t soundKamiHandle_ = 0;
	//----------------------------

	// 音声再生ハンドル
	uint32_t voiceTitleHandle_ = 0;

	
};