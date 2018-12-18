//=============================================================================
//
// クリア画面処理 [curea.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _CUREA_H_
#define _CUREA_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_CUREA		_T("data/TEXTURE/bg001.jpg")			// 読み込むテクスチャファイル名
#define	TEXTURE_CUREA_LOGO	_T("data/TEXTURE/gamecurea_logo.png")	// 読み込むテクスチャファイル名
#define	CUREA_POS_X			(0)							// クリアの表示位置
#define	CUREA_POS_Y			(0)							// クリアの表示位置
#define	CUREA_SIZE_X			(800)					// クリアの幅
#define	CUREA_SIZE_Y			(600)					// クリアの高さ
#define	CUREALOGO_POS_X		(160)						// クリアロゴの表示位置
#define	CUREALOGO_POS_Y		(200)						// クリアロゴの表示位置
#define	CUREALOGO_SIZE_X		(480)					// クリアロゴの幅
#define	CUREALOGO_SIZE_Y		(80)					// クリアロゴの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCurea(void);
void UninitCurea(void);
void UpdateCurea(void);
void DrawCurea(void);

#endif
