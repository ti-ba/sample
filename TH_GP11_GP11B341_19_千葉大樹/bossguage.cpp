//=============================================================================
//
// �Q�[�W���� [BOSSGUAGE.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "bossguage.h"
#include "player.h"
#include "boss.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBossguage(int no);
void SetTextureBossguage(int no, int cntPattern);
void SetVertexBossguage(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		TextureBossguage = NULL;		// �e�N�X�`���ւ̃|���S��

BOSSGUAGE					bossguageWk[BOSSGUAGE_MAX];				// �Q�[�W�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitBossguage(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSGUAGE *bossguage = &bossguageWk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOSSGUAGE,				// �t�@�C���̖��O
			&TextureBossguage);					// �ǂݍ��ރ������̃|�C���^
	}

	// �Q�[�W�̏���������
	for (int i = 0; i < BOSSGUAGE_MAX; i++, bossguage++)
	{
		bossguage->use = true;
		bossguage->pos = D3DXVECTOR3(-(TEXTURE_BOSS_SIZE_X), 100.0f, 100.0f);	// ���W�f�[�^��������

		bossguage->Radius = TEXTURE_BOSSGUAGE_SIZE_X;

		bossguage->Texture = TextureBossguage;					// �e�N�X�`�����
		MakeVertexBossguage(i);									// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBossguage(void)
{
	if (TextureBossguage != NULL)
	{	// �e�N�X�`���̊J��
		TextureBossguage->Release();
		TextureBossguage = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateBossguage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSGUAGE *bossguage = &bossguageWk[0];
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < BOSSGUAGE_MAX; i++, bossguage++, player++)
	{
		if (player->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			bossguage->pos = player->pos; //�v���C���[�ɂ��Ă���
		}
		else
		{
			bossguage->pos.x = -TEXTURE_BOSSGUAGE_SIZE_X;	//���񂾂������
		}
		SetTextureBossguage(i, 0);
		SetVertexBossguage(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBossguage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSGUAGE *bossguage = &bossguageWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSSGUAGE_MAX; i++, bossguage++)
	{
		if (bossguage->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, bossguage->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSSGUAGE, bossguage->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBossguage(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSGUAGE *bossguage = &bossguageWk[0];

	// ���_���W�̐ݒ�
	SetVertexBossguage(no);

	// rhw�̐ݒ�
	bossguage->vertexWk[0].rhw =
	bossguage->vertexWk[1].rhw =
	bossguage->vertexWk[2].rhw =
	bossguage->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bossguage->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bossguage->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bossguage->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bossguage->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bossguage->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bossguage->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bossguage->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bossguage->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBossguage(int no, int cntPattern)
{
	BOSSGUAGE *bossguage = &bossguageWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	bossguage->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	bossguage->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	bossguage->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	bossguage->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBossguage(int no)
{
	BOSSGUAGE *bossguage = &bossguageWk[no];

	// ���_���W�̐ݒ�
	bossguage->vertexWk[0].vtx = D3DXVECTOR3(bossguage->pos.x, bossguage->pos.y, 0.0f);
	bossguage->vertexWk[1].vtx = D3DXVECTOR3(bossguage->pos.x + bossguage->Radius, bossguage->pos.y, 0.0f);
	bossguage->vertexWk[2].vtx = D3DXVECTOR3(bossguage->pos.x, bossguage->pos.y + TEXTURE_BOSSGUAGE_SIZE_Y, 0.0f);
	bossguage->vertexWk[3].vtx = D3DXVECTOR3(bossguage->pos.x + bossguage->Radius, bossguage->pos.y + TEXTURE_BOSSGUAGE_SIZE_Y, 0.0f);
}

//============================================================================
// �Q�[�W�擾�֐�
//=============================================================================
BOSSGUAGE * GetBossguage(int no)
{
	return (&bossguageWk[no]);
}