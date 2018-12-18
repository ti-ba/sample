//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "player.h"
#include "BG.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTitle(void);
void SetVertexTitle(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureTitle = NULL;		// テクスチャへのポインタ
VERTEX_2D				vertexWkTitle[NUM_VERTEX];	// 頂点情報格納ワーク
D3DXVECTOR3				posTitle;					// 背景の位置

VERTEX_2D				vertexWkTitle2[NUM_VERTEX];		// 頂点情報格納ワーク
LPDIRECT3DTEXTURE9		D3DTextureTitle2 = NULL;		// テクスチャへのポインタ
D3DXVECTOR3				posTitle2;						// 背景の位置


VERTEX_2D				vertexWkTitleLogo[NUM_VERTEX];		// 頂点情報格納ワーク
LPDIRECT3DTEXTURE9		D3DTextureTitleLogo = NULL;	// テクスチャへのポインタ

VERTEX_2D				vertexWkpushLogo[NUM_VERTEX];		// 頂点情報格納ワーク
LPDIRECT3DTEXTURE9		D3DTexturepushLogo = NULL;	// テクスチャへのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,					// デバイスへのポインタ
								TEXTURE_TITLE,			// ファイルの名前
								&D3DTextureTitle);		// 読み込むメモリー

	D3DXCreateTextureFromFile(Device,					// デバイスへのポインタ
								TEXTURE_TITLE_LOGO,		// ファイルの名前
								&D3DTextureTitleLogo);	// 読み込むメモリー
	
	D3DXCreateTextureFromFile(Device,					// デバイスへのポインタ
								TEXTURE_TITLE2,			// ファイルの名前
								&D3DTextureTitle2);		// 読み込むメモリー

	D3DXCreateTextureFromFile(Device,					// デバイスへのポインタ
								TEXTURE_PUSH_LOGO,		// ファイルの名前
								&D3DTexturepushLogo);	// 読み込むメモリー

	posTitle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posTitle2 = D3DXVECTOR3(0.0f, -600.0f, 0.0f);


	// 頂点情報の作成
	MakeVertexTitle();

	posTitle.x = 4.0f;

	SetVertexTitle();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	if(D3DTextureTitle != NULL)
	{// テクスチャの開放
		D3DTextureTitle->Release();
		D3DTextureTitle = NULL;
	}

	if(D3DTextureTitleLogo != NULL)
	{// テクスチャの開放
		D3DTextureTitleLogo->Release();
		D3DTextureTitleLogo = NULL;
	}

	if (D3DTextureTitle2 != NULL)
	{// テクスチャの開放
		D3DTextureTitle2->Release();
		D3DTextureTitle2 = NULL;
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
void UpdateTitle(void)
{
	if(GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、ステージを切り替える
		SetStage(STAGE_TYUTO_GAME);
	}
	// ゲームパッドで移動処理
	else if (IsButtonRepeat(0, BUTTON_START))
	{
		SetStage(STAGE_TYUTO_GAME);
	}
	else if (IsButtonRepeat(0, BUTTON_B))
	{
		SetStage(STAGE_TYUTO_GAME);
	}

	// 毎フレーム実行する処理

	// スクロール処理
	posTitle.y += 3.0f;
	posTitle2.y += 3.0f;

	if (posTitle.y == 600)
	{
		posTitle = D3DXVECTOR3(0.0f, -600.0f, 0.0f);

	}

	if (posTitle2.y == 600)
	{
		posTitle2 = D3DXVECTOR3(0.0f, -600.0f, 0.0f);
	}

	SetVertexTitle();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0,D3DTextureTitle);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkTitle, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTextureTitle2);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkTitle2, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTextureTitleLogo);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkTitleLogo, sizeof(VERTEX_2D));


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
HRESULT MakeVertexTitle(void)
{
	// 頂点座標の設定
	vertexWkTitle[0].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	vertexWkTitle[1].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y, 0.0f);
	vertexWkTitle[2].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);
	vertexWkTitle[3].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkTitle[0].rhw =
	vertexWkTitle[1].rhw =
	vertexWkTitle[2].rhw =
	vertexWkTitle[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkTitle[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkTitle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkTitle[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点座標の設定
	vertexWkTitle2[0].vtx = D3DXVECTOR3(TITLE2_POS_X, TITLE2_POS_Y, 0.0f);
	vertexWkTitle2[1].vtx = D3DXVECTOR3(TITLE2_POS_X + TITLE2_SIZE_X, TITLE2_POS_Y, 0.0f);
	vertexWkTitle2[2].vtx = D3DXVECTOR3(TITLE2_POS_X, TITLE2_POS_Y + TITLE2_SIZE_Y, 0.0f);
	vertexWkTitle2[3].vtx = D3DXVECTOR3(TITLE2_POS_X + TITLE2_SIZE_X, TITLE2_POS_Y + TITLE2_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkTitle2[0].rhw =
	vertexWkTitle2[1].rhw =
	vertexWkTitle2[2].rhw =
	vertexWkTitle2[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkTitle2[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle2[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle2[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle2[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkTitle2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkTitle2[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkTitle2[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkTitle2[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点座標の設定
	vertexWkTitleLogo[0].vtx = D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y, 0.0f);
	vertexWkTitleLogo[1].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y, 0.0f);
	vertexWkTitleLogo[2].vtx = D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);
	vertexWkTitleLogo[3].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkTitleLogo[0].rhw =
	vertexWkTitleLogo[1].rhw =
	vertexWkTitleLogo[2].rhw =
	vertexWkTitleLogo[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkTitleLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitleLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitleLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitleLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkTitleLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkTitleLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkTitleLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkTitleLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);


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

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexTitle(void)
{
	// 頂点座標の設定
	vertexWkTitle[0].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f) + posTitle;
	vertexWkTitle[1].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y, 0.0f) + posTitle;
	vertexWkTitle[2].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f) + posTitle;
	vertexWkTitle[3].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f) + posTitle;



	// 頂点座標の設定
	vertexWkTitle2[0].vtx = D3DXVECTOR3(TITLE2_POS_X, TITLE2_POS_Y, 0.0f) + posTitle2;
	vertexWkTitle2[1].vtx = D3DXVECTOR3(TITLE2_POS_X + TITLE2_SIZE_X, TITLE2_POS_Y, 0.0f) + posTitle2;
	vertexWkTitle2[2].vtx = D3DXVECTOR3(TITLE2_POS_X, TITLE2_POS_Y + TITLE2_SIZE_Y, 0.0f) + posTitle2;
	vertexWkTitle2[3].vtx = D3DXVECTOR3(TITLE2_POS_X + TITLE2_SIZE_X, TITLE2_POS_Y + TITLE2_SIZE_Y, 0.0f) + posTitle2;
}