#include "GameScene.h"

// 初期化
void GameScene::Initialize()
{
	// シーン初期化
	titleScene = true;
	if (stageEnemy1 == 1)
	{
		playerHP_ = 7;
	}

	//-------------------------------
	// 自機のHPハート設定
	//-------------------------------

	// プレイヤーのハート画像を読み込み
	hatoHandle_ = TextureManager::Load("ha-to.png");

	// 複数のスプライトを生成
	for (int i = 0; i < playerHPPoint_; i++)
	{
		// X座標を少しずつずらして横に配置
		Sprite* heart = Sprite::Create(hatoHandle_, {300.0f + i * 55.0f, 660.0f});
		hearts_.push_back(heart);
	}

	//-------------------------------
	// 敵のHPハート設定
	//-------------------------------

	// 敵ハート画像を読み込み
	ehatoHadle_ = TextureManager::Load("Eha-to.png");

	// 敵ハートを5個生成して上部に並べる
	for (int i = 0; i < enemyHPPoint_; i++)
	{
		Sprite* enemyHeart = Sprite::Create(ehatoHadle_, {1000.0f + i * 55.0f, 10.0f});
		enemyHearts_.push_back(enemyHeart);
	}

	// HPの初期値（ハートの数で設定）
	playerHP_ = static_cast<int>(hearts_.size());
	enemyHP_ = static_cast<int>(enemyHearts_.size());

	//-------------------------------
	// プレイヤー設定
	//-------------------------------

	// 3Dモデルの読み込み
	modelPlayer_ = Model::CreateFromOBJ("suraimu");

	// プレイヤーオブジェクト生成
	player_ = new Player();

	// モデルとカメラを渡して初期化
	player_->Initialize(modelPlayer_, &camera_);

	//-------------------------------------

	//-------------------------------
	// 攻撃ゲージの設定
	//-------------------------------

	// 攻撃ゲージ本体の画像読み込み
	attackHandle_ = TextureManager::Load("geegiBer.png");
	attackSprite_ = Sprite::Create(attackHandle_, {0, 0});

	// 攻撃ゲージ上を動く矢印画像読み込み
	attackArrowHandle_ = TextureManager::Load("RighAttackArrow.png");
	attackArrowSprite_ = Sprite::Create(attackArrowHandle_, {attackArrowX, attackArrowY});

	//タイトル
	gameTitleHandle_ = TextureManager::Load("TD2_GameTitle.png");
	gameTitleSprite_ = Sprite::Create(gameTitleHandle_, {0, 0});

	// ルール説明
	gameRuruHandle_ = TextureManager::Load("TD2_GameRuru1.png");
	gameRuruSprite_ = Sprite::Create(gameRuruHandle_, {0, 0});

	//ゲームクリア
	gameClearHandle_ = TextureManager::Load("TD2_GameClear1.png");
	gameClearSprite_ = Sprite::Create(gameClearHandle_, {0, 0});

	//// ゲームオーバ
	gameOverHandle_ = TextureManager::Load("TD2_GameOver1.png");
	gameOverSprite_ = Sprite::Create(gameOverHandle_, {0, 0});



	//-------------------------------
	// カメラ設定
	//-------------------------------
	camera_.Initialize();

	//-------------------------------
	// 敵キャラ設定
	//-------------------------------

	enemyModel1_ = Model::CreateFromOBJ("otama");    // ステージ1オタマジャクシ
	enemyModel2_ = Model::CreateFromOBJ("kame"); // ステージ2亀
	//enemyModel3_ = Model::CreateFromOBJ("wani");  // ステージ3ワニ

	// 敵3Dモデル読み込み
	modelEnemy_ = enemyModel1_;

	// 敵オブジェクト生成
	enemy_ = new Enemy();

	// モデルとカメラを渡して初期化
	enemy_->Initialize(modelEnemy_, &camera_);

	//-------------------------------
	// 攻撃ターン初期値
	//-------------------------------
	playerAttackTurn = 3;
	//-------------------------------
	// 攻撃種類
	//-------------------------------
	// とげ攻撃
	// 3Dモデル読み込み
	modelToge_ = Model::CreateFromOBJ("toge");

	toge_ = new Toge();

	toge_->Initialize(modelToge_, &camera_);
	// 雷攻撃
	//  3Dモデル読み込み
	modelKami_ = Model::CreateFromOBJ("kaminari");

	kami_ = new Kaminari();
	kami_->Initialize(modelKami_, &camera_);

	// 3Dモデル読み込み
	modelBeam_ = Model::CreateFromOBJ("beam");

	// ビーム攻撃
	beam_ = new Beam();
	beam_->Initialize(modelBeam_, &camera_);

	// サウンドデータの読み込み
	soundTitleHandle_ = Audio::GetInstance()->LoadWave("Title.mp3");
	soundGameHandle_ = Audio::GetInstance()->LoadWave("toge.mp3");
	soundClearHandle_ = Audio::GetInstance()->LoadWave("beam.mp3");
	soundOverHandle_ = Audio::GetInstance()->LoadWave("kaminari.mp3");

	//音声再生
	voiceTitleHandle_ = Audio::GetInstance()->PlayWave(soundTitleHandle_, true);


	//効果音
	soundBotanHandle_ = Audio::GetInstance()->LoadWave("botan.mp3");
	soundTogeHandle_ = Audio::GetInstance()->LoadWave("toge.mp3");
	soundBeamHandle_ = Audio::GetInstance()->LoadWave("beam.mp3");
	soundKamiHandle_ = Audio::GetInstance()->LoadWave("kaminari.mp3");
}

