//=============================================================================
//
// �G�l�~�[�o���b�g���� [enemybullet.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_


// �}�N����`
#define	NUM_ENEMYBULLET				(2)			// �|���S����

#define TEXTURE_GAME_ENEMYBULLET		_T("data/TEXTURE/enemybullet.png")	// �摜
#define TEXTURE_ENEMYBULLET_SIZE_X	(30)		// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMYBULLET_SIZE_Y	(30)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMYBULLET			(TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET*TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMYBULLET			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define ENEMYBULLET_MAX						(1000) // �o���b�g�̍ő吔

#define ENEMYBULLET_SPEED			(7.0f)		// �o���b�g�̈ړ��X�s�[�h



//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �o���b�g�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				Radius;						// ���a
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} ENEMYBULLET;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemyBullet(int type);
void UninitEnemyBullet(void);
void UpdateEnemyBullet(void);
void DrawEnemyBullet(void);
void SetEnemyBullet(D3DXVECTOR3 pos);
ENEMYBULLET *GetEnemyBullet(int no);


#endif
