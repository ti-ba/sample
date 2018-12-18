//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLE		_T("data/TEXTURE/background_3.jpg")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	TITLE_POS_Y			(0)								// �^�C�g���̕\���ʒu
#define	TITLE_SIZE_X		(800)							// �^�C�g���̕�
#define	TITLE_SIZE_Y		(600)							// �^�C�g���̍���

#define	TEXTURE_TITLE_LOGO	_T("data/TEXTURE/shooting-3.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLELOGO_POS_X		(80)							// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_POS_Y		(150)							// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_SIZE_X	(480)							// �^�C�g�����S�̕�
#define	TITLELOGO_SIZE_Y	(100)							// �^�C�g�����S�̍���

#define	TEXTURE_TITLE2		_T("data/TEXTURE/background_3.jpg")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE2_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	TITLE2_POS_Y			(0)								// �^�C�g���̕\���ʒu
#define	TITLE2_SIZE_X		(800)							// �^�C�g���̕�
#define	TITLE2_SIZE_Y		(600)							// �^�C�g���̍���

#define	TEXTURE_PUSH_LOGO	_T("data/TEXTURE/push2.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	PUSHLOGO_POS_X		(230)							// �^�C�g�����S�̕\���ʒu
#define	PUSHLOGO_POS_Y		(270)							// �^�C�g�����S�̕\���ʒu
#define	PUSHLOGO_SIZE_X	(200)							// �^�C�g�����S�̕�
#define	PUSHLOGO_SIZE_Y	(200)							// �^�C�g�����S�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif
