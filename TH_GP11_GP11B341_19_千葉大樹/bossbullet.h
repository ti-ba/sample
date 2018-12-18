//=============================================================================
//
// バレット処理 [bossbullet.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _BOSSBULLET_H_
#define _BOSSBULLET_H_


// マクロ定義
#define	NUM_BOSSBULLET				(2)			// ポリゴン数

#define TEXTURE_GAME_BOSSBULLET		_T("data/TEXTURE/bullet04.jpg")	// 画像
#define TEXTURE_BOSSBULLET_SIZE_X	(40)		// テクスチャサイズ
#define TEXTURE_BOSSBULLET_SIZE_Y	(40)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSSBULLET	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BOSSBULLET			(TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET*TEXTURE_PATTERN_DIVIDE_Y_BOSSBULLET)	// アニメーションパターン数
#define TIME_ANIMATION_BOSSBULLET			(10)	// アニメーションの切り替わるカウント

#define BOSSBULLET_MAX						(100) // バレットの最大数

#define BOSSBULLET_SPEED			(7.0f)		// バレットの移動スピード


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

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						//半径
} BOSSBULLET;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBossBullet(int type);
void UninitBossBullet(void);
void UpdateBossBullet(void);
void DrawBossBullet(void);
void SetBossBullet(D3DXVECTOR3 pos);
BOSSBULLET *GetBossBullet(int no);


#endif
