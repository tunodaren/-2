#include <Novice.h>
#include "Enemy.h"
#include "Player.h"

const char kWindowTitle[] = "GC1D_08_ツノダ_レン_Shooting";


enum Scene
{
	Title,
	PLAY,
	CLEAR,
	GAMEOVER
};

//void Collision(int ob1_x, int ob1_y, int ob1_r, int ob2_x, int ob2_y, int ob2_r,bool life)
//{
//	//当たり判定
//	if (ob2_x + ob2_r > ob1_x &&
//		ob2_x < ob1_x + ob1_r &&
//		ob2_y < ob1_y + ob1_r &&
//		ob2_y + ob2_r > ob1_y) 
//	{
//		life = false;
//		return ;
//	}
//
//
//}

typedef struct vector2 {
	int  x;
	int  y;
}vector2;


typedef struct  Bullet {

	vector2 Pos;
	vector2 Pos2;
	int Width;
	int Hight;
	int Speed;

	bool isShot;

}Bullet;



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Scene scene = Title;
	Enemy* enemy = new Enemy();
	Player* player = new Player();

	Bullet bullet[10];
	for (int i = 0; i < 10; i++) {
		bullet[i].Pos.x = 0;
		bullet[i].Pos.y = 0;
		bullet[i].Pos2.x = 0;
		bullet[i].Pos2.y = 0;
		bullet[i].Hight = 10;
		bullet[i].Width = 10;
		bullet[i].Speed = 10;
		bullet[i].isShot = false;
	}
	int bullet_time = 0;


	enemy->Initalize();
	player->Initalize();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		switch (scene)
		{

		case Title:


			enemy->Initalize();
			player->Initalize();

			if (preKeys[DIK_RETURN]) {
				scene = PLAY;

			}

			break;

		case PLAY:

			enemy->Update();

			player->Move(preKeys);

			for (int i = 0; i < 10; i++) {
				bullet[i].Pos2.x = bullet[i].Pos.x + bullet[i].Width;
				bullet[i].Pos2.y = bullet[i].Pos.y + bullet[i].Hight;
			}



			if (keys[DIK_SPACE]) {
				if (bullet_time < 5) {
					bullet_time++;
				}
				else
				{
					bullet_time = 0;
				}


				if (bullet_time >= 5) {
					for (int i = 0; i < 10; i++) {
						if (!bullet[i].isShot) {
							bullet[i].Pos.x = player->GetPosX();
							bullet[i].Pos.y = player->GetPosY();
							bullet[i].isShot = true;
							break;
						}
					}
				}
			}

			for (int i = 0; i < 10; i++) {
				if (bullet[i].isShot) {
		
					bullet[i].Pos.y -= bullet[i].Speed;

					if (bullet[i].Pos.y <= 0) {
						bullet[i].Pos.x = 1300;
						bullet[i].isShot = false;
					}
				}
			}
		
			for (int i = 0; i < 10; i++) {
				if (enemy->GetPosX_2() > bullet[i].Pos.x &&
					enemy->GetPosX() < bullet[i].Pos2.x &&
					enemy->GetPosY() < bullet[i].Pos2.y &&
					enemy->GetPosY_2() > bullet[i].Pos.y) {
					scene = CLEAR;
					bullet[i].isShot = false;
				}
			}

			break;

		case CLEAR:

			for (int i = 0; i < 10; i++) {
				bullet[i].isShot = false;
			}
			enemy->Initalize();
			player->Initalize();

			if (preKeys[DIK_RETURN]) {
				scene = Title;
			}

			if (keys[DIK_RETURN] && preKeys[DIK_RETURN]) {
				scene = CLEAR;
			}

			break;

		case GAMEOVER:


			enemy->Initalize();
			player->Initalize();

			if (preKeys[DIK_RETURN]) {
				scene = Title;
			}

			if (keys[DIK_RETURN] && preKeys[DIK_RETURN]) {
				scene = GAMEOVER;
			}

			break;

		default:
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		/// 
		
		switch (scene)
		{

		case Title:

			Novice::ScreenPrintf(20, 20, "Title");

			break;

		case PLAY:

			for (int i = 0; i < 10; i++) {
				if (bullet[i].isShot) {
					Novice::DrawBox(bullet[i].Pos.x, bullet[i].Pos.y, bullet[i].Width, bullet[i].Hight, 0.0f, WHITE, kFillModeSolid);
				}
			}


			enemy->Draw();
			player->Draw();

			Novice::ScreenPrintf(20, 20, "PLAY");
			Novice::ScreenPrintf(20,40,"%d = playerX",player->GetPosX());
			Novice::ScreenPrintf(20, 60, "%d = playerY", player->GetPosY());

			break;

		case CLEAR:

			Novice::ScreenPrintf(20, 20, "CLEAR");

			break;

		case GAMEOVER:

			Novice::ScreenPrintf(20, 20, "GAMEOVER");

			break;



		default:
			break;
		}
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
