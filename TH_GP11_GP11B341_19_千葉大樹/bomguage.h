//=============================================================================
//
// �v���C���[���� [bomguage.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _BOMUAGE_H
#define _BOMUAGE_H

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_BOMGUAGE		(2)					// �|���S����

#define TEXTURE_GAME_BOMGUAGE	_T("data/TEXTURE/guage00.png")	// �摜
#define TEXTURE_BOMGUAGE_SIZE_X	(200/2) // �e�N�X�`���T�C�Y
#define TEXTURE_BOMGUAGE_SIZE_Y	(50/2) // ����

#define TEXTURE_PATTERN_DIVIDE_X_BOMGUAGE	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BOMGUAGE	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BOMGUAGE			(TEXTURE_PATTERN_DIVIDE_X_BOMGUAGE*TEXTURE_PATTERN_DIVIDE_Y_BOMGUAGE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BOMGUAGE				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BOMGUAGE_MAX					(1) // �Q�[�W�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �Q�[�W�\����
{

	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���


	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �Q�[�W�̔��a
	float			BaseAngle;					// �Q�[�W�̊p�x

} BOMGUAGE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBomGuage(int type);
void UninitBomGuage(void);
void UpdateBomGuage(void);
void DrawBomGuage(void);
BOMGUAGE *GetBomGuage(int no);


#endif