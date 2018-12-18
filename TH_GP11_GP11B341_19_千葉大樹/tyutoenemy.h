//=============================================================================
//
// 敵処理 [TYUTOENEMY.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _TYUTOENEMY_H_
#define _TYUTOENEMY_H_


// マクロ定義
#define	NUM_TYUTOENEMY				(2)			// ポリゴン数

#define TEXTURE_GAME_TYUTOENEMY		_T("data/TEXTURE/enemy00.png")	// 画像
#define TEXTURE_TYUTOENEMY_SIZE_X	(50/2)		// テクスチャサイズ
#define TEXTURE_TYUTOENEMY_SIZE_Y	(50/2)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_TYUTOENEMY	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_TYUTOENEMY			(TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY*TEXTURE_PATTERN_DIVIDE_Y_TYUTOENEMY)	// アニメーションパターン数
#define TIME_ANIMATION_TYUTOENEMY			(4)	// アニメーションの切り替わるカウント

#define TYUTOENEMY_MAX						(4) // 敵の最大数

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

} TYUTOENEMY;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTyutoEnemy(int type);
void UninitTyutoEnemy(void);
void UpdateTyutoEnemy(void);
void DrawTyutoEnemy(void);
TYUTOENEMY *GetTyutoEnemy(int no);


#endif

