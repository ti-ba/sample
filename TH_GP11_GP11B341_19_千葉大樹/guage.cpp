//=============================================================================
//
// �Q�[�W���� [GUAGE.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "guage.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexguage(int no);
void SetTextureguage(int no, int cntPattern);
void SetVertexguage(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureguage = NULL;		// �e�N�X�`���ւ̃|���S��

GUAGE					guageWk[GUAGE_MAX];				// �Q�[�W�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitGuage(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	GUAGE *guage = &guageWk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_GUAGE,					// �t�@�C���̖��O
			&D3DTextureguage);					// �ǂݍ��ރ������̃|�C���^
	}

	// �Q�[�W�̏���������
	for (int i = 0; i < GUAGE_MAX; i++, guage++)
	{
		guage->use = true;
		guage->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���W�f�[�^��������
		
		guage->Radius = TEXTURE_GUAGE_SIZE_X;

		guage->Texture = D3DTextureguage;					// �e�N�X�`�����
		MakeVertexguage(i);									// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGuage(void)
{
	if (D3DTextureguage != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureguage->Release();
		D3DTextureguage = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateGuage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	GUAGE *guage = &guageWk[0];
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < GUAGE_MAX; i++, guage++, player++)
	{
		if (player->use == true)			// �g�p���Ă����ԂȂ�`�悷��		
		{
			guage->pos.x = -TEXTURE_GUAGE_SIZE_X;	//���񂾂������
		}
		SetVertexguage(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGuage(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	GUAGE *guage = &guageWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < GUAGE_MAX; i++, guage++)
	{
		if (guage->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, guage->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GUAGE, guage->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexguage(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	GUAGE *guage = &guageWk[0];

	// ���_���W�̐ݒ�
	SetVertexguage(no);

	// rhw�̐ݒ�
	guage->vertexWk[0].rhw =
	guage->vertexWk[1].rhw =
	guage->vertexWk[2].rhw =
	guage->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	guage->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	guage->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	guage->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	guage->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	guage->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	guage->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	guage->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	guage->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureguage(int no, int cntPattern)
{
	GUAGE *guage = &guageWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	guage->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	guage->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	guage->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	guage->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexguage(int no)
{
	GUAGE *guage = &guageWk[no];

	// ���_���W�̐ݒ�
	guage->vertexWk[0].vtx = D3DXVECTOR3(guage->pos.x, guage->pos.y, 0.0f);
	guage->vertexWk[1].vtx = D3DXVECTOR3(guage->pos.x + guage->Radius, guage->pos.y, 0.0f);
	guage->vertexWk[2].vtx = D3DXVECTOR3(guage->pos.x, guage->pos.y + TEXTURE_GUAGE_SIZE_Y, 0.0f);
	guage->vertexWk[3].vtx = D3DXVECTOR3(guage->pos.x +  guage->Radius, guage->pos.y + TEXTURE_GUAGE_SIZE_Y, 0.0f);
}

//============================================================================
// �Q�[�W�擾�֐�
//=============================================================================
GUAGE * GetGuage(int no)
{
	return (&guageWk[no]);
}