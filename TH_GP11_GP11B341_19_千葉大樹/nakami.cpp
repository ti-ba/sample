//=============================================================================
//
// Main���� [main.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "enemy2.h"
#include "bullet.h"
#include "bg.h"
#include "enemybullet.h"
#include "guage.h"
#include "enemyguage.h"
#include "score.h"
#include "nakami.h"
#include "gameover.h"
#include "bom.h"
#include "bomguage.h"
#include "sound.h"
#include "boss.h"
#include "effect.h"
#include "effect2.h"
#include "bossguage.h"
#include "bossbullet.h"
#include "enemyguage2.h"
#include "EnemyBullet2.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SAFE_RELEASE(ptr)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
 LRESULT CALLBACK Wnd(HWND, UINT, WPARAM, LPARAM);

 bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);

 void CheckHit(void);
 void InitGame(void);


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

extern int			Score;							// �X�R�A
extern LPDIRECTSOUNDBUFFER8	enemySE;				// SE�p�o�b�t�@
extern LPDIRECTSOUNDBUFFER8	HitSE;					// SE�p�o�b�t�@
extern LPDIRECTSOUNDBUFFER8	enemybulletSE;			// SE�p�o�b�t�@

//=============================================================================
// �X�V����
//=============================================================================
void UpdateNakami(void)
{

		// �v���C���[�̍X�V����
		UpdatePlayer();

		// �G�l�~�[�̍X�V����
		UpdateEnemy();

		// �G�l�~�[�̍X�V����
		//UpdateEnemy2();

		// �o���b�g�̍X�V����
		UpdateBullet();

		// �{���̍X�V����
		UpdateBom();

		//�{���̃Q�[�W�X�V����
		UpdateBomGuage();


		// BG�̍X�V����
		UpdateBG();

		// �G�̒e�̍X�V����
		UpdateEnemyBullet();

		//�Q�[�W�̍X�V����
		UpdateGuage();

		//�G�l�~�[�Q�[�W�̍X�V����
		UpdateEnemyGuage();

		// �G�l�~�[�Q�[�W�̍X�V����
		UpdateEnemyGuage2();
				
		// �G�t�F�N�g�̍X�V����
		UpdateEffect();

		// �G�t�F�N�g�Q�̍X�V����
		UpdateEffect2();

		UpdateEnemyBullet2();


		//�����蔻��
		CheckHit();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawNakami(void)
{
			// BG�̕`�揈��
			DrawBG();

			// �Q�[�W�̕`�揈��
			DrawGuage();

			// �G�l�~�[�Q�[�W�̕`�揈��
			DrawEnemyGuage();

			// �G�l�~�[�Q�[�W�̕`�揈��
			DrawEnemyGuage2();

			// �G�l�~�[�̕`�揈��
			DrawEnemy();

			// �G�l�~�[�̕`�揈��
			//DrawEnemy2();

			// �v���C���[�̕`�揈��
			DrawPlayer();

			// �o���b�g�̕`�揈��
			DrawBullet();

			// �{���̕`�揈��
			DrawBom();

			// �{���̃Q�[�W�̕`�揈��
			DrawBomGuage();


			//�G�̒e�̕`�揈��
			DrawEnemyBullet();

			// �G�t�F�N�g�̕`�揈��
			DrawEffect();

			// �G�t�F�N�g�Q�̕`�揈��
			DrawEffect2();

			DrawEnemyBullet2();

}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CheckHit(void)
{
	PLAYER *player = GetPlayer(0);			//�v���C���[�̃|�C���^�[��������						
	ENEMY *enemy = GetEnemy(0);				// �G�l�~�[�̃|�C���^�[��������
	BULLET *bullet = GetBullet(0);			// �o���b�g�̃|�C���^�[��������
	GUAGE *guage = GetGuage(0);				// �Q�[�W�̃|�C���^�[��������
	ENEMYBULLET *enemybullet = GetEnemyBullet(0);	//�G�l�~�[�o���b�g�̃|�C���^�[��������
	BOM *bom = GetBom(0);					// �{���̃|�C���^�[��������
	ENEMYGUAGE *enemyguage = GetEnemyGuage(0);		//�G�̃Q�[�W�̃|�C���^�[��������
	EFFECT2 *effect2 = GetEffect2(0);		// �G�t�F�N�g�̃|�C���^�[��������
	BOSS *boss = GetBoss(0);				// �{�X�̃|�C���^�[��������
	ENEMY2 *enemy2 = GetEnemy2(0);
	ENEMYGUAGE2*Enemyguage2 = GetEnemyGuage2(0);
	/* �e�ƓG(BC)*/
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use == false) continue;
		

		for (int j = 0; j < ENEMY_MAX; j++, enemy++ ,enemyguage++)
		{
			if (enemy->use == false) continue;

			if (CheckHitBC(bullet->pos, enemy->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY_SIZE_X) == true)
			{
				bullet->use = false;		// �e�̏��ŏ������s��
				enemyguage->Radius -= 100 / 3;		// �Q�[�W����
				if (enemyguage->Radius <= 0)
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// ���������Ƃ��̉��Đ�
					enemy->use = false;		// �G�͓|�����
					SetEffect(enemy->pos);	// ���j
					AddScore(100);			// �X�R�A�v�Z
				}
				else
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// ���������Ƃ��̉��Đ�
				}
			}
		}
	}

	/* �e�ƓG2(BC)*/
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use == false) continue;


		for (int j = 0; j < ENEMY2_MAX; j++, enemy2++, Enemyguage2++)
		{
			if (enemy2->use == false) continue;

			if (CheckHitBC(bullet->pos, enemy->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY2_SIZE_X) == true)
			{
				bullet->use = false;		// �e�̏��ŏ������s��
				Enemyguage2->Radius -= 100 / 3;		// �Q�[�W����
				if (Enemyguage2->Radius <= 0)
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// ���������Ƃ��̉��Đ�
					enemy2->use = false;		// �G�͓|�����
					SetEffect(enemy2->pos);	// ���j
					AddScore(100);			// �X�R�A�v�Z
				}
				else
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// ���������Ƃ��̉��Đ�
				}
			}
		}
	}

	// �{���ƓG
	for (int i = 0; i < BOM_MAX; i++, bom++)
	{
		if (bom->use == false) continue;

		enemyguage = GetEnemyGuage(0);		//�G�̃Q�[�W�̃|�C���^�[��������
		enemy = GetEnemy(0);				//�G�̃|�C���^�[��������

		for (int j = 0; j < ENEMY_MAX; j++, enemy++ ,enemyguage++)
		{
			if (enemy->use == false) continue;

			if (CheckHitBC(bom->pos, enemy->pos, TEXTURE_BOM_SIZE_X, TEXTURE_ENEMY_SIZE_X) == true)
			{
				bom->use = false;			// �e�̏��ŏ������s��
				enemyguage->Radius -= 100 / 1;		// �Q�[�W����
				if (enemyguage->Radius <= 0)
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// ���������Ƃ��̉��Đ�
					enemy->use = false;		// �G�͓|�����
					SetEffect2(enemy->pos);	// ���j
					AddScore(100);			// �X�R�A�v�Z
				}
			}
		}
	}

	//�G�t�F�N�g�Q�ƓG
	for (int i = 0; i < EFFECT2_MAX; i++, effect2++)
	{

		if (effect2->use == false) continue;

		enemyguage = GetEnemyGuage(0);		//�G�̃Q�[�W�̃|�C���^�[��������
		enemy = GetEnemy(0);

		for (int j = 0; j < ENEMY_MAX; j++, enemy++, enemyguage++)
		{
			if (enemy->use == false) continue;

			if (CheckHitBC(effect2->pos, enemy->pos, TEXTURE_EFFECT2_SIZE_X, TEXTURE_ENEMY_SIZE_X) == true)
			{
				effect2->use = false;		// �e�̏��ŏ������s��
				enemyguage->Radius -= 100 / 1;		// �Q�[�W����
				if (enemyguage->Radius <= 0)
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// ���������Ƃ��̉��Đ�
					enemy->use = false;		// �G�͓|�����
					SetEffect2(enemy->pos);	// ���j
					AddScore(100);			// �X�R�A�v�Z
				}
				else
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// ���������Ƃ��̉��Đ�
				}
			}
		}
	}


	//�G���S�ł������ʑJ��
	enemy = GetEnemy(0);	//�G�l�~�[�̃|�C���^�[�̏�����
	int enemycnt = 0;		//�G�𐔂���

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)
		{
			enemycnt++;
		}
	}

	// ���������ʓG���S�ŁH
	if (enemycnt == 0)
	{
		boss = GetBoss(0);	//�{�X�̃|�C���^�[�̏�����
		boss->use = true;
		SetStage(STAGE_BOSS);
	}


	

	//�����ƓG�̒e(BC)
