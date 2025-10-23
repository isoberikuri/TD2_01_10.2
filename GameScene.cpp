#include "GameScene.h"


// 初期化
void GameScene::Initialize()
{
	titleScene = true;
	if (stageEnemy1 == 1)
	{
		playerHP_ = 7;
	}

	//自キャラ
	//自機のハート//
	//ファイル名を指定してテクスチャハンドルを読み込む
	hatoHandle_ = TextureManager::Load("ha-to.png");
	// 複数のスプライトを生成
	for (int i = 0; i < playerHPPoint_; i++)
	{
		// X座標を少しずつずらして配置
		Sprite* heart = Sprite::Create(hatoHandle_, {300.0f + i * 55.0f, 660.0f});
		hearts_.push_back(heart);
	}

	// 敵のハート//
	ehatoHadle_ = TextureManager::Load("Eha-to.png");
	// 複数のスプライトを生成
	for (int i = 0; i < enemyHPPoint_; i++)
	{
		// X座標を少しずつずらして配置
		Sprite* enemyHeart = Sprite::Create(ehatoHadle_, {1000.0f + i * 55.0f, 10.0f});
		enemyHearts_.push_back(enemyHeart);
	}

	// プレイヤーHP = ハート数
	playerHP_ = static_cast<int>(hearts_.size());
	// プレイヤーHP = ハート数
	enemyHP_ = static_cast<int>(enemyHearts_.size());

	//ファイル名を指定してテクスチャハンドルを読み込む
	playerHandle_ = TextureManager::Load("a.png");

	//3Dモデルデータの生成
	modelPlayer_ = Model::CreateFromOBJ("player");

	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize(modelPlayer_, &camera_);

	//-------------------------------------

	//攻撃ゲージ
	attackHandle_ = TextureManager::Load("geegiBer.png");
	attackSprite_ = Sprite::Create(attackHandle_, {0, 0});
	attackArrowHandle_ = TextureManager::Load("RighAttackArrow.png");
	attackArrowSprite_ = Sprite::Create(attackArrowHandle_, {attackArrowX,attackArrowY});
	//ルール説明
	gameRuruHandle_ = TextureManager::Load("TD2_GameRuru1.png");
	gameRuruSprite_ = Sprite::Create(gameRuruHandle_, {0, 0});


	//カメラの初期化
	camera_.Initialize();

	// デバッグカメラの生成
	//debugCamera_ = new KamataEngine::DebugCamera(1280, 720);
	// 軸方向表示の表示を有効にする
	//KamataEngine::AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	//KamataEngine::AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());

	//敵キャラ----------------------------
	
	// 3Dモデルデータの生成
	modelEnemy_ = Model::CreateFromOBJ("enemy");

	// 敵キャラの生成
	enemy_ = new Enemy();
	// 敵キャラの初期化
	enemy_->Initialize(modelEnemy_, &camera_); 
	 
	//------------------------------------

	playerAttackTurn = 3;
}

bool canPress = true;

