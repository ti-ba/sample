//=============================================================================
//
// タイトル画面処理 [gamestart.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _GAMESTART_H_
#define _GAMESTART_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_GAME_START		_T("data/TEXTURE/background_3.jpg")			// 読み込むテクスチャファイル名
#define	TEXTURE_GAME_START_LOGO	_T("data/TEXTURE/gamestart_logo.png")		// 読み込むテクスチャファイル名
#define	GAMESTART_POS_X			(0)								// タイトルの表示位置
#define	GAMESTART_POS_Y			(0)								// タイトルの表示位置
#define	GAMESTART_SIZE_X		(800)							// タイトルの幅
#define	GAMESTART_SIZE_Y		(600)							// タイトルの高さ

#define	GAMESTARTLOGO_POS_X		(80)							// タイトルロゴの表示位置
#define	GAMESTARTLOGO_POS_Y		(150)							// タイトルロゴの表示位置
#define	GAMESTARTLOGO_SIZE_X	(480)							// タイトルロゴの幅
#define	GAMESTARTLOGO_SIZE_Y	(80)							// タイトルロゴの高さ

#define	TEXTURE_PUSH_LOGO	_T("data/TEXTURE/push2.png")		// 読み込むテクスチャファイル名
#define	PUSHLOGO_POS_X		(230)							// タイトルロゴの表示位置
#define	PUSHLOGO_POS_Y		(270)							// タイトルロゴの表示位置
#define	PUSHLOGO_SIZE_X	(200)							// タイトルロゴの幅
#define	PUSHLOGO_SIZE_Y	(200)							// タイトルロゴの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGameStart(void);
void UninitGameStart(void);
void UpdateGameStart(void);
void DrawGameStart(void);

#endif