bool canPress = true;

void GameScene::Update() {
	//==================================================
	// 更新処理
	//==================================================
	
	// タイトルシーン
	if (titleScene == 1)
	{
		
		gameTitleSprite_->SetPosition({0, 0});
		if (Input::GetInstance()->TriggerKey(DIK_RETURN))
		{
			canPress = false; // 一時的に無効化
			titleScene = 0;
			gameClear = 0;
			gameOver = 0;
			gameRuruScene = 1;
			//音声停止
			Audio::GetInstance()->StopWave(voiceTitleHandle_);

			// 音声再生
			Audio::GetInstance()->PlayWave(soundBotanHandle_);
		}
	}

	// ルール説明
	else if (gameRuruScene == 1)
	{
		
		gameRuruSprite_->SetPosition({0, 0});
		if (Input::GetInstance()->TriggerKey(DIK_RETURN))
		{
			gameRuruScene = 0;
			stageEnemy1 = 1;
			playerHPPoint_ = 5;
			enemyHPPoint_ = 5;
			// 音声再生
			Audio::GetInstance()->PlayWave(soundBotanHandle_);
		}
	}

	// ステージ
	if (stageEnemy1 == 1 || stageEnemy2 == 1 || stageEnemy3 == 1 )
	{
		// voiceStageHandle_ = Audio::GetInstance()->PlayWave(stageBgmHandle_, true);
		// 自キャラ------------------------------------------
		//  スペースキーが押された瞬間に HP を1減らす
		if (playerAttackTurn > 0)
		{
			attackArrowY += arrowDirection * 2; // 上下移動のスピード（2ピクセル）

			//------------------------------------------
			// スペースキーで攻撃判定
			//------------------------------------------
			if (delayTimerPoint == 0)
			{
				if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
					// 一時停止 → 攻撃判定処理
					if (arrowDirection == 0) {
						// 動きを再開（上方向へ）
						attackArrowY = 576;
						arrowDirection = -5;
					} else {
						// 矢印の動きを止めて攻撃処理実行
						arrowDirection = 0;

						// 攻撃ターンを1消費
						playerAttackTurn--;

						// 矢印位置（攻撃ゲージライン）で攻撃の強さを決定
						if (attackGaugeLain >= 0 && attackGaugeLain <= 106) {
							playerHPPoint_--;    // ミス（自分にダメージ）
							player_->OnDamage(); // ★ ダメージリアクション発動！
							StartCameraShake();
						}
						if (attackGaugeLain >= 107 && attackGaugeLain <= 159) {
							enemyHPPoint_--;     // 弱攻撃
							player_->OnAttack(); // ★ 攻撃モーション発動！
							enemy_->OnDamage();
							// ★ ビーム発射！
							Vector3 startPos = player_->GetWorldTransform().translation_;
							startPos.x += 8.0f; // 自機前に出す
							beam_->Activate(startPos);
							// 音声再生
							Audio::GetInstance()->PlayWave(soundBeamHandle_);
						}
						if (attackGaugeLain >= 160 && attackGaugeLain <= 210) {
							enemyHPPoint_ -= attackGauge2; // 中攻撃
							player_->OnAttack();           // ★ 攻撃モーション発動！
							enemy_->OnDamage();
							toge_->Start(enemy_->GetWorldPosition()); // 敵の下からとげ出現！
							// 音声再生
							Audio::GetInstance()->PlayWave(soundTogeHandle_);
						}
						if (attackGaugeLain >= 211 && attackGaugeLain <= 262) {
							enemyHPPoint_ -= attackGauge3; // 強攻撃
							playerHPPoint_--;
							player_->OnAttack(); // ★ 攻撃モーション発動！
							enemy_->OnDamage();
							StartCameraShake();
							kami_->Start(enemy_->GetWorldPosition()); // 敵の上から雷が落ちる！
							// 音声再生
							Audio::GetInstance()->PlayWave(soundKamiHandle_);
						}
						if (attackGaugeLain >= 263 && attackGaugeLain <= 315) {
							enemyHPPoint_ -= attackGauge2; // 中攻撃
							player_->OnAttack();           // ★ 攻撃モーション発動！
							enemy_->OnDamage();
							toge_->Start(enemy_->GetWorldPosition()); // 敵の下からとげ出現！
							// 音声再生
							Audio::GetInstance()->PlayWave(soundTogeHandle_);
						}
						if (attackGaugeLain >= 316 && attackGaugeLain <= 367) {
							enemyHPPoint_--;     // 弱攻撃
							player_->OnAttack(); // ★ 攻撃モーション発動！
							enemy_->OnDamage();
							// ★ ビーム発射！
							Vector3 startPos = player_->GetWorldTransform().translation_;
							startPos.x += 8.0f; // 自機前に出す
							beam_->Activate(startPos);
							// 音声再生
							Audio::GetInstance()->PlayWave(soundBeamHandle_);
						}
						if (attackGaugeLain >= 368 && attackGaugeLain <= 576) {
							playerHPPoint_--;    // ミス（自分にダメージ）
							player_->OnDamage(); // ★ ダメージリアクション発動！
							StartCameraShake();
						}
					}
				}
			}
			

			// ネクストステージ
			if (stageEnemy1 == 1 && enemyHPPoint_ <= 0)
			{
				delayTimerPoint = 1;
				if (delayTimerPoint == 1)
				{
					delayTimer--;
				}
				if (delayTimer <= 0)
				{
					delayTimerPoint = 0;
					delayTimer = 150;
					stageEnemy2 = 1;
					playerHPPoint_ += 1;
					enemyHPPoint_ = 5;
					playerAttackTurn = 3;
					stageEnemy1 = 0;
					enemy_->Initialize(enemyModel2_, &camera_);
				}
				/*stageEnemy2 = 1;
				playerHPPoint_ += 1;
				enemyHPPoint_ = 5;
				playerAttackTurn = 3;
				stageEnemy1 = 0;
				enemy_->Initialize(enemyModel2_, &camera_); */
			}
			// ネクストステージ
			if (stageEnemy2 == 1 && enemyHPPoint_ <= 0)
			{
				delayTimerPoint = 1;
				if (delayTimerPoint == 1)
				{
					delayTimer--;
				}
				if (delayTimer <= 0)
				{
					delayTimerPoint = 0;
					delayTimer = 150;
					stageEnemy3 = 1;
					playerHPPoint_ += 1;
					enemyHPPoint_ = 5;
					playerAttackTurn = 3;
					stageEnemy2 = 0;
				}
				/*stageEnemy3 = 1;
				playerHPPoint_ += 1;
				enemyHPPoint_ = 5;
				playerAttackTurn = 3;
				stageEnemy2 = 0;*/
				
			}
			// ゲームクリアへ
			if (stageEnemy3 == 1 && enemyHPPoint_ <= 0)
			{
				gameClearSprite_->SetPosition({0, 0});
				gameClear = 1;
				gameOver = 0;
				stageEnemy3 = 0;
			}
			// ゲームオーバーへ
			if (delayTimerPoint == 0)
			{
				if (playerHPPoint_ <= 0)
				{
					stageEnemy1 = 0;
					stageEnemy2 = 0;
					stageEnemy3 = 0;
					gameClear = 0;
					gameOver = 1;
				}
			}
			
		}
		// ゲームオーバーへ
		if (delayTimerPoint == 0)
		{
			if (playerAttackTurn == 0 && enemyHPPoint_ >= 0)
			{
				stageEnemy1 = 0;
				stageEnemy2 = 0;
				stageEnemy3 = 0;
				gameClear = 0;
				gameOver = 1;
			}
		}
		
	}



	if (gameClear == 1) {

		if (Input::GetInstance()->TriggerKey(DIK_RETURN))
		{
			// 全リセット ------------------------
			titleScene = 1;
			gameClear = 0;

			stageEnemy1 = 0;
			stageEnemy2 = 0;
			stageEnemy3 = 0;

			playerHPPoint_ = 5;
			enemyHPPoint_ = 5;
			playerAttackTurn = 3;

			attackArrowY = 576 - 32; // 矢印位置リセット
			arrowDirection = -5;

			// 敵をステージ1へ戻す
			player_->Initialize(modelPlayer_, &camera_);
			enemy_->Initialize(enemyModel1_, &camera_);
		}
	}

	//===============================
	// ゲームオーバー後：ENTERでタイトルへ
	//===============================
	if (gameOver == 1)
	{

		if (Input::GetInstance()->TriggerKey(DIK_RETURN))
		{
			// 全リセット ------------------------
			titleScene = 1;
			gameOver = 0;

			stageEnemy1 = 0;
			stageEnemy2 = 0;
			stageEnemy3 = 0;

			playerHPPoint_ = 5;
			enemyHPPoint_ = 5;
			playerAttackTurn = 3;

			attackArrowY = 576 - 32; // 矢印位置リセット
			arrowDirection = -5;

			// 敵をステージ1へ戻す
			player_->Initialize(modelPlayer_, &camera_);
			enemy_->Initialize(enemyModel1_, &camera_);
		}
	}

	// 矢印スプライトの座標を更新
	attackArrowSprite_->SetPosition({attackArrowX, attackArrowY});

	// 攻撃ゲージライン位置を更新
	attackGaugeLain = attackArrowY + 24;
	//------------------------------------------
	// プレイヤー・敵の更新処理
	//------------------------------------------
	player_->Update();
	enemy_->Update();

	//------------------------------------------
	// 攻撃の更新処理
	//------------------------------------------
	toge_->Update();
	kami_->Update();
	beam_->Update();

	//------------------------------------------

	//------------------------------------------
	// カメラ更新
	//------------------------------------------
	camera_.translation_ = Vector3(0.0f, 0.0f, -10.0f);
	camera_.UpdateMatrix();

	if (isCameraShaking_) {
		cameraShakeTimer_--;
		camera_.translation_.x = defaultCameraPos_.x + (rand() % 100 / 100.0f - 0.5f) * cameraShakePower_;
		camera_.translation_.y = defaultCameraPos_.y + (rand() % 100 / 100.0f - 0.5f) * cameraShakePower_;

		if (cameraShakeTimer_ <= 0)
		{
			isCameraShaking_ = false;
			camera_.translation_ = defaultCameraPos_;
		}
	}
	else
	{
		camera_.translation_ = defaultCameraPos_;
	}
	camera_.UpdateMatrix();

	playerHPPoint_ = std::clamp(playerHPPoint_, 0, (int)hearts_.size());
	enemyHPPoint_ = std::clamp(enemyHPPoint_, 0, (int)enemyHearts_.size());
}

