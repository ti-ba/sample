//=============================================================================
//
// �v���C���[���� [GUAGE.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _GUAGE_H_
#define _GUAGE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_GUAGE		(2)					// �|���S����

#define TEXTURE_GAME_GUAGE	_T("data/TEXTURE/guage00.png")	// �摜
#define TEXTURE_GUAGE_SIZE_X	(100) // �e�N�X�`���T�C�Y
#define TEXTURE_GUAGE_SIZE_Y	(20) // ����

#define TEXTURE_PATTERN_DIVIDE_X_GUAGE	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_GUAGE	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_GUAGE			(TEXTURE_PATTERN_DIVIDE_X_GUAGE*TEXTURE_PATTERN_DIVIDE_Y_GUAGE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_GUAGE				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define GUAGE_MAX					(1) // �Q�[�W�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �Q�[�W�\����
{
	
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	int				HP;

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �Q�[�W�̔��a
	float			BaseAngle;					// �Q�[�W�̊p�x

} GUAGE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGuage(int type);
void UninitGuage(void);
void UpdateGuage(void);
void DrawGuage(void);
GUAGE *GetGuage(int no);


#endif