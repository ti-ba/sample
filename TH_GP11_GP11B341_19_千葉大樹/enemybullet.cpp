//=============================================================================
//
// バレット処理 [EnemyBullet.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "EnemyBullet.h"
#include "sound.h"
#include "tyutoenemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemyBullet(int no);
void SetTextureEnemyBullet(int no, int cntPattern);
void SetVertexEnemyBullet(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureEnemyBullet = NULL;		// テクスチャへのポリゴン
ENEMYBULLET				EnemyBulletWk[ENEMYBULLET_MAX];		// バレット構造体
LPDIRECTSOUNDBUFFER8	enemybulletSE;						// SE用バッファ


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyBullet(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYBULLET *EnemyBullet = &EnemyBulletWk[0];		// エネミーのポインターを初期化

										
	if (type == 0)										// テクスチャーの初期化を行う？
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,				// デバイスのポインタ
			TEXTURE_GAME_ENEMYBULLET,					// ファイルの名前
			&D3DTextureEnemyBullet);					// 読み込むメモリのポインタ
		enemybulletSE = LoadSound(SHOT_00);
	}

	// バレットの初期化処理
	for (int i = 0; i < ENEMYBULLET_MAX; i++, EnemyBullet++)
	{
		EnemyBullet->use = false;								// 未使用（発射されていない弾）
		EnemyBullet->pos = D3DXVECTOR3(+300.0f, 0.0f, 0.0f);	// 座標データを初期化
		EnemyBullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転データを初期化
		EnemyBullet->PatternAnim = 0;							// アニメパターン番号をランダムで初期化
		EnemyBullet->CountAnim = 0;								// アニメカウントを初期化

		EnemyBullet->Texture = D3DTextureEnemyBullet;			// テクスチャ情報
		MakeVertexEnemyBullet(i);								// 頂点情報の作成
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyBullet(void)
{
	if (D3DTextureEnemyBullet != NULL)
	{	// テクスチャの開放
		D3DTextureEnemyBullet->Release();
		D3DTextureEnemyBullet = NULL;
	}

	if (enemybulletSE != NULL)
	{	// テクスチャの開放
		enemybulletSE->Release();
		enemybulletSE = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyBullet(void)
{
	ENEMYBULLET *EnemyBullet = EnemyBulletWk;				// バレットのポインターを初期化

	for (int i = 0; i < ENEMYBULLET_MAX; i++, EnemyBullet++)
	{
		if (EnemyBullet->use == true)			// 使用している状態なら更新する
		{
			// 敵のバレットの移動処理
			EnemyBullet->pos.y += ENEMYBULLET_SPEED;

			// 画面外まで進んだ？
			if (EnemyBullet->pos.y < -TEXTURE_ENEMYBULLET_SIZE_Y)	// 自分の大きさを考慮して画面外か判定している
			{
				EnemyBullet->use = false;
				EnemyBullet->pos.x = -100.0f;
			}


			SetVertexEnemyBullet(i);				// 移動後の座標で頂点を設定
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYBULLET *EnemyBullet = EnemyBulletWk;				// バレットのポインターを初期化

											
	Device->SetFVF(FVF_VERTEX_2D);			// 頂点フォーマットの設定

	for (int i = 0; i <ENEMYBULLET_MAX; i++, EnemyBullet++)
	{
		if (EnemyBullet->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			Device->SetTexture(0, EnemyBullet->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMYBULLET, EnemyBullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemyBullet(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYBULLET*EnemyBullet = &EnemyBulletWk[no];			// バレットのポインターを初期化

											// 頂点座標の設定
	SetVertexEnemyBullet(no);

	// rhwの設定
	EnemyBullet->vertexWk[0].rhw =
	EnemyBullet->vertexWk[1].rhw =
	EnemyBullet->vertexWk[2].rhw =
	EnemyBullet->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	EnemyBullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	EnemyBullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	EnemyBullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	EnemyBullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	EnemyBullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	EnemyBullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET, 0.0f);
	EnemyBullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET);
	EnemyBullet->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET);

	EnemyBullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	EnemyBullet->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	EnemyBullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	EnemyBullet->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemyBullet(int no, int cntPattern)
{
	ENEMYBULLET *EnemyBullet = &EnemyBulletWk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET;

	EnemyBullet->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	EnemyBullet->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	EnemyBullet->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	EnemyBullet->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemyBullet(int no)
{
	ENEMYBULLET *EnemyBullet = &EnemyBulletWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	EnemyBullet->vertexWk[0].vtx.x = EnemyBullet->pos.x - TEXTURE_ENEMYBULLET_SIZE_X;
	EnemyBullet->vertexWk[0].vtx.y = EnemyBullet->pos.y - TEXTURE_ENEMYBULLET_SIZE_Y;
	EnemyBullet->vertexWk[0].vtx.z = 0.0f;

	EnemyBullet->vertexWk[1].vtx.x = EnemyBullet->pos.x + TEXTURE_ENEMYBULLET_SIZE_X;
	EnemyBullet->vertexWk[1].vtx.y = EnemyBullet->pos.y - TEXTURE_ENEMYBULLET_SIZE_Y;
	EnemyBullet->vertexWk[1].vtx.z = 0.0f;

	EnemyBullet->vertexWk[2].vtx.x = EnemyBullet->pos.x - TEXTURE_ENEMYBULLET_SIZE_X;
	EnemyBullet->vertexWk[2].vtx.y = EnemyBullet->pos.y + TEXTURE_ENEMYBULLET_SIZE_Y;
	EnemyBullet->vertexWk[2].vtx.z = 0.0f;

	EnemyBullet->vertexWk[3].vtx.x = EnemyBullet->pos.x + TEXTURE_ENEMYBULLET_SIZE_X;
	EnemyBullet->vertexWk[3].vtx.y = EnemyBullet->pos.y + TEXTURE_ENEMYBULLET_SIZE_Y;
	EnemyBullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetEnemyBullet(D3DXVECTOR3 pos)
{
	ENEMYBULLET *EnemyBullet = &EnemyBulletWk[0];			// バレットのポインターを初期化
	ENEMY *enemy = GetEnemy(0);

	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < ENEMYBULLET_MAX; i++,EnemyBullet++)
	{
		if (EnemyBullet->use == false)			// 未使用状態のバレットを見つける
		{
			EnemyBullet->use = true;			// 使用状態へ変更する
			EnemyBullet->pos = pos;				// 座標をセット


			PlaySound(enemybulletSE, E_DS8_FLAG_NONE);  // 発射音再生

			return;								// 1発セットしたので終了する
		}
		if (enemy->use = false)
		{
		return;
		}
	}
}

//=============================================================================
// エネミー取得関数
//=============================================================================
ENEMYBULLET *GetEnemyBullet(int no)
{
	return(&EnemyBulletWk[no]);
}
