//=============================================================================
//
// タイトル画面処理 [gameover.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_GAMEOVER		_T("data/TEXTURE/gameover.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_GAMEOVER_LOGO	_T("data/TEXTURE/gameover_logo.png")	// 読み込むテクスチャファイル名
#define	GAMEOVER_POS_X		(0)								// タイトルの表示位置
#define	GAMEOVER_POS_Y		(0)								// タイトルの表示位置
#define	GAMEOVER_SIZE_X		(800)							// タイトルの幅
#define	GAMEOVER_SIZE_Y		(600)							// タイトルの高さ
#define	GAMEOVERLOGO_POS_X	(160)							// タイトルロゴの表示位置
#define	GAMEOVERLOGO_POS_Y	(200)							// タイトルロゴの表示位置
#define	GAMEOVERLOGO_SIZE_X	(480)							// タイトルロゴの幅
#define	GAMEOVERLOGO_SIZE_Y	(80)							// タイトルロゴの高さ


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGameover(void);
void UninitGameover(void);
void UpdateGameover(void);
void DrawGameover(void);

#endif
