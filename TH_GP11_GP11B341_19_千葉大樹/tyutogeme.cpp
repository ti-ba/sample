//=============================================================================
//
// Main処理 [main.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "bg.h"
#include <time.h>
#include "tyutogeme.h"
#include "tyutoenemy.h"
#include "sound.h"
#include "bom.h"
#include "effect.h"
#include "effect2.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SAFE_RELEASE(ptr)

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexDescription(void);
LRESULT CALLBACK Wnd(HWND, UINT, WPARAM, LPARAM);

 void SetVertexTyutoBG(void);

  static void CheckHit(void);
  static bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);
  static void InitGame(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
   LPDIRECT3DTEXTURE9		D3DTextureTyutoBG = NULL;		// テクスチャへのポインタ
   VERTEX_2D				vertexWkTyutoBG[NUM_VERTEX];	// 頂点情報格納ワーク
   D3DXVECTOR3				posTyutoBG;						// 背景の位置

   VERTEX_2D				vertexWkTyutoBG2[NUM_VERTEX];	// 頂点情報格納ワーク
   LPDIRECT3DTEXTURE9		D3DTextureTyutoBG2 = NULL;		// テクスチャへのポインタ
   D3DXVECTOR3				posTyutoBG2;					// 背景の位置

   VERTEX_2D				vertexWkDescriptionLogo[NUM_VERTEX];		// 頂点情報格納ワーク
   LPDIRECT3DTEXTURE9		D3DTextureDescriptionLogo = NULL;	// テクスチャへのポインタ


  extern LPDIRECTSOUNDBUFFER8	enemySE;			// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTyutoGame(HWND hWnd, BOOL bWindow)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,					// デバイスへのポインタ
		TEXTURE_TYUTOBG,			// ファイルの名前
		&D3DTextureTyutoBG);		// 読み込むメモリー

	D3DXCreateTextureFromFile(Device,					// デバイスへのポインタ
		TEXTURE_TYUTOBG2,			// ファイルの名前
		&D3DTextureTyutoBG2);		// 読み込むメモリー

	D3DXCreateTextureFromFile(Device,						// デバイスへのポインタ
	TEXTURE_DESCRIPTION_LOGO,								// ファイル名
	&D3DTextureDescriptionLogo);							// 読み込むメモリー

	posTyutoBG = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posTyutoBG2 = D3DXVECTOR3(0.0f, -600.0f, 0.0f);

	// 頂点情報の作成
	MakeVertexDescription();

	posTyutoBG.x = -GetPlayer(0)->pos.x /4.0f;

	SetVertexTyutoBG();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTyutoGame(void)
{
	if (D3DTextureTyutoBG != NULL)
	{// テクスチャの開放
		D3DTextureTyutoBG->Release();
		D3DTextureTyutoBG = NULL;
	}

	if (D3DTextureTyutoBG2 != NULL)
	{// テクスチャの開放
		D3DTextureTyutoBG2->Release();
		D3DTextureTyutoBG2 = NULL;
	}

	if (D3DTextureDescriptionLogo != NULL)
	{// テクスチャの開放
		D3DTextureDescriptionLogo->Release();
		D3DTextureDescriptionLogo = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTyutoGame(void)
{
	// スクロール処理
	posTyutoBG.y += 3.0f;
	posTyutoBG2.y += 3.0f;

	if (posTyutoBG.y == 600)
	{
		posTyutoBG = D3DXVECTOR3(0.0f, -600.0f, 0.0f);

	}

	if (posTyutoBG2.y == 600)
	{
		posTyutoBG2 = D3DXVECTOR3(0.0f, -600.0f, 0.0f);
	}
	UpdateBG();
		// プレイヤーの更新処理
		UpdatePlayer();

		// バレットの更新処理
		UpdateBullet();

		//　ボムの更新処理
		UpdateBom();

		//チュートエネミー更新処理
		UpdateTyutoEnemy();

		// エフェクト更新処理
		UpdateEffect();

		// エフェクト２更新処理
		UpdateEffect2();

		// 当たり判定
		CheckHit();

		SetVertexTyutoBG();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTyutoGame(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTextureTyutoBG);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkTyutoBG, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTextureTyutoBG2);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkTyutoBG2, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTextureDescriptionLogo);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkDescriptionLogo, sizeof(VERTEX_2D));


	//チュートエネミー描画処理
	DrawTyutoEnemy();

	// プレイヤーの描画処理
	DrawPlayer();

	// バレットの描画処理
	DrawBullet();

	// エフェクトの描画処理
	DrawEffect();

	// エフェクト２の描画処理
	DrawEffect2();

	//ボムの描画処理
	DrawBom();

}


