//=============================================================================
//
// �G�̃Q�[�W���� [enemyguage.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "enemyguage.h"
#include "enemy.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define ANIME_MAX()

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexenemyguage(int no);
void SetTextureenemyguage(int no, int cntPattern);
void SetVertexenemyguage(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureenemyguage = NULL;		// �e�N�X�`���ւ̃|���S��

ENEMYGUAGE				enemyguageWk[ENEMYGUAGE_MAX];		// �Q�[�W�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyGuage(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE *enemyguage = &enemyguageWk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMYGUAGE,			// �t�@�C���̖��O
			&D3DTextureenemyguage);				// �ǂݍ��ރ������̃|�C���^
	}

	// �Q�[�W�̏���������
	for (int i = 0; i < ENEMYGUAGE_MAX; i++, enemyguage++)
	{
		enemyguage->use = true;
		enemyguage->pos = D3DXVECTOR3(/*150.0f*i - 30.0f, 0.0f, 0.0f*/0.0f,0.0f,0.0f);	// ���W�f�[�^��������
		enemyguage->Radius = TEXTURE_ENEMYGUAGE_SIZE_X;
		enemyguage->Texture = D3DTextureenemyguage;				// �e�N�X�`�����
		MakeVertexenemyguage(i);								// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyGuage(void)
{
	if (D3DTextureenemyguage != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureenemyguage->Release();
		D3DTextureenemyguage = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyGuage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE *enemyguage = &enemyguageWk[0];	//�G�̃Q�[�W�̏�����
	ENEMY *enemy = GetEnemy(0);					// �G�l�~�[�̃|�C���^�[��������
	
	for (int i = 0; i < ENEMYGUAGE_MAX; i++, enemyguage++,enemy++)
	{
		if (enemy->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			enemyguage->pos = enemy->pos; //�G�ɂ��Ă���
		}
		else
		{
			enemyguage->pos.x = -TEXTURE_ENEMYGUAGE_SIZE_X;	//���񂾂������
		}
		SetTextureenemyguage(i, 0);
		SetVertexenemyguage(i);
	}

	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyGuage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE *enemyguage = &enemyguageWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMYGUAGE_MAX; i++, enemyguage++)
	{
		if (enemyguage->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, enemyguage->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMYGUAGE, enemyguage->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexenemyguage(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYGUAGE *enemyguage = &enemyguageWk[no];

	// ���_���W�̐ݒ�
	SetVertexenemyguage(no);

	// rhw�̐ݒ�
		enemyguage->vertexWk[0].rhw =
		enemyguage->vertexWk[1].rhw =
		enemyguage->vertexWk[2].rhw =
		enemyguage->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemyguage->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyguage->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyguage->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyguage->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemyguage->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemyguage->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	enemyguage->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	enemyguage->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureenemyguage(int no, int cntPattern)
{
	ENEMYGUAGE *enemyguage = &enemyguageWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYGUAGE;

	enemyguage->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	enemyguage->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	enemyguage->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	enemyguage->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexenemyguage(int no)
{
	ENEMYGUAGE *enemyguage = &enemyguageWk[no];

	// ���_���W�̐ݒ�
	enemyguage->vertexWk[0].vtx = D3DXVECTOR3(enemyguage->pos.x, enemyguage->pos.y, 0.0f);
	enemyguage->vertexWk[1].vtx = D3DXVECTOR3(enemyguage->pos.x +enemyguage->Radius, enemyguage->pos.y, 0.0f);
	enemyguage->vertexWk[2].vtx = D3DXVECTOR3(enemyguage->pos.x, enemyguage->pos.y + TEXTURE_ENEMYGUAGE_SIZE_Y, 0.0f);
	enemyguage->vertexWk[3].vtx = D3DXVECTOR3(enemyguage->pos.x +enemyguage->Radius, enemyguage->pos.y + TEXTURE_ENEMYGUAGE_SIZE_Y, 0.0f);

}

//============================================================================
// �G�̃Q�[�W�擾�֐�
//=============================================================================
ENEMYGUAGE * GetEnemyGuage(int no)
{
	return (&enemyguageWk[no]);
}