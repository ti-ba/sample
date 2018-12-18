//=============================================================================
//
// �G���� [boss.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "boss.h"
#include "input.h"
#include "bossbullet.h"
#include "bossguage.h"
#include "sound.h"
#include "player.h"
#include "bg.h"
#include "guage.h"
#include "bullet.h"
#include "bom.h"
#include "effect2.h"
#include "score.h"
#include "nakami.h"
#include "bomguage.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakevertexBoss(int no);
void SetTextureBoss(int no, int cntPattern);
void SetVertexBoss(int no);

extern void CheckHit(void);
extern bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureBoss = NULL;		// �e�N�X�`���ւ̃|���S��

BOSS					bossWk[BOSS_MAX];			// �G�l�~�[�\����
LPDIRECTSOUNDBUFFER8	bossSE;						// SE�p�o�b�t�@
//=============================================================================
// ����������
//=============================================================================
HRESULT InitBoss(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSS *boss = bossWk;				// �G�l�~�[�̃|�C���^�[��������

										// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOSS,				// �t�@�C���̖��O
			&D3DTextureBoss);				// �ǂݍ��ރ������̃|�C���^
		bossSE = LoadSound(HIT_00);
	}

	// �{�X�̏���������
	for (int i = 0; i < BOSS_MAX; i++, boss++)
	{
		boss->use = false;										// �g�p
		boss->pos = D3DXVECTOR3(300.0f, 70.0f, 0.0f);			// ���W�f�[�^��������
		boss->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		boss->bulletTime = 0;									//�e���ˎ��Ԃ̏�����

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BOSS_SIZE_X, TEXTURE_BOSS_SIZE_Y);
		boss->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		boss->BaseAngle = atan2f(TEXTURE_BOSS_SIZE_Y, TEXTURE_BOSS_SIZE_X);	// �G�l�~�[�̊p�x��������

		boss->Texture = D3DTextureBoss;							// �e�N�X�`�����
		MakevertexBoss(i);										// ���_���̍쐬

	}


	return S_OK;
}

////=============================================================================
//// �I������
////=============================================================================
//void UninitBoss(void)
//{
//
//
//
//	 //�{�X�̏I������
//	UninitBoss();
//
//	//UninitBossguage();
//
//
//
//	//�{�X�̒e�I������
//	UninitBossBullet();
//
//
//
//
//}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss(void)
{
	BOSS *boss = bossWk;				// �G�l�~�[�̃|�C���^�[��������
	D3DXVECTOR3 pos = boss->pos;



	// �{�X�̃Q�[�W�X�V����
	UpdateBossguage();
	
	// �{�X�̍X�V����
	UpdateBoss(); 




	// �{�X�̒e�X�V����
	UpdateBossBullet();



	//�����蔻��
	//CheckHit_Boss();


	for (int i = 0; i < BOSS_MAX; i++, boss++)
	{
		if (boss->use == false)			// �g�p���Ă����ԂȂ�X�V����
		{
			boss->fire++;
			if (boss->fire == 40)
				{
					pos.y -= TEXTURE_BOSS_SIZE_Y;
					SetBossBullet(pos);
					boss->fire = 0;
				}
			
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSS *boss = bossWk;				// �G�l�~�[�̃|�C���^�[��������




	// �{�X�̕`�揈��
	DrawBoss();


	DrawBossguage();



	//�{�X�̒e
	DrawBossBullet();


	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSS_MAX; i++, boss++)
	{
		if (boss->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, boss->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSS, boss->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakevertexBoss(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSS *boss = &bossWk[no];			// �G�l�~�[�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexBoss(no);

	// rhw�̐ݒ�
	boss->vertexWk[0].rhw =


	boss->vertexWk[1].rhw =
	boss->vertexWk[2].rhw =
	boss->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	boss->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	boss->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS, 0.0f);
	boss->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS);
	boss->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS);

	boss->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	boss->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	boss->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBoss(int no, int cntPattern)
{
	BOSS *boss = &bossWk[no];			// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSS;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSS;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS;

	boss->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	boss->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	boss->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	boss->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBoss(int no)
{
	BOSS *boss = &bossWk[no];			// �G�l�~�[�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	boss->vertexWk[0].vtx.x = boss->pos.x - cosf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk[0].vtx.z = 0.0f;

	boss->vertexWk[1].vtx.x = boss->pos.x + cosf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk[1].vtx.y = boss->pos.y - sinf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk[1].vtx.z = 0.0f;

	boss->vertexWk[2].vtx.x = boss->pos.x - cosf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk[2].vtx.y = boss->pos.y + sinf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk[2].vtx.z = 0.0f;

	boss->vertexWk[3].vtx.x = boss->pos.x + cosf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk[3].vtx.y = boss->pos.y + sinf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk[3].vtx.z = 0.0f;
}


//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
BOSS *GetBoss(int no)
{
	return(&bossWk[no]);
}


