//=============================================================================
//
// �N���A��ʏ��� [curea.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _CUREA_H_
#define _CUREA_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_CUREA		_T("data/TEXTURE/bg001.jpg")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_CUREA_LOGO	_T("data/TEXTURE/gamecurea_logo.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	CUREA_POS_X			(0)							// �N���A�̕\���ʒu
#define	CUREA_POS_Y			(0)							// �N���A�̕\���ʒu
#define	CUREA_SIZE_X			(800)					// �N���A�̕�
#define	CUREA_SIZE_Y			(600)					// �N���A�̍���
#define	CUREALOGO_POS_X		(160)						// �N���A���S�̕\���ʒu
#define	CUREALOGO_POS_Y		(200)						// �N���A���S�̕\���ʒu
#define	CUREALOGO_SIZE_X		(480)					// �N���A���S�̕�
#define	CUREALOGO_SIZE_Y		(80)					// �N���A���S�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCurea(void);
void UninitCurea(void);
void UpdateCurea(void);
void DrawCurea(void);

#endif
