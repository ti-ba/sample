//=============================================================================
//
// リザルト画面処理 [curea.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "curea.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexcurea(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTexturecurea = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		D3DTexturecureaLogo = NULL;	// テクスチャへのポインタ

VERTEX_2D				vertexWkcurea[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				vertexWkcureaLogo[NUM_VERTEX];		// 頂点情報格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCurea(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,					// デバイスへのポインタ
								TEXTURE_CUREA,			// ファイルの名前
								&D3DTexturecurea);		// 読み込むメモリー

	D3DXCreateTextureFromFile(Device,					// デバイスへのポインタ
								TEXTURE_CUREA_LOGO,		// ファイルの名前
								&D3DTexturecureaLogo);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexcurea();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCurea(void)
{
	if(D3DTexturecurea != NULL)
	{// テクスチャの開放
		D3DTexturecurea->Release();
		D3DTexturecurea = NULL;
	}

	if(D3DTexturecureaLogo != NULL)
	{// テクスチャの開放
		D3DTexturecureaLogo->Release();
		D3DTexturecureaLogo = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCurea(void)
{
	int stage = 5;
	if(GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、ステージを切り替える
		SetStage( STAGE_TITLE );
	}
	else if (IsButtonRepeat(0, BUTTON_B))
	{
		SetStage(STAGE_TITLE);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCurea(void)
{

	LPDIRECT3DDEVICE9 Device = GetDevice();
	
	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTexturecurea);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkcurea, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTexturecureaLogo);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkcureaLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexcurea(void)
{	
	// 頂点座標の設定
	vertexWkcurea[0].vtx = D3DXVECTOR3(CUREA_POS_X, CUREA_POS_Y, 0.0f);
	vertexWkcurea[1].vtx = D3DXVECTOR3(CUREA_POS_X + CUREA_SIZE_X, CUREA_POS_Y, 0.0f);
	vertexWkcurea[2].vtx = D3DXVECTOR3(CUREA_POS_X, CUREA_POS_Y + CUREA_SIZE_Y, 0.0f);
	vertexWkcurea[3].vtx = D3DXVECTOR3(CUREA_POS_X + CUREA_SIZE_X, CUREA_POS_Y + CUREA_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkcurea[0].rhw =
	vertexWkcurea[1].rhw =
	vertexWkcurea[2].rhw =
	vertexWkcurea[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkcurea[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkcurea[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkcurea[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkcurea[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkcurea[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkcurea[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkcurea[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkcurea[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	vertexWkcureaLogo[0].vtx = D3DXVECTOR3(CUREALOGO_POS_X, CUREALOGO_POS_Y, 0.0f);
	vertexWkcureaLogo[1].vtx = D3DXVECTOR3(CUREALOGO_POS_X + CUREALOGO_SIZE_X, CUREALOGO_POS_Y, 0.0f);
	vertexWkcureaLogo[2].vtx = D3DXVECTOR3(CUREALOGO_POS_X, CUREALOGO_POS_Y + CUREALOGO_SIZE_Y, 0.0f);
	vertexWkcureaLogo[3].vtx = D3DXVECTOR3(CUREALOGO_POS_X + CUREALOGO_SIZE_X, CUREALOGO_POS_Y + CUREALOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkcureaLogo[0].rhw =
	vertexWkcureaLogo[1].rhw =
	vertexWkcureaLogo[2].rhw =
	vertexWkcureaLogo[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkcureaLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkcureaLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkcureaLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkcureaLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkcureaLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkcureaLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkcureaLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkcureaLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

