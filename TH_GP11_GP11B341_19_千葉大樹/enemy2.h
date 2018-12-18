//=============================================================================
//
// �G���� [enemy.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _ENEMY2_H_
#define _ENEMY2_H_

// �}�N����`
#define	NUM_ENEMY2				(2)			// �|���S����

#define TEXTURE_GAME_ENEMY2		_T("data/TEXTURE/enemy01.png")	// �摜
#define TEXTURE_ENEMY2_SIZE_X	(50/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMY2_SIZE_Y	(50/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY2	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY2	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMY2			(TEXTURE_PATTERN_DIVIDE_X_ENEMY2*TEXTURE_PATTERN_DIVIDE_Y_ENEMY2)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMY2			(5)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define ENEMY2_MAX						(5) // �G�̍ő吔

#define ENEMY2_SPEED			(1.5f)		// �G�l�~�[�̈ړ��X�s�[�h

#define START_COUNT2			(60.0f)	// ���ˎ��ԃJ�E���g

// �G�l�~�[�\����
typedef struct	
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

	int				bulletTime;					// �e���ˊԊu
	int				Startweit;					// �o�ꎞ��
	int				cnt;
	int				firecount;
} ENEMY2;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy2(int type);
void UninitEnemy2(void);
void UpdateEnemy2(void);
void DrawEnemy2(void);
ENEMY2 *GetEnemy2(int no);


#endif
