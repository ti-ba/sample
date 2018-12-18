//==================================
//
//  GP_11B_341_19 千葉　大樹
//
//==================================

#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

// マクロ定義
enum
{	// サウンド通しナンバー
	BGM_00,
	BGM_01,
	BGM_02,
	BOMB_00,
	DEFEND_00,
	DEFEND_01,
	HIT_00,
	LASER_00,
	LOCKON_00,
	SHOT_00,
	SOUND_MAX
};

enum
{	// 再生用フラグ
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,/* DSBPLAY_LOOPING = 1,*/
	E_DS8_FLAG_MAX
};

HRESULT					InitSound( HWND hWnd );	// 初期化
void					UninitSound();			// 後片付け
LPDIRECTSOUNDBUFFER8	LoadSound( int no );	// サウンドのロード
void					PlaySound( LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0 );	// 音ごとに再生
bool					IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer );					// 再生中かどうか

#endif