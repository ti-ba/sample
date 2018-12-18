//=============================================================================
//
// 敵処理 [enemy.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_


// マクロ定義
#define	NUM_ENEMY				(2)			// ポリゴン数

#define TEXTURE_GAME_ENEMY		_T("data/TEXTURE/enemy00.png")	// 画像
#define TEXTURE_ENEMY_SIZE_X	(50/2)		// テクスチャサイズ
#define TEXTURE_ENEMY_SIZE_Y	(50/2)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ENEMY			(TEXTURE_PATTERN_DIVIDE_X_ENEMY*TEXTURE_PATTERN_DIVIDE_Y_ENEMY)	// アニメーションパターン数
#define TIME_ANIMATION_ENEMY			(5)	// アニメーションの切り替わるカウント

#define ENEMY_MAX						(10) // 敵の最大数

#define ENEMY_SPEED			(1.5f)		// エネミーの移動スピード

#define START_COUNT			(-170.0f)	// 発射時間カウント




//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
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
} ENEMY;





//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(int type);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(int no);


#endif
