//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_


// �}�N����`
#define	NUM_BULLET				(2)			// �|���S����

#define TEXTURE_GAME_BULLET		_T("data/TEXTURE/winner.jpg")	// �摜
#define TEXTURE_BULLET_SIZE_X	(20)		// �e�N�X�`���T�C�Y
#define TEXTURE_BULLET_SIZE_Y	(20)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BULLET			(TEXTURE_PATTERN_DIVIDE_X_BULLET*TEXTURE_PATTERN_DIVIDE_Y_BULLET)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BULLET			(100)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BULLET_MAX						(10) // �o���b�g�̍ő吔

#define BULLET_SPEED			(10.0f)		// �o���b�g�̈ړ��X�s�[�h


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
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						//���a
} BULLET;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(int type);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos);
BULLET *GetBullet(int no);


#endif
