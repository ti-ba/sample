//=============================================================================
//
// Main処理 [main.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "enemy2.h"
#include "boss.h"
#include "bullet.h"
#include "bg.h"
#include "title.h"
#include "curea.h"
#include "score.h"
#include "sound.h"
#include <time.h>
#include "enemybullet.h"
#include "guage.h"
#include "enemyguage.h"
#include "tyutogeme.h"
#include "nakami.h"
#include "gamestart.h"
#include "tyutoenemy.h"
#include "gameover.h"
#include "bom.h"
#include "bomguage.h"
#include "effect.h"
#include "effect2.h"
#include "bossbullet.h"
#include "bossguage.h"
#include "enemyguage2.h"
#include "enemybullet2.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			_T("AppClass")			// ウインドウのクラス名
#define WINDOW_NAME			_T("シューティングゲーム")		// ウインドウのキャプション名
#define SAFE_RELEASE(ptr)
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

#ifdef _DEBUG
void DrawDebugFont(void);
#endif

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9				D3D = NULL;				// Direct3Dオブジェクト
LPDIRECT3DDEVICE9		D3DDevice = NULL;		// Deviceオブジェクト(描画に必要)

#ifdef _DEBUG
LPD3DXFONT				D3DXFont = NULL;		// フォントへのポインタ
int						CountFPS;				// FPSカウンタ
#endif

int						Stage =3;				// タイトル画面

LPDIRECTSOUNDBUFFER8	BGM;					// BGM用バッファ
//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

											// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,											// ウィンドウの左座標
		CW_USEDEFAULT,											// ウィンドウの上座標
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,		// ウィンドウ横幅
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
		NULL,
		NULL,
		hInstance,
		NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if (FAILED(Init(hWnd, true)))
	{
		return -1;
	}

	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;

	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();			// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
#ifdef _DEBUG
				CountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	// FPSを測定
#endif
				dwFPSLastTime = dwCurrentTime;		// FPSを測定した時刻を保存
				dwFrameCount = 0;					// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;		// 処理した時刻を保存

				Update();			// 更新処理
				Draw();				// 描画処理

				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	// Direct3Dオブジェクトの作成
	D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (D3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));			// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;					// バックバッファの数
	d3dpp.BackBufferWidth =  SCREEN_WIDTH;		// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed = bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;		// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// デプスバッファとして16bitを使う
	d3dpp.BackBufferFormat = d3ddm.Format;		// カラーモードの指定

	if (bWindow)
	{// ウィンドウモード
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;						// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;							// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(D3D->CreateDevice(D3DADAPTER_DEFAULT,		// ディスプレイアダプタ
		D3DDEVTYPE_HAL,								// ディスプレイタイプ
		hWnd,										// フォーカスするウインドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,		// デバイス作成制御の組み合わせ
		&d3dpp,										// デバイスのプレゼンテーションパラメータ
		&D3DDevice)))								// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(D3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&D3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(D3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&D3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダリングステートパラメータの設定
	D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// カリングを行わない
	D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// αブレンドを行う
	D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャＵ値の繰り返し設定
	D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャＶ値の繰り返し設定
	D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大時の補間設定
	D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小時の補間設定

#ifdef _DEBUG
	// 情報表示用フォントを設定
	D3DXCreateFont(D3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &D3DXFont);
