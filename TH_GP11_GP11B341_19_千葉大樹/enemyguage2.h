//=============================================================================
//
// プレイヤー処理 [ENEMYGUAGE2.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _ENEMYGUAGE2_H_
#define _ENEMYGUAGE2_H_
#define	NUM_ENEMYGUAGE2		(2)					// ポリゴン数

// マクロ定義
#define TEXTURE_GAME_ENEMYGUAGE2	_T("data/TEXTURE/guage00.png")	// 画像
#define TEXTURE_ENEMYGUAGE2_SIZE_X	(100) // テクスチャサイズ
#define TEXTURE_ENEMYGUAGE2_SIZE_Y	(20) // 同上

#define TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE2	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMYGUAGE2	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ENEMYGUAGE2			(TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE2*TEXTURE_PATTERN_DIVIDE_Y_ENEMYGUAGE2)	// アニメーションパターン数
#define TIME_ANIMATION_ENEMYGUAGE2			(4)	// アニメーションの切り替わるカウント

#define ENEMYGUAGE2_MAX					(10) // エネミーゲージの最大数


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// ゲージ構造体
{

	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	int				HP = 200;						// 体力


	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーゲージの半径
	float			BaseAngle;					// エネミーゲージの角度

} ENEMYGUAGE2;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemyGuage2(int type);
void UninitEnemyGuage2(void);
void UpdateEnemyGuage2(void);
void DrawEnemyGuage2(void);
ENEMYGUAGE2 *GetEnemyGuage2(int no);


#endif
