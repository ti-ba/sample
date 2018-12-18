//=============================================================================
//
// �G�̃Q�[�W���� [enemyguage2.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "enemyguage2.h"
#include "enemy2.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define ANIME_MAX()

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexenemyguage2(int no);
void SetTextureenemyguage2(int no, int cntPattern);
void SetVertexenemyguage2(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureenemyguage2 = NULL;		// �e�N�X�`���ւ̃|���S��

ENEMYGUAGE2				enemyguage2Wk[ENEMYGUAGE2_MAX];		// �Q�[�W�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyGuage2(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE2 *enemyguage2 = &enemyguage2Wk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMYGUAGE2,			// �t�@�C���̖��O
			&D3DTextureenemyguage2);				// �ǂݍ��ރ������̃|�C���^
	}

	// �Q�[�W�̏���������
	for (int i = 0; i < ENEMYGUAGE2_MAX; i++, enemyguage2++)
	{
		enemyguage2->use = true;
		enemyguage2->pos = D3DXVECTOR3(150.0f*i - 30.0f, 0.0f, 50.0f);	// ���W�f�[�^��������
		enemyguage2->Radius = TEXTURE_ENEMYGUAGE2_SIZE_X;
		enemyguage2->Texture = D3DTextureenemyguage2;				// �e�N�X�`�����
		MakeVertexenemyguage2(i);								// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyGuage2(void)
{
	if (D3DTextureenemyguage2 != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureenemyguage2->Release();
		D3DTextureenemyguage2 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyGuage2(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE2 *enemyguage2 = &enemyguage2Wk[0];	//�G�̃Q�[�W�̏�����
	ENEMY2 *enemy2 = GetEnemy2(0);					// �G�l�~�[�̃|�C���^�[��������

	for (int i = 0; i < ENEMYGUAGE2_MAX; i++, enemyguage2++, enemy2++)
	{
		if (enemy2->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			enemyguage2->pos = enemy2->pos; //�G�ɂ��Ă���
		}
		else
		{
			enemyguage2->pos.x = -TEXTURE_ENEMYGUAGE2_SIZE_X;	//���񂾂������
		}
		SetTextureenemyguage2(i, 0);
		SetVertexenemyguage2(i);
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyGuage2(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE2 *enemyguage2 = &enemyguage2Wk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMYGUAGE2_MAX; i++, enemyguage2++)
	{
		if (enemyguage2->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, enemyguage2->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMYGUAGE2, enemyguage2->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexenemyguage2(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE2 *enemyguage2 = &enemyguage2Wk[no];

	// ���_���W�̐ݒ�
	SetVertexenemyguage2(no);

	// rhw�̐ݒ�
	enemyguage2->vertexWk[0].rhw =
		enemyguage2->vertexWk[1].rhw =
		enemyguage2->vertexWk[2].rhw =
		enemyguage2->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemyguage2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyguage2->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyguage2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyguage2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemyguage2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemyguage2->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	enemyguage2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	enemyguage2->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureenemyguage2(int no, int cntPattern)
{
	ENEMYGUAGE2 *enemyguage2 = &enemyguage2Wk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYGUAGE2;

	enemyguage2->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	enemyguage2->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	enemyguage2->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	enemyguage2->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexenemyguage2(int no)
{
	ENEMYGUAGE2 *enemyguage2 = &enemyguage2Wk[no];

	// ���_���W�̐ݒ�
	enemyguage2->vertexWk[0].vtx = D3DXVECTOR3(enemyguage2->pos.x, enemyguage2->pos.y, 0.0f);
	enemyguage2->vertexWk[1].vtx = D3DXVECTOR3(enemyguage2->pos.x + enemyguage2->Radius, enemyguage2->pos.y, 0.0f);
	enemyguage2->vertexWk[2].vtx = D3DXVECTOR3(enemyguage2->pos.x, enemyguage2->pos.y + TEXTURE_ENEMYGUAGE2_SIZE_Y, 0.0f);
	enemyguage2->vertexWk[3].vtx = D3DXVECTOR3(enemyguage2->pos.x + enemyguage2->Radius, enemyguage2->pos.y + TEXTURE_ENEMYGUAGE2_SIZE_Y, 0.0f);

}

//============================================================================
// �G�̃Q�[�W�擾�֐�
//=============================================================================
ENEMYGUAGE2 * GetEnemyGuage2(int no)
{
	return (&enemyguage2Wk[no]);
}