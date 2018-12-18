//=============================================================================
//
// �G���� [enemy.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "enemy2.h"
#include "input.h"
#include "enemybullet2.h"
#include "sound.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy2(int no);
void SetTextureEnemy2(int no, int cntPattern);
void SetVertexEnemy2(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		D3DTextureEnemy2 = NULL;		// �e�N�X�`���ւ̃|���S��
ENEMY2					enemyWk2[ENEMY2_MAX];			// �G�l�~�[�\����
static LPDIRECTSOUNDBUFFER8	enemy2SE;					// SE�p�o�b�t�@


//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy2(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMY2 *enemy2 = enemyWk2;				// �G�l�~�[�̃|�C���^�[��������
											// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMY2,				// �t�@�C���̖��O
			&D3DTextureEnemy2);				// �ǂݍ��ރ������̃|�C���^
		enemy2SE = LoadSound(HIT_00);	//

	}
	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
	{
		enemy2->use = true;										// �g�p
		enemy2->pos = D3DXVECTOR3(0.0f,150 + i * 0.0f, 0.0f); // ���W�f�[�^��������
		enemy2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		enemy2->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		enemy2->CountAnim = 0;										// �A�j���J�E���g��������
		enemy2->bulletTime = 0;									// �e���ˎ��Ԃ̏�����

		D3DXVECTOR2 temp2 = D3DXVECTOR2(TEXTURE_ENEMY2_SIZE_X, TEXTURE_ENEMY2_SIZE_Y);
		enemy2->Radius = D3DXVec2Length(&temp2);					// �G�l�~�[�̔��a��������
		enemy2->BaseAngle = atan2f(TEXTURE_ENEMY2_SIZE_Y, TEXTURE_ENEMY2_SIZE_X);	// �G�l�~�[�̊p�x��������

		enemy2->Texture = D3DTextureEnemy2;						// �e�N�X�`�����
		MakeVertexEnemy2(i);										// ���_���̍쐬

		enemy2->pos.y = rand() % 500;		//�����ʒu�����炷����

		//�o������炷����
		enemy2->Startweit = rand() % 100;
	}

	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy2(void)
{
	if (D3DTextureEnemy2 != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureEnemy2->Release();
		D3DTextureEnemy2 = NULL;
	}

	if (enemy2SE != NULL)
	{	// �e�N�X�`���̊J��
		enemy2SE->Release();
		enemy2SE = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy2(void)
{
	ENEMY2 *enemy2 = enemyWk2;				// �G�l�~�[�̃|�C���^�[��������
	D3DXVECTOR3 pos = enemy2->pos;

	for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
	{
		if (enemy2->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{

			//�X�^�[�g�n�_�ɂ���ꍇ�A���ˎ��Ԃ��J�E���g�_�E������
			if (enemy2->pos.x == START_COUNT2)
			{
				enemy2->Startweit--;
			}

			if (enemy2->Startweit <= 0)
			{
				enemy2->pos.x += ENEMY2_SPEED;
			}

			SetVertexEnemy2(i);		// �ړ���̍��W�Œ��_��ݒ�

			enemy2->bulletTime++;	//���ˎ��Ԃ�����

			//�e����
			if (enemy2->bulletTime > (60 + rand() % (60 * 30)))
			{
				enemy2->bulletTime = 0;
				{
					D3DXVECTOR3 pos = enemy2->pos;
					pos.x -= TEXTURE_ENEMYBULLET2_SIZE_Y;
					SetEnemyBullet2(pos);
				}


				enemy2->firecount++;
				if (enemy2->firecount == 8)
				{
					pos.x -= TEXTURE_ENEMY2_SIZE_Y;
					SetEnemyBullet2(pos);
					enemy2->firecount = 0;
				}
			}
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy2(void)
{
	ENEMY2 *enemy2 = enemyWk2;			// �G�l�~�[�̃|�C���^�[��������
	LPDIRECT3DDEVICE9 Device = GetDevice();
	for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
	{
		if (enemy2->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, enemy2->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY2, enemy2->vertexWk, sizeof(VERTEX_2D));
		}
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy2(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMY2 *enemy2 = &enemyWk2[no];			// �G�l�~�[�̃|�C���^�[��������
											// rhw�̐ݒ�
	enemy2->vertexWk[0].rhw =
		enemy2->vertexWk[1].rhw =
		enemy2->vertexWk[2].rhw =
		enemy2->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemy2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemy2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy2->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY2, 0.0f);
	enemy2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY2);
	enemy2->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY2, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY2);

	enemy2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy2->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	enemy2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	enemy2->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;

}


//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy2(int no, int cntPattern)
{
	ENEMY2 *enemy2 = &enemyWk2[no];			// �G�l�~�[�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY2;

	enemy2->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	enemy2->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	enemy2->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	enemy2->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy2(int no)
{
	ENEMY2 *enemy2 = &enemyWk2[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	enemy2->vertexWk[0].vtx.x = enemy2->pos.x - cosf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[0].vtx.y = enemy2->pos.y - sinf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[0].vtx.z = 0.0f;

	enemy2->vertexWk[1].vtx.x = enemy2->pos.x + cosf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[1].vtx.y = enemy2->pos.y - sinf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[1].vtx.z = 0.0f;

	enemy2->vertexWk[2].vtx.x = enemy2->pos.x - cosf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[2].vtx.y = enemy2->pos.y + sinf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[2].vtx.z = 0.0f;

	enemy2->vertexWk[3].vtx.x = enemy2->pos.x + cosf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[3].vtx.y = enemy2->pos.y + sinf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk[3].vtx.z = 0.0f;

}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY2 *GetEnemy2(int no)
{
	return(&enemyWk2[no]);
}
