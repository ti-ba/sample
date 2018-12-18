//=============================================================================
//
// �v���C���[���� [ENEMYGUAGE.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _ENEMYGUAGE_H_
#define _ENEMYGUAGE_H_
#define	NUM_ENEMYGUAGE		(2)					// �|���S����

// �}�N����`


#define TEXTURE_GAME_ENEMYGUAGE	_T("data/TEXTURE/guage01 .png")	// �摜
#define TEXTURE_ENEMYGUAGE_SIZE_X	(100) // �e�N�X�`���T�C�Y
#define TEXTURE_ENEMYGUAGE_SIZE_Y	(20) // ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMYGUAGE	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMYGUAGE			(TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE*TEXTURE_PATTERN_DIVIDE_Y_ENEMYGUAGE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMYGUAGE			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define ENEMYGUAGE_MAX					(5) // �G�l�~�[�Q�[�W�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �Q�[�W�\����
{

	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	int				HP=200;						// �̗�


	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�Q�[�W�̔��a
	float			BaseAngle;					// �G�l�~�[�Q�[�W�̊p�x

} ENEMYGUAGE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemyGuage(int type);
void UninitEnemyGuage(void);
void UpdateEnemyGuage(void);
void DrawEnemyGuage(void);
ENEMYGUAGE *GetEnemyGuage(int no);


#endif