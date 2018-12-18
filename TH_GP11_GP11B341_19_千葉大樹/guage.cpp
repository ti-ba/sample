//=============================================================================
//
// ゲージ処理 [GUAGE.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "guage.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexguage(int no);
void SetTextureguage(int no, int cntPattern);
void SetVertexguage(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureguage = NULL;		// テクスチャへのポリゴン

GUAGE					guageWk[GUAGE_MAX];				// ゲージ構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGuage(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	GUAGE *guage = &guageWk[0];

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,		// デバイスのポインタ
			TEXTURE_GAME_GUAGE,					// ファイルの名前
			&D3DTextureguage);					// 読み込むメモリのポインタ
	}

	// ゲージの初期化処理
	for (int i = 0; i < GUAGE_MAX; i++, guage++)
	{
		guage->use = true;
		guage->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 座標データを初期化
		
		guage->Radius = TEXTURE_GUAGE_SIZE_X;

		guage->Texture = D3DTextureguage;					// テクスチャ情報
		MakeVertexguage(i);									// 頂点情報の作成
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGuage(void)
{
	if (D3DTextureguage != NULL)
	{	// テクスチャの開放
		D3DTextureguage->Release();
		D3DTextureguage = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateGuage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	GUAGE *guage = &guageWk[0];
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < GUAGE_MAX; i++, guage++, player++)
	{
		if (player->use == true)			// 使用している状態なら描画する		
		{
			guage->pos.x = -TEXTURE_GUAGE_SIZE_X;	//死んだら消える
		}
		SetVertexguage(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGuage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	GUAGE *guage = &guageWk[0];

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < GUAGE_MAX; i++, guage++)
	{
		if (guage->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			Device->SetTexture(0, guage->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GUAGE, guage->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexguage(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	GUAGE *guage = &guageWk[0];

	// 頂点座標の設定
	SetVertexguage(no);

	// rhwの設定
	guage->vertexWk[0].rhw =
	guage->vertexWk[1].rhw =
	guage->vertexWk[2].rhw =
	guage->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	guage->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	guage->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	guage->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	guage->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	guage->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	guage->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	guage->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	guage->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureguage(int no, int cntPattern)
{
	GUAGE *guage = &guageWk[no];

	// テクスチャ座標の設定
	int x = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	guage->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	guage->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	guage->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	guage->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexguage(int no)
{
	GUAGE *guage = &guageWk[no];

	// 頂点座標の設定
	guage->vertexWk[0].vtx = D3DXVECTOR3(guage->pos.x, guage->pos.y, 0.0f);
	guage->vertexWk[1].vtx = D3DXVECTOR3(guage->pos.x + guage->Radius, guage->pos.y, 0.0f);
	guage->vertexWk[2].vtx = D3DXVECTOR3(guage->pos.x, guage->pos.y + TEXTURE_GUAGE_SIZE_Y, 0.0f);
	guage->vertexWk[3].vtx = D3DXVECTOR3(guage->pos.x +  guage->Radius, guage->pos.y + TEXTURE_GUAGE_SIZE_Y, 0.0f);
}

//============================================================================
// ゲージ取得関数
//=============================================================================
GUAGE * GetGuage(int no)
{
	return (&guageWk[no]);
}