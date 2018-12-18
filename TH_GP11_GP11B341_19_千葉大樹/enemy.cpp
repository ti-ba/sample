//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "input.h"
#include "enemybullet.h"
#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy( int no );
void SetTextureEnemy( int no, int cntPattern );
void SetVertexEnemy( int no );


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureEnemy = NULL;		// テクスチャへのポリゴン
ENEMY					enemyWk[ENEMY_MAX];			// エネミー構造体
LPDIRECTSOUNDBUFFER8	enemySE;					// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMY *enemy = enemyWk;				// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
			TEXTURE_GAME_ENEMY,				// ファイルの名前
			&D3DTextureEnemy);				// 読み込むメモリのポインタ
		enemySE = LoadSound(HIT_00);

	}

	// エネミーの初期化処理
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		enemy->use = true;										// 使用
		enemy->pos = D3DXVECTOR3(100.0f,-170.0f, 0.0f);	// 座標データを初期化
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		enemy->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		enemy->CountAnim = 0;									// アニメカウントを初期化
		enemy->bulletTime = 0;									// 弾発射時間の初期化

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y);
 		enemy->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		enemy->BaseAngle = atan2f(TEXTURE_ENEMY_SIZE_Y, TEXTURE_ENEMY_SIZE_X);	// エネミーの角度を初期化

		enemy->Texture = D3DTextureEnemy;						// テクスチャ情報
		MakeVertexEnemy(i);										// 頂点情報の作成

		enemy->pos.x = rand() % 400;
		//登場をずらす処理
		enemy->Startweit = rand() % 1000; 
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	if (D3DTextureEnemy != NULL)
	{	// テクスチャの開放
		D3DTextureEnemy->Release();
		D3DTextureEnemy = NULL;
	}

	if (enemySE != NULL)
	{	// テクスチャの開放
		enemySE->Release();
		enemySE = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	ENEMY *enemy = enemyWk;				// エネミーのポインターを初期化

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)			// 使用している状態なら更新する
		{

			//スタート地点にいる場合、発射時間をカウントダウンする
			if (enemy->pos.y == START_COUNT)
			{
				enemy->Startweit--;
			}

			if (enemy->Startweit <= 0)
			{
				enemy->pos.y += ENEMY_SPEED;
			}

			SetVertexEnemy(i);		// 移動後の座標で頂点を設定

			enemy->bulletTime++;	//発射時間をたす

			//弾発射
			if (enemy->bulletTime > (60+rand()%(60*30)))
			{
				enemy->bulletTime = 0;
				
				{
					D3DXVECTOR3 pos = enemy->pos;
					pos.y += TEXTURE_ENEMYBULLET_SIZE_Y;
					SetEnemyBullet(pos);
				}
			}

			 //画面外まで進んだ？
			//enemy = GetEnemy(0);
			//if (enemy->pos.y < -TEXTURE_ENEMY_SIZE_Y)	// 自分の大きさを考慮して画面外か判定している
			//{
			//	enemy->use = true;
			//	enemy->pos.x = -100.0f;

			//	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
			//	{
			//		if (enemy->use == true)
			//		{
			//			enemy->cnt++;
			//		}
			//	}

			//}

		}
	}
	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMY *enemy = enemyWk;				// エネミーのポインターを初期化

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			Device->SetTexture(0, enemy->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, enemy->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy( int no )
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMY *enemy = &enemyWk[no];			// エネミーのポインターを初期化

	// 頂点座標の設定
	SetVertexEnemy( no );

	// rhwの設定
	enemy->vertexWk[0].rhw =
	enemy->vertexWk[1].rhw =
	enemy->vertexWk[2].rhw =
	enemy->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	enemy->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY, 0.0f);
	enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY);
	enemy->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY);

	enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	enemy->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy(int no, int cntPattern)
{
	ENEMY *enemy = &enemyWk[no];			// エネミーのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY;
	
	enemy->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}


//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy( int no )
{
	ENEMY *enemy = &enemyWk[no];			// エネミーのポインターを初期化

	// 頂点座標の設定
	enemy->vertexWk[0].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[0].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[0].vtx.z = 0.0f;

	enemy->vertexWk[1].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[1].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[1].vtx.z = 0.0f;

	enemy->vertexWk[2].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[2].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[2].vtx.z = 0.0f;

	enemy->vertexWk[3].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[3].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[3].vtx.z = 0.0f;

}

//=============================================================================
// エネミー取得関数
//=============================================================================
ENEMY *GetEnemy(int no)
{
	return(&enemyWk[no]);
}



