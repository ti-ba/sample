//=============================================================================
//
// ゲージ処理 [BOSSGUAGE.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "bossguage.h"
#include "player.h"
#include "boss.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBossguage(int no);
void SetTextureBossguage(int no, int cntPattern);
void SetVertexBossguage(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		TextureBossguage = NULL;		// テクスチャへのポリゴン

BOSSGUAGE					bossguageWk[BOSSGUAGE_MAX];				// ゲージ構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBossguage(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSGUAGE *bossguage = &bossguageWk[0];

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,		// デバイスのポインタ
			TEXTURE_GAME_BOSSGUAGE,				// ファイルの名前
			&TextureBossguage);					// 読み込むメモリのポインタ
	}

	// ゲージの初期化処理
	for (int i = 0; i < BOSSGUAGE_MAX; i++, bossguage++)
	{
		bossguage->use = true;
		bossguage->pos = D3DXVECTOR3(-(TEXTURE_BOSS_SIZE_X), 100.0f, 100.0f);	// 座標データを初期化

		bossguage->Radius = TEXTURE_BOSSGUAGE_SIZE_X;

		bossguage->Texture = TextureBossguage;					// テクスチャ情報
		MakeVertexBossguage(i);									// 頂点情報の作成
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBossguage(void)
{
	if (TextureBossguage != NULL)
	{	// テクスチャの開放
		TextureBossguage->Release();
		TextureBossguage = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateBossguage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSGUAGE *bossguage = &bossguageWk[0];
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < BOSSGUAGE_MAX; i++, bossguage++, player++)
	{
		if (player->use == true)			// 使用している状態なら描画する
		{
			bossguage->pos = player->pos; //プレイヤーについていく
		}
		else
		{
			bossguage->pos.x = -TEXTURE_BOSSGUAGE_SIZE_X;	//死んだら消える
		}
		SetTextureBossguage(i, 0);
		SetVertexBossguage(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBossguage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSGUAGE *bossguage = &bossguageWk[0];

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSSGUAGE_MAX; i++, bossguage++)
	{
		if (bossguage->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			Device->SetTexture(0, bossguage->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSSGUAGE, bossguage->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBossguage(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSGUAGE *bossguage = &bossguageWk[0];

	// 頂点座標の設定
	SetVertexBossguage(no);

	// rhwの設定
	bossguage->vertexWk[0].rhw =
	bossguage->vertexWk[1].rhw =
	bossguage->vertexWk[2].rhw =
	bossguage->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bossguage->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bossguage->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bossguage->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bossguage->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	bossguage->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bossguage->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bossguage->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bossguage->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBossguage(int no, int cntPattern)
{
	BOSSGUAGE *bossguage = &bossguageWk[no];

	// テクスチャ座標の設定
	int x = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	bossguage->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	bossguage->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	bossguage->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	bossguage->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBossguage(int no)
{
	BOSSGUAGE *bossguage = &bossguageWk[no];

	// 頂点座標の設定
	bossguage->vertexWk[0].vtx = D3DXVECTOR3(bossguage->pos.x, bossguage->pos.y, 0.0f);
	bossguage->vertexWk[1].vtx = D3DXVECTOR3(bossguage->pos.x + bossguage->Radius, bossguage->pos.y, 0.0f);
	bossguage->vertexWk[2].vtx = D3DXVECTOR3(bossguage->pos.x, bossguage->pos.y + TEXTURE_BOSSGUAGE_SIZE_Y, 0.0f);
	bossguage->vertexWk[3].vtx = D3DXVECTOR3(bossguage->pos.x + bossguage->Radius, bossguage->pos.y + TEXTURE_BOSSGUAGE_SIZE_Y, 0.0f);
}

//============================================================================
// ゲージ取得関数
//=============================================================================
BOSSGUAGE * GetBossguage(int no)
{
	return (&bossguageWk[no]);
}