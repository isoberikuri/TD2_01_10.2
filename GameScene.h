#pragma once
#include "KamataEngine.h"
#include"Player.h"
#include"Enemy.h"
#include"input/Input.h"
#include <algorithm>
#include <array>
#include <numbers>
#include"MyMath.h"

using namespace KamataEngine;
using namespace MathUtility;

class GameScene {

public:
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// デストラクタ
	~GameScene();

private:

	//自機--------------------------
	// 自機ハートハンドル
	uint32_t hatoHandle_ = 0;

	//敵ハートハンドル
	uint32_t ehatoHadle_ = 0;

	// 自機ハートを複数持つ
	std::vector<Sprite*> hearts_;
	// 敵ハートを複数持つ
	std::vector<Sprite*> enemyHearts_;
	//ルール説明
	uint32_t gameRuruHandle_ = 0;
	Sprite* gameRuruSprite_ = nullptr;


	//	HP管理
	int playerHPPoint_ = 5;
	int enemyHPPoint_ = 5;

	// プレイヤーHP
	int playerHP_ = playerHPPoint_;
	// 敵HP
	int enemyHP_ = enemyHPPoint_;


	//自機ハンドル
	uint32_t playerHandle_ = 0;

	//自機3Dモデルデータ
	Model* modelPlayer_ = nullptr;

	//自キャラ
	Player* player_ = nullptr;

	//敵キャラ
	Enemy* enemy_ = nullptr;

	Model* modelEnemy_ = nullptr;

	//

	//------------------------------

	//攻撃ゲージ
	uint32_t attackHandle_ = 0;
	Sprite* attackSprite_ = nullptr;
	uint32_t attackArrowHandle_ = 0;
	Sprite* attackArrowSprite_ = nullptr;
	float attackArrowX = 75;
	float attackArrowY = 576 - 32;
	int playerAttackTurn = 3;
	float attackGaugeLain = attackArrowY + 24;
	float arrowDirection = -5;
	int attackGauge2 = 2;
	int attackGauge3 = 3;

	//シーン切り替え
	int titleScene = false;
	int gameRuruScene = false;
	int stageEnemy1 = false;
	int stageEnemy2 = false;
	int stageEnemy3 = false;
	int gameOver = false;
	int gameClear = false;

	//カメラ
	Camera camera_;

	//デバッグカメラ
	//DebugCamera* debugCamera_ = nullptr;
	bool isDebugCameraActive_ = false;


};
