//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "bg.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBG(void);
void SetVertexBG(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureBG = NULL;	// テクスチャへのポインタ
VERTEX_2D				vertexWkBG[NUM_VERTEX];	// 頂点情報格納ワーク
D3DXVECTOR3				posBG;					// 背景の位置

LPDIRECT3DTEXTURE9		D3DBG = NULL;			// テクスチャへのポインタ
VERTEX_2D				vertexBG[NUM_VERTEX];	// 頂点情報格納ワーク
D3DXVECTOR3				BG;						// 背景の位置


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBG(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	
	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,					// デバイスへのポインタ
			TEXTURE_GAME_BG00,		// ファイルの名前
			&D3DTextureBG);			// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,					// デバイスへのポインタ
			TEXTURE_GAME_BG01,		// ファイルの名前
			&D3DBG);				// 読み込むメモリー

	}

	posBG = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	BG = D3DXVECTOR3(0.0f, -600.0f, 0.0f);

	// 頂点情報の作成
	MakeVertexBG();

	posBG.x = -GetPlayer(0)->pos.x / 4.0f;

	SetVertexBG();

	return S_OK;


}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBG(void)
{
	if (D3DTextureBG != NULL)
	{// テクスチャの開放
		D3DTextureBG->Release();
		D3DTextureBG = NULL;
	}

	if (D3DBG != NULL)
	{// テクスチャの開放
		D3DBG->Release();
		D3DBG = NULL;
	}

}



//=============================================================================
// 更新処理
//=============================================================================
void UpdateBG(void)
{
	
	// 毎フレーム実行する処理
	
	// スクロール処理
	posBG.y += 3.0f;
	   BG.y += 3.0f;

	 if (posBG.y == 600)
	 {
		 	posBG = D3DXVECTOR3(0.0f,-600.0f, 0.0f);
		 
	 }

	 if (BG.y == 600)
	 {
		 	BG = D3DXVECTOR3(0.0f, -600.0f, 0.0f);
	 }

	SetVertexBG();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	
	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTextureBG);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkBG, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DBG);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexBG, sizeof(VERTEX_2D));

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBG(void)
{
	// 頂点座標の設定
	vertexWkBG[0].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y, 0.0f);
	vertexWkBG[1].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f);
	vertexWkBG[2].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f);
	vertexWkBG[3].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f);

	// rhwの設定
	vertexWkBG[0].rhw =
	vertexWkBG[1].rhw =
	vertexWkBG[2].rhw =
	vertexWkBG[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	// 頂点座標の設定
	vertexBG[0].vtx = D3DXVECTOR3(BG01_POS_X, BG01_POS_Y, 0.0f);
	vertexBG[1].vtx = D3DXVECTOR3(BG01_POS_X + BG01_SIZE_X, BG01_POS_Y, 0.0f);
	vertexBG[2].vtx = D3DXVECTOR3(BG01_POS_X, BG01_POS_Y + BG01_SIZE_Y, 0.0f);
	vertexBG[3].vtx = D3DXVECTOR3(BG01_POS_X + BG01_SIZE_X, BG01_POS_Y + BG01_SIZE_Y, 0.0f);

	// rhwの設定
	vertexBG[0].rhw =
	vertexBG[1].rhw =
	vertexBG[2].rhw =
	vertexBG[3].rhw = 1.0f;

	// 反射光の設定
	vertexBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBG(void)
{
	// 頂点座標の設定
	vertexWkBG[0].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y, 0.0f) + posBG;
	vertexWkBG[1].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f) + posBG;
	vertexWkBG[2].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + posBG;
	vertexWkBG[3].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + posBG;



	// 頂点座標の設定
	vertexBG[0].vtx = D3DXVECTOR3(BG01_POS_X, BG01_POS_Y, 0.0f) + BG;
	vertexBG[1].vtx = D3DXVECTOR3(BG01_POS_X + BG01_SIZE_X, BG01_POS_Y, 0.0f) + BG;
	vertexBG[2].vtx = D3DXVECTOR3(BG01_POS_X, BG01_POS_Y + BG01_SIZE_Y, 0.0f) + BG;
	vertexBG[3].vtx = D3DXVECTOR3(BG01_POS_X + BG01_SIZE_X, BG01_POS_Y + BG01_SIZE_Y, 0.0f) + BG;

}
