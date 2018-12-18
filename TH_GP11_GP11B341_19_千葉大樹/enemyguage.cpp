//=============================================================================
//
// 敵のゲージ処理 [enemyguage.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "enemyguage.h"
#include "enemy.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define ANIME_MAX()

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexenemyguage(int no);
void SetTextureenemyguage(int no, int cntPattern);
void SetVertexenemyguage(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureenemyguage = NULL;		// テクスチャへのポリゴン

ENEMYGUAGE				enemyguageWk[ENEMYGUAGE_MAX];		// ゲージ構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyGuage(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE *enemyguage = &enemyguageWk[0];

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,		// デバイスのポインタ
			TEXTURE_GAME_ENEMYGUAGE,			// ファイルの名前
			&D3DTextureenemyguage);				// 読み込むメモリのポインタ
	}

	// ゲージの初期化処理
	for (int i = 0; i < ENEMYGUAGE_MAX; i++, enemyguage++)
	{
		enemyguage->use = true;
		enemyguage->pos = D3DXVECTOR3(/*150.0f*i - 30.0f, 0.0f, 0.0f*/0.0f,0.0f,0.0f);	// 座標データを初期化
		enemyguage->Radius = TEXTURE_ENEMYGUAGE_SIZE_X;
		enemyguage->Texture = D3DTextureenemyguage;				// テクスチャ情報
		MakeVertexenemyguage(i);								// 頂点情報の作成
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyGuage(void)
{
	if (D3DTextureenemyguage != NULL)
	{	// テクスチャの開放
		D3DTextureenemyguage->Release();
		D3DTextureenemyguage = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyGuage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE *enemyguage = &enemyguageWk[0];	//敵のゲージの初期化
	ENEMY *enemy = GetEnemy(0);					// エネミーのポインターを初期化
	
	for (int i = 0; i < ENEMYGUAGE_MAX; i++, enemyguage++,enemy++)
	{
		if (enemy->use == true)			// 使用している状態なら描画する
		{
			enemyguage->pos = enemy->pos; //敵についていく
		}
		else
		{
			enemyguage->pos.x = -TEXTURE_ENEMYGUAGE_SIZE_X;	//死んだら消える
		}
		SetTextureenemyguage(i, 0);
		SetVertexenemyguage(i);
	}

	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyGuage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE *enemyguage = &enemyguageWk[0];

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMYGUAGE_MAX; i++, enemyguage++)
	{
		if (enemyguage->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			Device->SetTexture(0, enemyguage->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMYGUAGE, enemyguage->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexenemyguage(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE *enemyguage = &enemyguageWk[no];

	// 頂点座標の設定
	SetVertexenemyguage(no);

	// rhwの設定
		enemyguage->vertexWk[0].rhw =
		enemyguage->vertexWk[1].rhw =
		enemyguage->vertexWk[2].rhw =
		enemyguage->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	enemyguage->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyguage->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyguage->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyguage->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	enemyguage->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemyguage->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	enemyguage->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	enemyguage->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureenemyguage(int no, int cntPattern)
{
	ENEMYGUAGE *enemyguage = &enemyguageWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYGUAGE;

	enemyguage->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	enemyguage->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	enemyguage->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	enemyguage->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexenemyguage(int no)
{
	ENEMYGUAGE *enemyguage = &enemyguageWk[no];

	// 頂点座標の設定
	enemyguage->vertexWk[0].vtx = D3DXVECTOR3(enemyguage->pos.x, enemyguage->pos.y, 0.0f);
	enemyguage->vertexWk[1].vtx = D3DXVECTOR3(enemyguage->pos.x +enemyguage->Radius, enemyguage->pos.y, 0.0f);
	enemyguage->vertexWk[2].vtx = D3DXVECTOR3(enemyguage->pos.x, enemyguage->pos.y + TEXTURE_ENEMYGUAGE_SIZE_Y, 0.0f);
	enemyguage->vertexWk[3].vtx = D3DXVECTOR3(enemyguage->pos.x +enemyguage->Radius, enemyguage->pos.y + TEXTURE_ENEMYGUAGE_SIZE_Y, 0.0f);

}

//============================================================================
// 敵のゲージ取得関数
//=============================================================================
ENEMYGUAGE * GetEnemyGuage(int no)
{
	return (&enemyguageWk[no]);
}