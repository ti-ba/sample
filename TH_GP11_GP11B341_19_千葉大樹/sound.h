//==================================
//
//  GP_11B_341_19 ��t�@���
//
//==================================

#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

// �}�N����`
enum
{	// �T�E���h�ʂ��i���o�[
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
{	// �Đ��p�t���O
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,/* DSBPLAY_LOOPING = 1,*/
	E_DS8_FLAG_MAX
};

HRESULT					InitSound( HWND hWnd );	// ������
void					UninitSound();			// ��Еt��
LPDIRECTSOUNDBUFFER8	LoadSound( int no );	// �T�E���h�̃��[�h
void					PlaySound( LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0 );	// �����ƂɍĐ�
bool					IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer );					// �Đ������ǂ���

#endif