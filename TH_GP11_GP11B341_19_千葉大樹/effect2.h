//=============================================================================
//
// �G�t�F�N�g���� [effect2.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _EFFECT2_H_
#define _EFFECT2_H_


// �}�N����`
#define	NUM_EFFECT2				(2)			// �|���S����

#define TEXTURE_GAME_EFFECT2		_T("data/TEXTURE/pipo-btleffect003.png")	// �摜
#define TEXTURE_EFFECT2_SIZE_X	(100)		// �e�N�X�`���T�C�Y
#define TEXTURE_EFFECT2_SIZE_Y	(100)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_EFFECT2	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT2	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_EFFECT2			(TEXTURE_PATTERN_DIVIDE_X_EFFECT2*TEXTURE_PATTERN_DIVIDE_Y_EFFECT2)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EFFECT2			(10)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define EFFECT2_MAX						(15)  // �G�t�F�N�g�̍ő吔




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
	int				time;						//  
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						//���a
} EFFECT2;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect2(int type);
void UninitEffect2(void);
void UpdateEffect2(void);
void DrawEffect2(void);
void SetEffect2(D3DXVECTOR3 pos);
EFFECT2 *GetEffect2(int no);


#endif