// 更新
void GameScene::Update()
{
	//タイトルシーン
	if (titleScene == 1)
	{
		if (Input::GetInstance()->TriggerKey(DIK_RETURN))
		{
			canPress = false; // 一時的に無効化
			titleScene = 0;
			gameRuruScene = 1;
		}
		// キーが離されたら再び有効にする
		if (!Input::GetInstance()->IsPressKey(DIK_RETURN)) {
			canPress = true;
	}

	//ルール説明
	if (gameRuruScene == 1)
	{
		gameRuruSprite_->SetPosition({0,0});
		if (Input::GetInstance()->TriggerKey(DIK_SPACE))
		{
			gameRuruScene = 0;
			stageEnemy1 = 1;
			playerHPPoint_ = 5;
			enemyHPPoint_ = 5;
		}
	}

	//ステージ
	if (stageEnemy1 == 1 || stageEnemy2 == 1 || stageEnemy3 == 1)
	{
		// 自キャラ------------------------------------------
		//  スペースキーが押された瞬間に HP を1減らす
		if (playerAttackTurn > 0)
		{
			attackArrowY += arrowDirection * 2; // 上下移動のスピード（2ピクセル）

			// 上端 or 下端に達したら方向を反転
			if (attackArrowY <= 0)
			{
				attackArrowY = 0;
				arrowDirection = 5; // 下に動くようにする
			} else if (attackArrowY >= 576)
			{
				attackArrowY = 576;
				arrowDirection = -5; // 上に動くようにする
			}
			if (Input::GetInstance()->TriggerKey(DIK_SPACE))
			{
				if (arrowDirection == 0)
				{
					attackArrowY = 576;
					arrowDirection = -5;
				}
				else
				{
					arrowDirection = 0;
					playerAttackTurn--;
					if (attackGaugeLain >= 0 && attackGaugeLain <= 106)
					{
						playerHPPoint_--;
					}
					if (attackGaugeLain >= 107 && attackGaugeLain <= 159)
					{
						enemyHPPoint_--;
					}
					if (attackGaugeLain >= 160 && attackGaugeLain <= 210)
					{
						enemyHPPoint_ = enemyHPPoint_ -= attackGauge2;
					}
					if (attackGaugeLain >= 211 && attackGaugeLain <= 262)
					{
						enemyHPPoint_ = enemyHPPoint_ -= attackGauge3;
						playerHPPoint_--;
					}
					if (attackGaugeLain >= 263 && attackGaugeLain <= 315)
					{
						enemyHPPoint_ = enemyHPPoint_ -= attackGauge2;
					}
					if (attackGaugeLain >= 316 && attackGaugeLain <= 367)
					{
						enemyHPPoint_--;
					}
					if (attackGaugeLain >= 368 && attackGaugeLain <= 576)
					{
						playerHPPoint_--;
					}
				}
			}

			//ネクストステージ
			if (stageEnemy1 == 1 && enemyHPPoint_ <= 0)
			{
				stageEnemy2 = 1;
				playerHPPoint_ = playerHPPoint_ += 1;
				enemyHPPoint_ = 5;
				playerAttackTurn = 3;
				stageEnemy1 = 0;
			}
			// ネクストステージ
			if (stageEnemy2 == 1 && enemyHPPoint_ <= 0)
			{
				stageEnemy3 = 1;
				playerHPPoint_ = playerHPPoint_ += 1;
				enemyHPPoint_ = 5;
				playerAttackTurn = 3;
				stageEnemy2 = 0;
			}
			//ゲームクリアへ
			if (stageEnemy3 == 1 && enemyHPPoint_ <= 0)
			{
				gameClear = 1;
				stageEnemy3 = 0;
			}
			// ゲームオーバーへ
			if (playerHPPoint_ <= 0)
			{
				stageEnemy1 = 0;
				stageEnemy2 = 0;
				stageEnemy3 = 0;
				gameOver = 1;
			}
			// ゲームオーバーへ
			if (playerAttackTurn == 0 && enemyHPPoint_ >= 0)
			{
				stageEnemy1 = 0;
				stageEnemy2 = 0;
				stageEnemy3 = 0;
				gameOver = 1;
			}

		}
	}
	attackArrowSprite_->SetPosition({attackArrowX, attackArrowY});
	attackGaugeLain = attackArrowY + 24;
	//自キャラの更新
	player_->Update();
	//-------------------------------------------------

	//敵キャラ-----------------------------------------
	enemy_->Update();





	//デバッグカメラの更新
	//debugCamera_->Update();

	camera_.translation_ = Vector3(0.0f, 0.0f, -10.0f);
	camera_.UpdateMatrix();
}

// 描画
void GameScene::Draw()
{

	if (gameRuruScene == 1)
	{
		// スプライト描画前処理
		Sprite::PreDraw();

		gameRuruSprite_->Draw();

		// スプライト描画後処理
		Sprite::PostDraw();
	}

	if (stageEnemy1 == 1 || stageEnemy2 == 1 || stageEnemy3 == 1)
	{
		// 3Dモデル描画前処理---------------
		Model::PreDraw();

		////自キャラの描画
		player_->Draw();

		// 敵キャラの描画
		enemy_->Draw();

		// 3Dモデル描画後処理---------------
		Model::PostDraw();

		// スプライト描画前処理
		Sprite::PreDraw();

		// 攻撃ゲージ
		attackSprite_->Draw();
		attackArrowSprite_->Draw();

		// プレイヤーHP分だけ描画する
		for (int i = 0; i < playerHPPoint_; i++)
		{
			hearts_[i]->Draw();
		}

		// 敵ハートは常に全描画
		for (int i = 0; i < enemyHPPoint_; i++)
		{
			enemyHearts_[i]->Draw();
		}

		// スプライト描画後処理
		Sprite::PostDraw();
	}

}

// デストラクタ
GameScene::~GameScene()
{

	//自機------------------------------------------------------
	

	// 生成したスプライトを解放
	for (auto& heart : hearts_)
	{
		delete heart;
	}
	hearts_.clear(); // ベクターの中身（ポインタの参照）を削除

	//自キャラの解放
	delete player_;
	//モデル解放
	delete modelPlayer_;

	//-----------------------------------------------------------

	delete attackSprite_;
	delete attackArrowSprite_;
	delete gameRuruSprite_;

	//敵---------------------------------------------------------

	//敵キャラの解放
	delete enemy_;
	delete modelEnemy_;


	//-----------------------------------------------------------

	//デバッグカメラ
	//delete debugCamera_;

	// 生成したスプライトを解放
	for (auto& enemyHeart : hearts_)
	{
		delete enemyHeart;
	}
	enemyHearts_.clear(); // ベクターの中身（ポインタの参照）を削除

}
