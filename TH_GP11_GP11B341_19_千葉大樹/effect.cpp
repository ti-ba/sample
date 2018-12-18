//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "effect.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEffect(int no);
void SetTextureEffect(int no, int cntPattern);
void SetVertexEffect(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureEffect = NULL;		// テクスチャへのポリゴン

EFFECT					effectWk[EFFECT_MAX];			// バレット構造体
LPDIRECTSOUNDBUFFER8	effectSE;						// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	EFFECT *effect = &effectWk[0];		// エネミーのポインターを初期化

										// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
			TEXTURE_GAME_EFFECT,			// ファイルの名前
			&D3DTextureEffect);			// 読み込むメモリのポインタ

		effectSE = LoadSound(SHOT_00);

	}

	// エフェクトの初期化処理
	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		effect->use = false;									// 未使用（発射されていない弾）
		effect->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// 座標データを初期化
		effect->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 回転データを初期化
		effect->PatternAnim = 0;								// アニメパターン番号をランダムで初期化
		effect->CountAnim = 0;									// アニメカウントを初期化

		effect->Texture = D3DTextureEffect;						// テクスチャ情報
		MakeVertexEffect(i);									// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	if (D3DTextureEffect != NULL)
	{	// テクスチャの開放
		D3DTextureEffect->Release();
		D3DTextureEffect = NULL;
	}

	if (effectSE != NULL)
	{	// テクスチャの開放
		effectSE->Release();
		effectSE = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	EFFECT *effect = effectWk;				// バレットのポインターを初期化

	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		if ((effect->use == true)&&(effect->time>=0))			// 使用している状態なら更新する
		{
			// アニメーション
			effect->CountAnim++;
			if ((effect->CountAnim % TIME_ANIMATION_EFFECT) == 0)
			{
				// パターンの切り替え
				effect->PatternAnim = (effect->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT;

				// テクスチャ座標を設定
				SetTextureEffect(i, effect->PatternAnim);
			}

			SetVertexEffect(i);				// 移動後の座標で頂点を設定
		}
		effect->time -= 1;
		if (effect->time == 0)
		{
			effect->use = false;
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	EFFECT *effect = effectWk;				// バレットのポインターを初期化

											// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		if (effect->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			Device->SetTexture(0, effect->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT, effect->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	EFFECT *effect = &effectWk[no];			// バレットのポインターを初期化

											// 頂点座標の設定
	SetVertexEffect(no);

	// rhwの設定
	effect->vertexWk[0].rhw =
		effect->vertexWk[1].rhw =
		effect->vertexWk[2].rhw =
		effect->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	effect->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	effect->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT, 0.0f);
	effect->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT);
	effect->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT);

	effect->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	effect->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	effect->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEffect(int no, int cntPattern)
{
	EFFECT *effect = &effectWk[no];			// バレットのポインターを初期化

											// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT;

	effect->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	effect->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	effect->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	effect->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEffect(int no)
{
	EFFECT *effect = &effectWk[no];			// バレットのポインターを初期化

											// 頂点座標の設定
	effect->vertexWk[0].vtx.x = effect->pos.x - TEXTURE_EFFECT_SIZE_X;
	effect->vertexWk[0].vtx.y = effect->pos.y - TEXTURE_EFFECT_SIZE_Y;
	effect->vertexWk[0].vtx.z = 0.0f;

	effect->vertexWk[1].vtx.x = effect->pos.x + TEXTURE_EFFECT_SIZE_X;
	effect->vertexWk[1].vtx.y = effect->pos.y - TEXTURE_EFFECT_SIZE_Y;
	effect->vertexWk[1].vtx.z = 0.0f;

	effect->vertexWk[2].vtx.x = effect->pos.x - TEXTURE_EFFECT_SIZE_X;
	effect->vertexWk[2].vtx.y = effect->pos.y + TEXTURE_EFFECT_SIZE_Y;
	effect->vertexWk[2].vtx.z = 0.0f;

	effect->vertexWk[3].vtx.x = effect->pos.x + TEXTURE_EFFECT_SIZE_X;
	effect->vertexWk[3].vtx.y = effect->pos.y + TEXTURE_EFFECT_SIZE_Y;
	effect->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エフェクトの発射設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos)
{
	EFFECT *effect = &effectWk[0];			// エフェクトのポインターを初期化

	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		if (effect->use == false)			// 未使用状態のバレットを見つける
		{
			effect->use = true;				// 使用状態へ変更する
			effect->pos = pos;				// 座標をセット

											
			effect->time = 60;

			return;							// 1発セットしたので終了する
		}
	}
}

//=============================================================================
// バレット取得関数
//=============================================================================
EFFECT *GetEffect(int no)
{
	return(&effectWk[no]);
}

