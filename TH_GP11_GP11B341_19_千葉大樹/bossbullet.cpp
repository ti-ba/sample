//=============================================================================
//
// バレット処理 [bossbullet.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "bossbullet.h"
#include "boss.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBossBullet(int no);
void SetTextureBossBullet(int no, int cntPattern);
void SetVertexBossBullet(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureBossBullet = NULL;		// テクスチャへのポリゴン

BOSSBULLET				bossbulletWk[BOSSBULLET_MAX];			// バレット構造体
LPDIRECTSOUNDBUFFER8	bossbulletSE;						// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBossBullet(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSBULLET *bossbullet = &bossbulletWk[0];		// エネミーのポインターを初期化

										// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
			TEXTURE_GAME_BOSSBULLET,		// ファイルの名前
			&D3DTextureBossBullet);			// 読み込むメモリのポインタ

		bossbulletSE = LoadSound(SHOT_00);

	}

	// バレットの初期化処理
	for (int i = 0; i < BOSSBULLET_MAX; i++, bossbullet++)
	{
		bossbullet->use = false;									// 未使用（発射されていない弾）
		bossbullet->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// 座標データを初期化
		bossbullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 回転データを初期化
		bossbullet->PatternAnim = 0;								// アニメパターン番号をランダムで初期化
		bossbullet->CountAnim = 0;									// アニメカウントを初期化

		bossbullet->Texture = D3DTextureBossBullet;					// テクスチャ情報
		MakeVertexBossBullet(i);									// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBossBullet(void)
{
	if (D3DTextureBossBullet != NULL)
	{	// テクスチャの開放
		D3DTextureBossBullet->Release();
		D3DTextureBossBullet = NULL;
	}

	if (bossbulletSE != NULL)
	{	// テクスチャの開放
		bossbulletSE->Release();
		bossbulletSE = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBossBullet(void)
{
	BOSSBULLET *bossbullet = &bossbulletWk[0];		// エネミーのポインターを初期化

	for (int i = 0; i < BOSSBULLET_MAX; i++, bossbullet++)
	{
		if (bossbullet->use == true)			// 使用している状態なら更新する
		{
			// バレットの移動処理
			bossbullet->pos.y += BOSSBULLET_SPEED;

			// 画面外まで進んだ？
			if (bossbullet->pos.y < -TEXTURE_BOSSBULLET_SIZE_Y)	// 自分の大きさを考慮して画面外か判定している
			{
				bossbullet->use = false;
				bossbullet->pos.x = -100.0f;
			}

			SetVertexBossBullet(i);				// 移動後の座標で頂点を設定
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBossBullet(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSBULLET *bossbullet = &bossbulletWk[0];		// エネミーのポインターを初期化

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSSBULLET_MAX; i++, bossbullet++)
	{
		if (bossbullet->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			Device->SetTexture(0, bossbullet->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSSBULLET, bossbullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBossBullet(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSBULLET *bossbullet = &bossbulletWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	SetVertexBossBullet(no);

	// rhwの設定
	bossbullet->vertexWk[0].rhw =
	bossbullet->vertexWk[1].rhw =
	bossbullet->vertexWk[2].rhw =
	bossbullet->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bossbullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bossbullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bossbullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bossbullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	bossbullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bossbullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET, 0.0f);
	bossbullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSSBULLET);
	bossbullet->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSSBULLET);

	bossbullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bossbullet->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bossbullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bossbullet->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBossBullet(int no, int cntPattern)
{
	BOSSBULLET *bossbullet = &bossbulletWk[no];			// バレットのポインターを初期化

											// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSSBULLET;

	bossbullet->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	bossbullet->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	bossbullet->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	bossbullet->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBossBullet(int no)
{
	BOSSBULLET *bossbullet = &bossbulletWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	bossbullet->vertexWk[0].vtx.x = bossbullet->pos.x - TEXTURE_BOSSBULLET_SIZE_X;
	bossbullet->vertexWk[0].vtx.y = bossbullet->pos.y - TEXTURE_BOSSBULLET_SIZE_Y;
	bossbullet->vertexWk[0].vtx.z = 0.0f;

	bossbullet->vertexWk[1].vtx.x = bossbullet->pos.x + TEXTURE_BOSSBULLET_SIZE_X;
	bossbullet->vertexWk[1].vtx.y = bossbullet->pos.y - TEXTURE_BOSSBULLET_SIZE_Y;
	bossbullet->vertexWk[1].vtx.z = 0.0f;

	bossbullet->vertexWk[2].vtx.x = bossbullet->pos.x - TEXTURE_BOSSBULLET_SIZE_X;
	bossbullet->vertexWk[2].vtx.y = bossbullet->pos.y + TEXTURE_BOSSBULLET_SIZE_Y;
	bossbullet->vertexWk[2].vtx.z = 0.0f;

	bossbullet->vertexWk[3].vtx.x = bossbullet->pos.x + TEXTURE_BOSSBULLET_SIZE_X;
	bossbullet->vertexWk[3].vtx.y = bossbullet->pos.y + TEXTURE_BOSSBULLET_SIZE_Y;
	bossbullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetBossBullet(D3DXVECTOR3 pos)
{
	BOSSBULLET *bossbullet = &bossbulletWk[0];			// バレットのポインターを初期化
	BOSS *boss = GetBoss(0);
											// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < BOSSBULLET_MAX; i++, bossbullet++)
	{
		if (bossbullet->use == false)			// 未使用状態のバレットを見つける
		{
			bossbullet->use = true;				// 使用状態へ変更する
			bossbullet->pos = pos;				// 座標をセット


			// 発射音再生
			PlaySound(bossbulletSE, E_DS8_FLAG_NONE);
			return;								// 1発セットしたので終了する

		}
	}
}

//=============================================================================
// バレット取得関数
//=============================================================================
BOSSBULLET *GetBossBullet(int no)
{
	return(&bossbulletWk[no]);
}
