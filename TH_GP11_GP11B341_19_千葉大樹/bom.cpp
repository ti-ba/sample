//=============================================================================
//
// �o���b�g���� [bom.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "bom.h"
#include "sound.h"
#include "bomguage.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBom(int no);
void SetTextureBom(int no, int cntPattern);
void SetVertexBom(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureBom = NULL;		// �e�N�X�`���ւ̃|���S��

BOM						bomWk[BOM_MAX];				// �o���b�g�\����
LPDIRECTSOUNDBUFFER8	bomSE;						// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBom(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOM *bom = &bomWk[0];		// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOM,			// �t�@�C���̖��O
			&D3DTextureBom);			// �ǂݍ��ރ������̃|�C���^

		bomSE = LoadSound(BOMB_00);

	}

	//  �{���̏���������
	for (int i = 0; i < BOM_MAX; i++, bom++)
	{
		bom->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		bom->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);		// ���W�f�[�^��������
		bom->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		bom->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		bom->CountAnim = 0;									// �A�j���J�E���g��������

		bom->Texture = D3DTextureBom;						// �e�N�X�`�����
		MakeVertexBom(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBom(void)
{
	if (D3DTextureBom != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureBom->Release();
		D3DTextureBom = NULL;
	}

	if (bomSE != NULL)
	{	// �e�N�X�`���̊J��
		bomSE->Release();
		bomSE = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBom(void)
{
	BOM *bom = bomWk;				// �o���b�g�̃|�C���^�[��������
	BOMGUAGE *bomguage = GetBomGuage(0);
	for (int i = 0; i < BOM_MAX; i++, bom++)
	{
		if (bom->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �o���b�g�̈ړ�����
			bom->pos.y -= BOM_SPEED;
			//bomguage->Radius -= 100 / 5;			//�Q�[�W�̌���

			// ��ʊO�܂Ői�񂾁H
			if (bom->pos.y < -TEXTURE_BOM_SIZE_Y)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				bom->use = false;
				bom->pos.x = -100.0f;
			}

			SetVertexBom(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBom(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOM *bom = bomWk;				// �o���b�g�̃|�C���^�[��������

											// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOM_MAX; i++, bom++)
	{
		if (bom->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, bom->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOM, bom->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBom(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOM *bom = &bomWk[no];			// �o���b�g�̃|�C���^�[��������
										
	SetVertexBom(no);				// ���_���W�̐ݒ�

	// rhw�̐ݒ�
	bom->vertexWk[0].rhw =
	bom->vertexWk[1].rhw =
	bom->vertexWk[2].rhw =
	bom->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bom->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bom->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bom->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bom->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bom->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bom->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOM, 0.0f);
	bom->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOM);
	bom->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOM, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOM);

	bom->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bom->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bom->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bom->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBom(int no, int cntPattern)
{
	BOM *bom = &bomWk[no];			// �o���b�g�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOM;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOM;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOM;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOM;

	bom->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	bom->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	bom->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	bom->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBom(int no)
{
	BOM *bom = &bomWk[no];			// �o���b�g�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	bom->vertexWk[0].vtx.x = bom->pos.x - TEXTURE_BOM_SIZE_X;
	bom->vertexWk[0].vtx.y = bom->pos.y - TEXTURE_BOM_SIZE_Y;
	bom->vertexWk[0].vtx.z = 0.0f;
	
	bom->vertexWk[1].vtx.x = bom->pos.x + TEXTURE_BOM_SIZE_X;
	bom->vertexWk[1].vtx.y = bom->pos.y - TEXTURE_BOM_SIZE_Y;
	bom->vertexWk[1].vtx.z = 0.0f;
	
	bom->vertexWk[2].vtx.x = bom->pos.x - TEXTURE_BOM_SIZE_X;
	bom->vertexWk[2].vtx.y = bom->pos.y + TEXTURE_BOM_SIZE_Y;
	bom->vertexWk[2].vtx.z = 0.0f;
	
	bom->vertexWk[3].vtx.x = bom->pos.x + TEXTURE_BOM_SIZE_X;
	bom->vertexWk[3].vtx.y = bom->pos.y + TEXTURE_BOM_SIZE_Y;
	bom->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �{���̔��ːݒ�
//=============================================================================
void SetBom(D3DXVECTOR3 pos)
{
	BOM *bom = &bomWk[0];			// �o���b�g�̃|�C���^�[��������

	for (int i = 0; i < BOM_MAX; i++, bom++)	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	{
		if (bom->use == false)				// ���g�p��Ԃ̃o���b�g��������
		{
			bom->use = true;				// �g�p��Ԃ֕ύX����
			bom->pos = pos;					// ���W���Z�b�g

											
			PlaySound(bomSE, E_DS8_FLAG_NONE);	// ���ˉ��Đ�

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �{���擾�֐�
//=============================================================================
BOM *GetBom(int no)
{
	return(&bomWk[no]);
}

