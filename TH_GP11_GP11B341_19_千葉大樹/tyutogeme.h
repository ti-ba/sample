//=============================================================================
//
// �^�C�g����ʏ��� [tyutogeme.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _TYUTOGAME_H_
#define _TYUTOGAME_H_
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_TYUTOBG		_T("data/TEXTURE/background_3.jpg")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define TYUTOBG_POS_X			(0)								// �w�i�̕\���ʒu
#define TYUTOBG_POS_Y			(0)								// �w�i�̕\���ʒu
#define TYUTOBG_SIZE_X		(800)								// �w�i�̕�
#define TYUTOBG_SIZE_Y		(600)								// �w�i�̍���

#define	TEXTURE_TYUTOBG2		_T("data/TEXTURE/background_3.jpg")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TYUTOBG2_POS_X			(0)								// �w�i�̕\���ʒu
#define	TYUTOBG2_POS_Y			(0)								// �w�i�̕\���ʒu
#define	TYUTOBG2_SIZE_X		(800)								// �w�i�̕�
#define	TYUTOBG2_SIZE_Y		(600)								// �w�i�̍���

#define	TEXTURE_DESCRIPTION_LOGO	_T("data/TEXTURE/Description2.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	DESCRIPTIONLOGO_POS_X	(50)							// �^�C�g�����S�̕\���ʒu
#define	DESCRIPTIONLOGO_POS_Y	(350)							// �^�C�g�����S�̕\���ʒu
#define	DESCRIPTIONLOGO_SIZE_X	(150)						// �^�C�g�����S�̕�
#define	DESCRIPTIONLOGO_SIZE_Y	(100)						// �^�C�g�����S�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTyutoGame(HWND hWnd, BOOL bWindow);
void UninitTyutoGame(void);
void UpdateTyutoGame(void);
void DrawTyutoGame(void);

LPDIRECT3DDEVICE9 GetDevice(void);		// �f�o�C�X�擾�֐�




#endif
