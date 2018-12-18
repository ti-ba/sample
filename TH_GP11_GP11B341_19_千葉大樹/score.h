//=============================================================================
//
// �X�R�A���� [score.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

// �}�N����`
#define	TEXTURE_GAME_SCORE		_T("data/TEXTURE/bg002.jpg")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_GAME_SCORE_LOGO	_T("data/TEXTURE/number16x32.png")		// �T���v���p�摜
#define SCORE_POS_X			(0)					// �^�C�g���̕\���ʒu
#define SCORE_POS_Y			(0)					// �^�C�g���̕\���ʒu
#define SCORE_SIZE_X		(800)				// �^�C�g���̕�
#define SCORE_SIZE_Y		(600)				// �^�C�g���̍���
#define TEXTURE_SCORE_LOGO_SIZE_X	(20)		// �e�N�X�`���T�C�Y
#define TEXTURE_SCORE_LOGO_SIZE_Y	(64)		// ����
#define SCORE_LOGO_POS_X			(350)		// �|���S���̏����ʒuX
#define SCORE_LOGO_POS_Y			(230)		// ����
#define SCORE_LOGO_MAX			(99999)			// �X�R�A�̍ő�l
#define SCORE_LOGO_DIGIT			(5)			// ����


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore( int add );

#endif