//=============================================================================
// 当たり判定処理
//=============================================================================
void CheckHit(void)
{
	PLAYER *player = GetPlayer(0);			//プレイヤーのポインターを初期化
	TYUTOENEMY *tyutoenemy = GetTyutoEnemy(0);  //エネミーポインター初期化
	BULLET *bullet = GetBullet(0);			// バレットのポインターを初期化
	BOM *bom = GetBom(0);					// ボムのポインターを初期化
	int tyutoenemycnt = 0;					//敵を数える

	/* 弾と敵(BC)*/
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
 		if (bullet->use == false) continue;

		for (int j = 0; j<TYUTOENEMY_MAX; j++, tyutoenemy++)
		{
			if (tyutoenemy->use == false) continue;

			if (CheckHitBC(bullet->pos, tyutoenemy->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_TYUTOENEMY_SIZE_X))
			{
				PlaySound(enemySE, E_DS8_FLAG_NONE);	// 当たったときの音再生
				bullet->use = false;				// 弾の消滅処理を行い
				SetEffect(tyutoenemy->pos);			// 爆破
				tyutoenemy->use = false;			// 敵は倒される
			}
		}
	}

	for (int i = 0; i < BOM_MAX; i++, bom++)
	{
		if (bom->use == false) continue;

		for (int j = 0; j < TYUTOENEMY_MAX; j++, tyutoenemy++)
		{
			if (tyutoenemy->use == false) continue;

			if (CheckHitBC(bom->pos, tyutoenemy->pos, TEXTURE_BOM_SIZE_X, TEXTURE_TYUTOENEMY_SIZE_X))
			{
				PlaySound(enemySE, E_DS8_FLAG_NONE);	// 当たったときの音再生
				bom->use = false;						// 弾の消滅処理を行い
				SetEffect2(tyutoenemy->pos);			// 爆破
				tyutoenemy->use = false;				// 敵は倒される
			}
		}
	}

	//敵が全滅したら画面遷移
	tyutoenemy = GetTyutoEnemy(0);			// エネミーのポインターを初期化
	for (int i = 0; i < TYUTOENEMY_MAX; i++, tyutoenemy++)
	{
		if (tyutoenemy->use == true)
		{
			tyutoenemycnt++;
		}
	}

	// 数えた結果敵が全滅？
	if (tyutoenemycnt == 0)
	{
		InitGame();		// ゲームの再初期化処理
		SetStage(STAGE_GAME_START);
	}
}

