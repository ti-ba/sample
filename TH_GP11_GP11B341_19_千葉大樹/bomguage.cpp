//=============================================================================
//
// ゲージ処理 [bomguage.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "bomguage.h"
#include "player.h"
#include "bom.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexbomguage(int no);
void SetTexturebomguage(int no, int cntPattern);
void SetVertexbomguage(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTexturebomguage = NULL;		// テクスチャへのポリゴン

BOMGUAGE					bomguageWk[BOMGUAGE_MAX];				// ゲージ構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBomGuage(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOMGUAGE *bomguage = &bomguageWk[0];

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,			// デバイスのポインタ
			TEXTURE_GAME_BOMGUAGE,					// ファイルの名前
			&D3DTexturebomguage);					// 読み込むメモリのポインタ
	}

	// ゲージの初期化処理
	for (int i = 0; i < BOMGUAGE_MAX; i++, bomguage++)
	{
		bomguage->use = true;
		bomguage->pos = D3DXVECTOR3(400, + 400.0f, 100.0f);	// 座標データを初期化

		bomguage->Radius = 1.0f;

		bomguage->Texture = D3DTexturebomguage;					// テクスチャ情報
		MakeVertexbomguage(i);									// 頂点情報の作成
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBomGuage(void)
{
	BOMGUAGE *bomguage = &bomguageWk[0];

	if (D3DTexturebomguage != NULL)
	{	// テクスチャの開放
		D3DTexturebomguage->Release();
		D3DTexturebomguage = NULL;
	}

	//bomguage->Radius -= 0.5f;
	//if (bomguage->Radius = 0)
	//{
	//	bomguage->Radius += 0.5f;
	//}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateBomGuage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOMGUAGE *bomguage = &bomguageWk[0];
	BOM *bom = GetBom(0);
	//PLAYER *player = GetPlayer(0);
	for (int i = 0; i < BOMGUAGE_MAX; i++, bomguage++, bom++)
	{
		if (bom->use == true)			// 使用している状態なら描画する
		{
			bomguage->Radius -= 0.5f;
			if (bomguage->Radius = 0)
			{
				bomguage->Radius += 0.5f;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBomGuage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOMGUAGE *bomguage = &bomguageWk[0];

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOMGUAGE_MAX; i++, bomguage++)
	{
		if (bomguage->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			Device->SetTexture(0, bomguage->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOMGUAGE, bomguage->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexbomguage(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOMGUAGE *bomguage = &bomguageWk[0];

	// 頂点座標の設定
	SetVertexbomguage(no);

	// rhwの設定
	bomguage->vertexWk[0].rhw =
		bomguage->vertexWk[1].rhw =
		bomguage->vertexWk[2].rhw =
		bomguage->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bomguage->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bomguage->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bomguage->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bomguage->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	bomguage->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bomguage->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bomguage->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bomguage->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturebomguage(int no, int cntPattern)
{
	BOMGUAGE *bomguage = &bomguageWk[no];

	// テクスチャ座標の設定
	int x = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	bomguage->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	bomguage->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	bomguage->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	bomguage->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexbomguage(int no)
{
	BOMGUAGE *bomguage = &bomguageWk[no];

	// 頂点座標の設定
	bomguage->vertexWk[0].vtx = D3DXVECTOR3(bomguage->pos.x, bomguage->pos.y, 0.0f);
	bomguage->vertexWk[1].vtx = D3DXVECTOR3(bomguage->pos.x +(TEXTURE_BOMGUAGE_SIZE_X * bomguage->Radius), bomguage->pos.y, 0.0f);
	bomguage->vertexWk[2].vtx = D3DXVECTOR3(bomguage->pos.x, bomguage->pos.y + TEXTURE_BOMGUAGE_SIZE_Y, 0.0f);
	bomguage->vertexWk[3].vtx = D3DXVECTOR3(bomguage->pos.x +(TEXTURE_BOMGUAGE_SIZE_X * bomguage->Radius), bomguage->pos.y + TEXTURE_BOMGUAGE_SIZE_Y, 0.0f);
}

//===========================================================================
// ゲージ取得関数
//=============================================================================
BOMGUAGE * GetBomGuage(int no)
{
	return (&bomguageWk[no]);
}