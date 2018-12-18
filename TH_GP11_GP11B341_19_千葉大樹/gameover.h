//=============================================================================
//
// �^�C�g����ʏ��� [gameover.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_GAMEOVER		_T("data/TEXTURE/gameover.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_GAMEOVER_LOGO	_T("data/TEXTURE/gameover_logo.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	GAMEOVER_POS_X		(0)								// �^�C�g���̕\���ʒu
#define	GAMEOVER_POS_Y		(0)								// �^�C�g���̕\���ʒu
#define	GAMEOVER_SIZE_X		(800)							// �^�C�g���̕�
#define	GAMEOVER_SIZE_Y		(600)							// �^�C�g���̍���
#define	GAMEOVERLOGO_POS_X	(160)							// �^�C�g�����S�̕\���ʒu
#define	GAMEOVERLOGO_POS_Y	(200)							// �^�C�g�����S�̕\���ʒu
#define	GAMEOVERLOGO_SIZE_X	(480)							// �^�C�g�����S�̕�
#define	GAMEOVERLOGO_SIZE_Y	(80)							// �^�C�g�����S�̍���


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGameover(void);
void UninitGameover(void);
void UpdateGameover(void);
void DrawGameover(void);

#endif
