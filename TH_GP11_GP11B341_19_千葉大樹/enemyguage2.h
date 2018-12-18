//=============================================================================
//
// �v���C���[���� [ENEMYGUAGE2.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _ENEMYGUAGE2_H_
#define _ENEMYGUAGE2_H_
#define	NUM_ENEMYGUAGE2		(2)					// �|���S����

// �}�N����`
#define TEXTURE_GAME_ENEMYGUAGE2	_T("data/TEXTURE/guage00.png")	// �摜
#define TEXTURE_ENEMYGUAGE2_SIZE_X	(100) // �e�N�X�`���T�C�Y
#define TEXTURE_ENEMYGUAGE2_SIZE_Y	(20) // ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE2	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMYGUAGE2	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMYGUAGE2			(TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE2*TEXTURE_PATTERN_DIVIDE_Y_ENEMYGUAGE2)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMYGUAGE2			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define ENEMYGUAGE2_MAX					(10) // �G�l�~�[�Q�[�W�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �Q�[�W�\����
{

	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	int				HP = 200;						// �̗�


	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�Q�[�W�̔��a
	float			BaseAngle;					// �G�l�~�[�Q�[�W�̊p�x

} ENEMYGUAGE2;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemyGuage2(int type);
void UninitEnemyGuage2(void);
void UpdateEnemyGuage2(void);
void DrawEnemyGuage2(void);
ENEMYGUAGE2 *GetEnemyGuage2(int no);


#endif
