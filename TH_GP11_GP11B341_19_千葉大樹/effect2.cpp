//=============================================================================
//
// �G�t�F�N�g���� [effect2.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "effect2.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffect2(int no);
void SetTextureEffect2(int no, int cntPattern);
void SetVertexEffect2(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureEffect2 = NULL;		// �e�N�X�`���ւ̃|���S��

EFFECT2					effect2Wk[EFFECT2_MAX];			// �o���b�g�\����
LPDIRECTSOUNDBUFFER8	effect2SE;						// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect2(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	EFFECT2 *effect2 = &effect2Wk[0];		// �G�l�~�[�̃|�C���^�[��������

										// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EFFECT2,			// �t�@�C���̖��O
			&D3DTextureEffect2);			// �ǂݍ��ރ������̃|�C���^

		effect2SE = LoadSound(SHOT_00);

	}

	// �o���b�g�̏���������
	for (int i = 0; i < EFFECT2_MAX; i++, effect2++)
	{
		effect2->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		effect2->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);		// ���W�f�[�^��������
		effect2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		effect2->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		effect2->CountAnim = 0;									// �A�j���J�E���g��������

		effect2->Texture = D3DTextureEffect2;					// �e�N�X�`�����
		MakeVertexEffect2(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect2(void)
{
	if (D3DTextureEffect2 != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureEffect2->Release();
		D3DTextureEffect2 = NULL;
	}

	if (effect2SE != NULL)
	{	// �e�N�X�`���̊J��
		effect2SE->Release();
		effect2SE = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect2(void)
{
	EFFECT2 *effect2 = effect2Wk;				// �o���b�g�̃|�C���^�[��������

	for (int i = 0; i < EFFECT2_MAX; i++, effect2++)
	{
		if ((effect2->use == true) && (effect2->time >= 0))			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			effect2->CountAnim++;
			if ((effect2->CountAnim % TIME_ANIMATION_EFFECT2) == 0)
			{
				// �p�^�[���̐؂�ւ�
				effect2->PatternAnim = (effect2->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT2;

				// �e�N�X�`�����W��ݒ�
				SetTextureEffect2(i, effect2->PatternAnim);
			}

			SetVertexEffect2(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
		effect2->time -= 1;
		if (effect2->time == 0)
		{
			effect2->use = false;
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect2(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	EFFECT2 *effect2 = effect2Wk;				// �o���b�g�̃|�C���^�[��������

											// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT2_MAX; i++, effect2++)
	{
		if (effect2->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, effect2->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT2, effect2->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect2(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	EFFECT2 *effect2 = &effect2Wk[no];			// �o���b�g�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	SetVertexEffect2(no);

	// rhw�̐ݒ�
	effect2->vertexWk[0].rhw =
	effect2->vertexWk[1].rhw =
	effect2->vertexWk[2].rhw =
	effect2->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	effect2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect2->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	effect2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect2->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT2, 0.0f);
	effect2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT2);
	effect2->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT2, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT2);

	effect2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect2->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	effect2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	effect2->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEffect2(int no, int cntPattern)
{
	EFFECT2 *effect2 = &effect2Wk[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT2;

	effect2->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	effect2->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	effect2->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	effect2->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEffect2(int no)
{
	EFFECT2 *effect2 = &effect2Wk[no];			// �o���b�g�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	effect2->vertexWk[0].vtx.x = effect2->pos.x - TEXTURE_EFFECT2_SIZE_X;
	effect2->vertexWk[0].vtx.y = effect2->pos.y - TEXTURE_EFFECT2_SIZE_Y;
	effect2->vertexWk[0].vtx.z = 0.0f;

	effect2->vertexWk[1].vtx.x = effect2->pos.x + TEXTURE_EFFECT2_SIZE_X;
	effect2->vertexWk[1].vtx.y = effect2->pos.y - TEXTURE_EFFECT2_SIZE_Y;
	effect2->vertexWk[1].vtx.z = 0.0f;

	effect2->vertexWk[2].vtx.x = effect2->pos.x - TEXTURE_EFFECT2_SIZE_X;
	effect2->vertexWk[2].vtx.y = effect2->pos.y + TEXTURE_EFFECT2_SIZE_Y;
	effect2->vertexWk[2].vtx.z = 0.0f;

	effect2->vertexWk[3].vtx.x = effect2->pos.x + TEXTURE_EFFECT2_SIZE_X;
	effect2->vertexWk[3].vtx.y = effect2->pos.y + TEXTURE_EFFECT2_SIZE_Y;
	effect2->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�t�F�N�g�̔��ːݒ�
//=============================================================================
void SetEffect2(D3DXVECTOR3 pos)
{
	EFFECT2 *effect2 = &effect2Wk[0];			// �G�t�F�N�g�̃|�C���^�[��������

	for (int i = 0; i < EFFECT2_MAX; i++, effect2++)
	{
		if (effect2->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			effect2->use = true;				// �g�p��Ԃ֕ύX����
			effect2->pos = pos;				// ���W���Z�b�g


			effect2->time = 60;

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �o���b�g�擾�֐�
//=============================================================================
EFFECT2 *GetEffect2(int no)
{
	return(&effect2Wk[no]);
}

