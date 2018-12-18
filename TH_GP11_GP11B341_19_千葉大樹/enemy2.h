//=============================================================================
//
// 敵処理 [enemy.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _ENEMY2_H_
#define _ENEMY2_H_

// マクロ定義
#define	NUM_ENEMY2				(2)			// ポリゴン数

#define TEXTURE_GAME_ENEMY2		_T("data/TEXTURE/enemy01.png")	// 画像
#define TEXTURE_ENEMY2_SIZE_X	(50/2)		// テクスチャサイズ
#define TEXTURE_ENEMY2_SIZE_Y	(50/2)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY2	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY2	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ENEMY2			(TEXTURE_PATTERN_DIVIDE_X_ENEMY2*TEXTURE_PATTERN_DIVIDE_Y_ENEMY2)	// アニメーションパターン数
#define TIME_ANIMATION_ENEMY2			(5)	// アニメーションの切り替わるカウント

#define ENEMY2_MAX						(5) // 敵の最大数

#define ENEMY2_SPEED			(1.5f)		// エネミーの移動スピード

#define START_COUNT2			(60.0f)	// 発射時間カウント

// エネミー構造体
typedef struct	
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

	int				bulletTime;					// 弾発射間隔
	int				Startweit;					// 登場時間
	int				cnt;
	int				firecount;
} ENEMY2;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy2(int type);
void UninitEnemy2(void);
void UpdateEnemy2(void);
void DrawEnemy2(void);
ENEMY2 *GetEnemy2(int no);


#endif
