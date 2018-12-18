//=============================================================================
//
// ボム処理 [bom.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _BOM_H_
#define _BOM_H_


// マクロ定義
#define	NUM_BOM				(2)			// ポリゴン数

#define TEXTURE_GAME_BOM		_T("data/TEXTURE/bullet04.png")	// 画像
#define TEXTURE_BOM_SIZE_X	(50/2)		// テクスチャサイズ
#define TEXTURE_BOM_SIZE_Y	(50/2)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_BOM	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BOM	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BOM			(TEXTURE_PATTERN_DIVIDE_X_BOM*TEXTURE_PATTERN_DIVIDE_Y_BOM)	// アニメーションパターン数
#define TIME_ANIMATION_BOM			(10)	// アニメーションの切り替わるカウント

#define BOM_MAX						(10) // バレットの最大数

#define BOM_SPEED			(10.0f)		// バレットの移動スピード


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// ボム構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
	
	float			Radius;						//半径
} BOM;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBom(int type);
void UninitBom(void);
void UpdateBom(void);
void DrawBom(void);
void SetBom(D3DXVECTOR3 pos);
BOM *GetBom(int no);


#endif

