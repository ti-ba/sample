//=============================================================================
//
// �G���� [tyutoenemy.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "tyutoenemy.h"
#include "input.h"
#include "enemybullet.h"
#include "sound.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTyutoEnemy(int no);
void SetTextureTyutoEnemy(int no, int cntPattern);
void SetVertexTyutoEnemy(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureTyutoEnemy = NULL;	// �e�N�X�`���ւ̃|���S��

TYUTOENEMY				tyutoenemyWk[TYUTOENEMY_MAX];	// �G�l�~�[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitTyutoEnemy(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_TYUTOENEMY,		// �t�@�C���̖��O
			&D3DTextureTyutoEnemy);		// �ǂݍ��ރ������̃|�C���^
	}

	// �G�l�~�[�̏���������
	TYUTOENEMY *tyutoenemy = tyutoenemyWk;				// �G�l�~�[�̃|�C���^�[��������
	for (int i = 0; i < TYUTOENEMY_MAX; i++, tyutoenemy++)
	{
		tyutoenemy->use = true;										// �g�p
		tyutoenemy->pos = D3DXVECTOR3(50 + i * 170.0f, 100.0f, 0.0f);	// ���W�f�[�^��������
		tyutoenemy->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		tyutoenemy->CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_TYUTOENEMY_SIZE_X, TEXTURE_TYUTOENEMY_SIZE_Y);
		tyutoenemy->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		tyutoenemy->BaseAngle = atan2f(TEXTURE_TYUTOENEMY_SIZE_Y, TEXTURE_TYUTOENEMY_SIZE_X);	// �G�l�~�[�̊p�x��������

		tyutoenemy->Texture = D3DTextureTyutoEnemy;					// �e�N�X�`�����
		MakeVertexTyutoEnemy(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTyutoEnemy(void)
{
	if (D3DTextureTyutoEnemy != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureTyutoEnemy->Release();
		D3DTextureTyutoEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTyutoEnemy(void)
{
	TYUTOENEMY *tyutoenemy = tyutoenemyWk;				// �G�l�~�[�̃|�C���^�[��������
	

	for (int i = 0; i < TYUTOENEMY_MAX; i++, tyutoenemy++)
	{
		if (tyutoenemy->use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			SetVertexTyutoEnemy(i);						// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTyutoEnemy(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	TYUTOENEMY *tyutoenemy = tyutoenemyWk;		// �G�l�~�[�̃|�C���^�[��������

										
	Device->SetFVF(FVF_VERTEX_2D);				// ���_�t�H�[�}�b�g�̐ݒ�

	for (int i = 0; i < TYUTOENEMY_MAX; i++, tyutoenemy++)
	{
		if (tyutoenemy->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, tyutoenemy->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_TYUTOENEMY, tyutoenemy->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTyutoEnemy(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	TYUTOENEMY *tyutoenemy = &tyutoenemyWk[no];			// �G�l�~�[�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexTyutoEnemy(no);

	// rhw�̐ݒ�
		tyutoenemy->vertexWk[0].rhw =
		tyutoenemy->vertexWk[1].rhw =
		tyutoenemy->vertexWk[2].rhw =
		tyutoenemy->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	tyutoenemy->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tyutoenemy->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tyutoenemy->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tyutoenemy->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	tyutoenemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	tyutoenemy->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY, 0.0f);
	tyutoenemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TYUTOENEMY);
	tyutoenemy->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TYUTOENEMY);

	tyutoenemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	tyutoenemy->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	tyutoenemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	tyutoenemy->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureTyutoEnemy(int no, int cntPattern)
{
	TYUTOENEMY *tyutoenemy = &tyutoenemyWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_TYUTOENEMY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TYUTOENEMY;

	tyutoenemy->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	tyutoenemy->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	tyutoenemy->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	tyutoenemy->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexTyutoEnemy(int no)
{
	TYUTOENEMY *tyutoenemy = &tyutoenemyWk[no];			// �G�l�~�[�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	tyutoenemy->vertexWk[0].vtx.x = tyutoenemy->pos.x - cosf(tyutoenemy->BaseAngle + tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[0].vtx.y = tyutoenemy->pos.y - sinf(tyutoenemy->BaseAngle + tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[0].vtx.z = 0.0f;

	tyutoenemy->vertexWk[1].vtx.x = tyutoenemy->pos.x + cosf(tyutoenemy->BaseAngle - tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[1].vtx.y = tyutoenemy->pos.y - sinf(tyutoenemy->BaseAngle - tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[1].vtx.z = 0.0f;

	tyutoenemy->vertexWk[2].vtx.x = tyutoenemy->pos.x - cosf(tyutoenemy->BaseAngle - tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[2].vtx.y = tyutoenemy->pos.y + sinf(tyutoenemy->BaseAngle - tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[2].vtx.z = 0.0f;

	tyutoenemy->vertexWk[3].vtx.x = tyutoenemy->pos.x + cosf(tyutoenemy->BaseAngle + tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[3].vtx.y = tyutoenemy->pos.y + sinf(tyutoenemy->BaseAngle + tyutoenemy->rot.z) * tyutoenemy->Radius;
	tyutoenemy->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
TYUTOENEMY *GetTyutoEnemy(int no)
{
	return(&tyutoenemyWk[no]);
}


