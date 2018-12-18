//=============================================================================
//
// バレット処理 [EnemyBullet2.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "EnemyBullet2.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemyBullet2(int no);
void SetTextureEnemyBullet2(int no, int cntPattern);
void SetVertexEnemyBullet2(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureEnemyBullet2 = NULL;		// テクスチャへのポリゴン
ENEMYBULLET2				EnemyBullet2Wk[ENEMYBULLET2_MAX];		// バレット構造体
LPDIRECTSOUNDBUFFER8	enemybullet2SE;						// SE用バッファ


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyBullet2(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYBULLET2 *EnemyBullet2 = &EnemyBullet2Wk[0];		// エネミーのポインターを初期化


	if (type == 0)										// テクスチャーの初期化を行う？
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,				// デバイスのポインタ
			TEXTURE_GAME_ENEMYBULLET2,					// ファイルの名前
			&D3DTextureEnemyBullet2);					// 読み込むメモリのポインタ
		enemybullet2SE = LoadSound(SHOT_00);
	}

	// バレットの初期化処理
	for (int i = 0; i < ENEMYBULLET2_MAX; i++, EnemyBullet2++)
	{
		EnemyBullet2->use = false;								// 未使用（発射されていない弾）
		EnemyBullet2->pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);		// 座標データを初期化
		EnemyBullet2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転データを初期化
		EnemyBullet2->PatternAnim = 0;							// アニメパターン番号をランダムで初期化
		EnemyBullet2->CountAnim = 0;							// アニメカウントを初期化

		EnemyBullet2->Texture = D3DTextureEnemyBullet2;			// テクスチャ情報
		MakeVertexEnemyBullet2(i);								// 頂点情報の作成
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyBullet2(void)
{
	if (D3DTextureEnemyBullet2 != NULL)
	{	// テクスチャの開放
		D3DTextureEnemyBullet2->Release();
		D3DTextureEnemyBullet2 = NULL;
	}

	if (enemybullet2SE != NULL)
	{	// テクスチャの開放
		enemybullet2SE->Release();
		enemybullet2SE = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyBullet2(void)
{
	ENEMYBULLET2 *EnemyBullet2 = EnemyBullet2Wk;				// バレットのポインターを初期化

	for (int i = 0; i < ENEMYBULLET2_MAX; i++, EnemyBullet2++)
	{
		if (EnemyBullet2->use == true)			// 使用している状態なら更新する
		{
			// 敵のバレットの移動処理
			EnemyBullet2->pos.x += ENEMYBULLET2_SPEED;

			// 画面外まで進んだ？
			if (EnemyBullet2->pos.x < -TEXTURE_ENEMYBULLET2_SIZE_X)	// 自分の大きさを考慮して画面外か判定している
			{
				EnemyBullet2->use = false;
				EnemyBullet2->pos.x = 100.0f;
			}


			SetVertexEnemyBullet2(i);				// 移動後の座標で頂点を設定
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyBullet2(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYBULLET2 *EnemyBullet2 = EnemyBullet2Wk;				// バレットのポインターを初期化


	Device->SetFVF(FVF_VERTEX_2D);			// 頂点フォーマットの設定

	for (int i = 0; i <ENEMYBULLET2_MAX; i++, EnemyBullet2++)
	{
		if (EnemyBullet2->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			Device->SetTexture(0, EnemyBullet2->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMYBULLET2, EnemyBullet2->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemyBullet2(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYBULLET2*EnemyBullet2 = &EnemyBullet2Wk[no];			// バレットのポインターを初期化

															// 頂点座標の設定
	SetVertexEnemyBullet2(no);

	// rhwの設定
	EnemyBullet2->vertexWk[0].rhw =
		EnemyBullet2->vertexWk[1].rhw =
		EnemyBullet2->vertexWk[2].rhw =
		EnemyBullet2->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	EnemyBullet2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	EnemyBullet2->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	EnemyBullet2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	EnemyBullet2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	EnemyBullet2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	EnemyBullet2->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2, 0.0f);
	EnemyBullet2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET2);
	EnemyBullet2->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET2);

	EnemyBullet2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	EnemyBullet2->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	EnemyBullet2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	EnemyBullet2->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemyBullet2(int no, int cntPattern)
{
	ENEMYBULLET2 *EnemyBullet2 = &EnemyBullet2Wk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET2;

	EnemyBullet2->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	EnemyBullet2->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	EnemyBullet2->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	EnemyBullet2->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemyBullet2(int no)
{
	ENEMYBULLET2 *EnemyBullet2 = &EnemyBullet2Wk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	EnemyBullet2->vertexWk[0].vtx.x = EnemyBullet2->pos.x - TEXTURE_ENEMYBULLET2_SIZE_X;
	EnemyBullet2->vertexWk[0].vtx.y = EnemyBullet2->pos.y - TEXTURE_ENEMYBULLET2_SIZE_Y;
	EnemyBullet2->vertexWk[0].vtx.z = 0.0f;

	EnemyBullet2->vertexWk[1].vtx.x = EnemyBullet2->pos.x + TEXTURE_ENEMYBULLET2_SIZE_X;
	EnemyBullet2->vertexWk[1].vtx.y = EnemyBullet2->pos.y - TEXTURE_ENEMYBULLET2_SIZE_Y;
	EnemyBullet2->vertexWk[1].vtx.z = 0.0f;

	EnemyBullet2->vertexWk[2].vtx.x = EnemyBullet2->pos.x - TEXTURE_ENEMYBULLET2_SIZE_X;
	EnemyBullet2->vertexWk[2].vtx.y = EnemyBullet2->pos.y + TEXTURE_ENEMYBULLET2_SIZE_Y;
	EnemyBullet2->vertexWk[2].vtx.z = 0.0f;

	EnemyBullet2->vertexWk[3].vtx.x = EnemyBullet2->pos.x + TEXTURE_ENEMYBULLET2_SIZE_X;
	EnemyBullet2->vertexWk[3].vtx.y = EnemyBullet2->pos.y + TEXTURE_ENEMYBULLET2_SIZE_Y;
	EnemyBullet2->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetEnemyBullet2(D3DXVECTOR3 pos)
{
	ENEMYBULLET2 *EnemyBullet2 = &EnemyBullet2Wk[0];			// バレットのポインターを初期化
	ENEMY *enemy = GetEnemy(0);

	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < ENEMYBULLET2_MAX; i++, EnemyBullet2++)
	{
		if (EnemyBullet2->use == false)			// 未使用状態のバレットを見つける
		{
			EnemyBullet2->use = true;			// 使用状態へ変更する
			EnemyBullet2->pos = pos;				// 座標をセット


			PlaySound(enemybullet2SE, E_DS8_FLAG_NONE);  // 発射音再生

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
ENEMYBULLET2 *GetEnemyBullet2(int no)
{
	return(&EnemyBullet2Wk[no]);
}
