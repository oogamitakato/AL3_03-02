#include "DxLib.h"
#include<math.h>

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "AL4_03_02b";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 400;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	float circleX = 400.0f;
	float circleY = 100.0f;
	float radius = 20.0f;

	float lineStartX = 100.0f;
	float lineStartY = 200.0f;
	float lineEndX = 400.0f;
	float lineEndY = 300.0f;
	float cross = 0.0f;
	VECTOR vec_line,vec_circle;
	bool isHit = false;
	int color;
		
	//float vec_line_val;
	//float vec_circle_val;
	//float angle;
	//float dot = 0.0f;

	// 最新のキーボード情報用
	char keys[256] = {0};

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = {0};

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		if (keys[KEY_INPUT_A]) {
			circleX -= 4;
		}
		if (keys[KEY_INPUT_D]) {
			circleX += 4;
		}
		if (keys[KEY_INPUT_W]) {
			circleY -= 4;
		}
		if (keys[KEY_INPUT_S]) {
			circleY += 4;
		}

		vec_line = VGet(lineEndX - lineStartX, lineEndY - lineStartY, 0.0f);
		vec_line = VNorm(vec_line);

		vec_circle = VGet(circleX - lineStartX, circleY - lineStartY, 0.0f);

		//vec_line_val = sqrt(pow(vec_line.x, 2) + pow(vec_line.y, 2));
		//vec_circle_val = sqrt(pow(vec_circle.x, 2) + pow(vec_circle.y, 2));
		//angle = (vec_line_val * vec_circle_val) / ()
		//dot = vec_line.x * vec_line.y + vec_circle.x * vec_circle.y;

		isHit = false;
		//当たり判定
		if (circleX >= lineStartX && circleX < lineEndX) {
			// 外積を計算
			cross = vec_line.x * vec_circle.y - vec_line.y * vec_circle.x;

			if (cross > -radius && cross < radius) {
				isHit = true;
			}
			else {
				isHit = false;
			}
		}
		else {

			if (pow(circleX - lineStartX, 2) + pow(circleY - lineStartY, 2) <= radius * radius) {
				isHit = true;
			}

			if (pow(circleX - lineEndX, 2) + pow(circleY - lineEndY, 2) <= radius * radius) {
				isHit = true;
			}
		}

		if (isHit == true) {
			color = GetColor(255, 0, 0);
		}
		else {
			color = GetColor(255, 255, 255);
		}

		// 描画処理
		DrawCircle(circleX, circleY, radius, color, true);
		DrawLine(lineStartX, lineStartY, lineEndX, lineEndY, GetColor(255, 255, 255));

		DrawFormatString(0, 0, GetColor(255, 255, 255), "WASD : 移動");
	
		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
