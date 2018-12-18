//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "effect.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffect(int no);
void SetTextureEffect(int no, int cntPattern);
void SetVertexEffect(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureEffect = NULL;		// �e�N�X�`���ւ̃|���S��

EFFECT					effectWk[EFFECT_MAX];			// �o���b�g�\����
LPDIRECTSOUNDBUFFER8	effectSE;						// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	EFFECT *effect = &effectWk[0];		// �G�l�~�[�̃|�C���^�[��������

										// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EFFECT,			// �t�@�C���̖��O
			&D3DTextureEffect);			// �ǂݍ��ރ������̃|�C���^

		effectSE = LoadSound(SHOT_00);

	}

	// �G�t�F�N�g�̏���������
	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		effect->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		effect->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		effect->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		effect->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		effect->CountAnim = 0;									// �A�j���J�E���g��������

		effect->Texture = D3DTextureEffect;						// �e�N�X�`�����
		MakeVertexEffect(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	if (D3DTextureEffect != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureEffect->Release();
		D3DTextureEffect = NULL;
	}

	if (effectSE != NULL)
	{	// �e�N�X�`���̊J��
		effectSE->Release();
		effectSE = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	EFFECT *effect = effectWk;				// �o���b�g�̃|�C���^�[��������

	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		if ((effect->use == true)&&(effect->time>=0))			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			effect->CountAnim++;
			if ((effect->CountAnim % TIME_ANIMATION_EFFECT) == 0)
			{
				// �p�^�[���̐؂�ւ�
				effect->PatternAnim = (effect->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT;

				// �e�N�X�`�����W��ݒ�
				SetTextureEffect(i, effect->PatternAnim);
			}

			SetVertexEffect(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
		effect->time -= 1;
		if (effect->time == 0)
		{
			effect->use = false;
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	EFFECT *effect = effectWk;				// �o���b�g�̃|�C���^�[��������

											// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		if (effect->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, effect->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT, effect->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	EFFECT *effect = &effectWk[no];			// �o���b�g�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	SetVertexEffect(no);

	// rhw�̐ݒ�
	effect->vertexWk[0].rhw =
		effect->vertexWk[1].rhw =
		effect->vertexWk[2].rhw =
		effect->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	effect->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	effect->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT, 0.0f);
	effect->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT);
	effect->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT);

	effect->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	effect->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	effect->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEffect(int no, int cntPattern)
{
	EFFECT *effect = &effectWk[no];			// �o���b�g�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT;

	effect->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	effect->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	effect->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	effect->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEffect(int no)
{
	EFFECT *effect = &effectWk[no];			// �o���b�g�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	effect->vertexWk[0].vtx.x = effect->pos.x - TEXTURE_EFFECT_SIZE_X;
	effect->vertexWk[0].vtx.y = effect->pos.y - TEXTURE_EFFECT_SIZE_Y;
	effect->vertexWk[0].vtx.z = 0.0f;

	effect->vertexWk[1].vtx.x = effect->pos.x + TEXTURE_EFFECT_SIZE_X;
	effect->vertexWk[1].vtx.y = effect->pos.y - TEXTURE_EFFECT_SIZE_Y;
	effect->vertexWk[1].vtx.z = 0.0f;

	effect->vertexWk[2].vtx.x = effect->pos.x - TEXTURE_EFFECT_SIZE_X;
	effect->vertexWk[2].vtx.y = effect->pos.y + TEXTURE_EFFECT_SIZE_Y;
	effect->vertexWk[2].vtx.z = 0.0f;

	effect->vertexWk[3].vtx.x = effect->pos.x + TEXTURE_EFFECT_SIZE_X;
	effect->vertexWk[3].vtx.y = effect->pos.y + TEXTURE_EFFECT_SIZE_Y;
	effect->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�t�F�N�g�̔��ːݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos)
{
	EFFECT *effect = &effectWk[0];			// �G�t�F�N�g�̃|�C���^�[��������

	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		if (effect->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			effect->use = true;				// �g�p��Ԃ֕ύX����
			effect->pos = pos;				// ���W���Z�b�g

											
			effect->time = 60;

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �o���b�g�擾�֐�
//=============================================================================
EFFECT *GetEffect(int no)
{
	return(&effectWk[no]);
}