;	for (int i = 0; i < ENEMYBULLET_MAX; i++, enemybullet++)
	{
		
		if (enemybullet->use == false) continue;
		{
			//guage = GetGuage(0);		// �v���C���[�̃Q�[�W�̃|�C���^�[��������
			player = GetPlayer(0);		// �v���C���[�̃|�C���^�[��������
			for (int j = 0; j < PLAYER_MAX; j++, player++, guage++)
			{
				if (player->use == false) continue;

				if (CheckHitBC(enemybullet->pos, player->pos, TEXTURE_ENEMYBULLET_SIZE_X, TEXTURE_PLAYER_SIZE_X) == true)
				{
					enemybullet->use = false;	// �e�̏��ŏ������s��
					guage->Radius -= 100 / 9;			//�Q�[�W�̌���
					if (guage->Radius <= 0)
					{
						PlaySound(HitSE, E_DS8_FLAG_NONE);	// ��e�������Đ�
						player->use = false;	// �v���C���[�͓|�����
						InitGame();				// �Q�[���̍ď���������
						SetStage(STAGE_GAME_OVER);	//��ʑJ��
					}
					else
					{
						PlaySound(HitSE, E_DS8_FLAG_NONE);	// ��e�������Đ�
					}
				}
			}
		}
	}

}


