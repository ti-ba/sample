//=============================================================================
//
// 敵処理 [tyutoenemy.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "tyutoenemy.h"
#include "input.h"
#include "enemybullet.h"
#include "sound.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTyutoEnemy(int no);
void SetTextureTyutoEnemy(int no, int cntPattern);
void SetVertexTyutoEnemy(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureTyutoEnemy = NULL;	// テクスチャへのポリゴン

TYUTOENEMY				tyutoenemyWk[TYUTOENEMY_MAX];	// エネミー構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTyutoEnemy(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
			TEXTURE_GAME_TYUTOENEMY,		// ファイルの名前
			&D3DTextureTyutoEnemy);		// 読み込むメモリのポインタ
	}

	// エネミーの初期化処理
	TYUTOENEMY *tyutoenemy = tyutoenemyWk;				// エネミーのポインターを初期化
	for (int i = 0; i < TYUTOENEMY_MAX; i++, tyutoenemy++)
	{
		tyutoenemy->use = true;										// 使用
		tyutoenemy->pos = D3DXVECTOR3(50 + i * 170.0f, 100.0f, 0.0f);	// 座標データを初期化
		tyutoenemy->PatternAnim = 0;								// アニメパターン番号をランダムで初期化
		tyutoenemy->CountAnim = 0;									// アニメカウントを初期化

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_TYUTOENEMY_SIZE_X, TEXTURE_TYUTOENEMY_SIZE_Y);
		tyutoenemy->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		tyutoenemy->BaseAngle = atan2f(TEXTURE_TYUTOENEMY_SIZE_Y, TEXTURE_TYUTOENEMY_SIZE_X);	// エネミーの角度を初期化

		tyutoenemy->Texture = D3DTextureTyutoEnemy;					// テクスチャ情報
		MakeVertexTyutoEnemy(i);									// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTyutoEnemy(void)
{
	if (D3DTextureTyutoEnemy != NULL)
	{	// テクスチャの開放
		D3DTextureTyutoEnemy->Release();
		D3DTextureTyutoEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTyutoEnemy(void)
{
	TYUTOENEMY *tyutoenemy = tyutoenemyWk;				// エネミーのポインターを初期化
	

	for (int i = 0; i < TYUTOENEMY_MAX; i++, tyutoenemy++)
	{
		if (tyutoenemy->use == true)					// 使用している状態なら更新する
		{
			SetVertexTyutoEnemy(i);						// 移動後の座標で頂点を設定
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTyutoEnemy(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	TYUTOENEMY *tyutoenemy = tyutoenemyWk;		// エネミーのポインターを初期化

										
	Device->SetFVF(FVF_VERTEX_2D);				// 頂点フォーマットの設定

	for (int i = 0; i < TYUTOENEMY_MAX; i++, tyutoenemy++)
	{
		if (tyutoenemy->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			Device->SetTexture(0, tyutoenemy->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_TYUTOENEMY, tyutoenemy->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTyutoEnemy(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	TYUTOENEMY *tyutoenemy = &tyutoenemyWk[no];			// エネミーのポインターを初期化

	// 頂点座標の設定
	SetVertexTyutoEnemy(no);

	// rhwの設定
		tyutoenemy->vertexWk[0].rhw =
		tyutoenemy->vertexWk[1].rhw =
		tyutoenemy->vertexWk[2].rhw =
		tyutoenemy->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	tyutoenemy->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tyutoenemy->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tyutoenemy->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tyutoenemy->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	tyutoenemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	tyutoenemy->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY, 0.0f);
	tyutoenemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TYUTOENEMY);
	tyutoenemy->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TYUTOENEMY);

	tyutoenemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	tyutoenemy->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	tyutoenemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	tyutoenemy->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureTyutoEnemy(int no, int cntPattern)
{
	TYUTOENEMY *tyutoenemy = &tyutoenemyWk[no];			// エネミーのポインターを初期化

											// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TYUTOENEMY;

	tyutoenemy->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	tyutoenemy->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	tyutoenemy->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	tyutoenemy->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexTyutoEnemy(int no)
{
	TYUTOENEMY *tyutoenemy = &tyutoenemyWk[no];			// エネミーのポインターを初期化

	// 頂点座標の設定
	tyutoenemy->vertexWk[0].vtx.x = tyutoenemy->pos.x - cosf(tyutoenemy->BaseAngle + tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[0].vtx.y = tyutoenemy->pos.y - sinf(tyutoenemy->BaseAngle + tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[0].vtx.z = 0.0f;

	tyutoenemy->vertexWk[1].vtx.x = tyutoenemy->pos.x + cosf(tyutoenemy->BaseAngle - tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[1].vtx.y = tyutoenemy->pos.y - sinf(tyutoenemy->BaseAngle - tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[1].vtx.z = 0.0f;

	tyutoenemy->vertexWk[2].vtx.x = tyutoenemy->pos.x - cosf(tyutoenemy->BaseAngle - tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[2].vtx.y = tyutoenemy->pos.y + sinf(tyutoenemy->BaseAngle - tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[2].vtx.z = 0.0f;

	tyutoenemy->vertexWk[3].vtx.x = tyutoenemy->pos.x + cosf(tyutoenemy->BaseAngle + tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[3].vtx.y = tyutoenemy->pos.y + sinf(tyutoenemy->BaseAngle + tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エネミー取得関数
//=============================================================================
TYUTOENEMY *GetTyutoEnemy(int no)
{
	return(&tyutoenemyWk[no]);
}


