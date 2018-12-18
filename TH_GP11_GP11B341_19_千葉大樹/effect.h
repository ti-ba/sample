//=============================================================================
//
// エフェクト処理 [effect.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_


// マクロ定義
#define	NUM_EFFECT				(2)			// ポリゴン数

#define TEXTURE_GAME_EFFECT		_T("data/TEXTURE/pipo-btleffect036.png")	// 画像
#define TEXTURE_EFFECT_SIZE_X	(30)		// テクスチャサイズ
#define TEXTURE_EFFECT_SIZE_Y	(30)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_EFFECT	(7)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_EFFECT			(TEXTURE_PATTERN_DIVIDE_X_EFFECT*TEXTURE_PATTERN_DIVIDE_Y_EFFECT)	// アニメーションパターン数
#define TIME_ANIMATION_EFFECT			(10)	// アニメーションの切り替わるカウント

#define EFFECT_MAX						(15) // エフェクトの最大数




//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// バレット構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				time;						
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						//半径
} EFFECT;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect(int type);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos);
EFFECT *GetEffect(int no);


#endif

