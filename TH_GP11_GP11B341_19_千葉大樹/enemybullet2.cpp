//=============================================================================
//
// �o���b�g���� [EnemyBullet2.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "EnemyBullet2.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemyBullet2(int no);
void SetTextureEnemyBullet2(int no, int cntPattern);
void SetVertexEnemyBullet2(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureEnemyBullet2 = NULL;		// �e�N�X�`���ւ̃|���S��
ENEMYBULLET2				EnemyBullet2Wk[ENEMYBULLET2_MAX];		// �o���b�g�\����
LPDIRECTSOUNDBUFFER8	enemybullet2SE;						// SE�p�o�b�t�@


//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyBullet2(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYBULLET2 *EnemyBullet2 = &EnemyBullet2Wk[0];		// �G�l�~�[�̃|�C���^�[��������


	if (type == 0)										// �e�N�X�`���[�̏��������s���H
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,				// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMYBULLET2,					// �t�@�C���̖��O
			&D3DTextureEnemyBullet2);					// �ǂݍ��ރ������̃|�C���^
		enemybullet2SE = LoadSound(SHOT_00);
	}

	// �o���b�g�̏���������
	for (int i = 0; i < ENEMYBULLET2_MAX; i++, EnemyBullet2++)
	{
		EnemyBullet2->use = false;								// ���g�p�i���˂���Ă��Ȃ��e�j
		EnemyBullet2->pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);		// ���W�f�[�^��������
		EnemyBullet2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]�f�[�^��������
		EnemyBullet2->PatternAnim = 0;							// �A�j���p�^�[���ԍ��������_���ŏ�����
		EnemyBullet2->CountAnim = 0;							// �A�j���J�E���g��������

		EnemyBullet2->Texture = D3DTextureEnemyBullet2;			// �e�N�X�`�����
		MakeVertexEnemyBullet2(i);								// ���_���̍쐬
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyBullet2(void)
{
	if (D3DTextureEnemyBullet2 != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureEnemyBullet2->Release();
		D3DTextureEnemyBullet2 = NULL;
	}

	if (enemybullet2SE != NULL)
	{	// �e�N�X�`���̊J��
		enemybullet2SE->Release();
		enemybullet2SE = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyBullet2(void)
{
	ENEMYBULLET2 *EnemyBullet2 = EnemyBullet2Wk;				// �o���b�g�̃|�C���^�[��������

	for (int i = 0; i < ENEMYBULLET2_MAX; i++, EnemyBullet2++)
	{
		if (EnemyBullet2->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �G�̃o���b�g�̈ړ�����
			EnemyBullet2->pos.x += ENEMYBULLET2_SPEED;

			// ��ʊO�܂Ői�񂾁H
			if (EnemyBullet2->pos.x < -TEXTURE_ENEMYBULLET2_SIZE_X)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				EnemyBullet2->use = false;
				EnemyBullet2->pos.x = 100.0f;
			}


			SetVertexEnemyBullet2(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyBullet2(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYBULLET2 *EnemyBullet2 = EnemyBullet2Wk;				// �o���b�g�̃|�C���^�[��������


	Device->SetFVF(FVF_VERTEX_2D);			// ���_�t�H�[�}�b�g�̐ݒ�

	for (int i = 0; i <ENEMYBULLET2_MAX; i++, EnemyBullet2++)
	{
		if (EnemyBullet2->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, EnemyBullet2->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMYBULLET2, EnemyBullet2->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemyBullet2(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMYBULLET2*EnemyBullet2 = &EnemyBullet2Wk[no];			// �o���b�g�̃|�C���^�[��������

															// ���_���W�̐ݒ�
	SetVertexEnemyBullet2(no);

	// rhw�̐ݒ�
	EnemyBullet2->vertexWk[0].rhw =
		EnemyBullet2->vertexWk[1].rhw =
		EnemyBullet2->vertexWk[2].rhw =
		EnemyBullet2->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	EnemyBullet2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	EnemyBullet2->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	EnemyBullet2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	EnemyBullet2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	EnemyBullet2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	EnemyBullet2->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2, 0.0f);
	EnemyBullet2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET2);
	EnemyBullet2->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET2);

	EnemyBullet2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	EnemyBullet2->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	EnemyBullet2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	EnemyBullet2->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemyBullet2(int no, int cntPattern)
{
	ENEMYBULLET2 *EnemyBullet2 = &EnemyBullet2Wk[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET2;

	EnemyBullet2->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	EnemyBullet2->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	EnemyBullet2->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	EnemyBullet2->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemyBullet2(int no)
{
	ENEMYBULLET2 *EnemyBullet2 = &EnemyBullet2Wk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	EnemyBullet2->vertexWk[0].vtx.x = EnemyBullet2->pos.x - TEXTURE_ENEMYBULLET2_SIZE_X;
	EnemyBullet2->vertexWk[0].vtx.y = EnemyBullet2->pos.y - TEXTURE_ENEMYBULLET2_SIZE_Y;
	EnemyBullet2->vertexWk[0].vtx.z = 0.0f;

	EnemyBullet2->vertexWk[1].vtx.x = EnemyBullet2->pos.x + TEXTURE_ENEMYBULLET2_SIZE_X;
	EnemyBullet2->vertexWk[1].vtx.y = EnemyBullet2->pos.y - TEXTURE_ENEMYBULLET2_SIZE_Y;
	EnemyBullet2->vertexWk[1].vtx.z = 0.0f;

	EnemyBullet2->vertexWk[2].vtx.x = EnemyBullet2->pos.x - TEXTURE_ENEMYBULLET2_SIZE_X;
	EnemyBullet2->vertexWk[2].vtx.y = EnemyBullet2->pos.y + TEXTURE_ENEMYBULLET2_SIZE_Y;
	EnemyBullet2->vertexWk[2].vtx.z = 0.0f;

	EnemyBullet2->vertexWk[3].vtx.x = EnemyBullet2->pos.x + TEXTURE_ENEMYBULLET2_SIZE_X;
	EnemyBullet2->vertexWk[3].vtx.y = EnemyBullet2->pos.y + TEXTURE_ENEMYBULLET2_SIZE_Y;
	EnemyBullet2->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetEnemyBullet2(D3DXVECTOR3 pos)
{
	ENEMYBULLET2 *EnemyBullet2 = &EnemyBullet2Wk[0];			// �o���b�g�̃|�C���^�[��������
	ENEMY *enemy = GetEnemy(0);

	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < ENEMYBULLET2_MAX; i++, EnemyBullet2++)
	{
		if (EnemyBullet2->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			EnemyBullet2->use = true;			// �g�p��Ԃ֕ύX����
			EnemyBullet2->pos = pos;				// ���W���Z�b�g


			PlaySound(enemybullet2SE, E_DS8_FLAG_NONE);  // ���ˉ��Đ�

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
ENEMYBULLET2 *GetEnemyBullet2(int no)
{
	return(&EnemyBullet2Wk[no]);
}
