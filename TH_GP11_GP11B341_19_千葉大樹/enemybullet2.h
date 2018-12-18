//=============================================================================
//
// �G�l�~�[�o���b�g���� [enemybullet.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _ENEMYBULLET2_H_
#define _ENEMYBULLET2_H_


// �}�N����`
#define	NUM_ENEMYBULLET2				(2)			// �|���S����			

#define TEXTURE_GAME_ENEMYBULLET2		_T("data/TEXTURE/enemybullet02 .png")	// �摜
#define TEXTURE_ENEMYBULLET2_SIZE_X	(30)		// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMYBULLET2_SIZE_Y	(30)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET2	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMYBULLET2			(TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2*TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET2)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMYBULLET2			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define ENEMYBULLET2_MAX						(600) // �o���b�g�̍ő吔

#define ENEMYBULLET2_SPEED			(7.0f)		// �o���b�g�̈ړ��X�s�[�h



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

} ENEMYBULLET2;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemyBullet2(int type);
void UninitEnemyBullet2(void);
void UpdateEnemyBullet2(void);
void DrawEnemyBullet2(void);
void SetEnemyBullet2(D3DXVECTOR3 pos);
ENEMYBULLET2 *GetEnemyBullet2(int no);


#endif
