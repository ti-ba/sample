//=============================================================================
//
// 敵のゲージ処理 [enemyguage2.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "enemyguage2.h"
#include "enemy2.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define ANIME_MAX()

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexenemyguage2(int no);
void SetTextureenemyguage2(int no, int cntPattern);
void SetVertexenemyguage2(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureenemyguage2 = NULL;		// テクスチャへのポリゴン

ENEMYGUAGE2				enemyguage2Wk[ENEMYGUAGE2_MAX];		// ゲージ構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyGuage2(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE2 *enemyguage2 = &enemyguage2Wk[0];

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,		// デバイスのポインタ
			TEXTURE_GAME_ENEMYGUAGE2,			// ファイルの名前
			&D3DTextureenemyguage2);				// 読み込むメモリのポインタ
	}

	// ゲージの初期化処理
	for (int i = 0; i < ENEMYGUAGE2_MAX; i++, enemyguage2++)
	{
		enemyguage2->use = true;
		enemyguage2->pos = D3DXVECTOR3(150.0f*i - 30.0f, 0.0f, 50.0f);	// 座標データを初期化
		enemyguage2->Radius = TEXTURE_ENEMYGUAGE2_SIZE_X;
		enemyguage2->Texture = D3DTextureenemyguage2;				// テクスチャ情報
		MakeVertexenemyguage2(i);								// 頂点情報の作成
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyGuage2(void)
{
	if (D3DTextureenemyguage2 != NULL)
	{	// テクスチャの開放
		D3DTextureenemyguage2->Release();
		D3DTextureenemyguage2 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyGuage2(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE2 *enemyguage2 = &enemyguage2Wk[0];	//敵のゲージの初期化
	ENEMY2 *enemy2 = GetEnemy2(0);					// エネミーのポインターを初期化

	for (int i = 0; i < ENEMYGUAGE2_MAX; i++, enemyguage2++, enemy2++)
	{
		if (enemy2->use == true)			// 使用している状態なら描画する
		{
			enemyguage2->pos = enemy2->pos; //敵についていく
		}
		else
		{
			enemyguage2->pos.x = -TEXTURE_ENEMYGUAGE2_SIZE_X;	//死んだら消える
		}
		SetTextureenemyguage2(i, 0);
		SetVertexenemyguage2(i);
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyGuage2(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE2 *enemyguage2 = &enemyguage2Wk[0];

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMYGUAGE2_MAX; i++, enemyguage2++)
	{
		if (enemyguage2->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			Device->SetTexture(0, enemyguage2->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMYGUAGE2, enemyguage2->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexenemyguage2(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE2 *enemyguage2 = &enemyguage2Wk[no];

	// 頂点座標の設定
	SetVertexenemyguage2(no);

	// rhwの設定
	enemyguage2->vertexWk[0].rhw =
		enemyguage2->vertexWk[1].rhw =
		enemyguage2->vertexWk[2].rhw =
		enemyguage2->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	enemyguage2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyguage2->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyguage2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyguage2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	enemyguage2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemyguage2->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	enemyguage2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	enemyguage2->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureenemyguage2(int no, int cntPattern)
{
	ENEMYGUAGE2 *enemyguage2 = &enemyguage2Wk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYGUAGE2;

	enemyguage2->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	enemyguage2->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	enemyguage2->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	enemyguage2->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexenemyguage2(int no)
{
	ENEMYGUAGE2 *enemyguage2 = &enemyguage2Wk[no];

	// 頂点座標の設定
	enemyguage2->vertexWk[0].vtx = D3DXVECTOR3(enemyguage2->pos.x, enemyguage2->pos.y, 0.0f);
	enemyguage2->vertexWk[1].vtx = D3DXVECTOR3(enemyguage2->pos.x + enemyguage2->Radius, enemyguage2->pos.y, 0.0f);
	enemyguage2->vertexWk[2].vtx = D3DXVECTOR3(enemyguage2->pos.x, enemyguage2->pos.y + TEXTURE_ENEMYGUAGE2_SIZE_Y, 0.0f);
	enemyguage2->vertexWk[3].vtx = D3DXVECTOR3(enemyguage2->pos.x + enemyguage2->Radius, enemyguage2->pos.y + TEXTURE_ENEMYGUAGE2_SIZE_Y, 0.0f);

}

//============================================================================
// 敵のゲージ取得関数
//=============================================================================
ENEMYGUAGE2 * GetEnemyGuage2(int no)
{
	return (&enemyguage2Wk[no]);
}