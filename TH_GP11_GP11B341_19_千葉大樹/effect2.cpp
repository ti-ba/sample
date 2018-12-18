//=============================================================================
//
// エフェクト処理 [effect2.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "effect2.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEffect2(int no);
void SetTextureEffect2(int no, int cntPattern);
void SetVertexEffect2(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureEffect2 = NULL;		// テクスチャへのポリゴン

EFFECT2					effect2Wk[EFFECT2_MAX];			// バレット構造体
LPDIRECTSOUNDBUFFER8	effect2SE;						// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect2(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	EFFECT2 *effect2 = &effect2Wk[0];		// エネミーのポインターを初期化

										// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
			TEXTURE_GAME_EFFECT2,			// ファイルの名前
			&D3DTextureEffect2);			// 読み込むメモリのポインタ

		effect2SE = LoadSound(SHOT_00);

	}

	// バレットの初期化処理
	for (int i = 0; i < EFFECT2_MAX; i++, effect2++)
	{
		effect2->use = false;									// 未使用（発射されていない弾）
		effect2->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);		// 座標データを初期化
		effect2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 回転データを初期化
		effect2->PatternAnim = 0;								// アニメパターン番号をランダムで初期化
		effect2->CountAnim = 0;									// アニメカウントを初期化

		effect2->Texture = D3DTextureEffect2;					// テクスチャ情報
		MakeVertexEffect2(i);									// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect2(void)
{
	if (D3DTextureEffect2 != NULL)
	{	// テクスチャの開放
		D3DTextureEffect2->Release();
		D3DTextureEffect2 = NULL;
	}

	if (effect2SE != NULL)
	{	// テクスチャの開放
		effect2SE->Release();
		effect2SE = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect2(void)
{
	EFFECT2 *effect2 = effect2Wk;				// バレットのポインターを初期化

	for (int i = 0; i < EFFECT2_MAX; i++, effect2++)
	{
		if ((effect2->use == true) && (effect2->time >= 0))			// 使用している状態なら更新する
		{
			// アニメーション
			effect2->CountAnim++;
			if ((effect2->CountAnim % TIME_ANIMATION_EFFECT2) == 0)
			{
				// パターンの切り替え
				effect2->PatternAnim = (effect2->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT2;

				// テクスチャ座標を設定
				SetTextureEffect2(i, effect2->PatternAnim);
			}

			SetVertexEffect2(i);				// 移動後の座標で頂点を設定
		}
		effect2->time -= 1;
		if (effect2->time == 0)
		{
			effect2->use = false;
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect2(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	EFFECT2 *effect2 = effect2Wk;				// バレットのポインターを初期化

											// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT2_MAX; i++, effect2++)
	{
		if (effect2->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			Device->SetTexture(0, effect2->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT2, effect2->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect2(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	EFFECT2 *effect2 = &effect2Wk[no];			// バレットのポインターを初期化

											// 頂点座標の設定
	SetVertexEffect2(no);

	// rhwの設定
	effect2->vertexWk[0].rhw =
	effect2->vertexWk[1].rhw =
	effect2->vertexWk[2].rhw =
	effect2->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	effect2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect2->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	effect2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect2->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT2, 0.0f);
	effect2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT2);
	effect2->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT2, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT2);

	effect2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect2->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	effect2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	effect2->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEffect2(int no, int cntPattern)
{
	EFFECT2 *effect2 = &effect2Wk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT2;

	effect2->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	effect2->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	effect2->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	effect2->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEffect2(int no)
{
	EFFECT2 *effect2 = &effect2Wk[no];			// バレットのポインターを初期化

											// 頂点座標の設定
	effect2->vertexWk[0].vtx.x = effect2->pos.x - TEXTURE_EFFECT2_SIZE_X;
	effect2->vertexWk[0].vtx.y = effect2->pos.y - TEXTURE_EFFECT2_SIZE_Y;
	effect2->vertexWk[0].vtx.z = 0.0f;

	effect2->vertexWk[1].vtx.x = effect2->pos.x + TEXTURE_EFFECT2_SIZE_X;
	effect2->vertexWk[1].vtx.y = effect2->pos.y - TEXTURE_EFFECT2_SIZE_Y;
	effect2->vertexWk[1].vtx.z = 0.0f;

	effect2->vertexWk[2].vtx.x = effect2->pos.x - TEXTURE_EFFECT2_SIZE_X;
	effect2->vertexWk[2].vtx.y = effect2->pos.y + TEXTURE_EFFECT2_SIZE_Y;
	effect2->vertexWk[2].vtx.z = 0.0f;

	effect2->vertexWk[3].vtx.x = effect2->pos.x + TEXTURE_EFFECT2_SIZE_X;
	effect2->vertexWk[3].vtx.y = effect2->pos.y + TEXTURE_EFFECT2_SIZE_Y;
	effect2->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エフェクトの発射設定
//=============================================================================
void SetEffect2(D3DXVECTOR3 pos)
{
	EFFECT2 *effect2 = &effect2Wk[0];			// エフェクトのポインターを初期化

	for (int i = 0; i < EFFECT2_MAX; i++, effect2++)
	{
		if (effect2->use == false)			// 未使用状態のバレットを見つける
		{
			effect2->use = true;				// 使用状態へ変更する
			effect2->pos = pos;				// 座標をセット


			effect2->time = 60;

			return;							// 1発セットしたので終了する
		}
	}
}

//=============================================================================
// バレット取得関数
//=============================================================================
EFFECT2 *GetEffect2(int no)
{
	return(&effect2Wk[no]);
}

