//=============================================================================
//
// �{������ [bom.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _BOM_H_
#define _BOM_H_


// �}�N����`
#define	NUM_BOM				(2)			// �|���S����

#define TEXTURE_GAME_BOM		_T("data/TEXTURE/bullet04.png")	// �摜
#define TEXTURE_BOM_SIZE_X	(50/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_BOM_SIZE_Y	(50/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BOM	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BOM	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BOM			(TEXTURE_PATTERN_DIVIDE_X_BOM*TEXTURE_PATTERN_DIVIDE_Y_BOM)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BOM			(10)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BOM_MAX						(10) // �o���b�g�̍ő吔

#define BOM_SPEED			(10.0f)		// �o���b�g�̈ړ��X�s�[�h


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �{���\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
	
	float			Radius;						//���a
} BOM;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBom(int type);
void UninitBom(void);
void UpdateBom(void);
void DrawBom(void);
void SetBom(D3DXVECTOR3 pos);
BOM *GetBom(int no);


#endif