void CheckHit_Boss(void)
{
	PLAYER *player = GetPlayer(0);			//�v���C���[�̃|�C���^�[��������						
	BULLET *bullet = GetBullet(0);			// �o���b�g�̃|�C���^�[��������
	GUAGE *guage = GetGuage(0);				// �Q�[�W�̃|�C���^�[��������
	BOM *bom = GetBom(0);					// �{���̃|�C���^�[��������
	EFFECT2 *effect2 = GetEffect2(0);		// �G�t�F�N�g�̃|�C���^�[��������
	BOSS *boss = GetBoss(0);				// �{�X�̃|�C���^�[��������
	BOSSGUAGE *bossguage = GetBossguage(0); // �{�X�Q�[�W�̃|�C���^�[��������
	BOSSBULLET *bossbullet = GetBossBullet(0);


	// �{�X�ƒe(BC)
	bullet = GetBullet(0);
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use == false) continue;
		bossguage = GetBossguage(0);		//�G�̃Q�[�W�̃|�C���^�[��������
		boss = GetBoss(0);

		for (int j = 0; j < BOSS_MAX; j++, boss++, bossguage++)
		{
			if (boss->use == false) continue;

			if (CheckHitBC(bullet->pos, boss->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_BOSS_SIZE_X) == true)
			{
				bullet->use = false;		// �e�̏��ŏ������s��
				bossguage->Radius -= 100 / 20;		// �Q�[�W����
				if (bossguage->Radius <= 0)
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// ���������Ƃ��̉��Đ�
					boss->use = false;		// �G�͓|�����
					SetEffect2(boss->pos);	// ���j
					AddScore(100);			// �X�R�A�v�Z
				}
				else
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// ���������Ƃ��̉��Đ�
				}
			}
		}
	}

	//�{���ƃ{�X(BC)
	bom = GetBom(0);					// �{���̃|�C���^�[��������
	for (int i = 0; i < BOM_MAX; i++, bom++)
	{
		if (bom->use == false) continue;
		bossguage = GetBossguage(0);		//�G�̃Q�[�W�̃|�C���^�[��������
		boss = GetBoss(0);


		for (int j = 0; j < BOSS_MAX; j++, boss++, bossguage++)
		{
			if (boss->use == false) continue;

			if (CheckHitBC(bom->pos, boss->pos, TEXTURE_BOM_SIZE_X, TEXTURE_BOSS_SIZE_X) == true)
			{
				bom->use = false;			// �e�̏��ŏ������s��
				bossguage->Radius -= 100 / 10;		// �Q�[�W����
				if (bossguage->Radius <= 0)
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// ���������Ƃ��̉��Đ�
					boss->use = false;		// �G�͓|�����
					SetEffect2(boss->pos);	// ���j
					AddScore(100);			// �X�R�A�v�Z
				}
			}
		}
	}

	//�G���S�ł������ʑJ��
	boss = GetBoss(0);	//�{�X�̃|�C���^�[�̏�����
	int bosscnt = 0;		//�G�𐔂���
	for (int i = 0; i < BOSS_MAX; i++, boss++)
	{
		if (boss->use == true)
		{
			bosscnt++;
		}
	}

	// ���������ʓG���S�ŁH
	if (bosscnt == 0)
	{
		InitGame();		// �Q�[���̍ď���������
		SetStage(STAGE_SCORE);
	}

	//�����ƃ{�X�̒e(BC)
	for (int i = 0; i < BOSSBULLET_MAX; i++, bossbullet++)
	{

		if (bossbullet->use == false) continue;

		guage = GetGuage(0);		// �v���C���[�̃Q�[�W�̃|�C���^�[��������
		player = GetPlayer(0);		// �v���C���[�̃|�C���^�[��������
		for (int j = 0; j < PLAYER_MAX; j++, player++, guage++)
		{
			if (player->use == false) continue;

			if (CheckHitBC(bossbullet->pos, player->pos, TEXTURE_BOSSBULLET_SIZE_X, TEXTURE_PLAYER_SIZE_X) == true)
			{
				bossbullet->use = false;	// �e�̏��ŏ������s��
				guage->Radius -= 100 / 9;			//�Q�[�W�̌���
				if (guage->Radius <= 0)
				{
					PlaySound(HitSE, E_DS8_FLAG_NONE);	// ��e�������Đ�
					player->use = false;	// �v���C���[�͓|�����
					InitGame();				// �Q�[���̍ď���������
					SetStage(STAGE_GAME_OVER);	//��ʑJ��
				}
				else
				{
					PlaySound(HitSE, E_DS8_FLAG_NONE);	// ��e�������Đ�
				}
			}
		}
	}

}


//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
	bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
	{
		if ((size1 + size2) * (size1 + size2) >
			(pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y))
		{
			return true;
		}

		return false;
	}

//=============================================================================
// �Q�[���̍ď�������������
// �߂�l�F����
//=============================================================================
	void InitGame(void)
	{
		InitPlayer(1);		// �v���C���[�̍ď�����
		//InitGuage(1);		// �Q�[�W�̍ď�����
		InitEnemy(1);		// �G�l�~�[�̍ď�����
		InitBullet(1);		// �o���b�g�̍ď�����
		InitBG(1);			// BG�̍ď�����
		InitEnemyBullet(1);	// �G�l�~�[�o���b�g�̍ď�����
		//InitEnemyGuage(1);	// �G�l�~�[�Q�[�W�̍ď�����
		InitEffect(1);		// �G�t�F�N�g�ď�����
		InitEffect2(1);		// �G�t�F�N�g�Q�ď�����
		InitBoss(1);		// �{�X�ď�����
		InitBossBullet(1);	// �{�X�o���b�g�ď�����
		//InitBossguage(1);
	}
