//=============================================================================
//
// �v���C���[���� [BOSSGUAGE.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _BOSSGUAGE_H_
#define _BOSSGUAGE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_BOSSGUAGE		(2)					// �|���S����

#define TEXTURE_GAME_BOSSGUAGE	_T("data/TEXTURE/guage00.png")	// �摜
#define TEXTURE_BOSSGUAGE_SIZE_X	(100) // �e�N�X�`���T�C�Y
#define TEXTURE_BOSSGUAGE_SIZE_Y	(20) // ����

#define TEXTURE_PATTERN_DIVIDE_X_BOSSGUAGE	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSSGUAGE	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BOSSGUAGE			(TEXTURE_PATTERN_DIVIDE_X_BOSSGUAGE*TEXTURE_PATTERN_DIVIDE_Y_BOSSGUAGE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BOSSGUAGE			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BOSSGUAGE_MAX					(1) // �Q�[�W�̍ő吔


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

} BOSSGUAGE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBossguage(int type);
void UninitBossguage(void);
void UpdateBossguage(void);
void DrawBossguage(void);
BOSSGUAGE *GetBossguage(int no);


#endif