//==================================================
// 描画処理
//==================================================
void GameScene::Draw()
{

	if (titleScene == 1)
	{
		Sprite::PreDraw();
		gameTitleSprite_->Draw();
		// スプライト描画後処理
		Sprite::PostDraw();
	}

	if (gameRuruScene == 1)
	{
		// スプライト描画前処理
		Sprite::PreDraw();
		gameRuruSprite_->Draw();
		// スプライト描画後処理
		Sprite::PostDraw();
	}
	// ゲームクリア描画
	if (gameClear == 1)
	{
		Sprite::PreDraw();
		gameClearSprite_->Draw();
		Sprite::PostDraw();
	}
	// ゲームオーバー描画
	if (gameOver == 1)
	{
		Sprite::PreDraw();
		gameOverSprite_->Draw();
		Sprite::PostDraw();
	}


	if (stageEnemy1 == 1 || stageEnemy2 == 1 || stageEnemy3 == 1)
	{
		//------------------------------------------
		// 3Dモデル描画
		//------------------------------------------
		Model::PreDraw();

		player_->Draw(); // プレイヤー
		enemy_->Draw();  // 敵
		toge_->Draw();   // とげ攻撃
		kami_->Draw();   // 雷攻撃
		beam_->Draw();   // ビーム攻撃

		Model::PostDraw();

		//------------------------------------------
		// 2Dスプライト描画
		//------------------------------------------
		Sprite::PreDraw();

		// 攻撃ゲージと矢印を描画
		attackSprite_->Draw();
		attackArrowSprite_->Draw();

		int pMax = (int)hearts_.size();
		int eMax = (int)enemyHearts_.size();

		int pDraw = std::clamp(playerHPPoint_, 0, pMax);
		int eDraw = std::clamp(enemyHPPoint_, 0, eMax);


		// プレイヤーの残りHP分ハートを描画
		for (int i = 0; i < pDraw; i++)
		{
			hearts_[i]->Draw();
		}

		// 敵の残りHP分ハートを描画
		for (int i = 0; i < eDraw; i++)
		{
			enemyHearts_[i]->Draw();
		}

		// スプライト描画後処理
		Sprite::PostDraw();
	}
}

