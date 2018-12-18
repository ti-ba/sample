//=============================================================================
//
// �o���b�g���� [bossbullet.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "bossbullet.h"
#include "boss.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBossBullet(int no);
void SetTextureBossBullet(int no, int cntPattern);
void SetVertexBossBullet(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureBossBullet = NULL;		// �e�N�X�`���ւ̃|���S��

BOSSBULLET				bossbulletWk[BOSSBULLET_MAX];			// �o���b�g�\����
LPDIRECTSOUNDBUFFER8	bossbulletSE;						// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBossBullet(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSBULLET *bossbullet = &bossbulletWk[0];		// �G�l�~�[�̃|�C���^�[��������

										// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOSSBULLET,		// �t�@�C���̖��O
			&D3DTextureBossBullet);			// �ǂݍ��ރ������̃|�C���^

		bossbulletSE = LoadSound(SHOT_00);

	}

	// �o���b�g�̏���������
	for (int i = 0; i < BOSSBULLET_MAX; i++, bossbullet++)
	{
		bossbullet->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		bossbullet->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		bossbullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		bossbullet->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		bossbullet->CountAnim = 0;									// �A�j���J�E���g��������

		bossbullet->Texture = D3DTextureBossBullet;					// �e�N�X�`�����
		MakeVertexBossBullet(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBossBullet(void)
{
	if (D3DTextureBossBullet != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureBossBullet->Release();
		D3DTextureBossBullet = NULL;
	}

	if (bossbulletSE != NULL)
	{	// �e�N�X�`���̊J��
		bossbulletSE->Release();
		bossbulletSE = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBossBullet(void)
{
	BOSSBULLET *bossbullet = &bossbulletWk[0];		// �G�l�~�[�̃|�C���^�[��������

	for (int i = 0; i < BOSSBULLET_MAX; i++, bossbullet++)
	{
		if (bossbullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �o���b�g�̈ړ�����
			bossbullet->pos.y += BOSSBULLET_SPEED;

			// ��ʊO�܂Ői�񂾁H
			if (bossbullet->pos.y < -TEXTURE_BOSSBULLET_SIZE_Y)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				bossbullet->use = false;
				bossbullet->pos.x = -100.0f;
			}

			SetVertexBossBullet(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBossBullet(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSBULLET *bossbullet = &bossbulletWk[0];		// �G�l�~�[�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSSBULLET_MAX; i++, bossbullet++)
	{
		if (bossbullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, bossbullet->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSSBULLET, bossbullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBossBullet(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSSBULLET *bossbullet = &bossbulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexBossBullet(no);

	// rhw�̐ݒ�
	bossbullet->vertexWk[0].rhw =
	bossbullet->vertexWk[1].rhw =
	bossbullet->vertexWk[2].rhw =
	bossbullet->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bossbullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bossbullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bossbullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bossbullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bossbullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bossbullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET, 0.0f);
	bossbullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSSBULLET);
	bossbullet->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSSBULLET);

	bossbullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bossbullet->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bossbullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bossbullet->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBossBullet(int no, int cntPattern)
{
	BOSSBULLET *bossbullet = &bossbulletWk[no];			// �o���b�g�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSSBULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSSBULLET;

	bossbullet->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	bossbullet->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	bossbullet->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	bossbullet->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBossBullet(int no)
{
	BOSSBULLET *bossbullet = &bossbulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	bossbullet->vertexWk[0].vtx.x = bossbullet->pos.x - TEXTURE_BOSSBULLET_SIZE_X;
	bossbullet->vertexWk[0].vtx.y = bossbullet->pos.y - TEXTURE_BOSSBULLET_SIZE_Y;
	bossbullet->vertexWk[0].vtx.z = 0.0f;

	bossbullet->vertexWk[1].vtx.x = bossbullet->pos.x + TEXTURE_BOSSBULLET_SIZE_X;
	bossbullet->vertexWk[1].vtx.y = bossbullet->pos.y - TEXTURE_BOSSBULLET_SIZE_Y;
	bossbullet->vertexWk[1].vtx.z = 0.0f;

	bossbullet->vertexWk[2].vtx.x = bossbullet->pos.x - TEXTURE_BOSSBULLET_SIZE_X;
	bossbullet->vertexWk[2].vtx.y = bossbullet->pos.y + TEXTURE_BOSSBULLET_SIZE_Y;
	bossbullet->vertexWk[2].vtx.z = 0.0f;

	bossbullet->vertexWk[3].vtx.x = bossbullet->pos.x + TEXTURE_BOSSBULLET_SIZE_X;
	bossbullet->vertexWk[3].vtx.y = bossbullet->pos.y + TEXTURE_BOSSBULLET_SIZE_Y;
	bossbullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetBossBullet(D3DXVECTOR3 pos)
{
	BOSSBULLET *bossbullet = &bossbulletWk[0];			// �o���b�g�̃|�C���^�[��������
	BOSS *boss = GetBoss(0);
											// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < BOSSBULLET_MAX; i++, bossbullet++)
	{
		if (bossbullet->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			bossbullet->use = true;				// �g�p��Ԃ֕ύX����
			bossbullet->pos = pos;				// ���W���Z�b�g


			// ���ˉ��Đ�
			PlaySound(bossbulletSE, E_DS8_FLAG_NONE);
			return;								// 1���Z�b�g�����̂ŏI������

		}
	}
}

//=============================================================================
// �o���b�g�擾�֐�
//=============================================================================
BOSSBULLET *GetBossBullet(int no)
{
	return(&bossbulletWk[no]);
}