#endif

	// サウンド初期化
	InitSound(hWnd);
	SAFE_RELEASE(BGM);
	// ロードと再生
	BGM = LoadSound(BGM_01);
	PlaySound(BGM, E_DS8_FLAG_LOOP);


	// プレイヤーの初期化処理
	InitPlayer(0);

	// エネミーの初期化処理
	InitEnemy(0);

	// エネミーの初期化
	//InitEnemy2(0);

	// ボスの初期化
	InitBoss(0);

	// ボスゲージの初期化
	InitBossguage(0);

	// バレットの初期化処理
	InitBullet(0);

	InitBossBullet(0);

	InitEnemyBullet2(0);

	// ボムの初期化
	InitBom(0);

	// ボムのゲージ初期化
	InitBomGuage(0);

	// BG初期化
	InitBG(0);

	// タイトル初期化
	InitTitle();

	// ゲームタイトル初期化
	InitGameStart();

	// クリア初期化
	InitCurea();

	// ゲームオーバー初期化
	InitGameover();

	// スコア初期化
	InitScore(0);

	// 敵の弾の初期化
	InitEnemyBullet(0);

	// ボスの弾
	InitBossBullet(0);

	// ゲージ初期化
	InitGuage(0);

	// エネミーゲージ初期化
	InitEnemyGuage(0);

	// エネミーゲージ２初期化
	InitEnemyGuage2(0);

	// チュートエネミー初期化
	InitTyutoEnemy(0);

	// チュートゲーム初期化
	InitTyutoGame( hWnd,  bWindow);

	// エフェクト初期化
	InitEffect(0);

	// エフェクト２初期化
	InitEffect2(0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// 入力処理の終了処理
	UninitInput();

	// プレイヤーの終了処理
	//UninitPlayer();

	// エネミーの終了処理
	UninitEnemy();

	// エネミーの終了処理
	//UninitEnemy2();

	// ボスの終了処理
	//UninitBoss();

	// ボスゲージの終了処理
	UninitBossguage();

	// ボスの弾の終了処理
	UninitBossBullet();

	// バレットの終了処理
	UninitBullet();

	//ボムの終了処理
	UninitBom();

	//ボムのゲージの終了処理
	UninitBomGuage();

	// BG終了処理
	UninitBG();

	// タイトル終了処理
	UninitTitle();

	// ゲームタイトル終了処理
	UninitGameStart();

	// クリア終了処理
	UninitCurea();

	//ゲームオーバー終了処理
	UninitGameover();

	// スコア終了処理
	UninitScore();

	// 敵の弾終了処理
	UninitEnemyBullet();

	//ゲージ終了処理
	UninitGuage();

	//エネミーゲージ終了処理
	UninitEnemyGuage();

	// エネミーゲージ２終了処理
	UninitEnemyGuage2();

	//チュートエネミー終了処理
	UninitTyutoEnemy();

	//チュートゲーム終了処理
	UninitTyutoGame();

	// エフェクト終了処理
	UninitEffect();

	// エフェクト２終了処理
	UninitEffect2();

	UninitEnemyBullet2();

	if (D3DDevice != NULL)
	{// デバイスの開放
		D3DDevice->Release();
	}

	if (D3D != NULL)
	{// Direct3Dオブジェクトの開放
		D3D->Release();
	}

	SAFE_RELEASE(BGM)
	UninitSound();
#define SAFE_RELEASE(ptr)
	
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	
	// 入力の更新処理
	UpdateInput();
	
	// 画面遷移
	switch (Stage)
	{
		// 入力の更新処理
	case STAGE_TITLE:
		UpdateTitle();
		break;

	case STAGE_TYUTO_GAME:
		UpdateTyutoGame();
		break;

	case STAGE_GAME_START:
		UpdateGameStart();
		break;

	case STAGE_GAME:	
		UpdateNakami();
		break;

	case STAGE_BOSS:
		UpdateBoss();
		break;

	case STAGE_SCORE:
		UpdateScore();
		break;

	case STAGE_CUREA:
		UpdateCurea();
		break;
		
	case STAGE_GAME_OVER:
		UpdateGameover();
		break;
	}
	

}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	D3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(D3DDevice->BeginScene()))
	{
		// 画面遷移
		switch (Stage)
		{
		case STAGE_TITLE:
			DrawTitle();
			break;

		case STAGE_TYUTO_GAME:
			DrawTyutoGame();
			break;

		case STAGE_GAME_START:
			DrawGameStart();
			break;

		case STAGE_GAME:
			DrawNakami();
			break;

		case STAGE_BOSS:
			DrawBoss();
			break;

		case STAGE_SCORE:
			DrawScore();
			break;

		case  STAGE_CUREA:
			DrawCurea();
			break;

		case STAGE_GAME_OVER:
			DrawGameover();
			break;
		}

#ifdef _DEBUG
		// デバッグ表示
		DrawDebugFont();
#endif

		// Direct3Dによる描画の終了
		D3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	D3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイス取得関数
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(D3DDevice);
}


#ifdef _DEBUG
//=============================================================================
// デバッグ表示処理
//=============================================================================
void DrawDebugFont(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	PLAYER *player = GetPlayer(0);

	// テキスト描画
	sprintf(str, _T("FPS:%d"), CountFPS);
	D3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top = 20;
	sprintf(str, "PX:%f  PY:%f", player->pos.x, player->pos.y);
	D3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

}
#endif

//=============================================================================
// 画面遷移
//=============================================================================
void SetStage(int stage)
{
	if( stage < 0 || stage >= STAGE_MAX ) return;

	Stage = stage;
}

