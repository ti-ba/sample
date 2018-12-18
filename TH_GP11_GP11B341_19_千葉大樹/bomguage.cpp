//=============================================================================
//
// �Q�[�W���� [bomguage.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "bomguage.h"
#include "player.h"
#include "bom.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexbomguage(int no);
void SetTexturebomguage(int no, int cntPattern);
void SetVertexbomguage(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTexturebomguage = NULL;		// �e�N�X�`���ւ̃|���S��

BOMGUAGE					bomguageWk[BOMGUAGE_MAX];				// �Q�[�W�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitBomGuage(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOMGUAGE *bomguage = &bomguageWk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,			// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOMGUAGE,					// �t�@�C���̖��O
			&D3DTexturebomguage);					// �ǂݍ��ރ������̃|�C���^
	}

	// �Q�[�W�̏���������
	for (int i = 0; i < BOMGUAGE_MAX; i++, bomguage++)
	{
		bomguage->use = true;
		bomguage->pos = D3DXVECTOR3(400, + 400.0f, 100.0f);	// ���W�f�[�^��������

		bomguage->Radius = 1.0f;

		bomguage->Texture = D3DTexturebomguage;					// �e�N�X�`�����
		MakeVertexbomguage(i);									// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBomGuage(void)
{
	BOMGUAGE *bomguage = &bomguageWk[0];

	if (D3DTexturebomguage != NULL)
	{	// �e�N�X�`���̊J��
		D3DTexturebomguage->Release();
		D3DTexturebomguage = NULL;
	}

	//bomguage->Radius -= 0.5f;
	//if (bomguage->Radius = 0)
	//{
	//	bomguage->Radius += 0.5f;
	//}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateBomGuage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOMGUAGE *bomguage = &bomguageWk[0];
	BOM *bom = GetBom(0);
	//PLAYER *player = GetPlayer(0);
	for (int i = 0; i < BOMGUAGE_MAX; i++, bomguage++, bom++)
	{
		if (bom->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			bomguage->Radius -= 0.5f;
			if (bomguage->Radius = 0)
			{
				bomguage->Radius += 0.5f;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBomGuage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOMGUAGE *bomguage = &bomguageWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOMGUAGE_MAX; i++, bomguage++)
	{
		if (bomguage->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, bomguage->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOMGUAGE, bomguage->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexbomguage(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOMGUAGE *bomguage = &bomguageWk[0];

	// ���_���W�̐ݒ�
	SetVertexbomguage(no);

	// rhw�̐ݒ�
	bomguage->vertexWk[0].rhw =
		bomguage->vertexWk[1].rhw =
		bomguage->vertexWk[2].rhw =
		bomguage->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bomguage->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bomguage->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bomguage->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bomguage->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bomguage->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bomguage->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bomguage->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bomguage->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturebomguage(int no, int cntPattern)
{
	BOMGUAGE *bomguage = &bomguageWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	bomguage->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	bomguage->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	bomguage->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	bomguage->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexbomguage(int no)
{
	BOMGUAGE *bomguage = &bomguageWk[no];

	// ���_���W�̐ݒ�
	bomguage->vertexWk[0].vtx = D3DXVECTOR3(bomguage->pos.x, bomguage->pos.y, 0.0f);
	bomguage->vertexWk[1].vtx = D3DXVECTOR3(bomguage->pos.x +(TEXTURE_BOMGUAGE_SIZE_X * bomguage->Radius), bomguage->pos.y, 0.0f);
	bomguage->vertexWk[2].vtx = D3DXVECTOR3(bomguage->pos.x, bomguage->pos.y + TEXTURE_BOMGUAGE_SIZE_Y, 0.0f);
	bomguage->vertexWk[3].vtx = D3DXVECTOR3(bomguage->pos.x +(TEXTURE_BOMGUAGE_SIZE_X * bomguage->Radius), bomguage->pos.y + TEXTURE_BOMGUAGE_SIZE_Y, 0.0f);
}

//===========================================================================
// �Q�[�W�擾�֐�
//=============================================================================
BOMGUAGE * GetBomGuage(int no)
{
	return (&bomguageWk[no]);
}