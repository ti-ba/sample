//=============================================================================
//
// �^�C�g����ʏ��� [gamestart.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _GAMESTART_H_
#define _GAMESTART_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_GAME_START		_T("data/TEXTURE/background_3.jpg")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_GAME_START_LOGO	_T("data/TEXTURE/gamestart_logo.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	GAMESTART_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	GAMESTART_POS_Y			(0)								// �^�C�g���̕\���ʒu
#define	GAMESTART_SIZE_X		(800)							// �^�C�g���̕�
#define	GAMESTART_SIZE_Y		(600)							// �^�C�g���̍���

#define	GAMESTARTLOGO_POS_X		(80)							// �^�C�g�����S�̕\���ʒu
#define	GAMESTARTLOGO_POS_Y		(150)							// �^�C�g�����S�̕\���ʒu
#define	GAMESTARTLOGO_SIZE_X	(480)							// �^�C�g�����S�̕�
#define	GAMESTARTLOGO_SIZE_Y	(80)							// �^�C�g�����S�̍���

#define	TEXTURE_PUSH_LOGO	_T("data/TEXTURE/push2.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	PUSHLOGO_POS_X		(230)							// �^�C�g�����S�̕\���ʒu
#define	PUSHLOGO_POS_Y		(270)							// �^�C�g�����S�̕\���ʒu
#define	PUSHLOGO_SIZE_X	(200)							// �^�C�g�����S�̕�
#define	PUSHLOGO_SIZE_Y	(200)							// �^�C�g�����S�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGameStart(void);
void UninitGameStart(void);
void UpdateGameStart(void);
void DrawGameStart(void);

#endif
