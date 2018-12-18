//=============================================================================
//
// タイトル画面処理 [GameStart.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "gamestart.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexGameStart(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureGameStart = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		D3DTextureGameStartLogo = NULL;	// テクスチャへのポインタ

VERTEX_2D				vertexWkGameStart[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				vertexWkGameStartLogo[NUM_VERTEX];		// 頂点情報格納ワーク

static VERTEX_2D				vertexWkpushLogo[NUM_VERTEX];		// 頂点情報格納ワーク
static LPDIRECT3DTEXTURE9		D3DTexturepushLogo = NULL;	// テクスチャへのポインタ
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGameStart(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,						// デバイスへのポインタ
		TEXTURE_GAME_START,									// ファイルの名前
		&D3DTextureGameStart);								// 読み込むメモリー

	D3DXCreateTextureFromFile(Device,						// デバイスへのポインタ
		TEXTURE_GAME_START_LOGO,							// ファイルの名前
		&D3DTextureGameStartLogo);							// 読み込むメモリー

	D3DXCreateTextureFromFile(Device,						// デバイスへのポインタ
		TEXTURE_PUSH_LOGO,									// ファイルの名前
		&D3DTexturepushLogo);								// 読み込むメモリー

	MakeVertexGameStart();									// 頂点情報の作成

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGameStart(void)
{
	if (D3DTextureGameStart != NULL)
	{// テクスチャの開放
		D3DTextureGameStart->Release();
		D3DTextureGameStart = NULL;
	}

	if (D3DTextureGameStartLogo != NULL)
	{// テクスチャの開放
		D3DTextureGameStartLogo->Release();
		D3DTextureGameStartLogo = NULL;
	}

	if (D3DTexturepushLogo != NULL)
	{// テクスチャの開放
		D3DTexturepushLogo->Release();
		D3DTexturepushLogo = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGameStart(void)
{
		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter押したら、ステージを切り替える
			SetStage(STAGE_GAME);
		}
		// ゲームパッドで移動処理
		else if (IsButtonRepeat(0, BUTTON_START))
		{
			SetStage(STAGE_GAME);
		}
		else if (IsButtonRepeat(0, BUTTON_B))
		{
			SetStage(STAGE_GAME);
		}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGameStart(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTextureGameStart);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkGameStart, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTextureGameStartLogo);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkGameStartLogo, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTexturepushLogo);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkpushLogo, sizeof(VERTEX_2D));

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexGameStart(void)
{

	// 頂点座標の設定
	vertexWkGameStart[0].vtx = D3DXVECTOR3(GAMESTART_POS_X, GAMESTART_POS_Y, 0.0f);
	vertexWkGameStart[1].vtx = D3DXVECTOR3(GAMESTART_POS_X + GAMESTART_SIZE_X, GAMESTART_POS_Y, 0.0f);
	vertexWkGameStart[2].vtx = D3DXVECTOR3(GAMESTART_POS_X, GAMESTART_POS_Y + GAMESTART_SIZE_Y, 0.0f);
	vertexWkGameStart[3].vtx = D3DXVECTOR3(GAMESTART_POS_X + GAMESTART_SIZE_X, GAMESTART_POS_Y + GAMESTART_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkGameStart[0].rhw =
	vertexWkGameStart[1].rhw =
	vertexWkGameStart[2].rhw =
	vertexWkGameStart[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkGameStart[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameStart[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameStart[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameStart[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkGameStart[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkGameStart[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkGameStart[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkGameStart[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	vertexWkGameStartLogo[0].vtx = D3DXVECTOR3(GAMESTARTLOGO_POS_X, GAMESTARTLOGO_POS_Y, 0.0f);
	vertexWkGameStartLogo[1].vtx = D3DXVECTOR3(GAMESTARTLOGO_POS_X + GAMESTARTLOGO_SIZE_X, GAMESTARTLOGO_POS_Y, 0.0f);
	vertexWkGameStartLogo[2].vtx = D3DXVECTOR3(GAMESTARTLOGO_POS_X, GAMESTARTLOGO_POS_Y + GAMESTARTLOGO_SIZE_Y, 0.0f);
	vertexWkGameStartLogo[3].vtx = D3DXVECTOR3(GAMESTARTLOGO_POS_X + GAMESTARTLOGO_SIZE_X, GAMESTARTLOGO_POS_Y + GAMESTARTLOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkGameStartLogo[0].rhw =
	vertexWkGameStartLogo[1].rhw =
	vertexWkGameStartLogo[2].rhw =
	vertexWkGameStartLogo[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkGameStartLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameStartLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameStartLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameStartLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkGameStartLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkGameStartLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkGameStartLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkGameStartLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点座標の設定
	vertexWkpushLogo[0].vtx = D3DXVECTOR3(PUSHLOGO_POS_X, PUSHLOGO_POS_Y, 0.0f);
	vertexWkpushLogo[1].vtx = D3DXVECTOR3(PUSHLOGO_POS_X + PUSHLOGO_SIZE_X, PUSHLOGO_POS_Y, 0.0f);
	vertexWkpushLogo[2].vtx = D3DXVECTOR3(PUSHLOGO_POS_X, PUSHLOGO_POS_Y + PUSHLOGO_SIZE_Y, 0.0f);
	vertexWkpushLogo[3].vtx = D3DXVECTOR3(PUSHLOGO_POS_X + PUSHLOGO_SIZE_X, PUSHLOGO_POS_Y + PUSHLOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkpushLogo[0].rhw =
	vertexWkpushLogo[1].rhw =
	vertexWkpushLogo[2].rhw =
	vertexWkpushLogo[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkpushLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkpushLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkpushLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkpushLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkpushLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkpushLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkpushLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkpushLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
