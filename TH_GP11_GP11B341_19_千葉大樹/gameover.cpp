//=============================================================================
//
// タイトル画面処理 [gameover.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "gameover.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexGameover(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureGameover = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		D3DTextureGameoverLogo = NULL;	// テクスチャへのポインタ

VERTEX_2D				vertexWkGameover[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				vertexWkGameoverLogo[NUM_VERTEX];		// 頂点情報格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGameover(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,						// デバイスへのポインタ
		TEXTURE_GAMEOVER,				// ファイルの名前
		&D3DTextureGameover);		// 読み込むメモリー

	D3DXCreateTextureFromFile(Device,						// デバイスへのポインタ
		TEXTURE_GAMEOVER_LOGO,			// ファイルの名前
		&D3DTextureGameoverLogo);	// 読み込むメモリー

									// 頂点情報の作成
	MakeVertexGameover();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGameover(void)
{
	if (D3DTextureGameover != NULL)
	{// テクスチャの開放
		D3DTextureGameover->Release();
		D3DTextureGameover = NULL;
	}

	if (D3DTextureGameoverLogo != NULL)
	{// テクスチャの開放
		D3DTextureGameoverLogo->Release();
		D3DTextureGameoverLogo = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGameover(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、ステージを切り替える
		SetStage(STAGE_TITLE);
	}
	// ゲームパッドで移動処理
	else if (IsButtonRepeat(0, BUTTON_START))
	{
		SetStage(STAGE_TITLE);
	}
	else if (IsButtonRepeat(0, BUTTON_B))
	{
		SetStage(STAGE_TITLE);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGameover(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTextureGameover);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkGameover, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTextureGameoverLogo);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkGameoverLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexGameover(void)
{

	// 頂点座標の設定
	vertexWkGameover[0].vtx = D3DXVECTOR3(GAMEOVER_POS_X, GAMEOVER_POS_Y, 0.0f);
	vertexWkGameover[1].vtx = D3DXVECTOR3(GAMEOVER_POS_X + GAMEOVER_SIZE_X, GAMEOVER_POS_Y, 0.0f);
	vertexWkGameover[2].vtx = D3DXVECTOR3(GAMEOVER_POS_X, GAMEOVER_POS_Y + GAMEOVER_SIZE_Y, 0.0f);
	vertexWkGameover[3].vtx = D3DXVECTOR3(GAMEOVER_POS_X + GAMEOVER_SIZE_X, GAMEOVER_POS_Y + GAMEOVER_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkGameover[0].rhw =
		vertexWkGameover[1].rhw =
		vertexWkGameover[2].rhw =
		vertexWkGameover[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkGameover[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameover[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameover[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameover[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkGameover[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkGameover[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkGameover[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkGameover[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	vertexWkGameoverLogo[0].vtx = D3DXVECTOR3(GAMEOVERLOGO_POS_X, GAMEOVERLOGO_POS_Y, 0.0f);
	vertexWkGameoverLogo[1].vtx = D3DXVECTOR3(GAMEOVERLOGO_POS_X + GAMEOVERLOGO_SIZE_X, GAMEOVERLOGO_POS_Y, 0.0f);
	vertexWkGameoverLogo[2].vtx = D3DXVECTOR3(GAMEOVERLOGO_POS_X, GAMEOVERLOGO_POS_Y + GAMEOVERLOGO_SIZE_Y, 0.0f);
	vertexWkGameoverLogo[3].vtx = D3DXVECTOR3(GAMEOVERLOGO_POS_X + GAMEOVERLOGO_SIZE_X, GAMEOVERLOGO_POS_Y + GAMEOVERLOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
		vertexWkGameoverLogo[0].rhw =
		vertexWkGameoverLogo[1].rhw =
		vertexWkGameoverLogo[2].rhw =
		vertexWkGameoverLogo[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkGameoverLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameoverLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameoverLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameoverLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkGameoverLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkGameoverLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkGameoverLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkGameoverLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

