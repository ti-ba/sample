//=============================================================================
//
// エフェクト処理 [effect2.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _EFFECT2_H_
#define _EFFECT2_H_


// マクロ定義
#define	NUM_EFFECT2				(2)			// ポリゴン数

#define TEXTURE_GAME_EFFECT2		_T("data/TEXTURE/pipo-btleffect003.png")	// 画像
#define TEXTURE_EFFECT2_SIZE_X	(100)		// テクスチャサイズ
#define TEXTURE_EFFECT2_SIZE_Y	(100)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_EFFECT2	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT2	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_EFFECT2			(TEXTURE_PATTERN_DIVIDE_X_EFFECT2*TEXTURE_PATTERN_DIVIDE_Y_EFFECT2)	// アニメーションパターン数
#define TIME_ANIMATION_EFFECT2			(10)	// アニメーションの切り替わるカウント

#define EFFECT2_MAX						(15)  // エフェクトの最大数




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
	int				time;						//  
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						//半径
} EFFECT2;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect2(int type);
void UninitEffect2(void);
void UpdateEffect2(void);
void DrawEffect2(void);
void SetEffect2(D3DXVECTOR3 pos);
EFFECT2 *GetEffect2(int no);


#endif

