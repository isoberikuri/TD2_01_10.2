#include "GameScene.h"

// 初期化
void GameScene::Initialize() {
	//ファイル名を指定してテクスチャハンドルを読み込む
	textureHandle_ = TextureManager::Load("ha-to.png");

	// 複数のスプライトを生成
	for (int i = 0; i < 5; i++) {
		// X座標を少しずつずらして配置
		Sprite* heart = Sprite::Create(textureHandle_, {500.0f + i * 55.0f, 400.0f});
		hearts_.push_back(heart);
	}


}

// 更新
void GameScene::Update() {}

// 描画
void GameScene::Draw() {
	//スプライト描画前処理
	Sprite::PreDraw();

	// 複数のスプライトを描画
	for (auto& heart : hearts_) {
		heart->Draw();
	}

	//スプライト描画後処理
	Sprite::PostDraw();


}

// デストラクタ
GameScene::~GameScene() {
	// 生成したスプライトを解放
	for (auto& heart : hearts_) {
		delete heart;
	}
	hearts_.clear(); // ベクターの中身（ポインタの参照）を削除

}
