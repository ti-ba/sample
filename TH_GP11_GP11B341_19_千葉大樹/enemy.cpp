//=============================================================================
//
// �G���� [enemy.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "input.h"
#include "enemybullet.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy( int no );
void SetTextureEnemy( int no, int cntPattern );
void SetVertexEnemy( int no );


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureEnemy = NULL;		// �e�N�X�`���ւ̃|���S��
ENEMY					enemyWk[ENEMY_MAX];			// �G�l�~�[�\����
LPDIRECTSOUNDBUFFER8	enemySE;					// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMY *enemy = enemyWk;				// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMY,				// �t�@�C���̖��O
			&D3DTextureEnemy);				// �ǂݍ��ރ������̃|�C���^
		enemySE = LoadSound(HIT_00);

	}

	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		enemy->use = true;										// �g�p
		enemy->pos = D3DXVECTOR3(100.0f,-170.0f, 0.0f);	// ���W�f�[�^��������
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		enemy->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		enemy->CountAnim = 0;									// �A�j���J�E���g��������
		enemy->bulletTime = 0;									// �e���ˎ��Ԃ̏�����

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y);
 		enemy->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		enemy->BaseAngle = atan2f(TEXTURE_ENEMY_SIZE_Y, TEXTURE_ENEMY_SIZE_X);	// �G�l�~�[�̊p�x��������

		enemy->Texture = D3DTextureEnemy;						// �e�N�X�`�����
		MakeVertexEnemy(i);										// ���_���̍쐬

		enemy->pos.x = rand() % 400;
		//�o������炷����
		enemy->Startweit = rand() % 1000; 
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	if (D3DTextureEnemy != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureEnemy->Release();
		D3DTextureEnemy = NULL;
	}

	if (enemySE != NULL)
	{	// �e�N�X�`���̊J��
		enemySE->Release();
		enemySE = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	ENEMY *enemy = enemyWk;				// �G�l�~�[�̃|�C���^�[��������

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{

			//�X�^�[�g�n�_�ɂ���ꍇ�A���ˎ��Ԃ��J�E���g�_�E������
			if (enemy->pos.y == START_COUNT)
			{
				enemy->Startweit--;
			}

			if (enemy->Startweit <= 0)
			{
				enemy->pos.y += ENEMY_SPEED;
			}

			SetVertexEnemy(i);		// �ړ���̍��W�Œ��_��ݒ�

			enemy->bulletTime++;	//���ˎ��Ԃ�����

			//�e����
			if (enemy->bulletTime > (60+rand()%(60*30)))
			{
				enemy->bulletTime = 0;
				
				{
					D3DXVECTOR3 pos = enemy->pos;
					pos.y += TEXTURE_ENEMYBULLET_SIZE_Y;
					SetEnemyBullet(pos);
				}
			}

			 //��ʊO�܂Ői�񂾁H
			//enemy = GetEnemy(0);
			//if (enemy->pos.y < -TEXTURE_ENEMY_SIZE_Y)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			//{
			//	enemy->use = true;
			//	enemy->pos.x = -100.0f;

			//	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
			//	{
			//		if (enemy->use == true)
			//		{
			//			enemy->cnt++;
			//		}
			//	}

			//}

		}
	}
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMY *enemy = enemyWk;				// �G�l�~�[�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, enemy->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, enemy->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy( int no )
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	ENEMY *enemy = &enemyWk[no];			// �G�l�~�[�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexEnemy( no );

	// rhw�̐ݒ�
	enemy->vertexWk[0].rhw =
	enemy->vertexWk[1].rhw =
	enemy->vertexWk[2].rhw =
	enemy->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemy->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY, 0.0f);
	enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY);
	enemy->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY);

	enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	enemy->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy(int no, int cntPattern)
{
	ENEMY *enemy = &enemyWk[no];			// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY;
	
	enemy->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}


//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy( int no )
{
	ENEMY *enemy = &enemyWk[no];			// �G�l�~�[�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	enemy->vertexWk[0].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[0].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[0].vtx.z = 0.0f;

	enemy->vertexWk[1].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[1].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[1].vtx.z = 0.0f;

	enemy->vertexWk[2].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[2].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[2].vtx.z = 0.0f;

	enemy->vertexWk[3].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[3].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[3].vtx.z = 0.0f;

}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY *GetEnemy(int no)
{
	return(&enemyWk[no]);
}