//=============================================================================
// BCによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	if ((size1 + size2) * (size1 + size2) >
		(pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y))
	{
		return true;
	}

	return false;
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexDescription(void)
{
	// 頂点座標の設定
	vertexWkTyutoBG[0].vtx = D3DXVECTOR3(TYUTOBG_POS_X, TYUTOBG_POS_Y, 0.0f);
	vertexWkTyutoBG[1].vtx = D3DXVECTOR3(TYUTOBG_POS_X +TYUTOBG_SIZE_X, TYUTOBG_POS_Y, 0.0f);
	vertexWkTyutoBG[2].vtx = D3DXVECTOR3(TYUTOBG_POS_X, TYUTOBG_POS_Y + TYUTOBG_SIZE_Y, 0.0f);
	vertexWkTyutoBG[3].vtx = D3DXVECTOR3(TYUTOBG_POS_X +TYUTOBG_SIZE_X, TYUTOBG_POS_Y + TYUTOBG_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkTyutoBG[0].rhw =
	vertexWkTyutoBG[1].rhw =
	vertexWkTyutoBG[2].rhw =
	vertexWkTyutoBG[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkTyutoBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTyutoBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTyutoBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTyutoBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkTyutoBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkTyutoBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkTyutoBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkTyutoBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点座標の設定
	vertexWkTyutoBG2[0].vtx = D3DXVECTOR3(TYUTOBG2_POS_X, TYUTOBG2_POS_Y, 0.0f);
	vertexWkTyutoBG2[1].vtx = D3DXVECTOR3(TYUTOBG2_POS_X +TYUTOBG2_SIZE_X, TYUTOBG2_POS_Y, 0.0f);
	vertexWkTyutoBG2[2].vtx = D3DXVECTOR3(TYUTOBG2_POS_X, TYUTOBG2_POS_Y + TYUTOBG2_SIZE_Y, 0.0f);
	vertexWkTyutoBG2[3].vtx = D3DXVECTOR3(TYUTOBG2_POS_X +TYUTOBG2_SIZE_X, TYUTOBG2_POS_Y + TYUTOBG2_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkTyutoBG2[0].rhw =
	vertexWkTyutoBG2[1].rhw =
	vertexWkTyutoBG2[2].rhw =
	vertexWkTyutoBG2[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkTyutoBG2[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTyutoBG2[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTyutoBG2[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTyutoBG2[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkTyutoBG2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkTyutoBG2[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkTyutoBG2[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkTyutoBG2[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点座標の設定
	vertexWkDescriptionLogo[0].vtx = D3DXVECTOR3(DESCRIPTIONLOGO_POS_X, DESCRIPTIONLOGO_POS_Y, 0.0f);
	vertexWkDescriptionLogo[1].vtx = D3DXVECTOR3(DESCRIPTIONLOGO_POS_X + DESCRIPTIONLOGO_SIZE_X, DESCRIPTIONLOGO_POS_Y, 0.0f);
	vertexWkDescriptionLogo[2].vtx = D3DXVECTOR3(DESCRIPTIONLOGO_POS_X, DESCRIPTIONLOGO_POS_Y + DESCRIPTIONLOGO_SIZE_Y, 0.0f);
	vertexWkDescriptionLogo[3].vtx = D3DXVECTOR3(DESCRIPTIONLOGO_POS_X + DESCRIPTIONLOGO_SIZE_X, DESCRIPTIONLOGO_POS_Y + DESCRIPTIONLOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkDescriptionLogo[0].rhw =
	vertexWkDescriptionLogo[1].rhw =
	vertexWkDescriptionLogo[2].rhw =
	vertexWkDescriptionLogo[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkDescriptionLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkDescriptionLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkDescriptionLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkDescriptionLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkDescriptionLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkDescriptionLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkDescriptionLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkDescriptionLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexTyutoBG(void)
{
	// 頂点座標の設定
	vertexWkTyutoBG[0].vtx = D3DXVECTOR3(TYUTOBG_POS_X, TYUTOBG_POS_Y, 0.0f) + posTyutoBG;
	vertexWkTyutoBG[1].vtx = D3DXVECTOR3(TYUTOBG_POS_X + TYUTOBG_SIZE_X, TYUTOBG_POS_Y, 0.0f) + posTyutoBG;
	vertexWkTyutoBG[2].vtx = D3DXVECTOR3(TYUTOBG_POS_X, TYUTOBG_POS_Y + TYUTOBG_SIZE_Y, 0.0f) + posTyutoBG;
	vertexWkTyutoBG[3].vtx = D3DXVECTOR3(TYUTOBG_POS_X + TYUTOBG_SIZE_X, TYUTOBG_POS_Y + TYUTOBG_SIZE_Y, 0.0f) + posTyutoBG;



	// 頂点座標の設定
	vertexWkTyutoBG2[0].vtx = D3DXVECTOR3(TYUTOBG2_POS_X, TYUTOBG2_POS_Y, 0.0f) + posTyutoBG2;
	vertexWkTyutoBG2[1].vtx = D3DXVECTOR3(TYUTOBG2_POS_X + TYUTOBG2_SIZE_X, TYUTOBG2_POS_Y, 0.0f) + posTyutoBG2;
	vertexWkTyutoBG2[2].vtx = D3DXVECTOR3(TYUTOBG2_POS_X, TYUTOBG2_POS_Y + TYUTOBG2_SIZE_Y, 0.0f) + posTyutoBG2;
	vertexWkTyutoBG2[3].vtx = D3DXVECTOR3(TYUTOBG2_POS_X + TYUTOBG2_SIZE_X, TYUTOBG2_POS_Y + TYUTOBG2_SIZE_Y, 0.0f) + posTyutoBG2;
}

//=============================================================================
// ゲームの再初期化処理処理
// 戻り値：無し
//=============================================================================
void InitGame(void)
{
	InitPlayer(1);		// プレイヤーの再初期化
	InitTyutoEnemy(1);	// エネミーの再初期化
	InitBullet(1);		// バレットの再初期化
	InitBG(1);			// BGの再初期化
	InitEffect(1);		// エフェクト再初期化
	InitEffect2(1);		// エフェクト２再初期化
	InitBom(1);			// ボム再初期化
}
