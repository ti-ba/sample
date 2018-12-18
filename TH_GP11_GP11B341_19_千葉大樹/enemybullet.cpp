//=============================================================================
//
// �o���b�g���� [EnemyBullet.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "EnemyBullet.h"
#include "sound.h"
#include "tyutoenemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemyBullet(int no);
void SetTextureEnemyBullet(int no, int cntPattern);
void SetVertexEnemyBullet(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureEnemyBullet = NULL;		// �e�N�X�`���ւ̃|���S��
ENEMYBULLET				EnemyBulletWk[ENEMYBULLET_MAX];		// �o���b�g�\����
LPDIRECTSOUNDBUFFER8	enemybulletSE;						// SE�p�o�b�t�@


//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyBullet(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYBULLET *EnemyBullet = &EnemyBulletWk[0];		// �G�l�~�[�̃|�C���^�[��������

										
	if (type == 0)										// �e�N�X�`���[�̏��������s���H
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,				// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMYBULLET,					// �t�@�C���̖��O
			&D3DTextureEnemyBullet);					// �ǂݍ��ރ������̃|�C���^
		enemybulletSE = LoadSound(SHOT_00);
	}

	// �o���b�g�̏���������
	for (int i = 0; i < ENEMYBULLET_MAX; i++, EnemyBullet++)
	{
		EnemyBullet->use = false;								// ���g�p�i���˂���Ă��Ȃ��e�j
		EnemyBullet->pos = D3DXVECTOR3(+300.0f, 0.0f, 0.0f);	// ���W�f�[�^��������
		EnemyBullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]�f�[�^��������
		EnemyBullet->PatternAnim = 0;							// �A�j���p�^�[���ԍ��������_���ŏ�����
		EnemyBullet->CountAnim = 0;								// �A�j���J�E���g��������

		EnemyBullet->Texture = D3DTextureEnemyBullet;			// �e�N�X�`�����
		MakeVertexEnemyBullet(i);								// ���_���̍쐬
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyBullet(void)
{
	if (D3DTextureEnemyBullet != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureEnemyBullet->Release();
		D3DTextureEnemyBullet = NULL;
	}

	if (enemybulletSE != NULL)
	{	// �e�N�X�`���̊J��
		enemybulletSE->Release();
		enemybulletSE = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyBullet(void)
{
	ENEMYBULLET *EnemyBullet = EnemyBulletWk;				// �o���b�g�̃|�C���^�[��������

	for (int i = 0; i < ENEMYBULLET_MAX; i++, EnemyBullet++)
	{
		if (EnemyBullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �G�̃o���b�g�̈ړ�����
			EnemyBullet->pos.y += ENEMYBULLET_SPEED;

			// ��ʊO�܂Ői�񂾁H
			if (EnemyBullet->pos.y < -TEXTURE_ENEMYBULLET_SIZE_Y)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				EnemyBullet->use = false;
				EnemyBullet->pos.x = -100.0f;
			}


			SetVertexEnemyBullet(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYBULLET *EnemyBullet = EnemyBulletWk;				// �o���b�g�̃|�C���^�[��������

											
	Device->SetFVF(FVF_VERTEX_2D);			// ���_�t�H�[�}�b�g�̐ݒ�

	for (int i = 0; i <ENEMYBULLET_MAX; i++, EnemyBullet++)
	{
		if (EnemyBullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, EnemyBullet->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMYBULLET, EnemyBullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemyBullet(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYBULLET*EnemyBullet = &EnemyBulletWk[no];			// �o���b�g�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	SetVertexEnemyBullet(no);

	// rhw�̐ݒ�
	EnemyBullet->vertexWk[0].rhw =
	EnemyBullet->vertexWk[1].rhw =
	EnemyBullet->vertexWk[2].rhw =
	EnemyBullet->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	EnemyBullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	EnemyBullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	EnemyBullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	EnemyBullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	EnemyBullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	EnemyBullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET, 0.0f);
	EnemyBullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET);
	EnemyBullet->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET);

	EnemyBullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	EnemyBullet->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	EnemyBullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	EnemyBullet->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemyBullet(int no, int cntPattern)
{
	ENEMYBULLET *EnemyBullet = &EnemyBulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET;

	EnemyBullet->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	EnemyBullet->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	EnemyBullet->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	EnemyBullet->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemyBullet(int no)
{
	ENEMYBULLET *EnemyBullet = &EnemyBulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	EnemyBullet->vertexWk[0].vtx.x = EnemyBullet->pos.x - TEXTURE_ENEMYBULLET_SIZE_X;
	EnemyBullet->vertexWk[0].vtx.y = EnemyBullet->pos.y - TEXTURE_ENEMYBULLET_SIZE_Y;
	EnemyBullet->vertexWk[0].vtx.z = 0.0f;

	EnemyBullet->vertexWk[1].vtx.x = EnemyBullet->pos.x + TEXTURE_ENEMYBULLET_SIZE_X;
	EnemyBullet->vertexWk[1].vtx.y = EnemyBullet->pos.y - TEXTURE_ENEMYBULLET_SIZE_Y;
	EnemyBullet->vertexWk[1].vtx.z = 0.0f;

	EnemyBullet->vertexWk[2].vtx.x = EnemyBullet->pos.x - TEXTURE_ENEMYBULLET_SIZE_X;
	EnemyBullet->vertexWk[2].vtx.y = EnemyBullet->pos.y + TEXTURE_ENEMYBULLET_SIZE_Y;
	EnemyBullet->vertexWk[2].vtx.z = 0.0f;

	EnemyBullet->vertexWk[3].vtx.x = EnemyBullet->pos.x + TEXTURE_ENEMYBULLET_SIZE_X;
	EnemyBullet->vertexWk[3].vtx.y = EnemyBullet->pos.y + TEXTURE_ENEMYBULLET_SIZE_Y;
	EnemyBullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetEnemyBullet(D3DXVECTOR3 pos)
{
	ENEMYBULLET *EnemyBullet = &EnemyBulletWk[0];			// �o���b�g�̃|�C���^�[��������
	ENEMY *enemy = GetEnemy(0);

	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < ENEMYBULLET_MAX; i++,EnemyBullet++)
	{
		if (EnemyBullet->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			EnemyBullet->use = true;			// �g�p��Ԃ֕ύX����
			EnemyBullet->pos = pos;				// ���W���Z�b�g


			PlaySound(enemybulletSE, E_DS8_FLAG_NONE);  // ���ˉ��Đ�

			return;								// 1���Z�b�g�����̂ŏI������
		}
		if (enemy->use = false)
		{
		return;
		}
	}
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMYBULLET *GetEnemyBullet(int no)
{
	return(&EnemyBulletWk[no]);
}
