//=============================================================================
//
// �G���� [TYUTOENEMY.h]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#ifndef _TYUTOENEMY_H_
#define _TYUTOENEMY_H_


// �}�N����`
#define	NUM_TYUTOENEMY				(2)			// �|���S����

#define TEXTURE_GAME_TYUTOENEMY		_T("data/TEXTURE/enemy00.png")	// �摜
#define TEXTURE_TYUTOENEMY_SIZE_X	(50/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_TYUTOENEMY_SIZE_Y	(50/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_TYUTOENEMY	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_TYUTOENEMY			(TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY*TEXTURE_PATTERN_DIVIDE_Y_TYUTOENEMY)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_TYUTOENEMY			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define TYUTOENEMY_MAX						(4) // �G�̍ő吔

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
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

} TYUTOENEMY;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTyutoEnemy(int type);
void UninitTyutoEnemy(void);
void UpdateTyutoEnemy(void);
void DrawTyutoEnemy(void);
TYUTOENEMY *GetTyutoEnemy(int no);


#endif