//==================================================
// デストラクタ（終了処理）
//==================================================
GameScene::~GameScene()
{

	//------------------------------------------
	// プレイヤー関連の解放
	//------------------------------------------
	for (auto& heart : hearts_)
	{
		delete heart;
	}
	hearts_.clear();

	delete player_;
	delete modelPlayer_;

	delete attackSprite_;
	delete attackArrowSprite_;
	delete gameRuruSprite_;
	delete gameTitleSprite_;

	//------------------------------------------
	// 敵関連の解放
	//------------------------------------------
	delete enemy_;
	
	delete enemyModel1_;
	delete enemyModel2_;
	delete enemyModel3_;

	for (auto& enemyHeart : enemyHearts_)
	{
		delete enemyHeart;
	}
	enemyHearts_.clear();

	//------------------------------------------
	// 攻撃の解放
	//------------------------------------------
	// とげ攻撃
	delete toge_;
	delete modelToge_;

	// 雷攻撃
	delete kami_;
	delete modelKami_;

	// ビーム攻撃

	delete modelBeam_;

	//------------------------------------------
	// （デバッグカメラは未使用）
	//------------------------------------------
	// delete debugCamera_;
}

void GameScene::StartCameraShake()
{
	isCameraShaking_ = true;
	cameraShakeTimer_ = 30;   // 揺れるフレーム数
	cameraShakePower_ = 0.1f; // 揺れの強さ
}