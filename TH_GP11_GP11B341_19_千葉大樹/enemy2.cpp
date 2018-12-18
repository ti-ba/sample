//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "enemy2.h"
#include "input.h"
#include "enemybullet2.h"
#include "sound.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy2(int no);
void SetTextureEnemy2(int no, int cntPattern);
void SetVertexEnemy2(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		D3DTextureEnemy2 = NULL;		// テクスチャへのポリゴン
ENEMY2					enemyWk2[ENEMY2_MAX];			// エネミー構造体
static LPDIRECTSOUNDBUFFER8	enemy2SE;					// SE用バッファ


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy2(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMY2 *enemy2 = enemyWk2;				// エネミーのポインターを初期化
											// テクスチャーの初期化を行う？
	if (type == 0)
	{

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
			TEXTURE_GAME_ENEMY2,				// ファイルの名前
			&D3DTextureEnemy2);				// 読み込むメモリのポインタ
		enemy2SE = LoadSound(HIT_00);	//

	}
	// エネミーの初期化処理
	for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
	{
		enemy2->use = true;										// 使用
		enemy2->pos = D3DXVECTOR3(0.0f,150 + i * 0.0f, 0.0f); // 座標データを初期化
		enemy2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		enemy2->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		enemy2->CountAnim = 0;										// アニメカウントを初期化
		enemy2->bulletTime = 0;									// 弾発射時間の初期化

		D3DXVECTOR2 temp2 = D3DXVECTOR2(TEXTURE_ENEMY2_SIZE_X, TEXTURE_ENEMY2_SIZE_Y);
		enemy2->Radius = D3DXVec2Length(&temp2);					// エネミーの半径を初期化
		enemy2->BaseAngle = atan2f(TEXTURE_ENEMY2_SIZE_Y, TEXTURE_ENEMY2_SIZE_X);	// エネミーの角度を初期化

		enemy2->Texture = D3DTextureEnemy2;						// テクスチャ情報
		MakeVertexEnemy2(i);										// 頂点情報の作成

		enemy2->pos.y = rand() % 500;		//初期位置をずらす処理

		//登場をずらす処理
		enemy2->Startweit = rand() % 100;
	}

	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy2(void)
{
	if (D3DTextureEnemy2 != NULL)
	{	// テクスチャの開放
		D3DTextureEnemy2->Release();
		D3DTextureEnemy2 = NULL;
	}

	if (enemy2SE != NULL)
	{	// テクスチャの開放
		enemy2SE->Release();
		enemy2SE = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy2(void)
{
	ENEMY2 *enemy2 = enemyWk2;				// エネミーのポインターを初期化
	D3DXVECTOR3 pos = enemy2->pos;

	for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
	{
		if (enemy2->use == true)			// 使用している状態なら更新する
		{

			//スタート地点にいる場合、発射時間をカウントダウンする
			if (enemy2->pos.x == START_COUNT2)
			{
				enemy2->Startweit--;
			}

			if (enemy2->Startweit <= 0)
			{
				enemy2->pos.x += ENEMY2_SPEED;
			}

			SetVertexEnemy2(i);		// 移動後の座標で頂点を設定

			enemy2->bulletTime++;	//発射時間をたす

			//弾発射
			if (enemy2->bulletTime > (60 + rand() % (60 * 30)))
			{
				enemy2->bulletTime = 0;
				{
					D3DXVECTOR3 pos = enemy2->pos;
					pos.x -= TEXTURE_ENEMYBULLET2_SIZE_Y;
					SetEnemyBullet2(pos);
				}


				enemy2->firecount++;
				if (enemy2->firecount == 8)
				{
					pos.x -= TEXTURE_ENEMY2_SIZE_Y;
					SetEnemyBullet2(pos);
					enemy2->firecount = 0;
				}
			}
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy2(void)
{
	ENEMY2 *enemy2 = enemyWk2;			// エネミーのポインターを初期化
	LPDIRECT3DDEVICE9 Device = GetDevice();
	for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
	{
		if (enemy2->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			Device->SetTexture(0, enemy2->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY2, enemy2->vertexWk, sizeof(VERTEX_2D));
		}
	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy2(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMY2 *enemy2 = &enemyWk2[no];			// エネミーのポインターを初期化
											// rhwの設定
	enemy2->vertexWk[0].rhw =
		enemy2->vertexWk[1].rhw =
		enemy2->vertexWk[2].rhw =
		enemy2->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	enemy2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	enemy2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy2->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY2, 0.0f);
	enemy2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY2);
	enemy2->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY2, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY2);

	enemy2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy2->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	enemy2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	enemy2->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;

}


//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy2(int no, int cntPattern)
{
	ENEMY2 *enemy2 = &enemyWk2[no];			// エネミーのポインターを初期化

											// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY2;

	enemy2->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	enemy2->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	enemy2->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	enemy2->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy2(int no)
{
	ENEMY2 *enemy2 = &enemyWk2[no];			// エネミーのポインターを初期化

											// 頂点座標の設定
	enemy2->vertexWk[0].vtx.x = enemy2->pos.x - cosf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[0].vtx.y = enemy2->pos.y - sinf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[0].vtx.z = 0.0f;

	enemy2->vertexWk[1].vtx.x = enemy2->pos.x + cosf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[1].vtx.y = enemy2->pos.y - sinf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[1].vtx.z = 0.0f;

	enemy2->vertexWk[2].vtx.x = enemy2->pos.x - cosf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[2].vtx.y = enemy2->pos.y + sinf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[2].vtx.z = 0.0f;

	enemy2->vertexWk[3].vtx.x = enemy2->pos.x + cosf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[3].vtx.y = enemy2->pos.y + sinf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[3].vtx.z = 0.0f;

}

//=============================================================================
// エネミー取得関数
//=============================================================================
ENEMY2 *GetEnemy2(int no)
{
	return(&enemyWk2[no]);
}
