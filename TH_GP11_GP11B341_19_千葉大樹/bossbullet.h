//=============================================================================
//
// �o���b�g���� [bossbullet.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _BOSSBULLET_H_
#define _BOSSBULLET_H_


// �}�N����`
#define	NUM_BOSSBULLET				(2)			// �|���S����

#define TEXTURE_GAME_BOSSBULLET		_T("data/TEXTURE/bullet04.jpg")	// �摜
#define TEXTURE_BOSSBULLET_SIZE_X	(40)		// �e�N�X�`���T�C�Y
#define TEXTURE_BOSSBULLET_SIZE_Y	(40)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSSBULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BOSSBULLET			(TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET*TEXTURE_PATTERN_DIVIDE_Y_BOSSBULLET)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BOSSBULLET			(10)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BOSSBULLET_MAX						(100) // �o���b�g�̍ő吔

#define BOSSBULLET_SPEED			(7.0f)		// �o���b�g�̈ړ��X�s�[�h


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
} BOSSBULLET;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBossBullet(int type);
void UninitBossBullet(void);
void UpdateBossBullet(void);
void DrawBossBullet(void);
void SetBossBullet(D3DXVECTOR3 pos);
BOSSBULLET *GetBossBullet(int no);


#endif
