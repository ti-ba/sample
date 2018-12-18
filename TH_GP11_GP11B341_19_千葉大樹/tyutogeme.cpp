//=============================================================================
//
// Main���� [main.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "bg.h"
#include <time.h>
#include "tyutogeme.h"
#include "tyutoenemy.h"
#include "sound.h"
#include "bom.h"
#include "effect.h"
#include "effect2.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SAFE_RELEASE(ptr)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexDescription(void);
LRESULT CALLBACK Wnd(HWND, UINT, WPARAM, LPARAM);

 void SetVertexTyutoBG(void);

  static void CheckHit(void);
  static bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);
  static void InitGame(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
   LPDIRECT3DTEXTURE9		D3DTextureTyutoBG = NULL;		// �e�N�X�`���ւ̃|�C���^
   VERTEX_2D				vertexWkTyutoBG[NUM_VERTEX];	// ���_���i�[���[�N
   D3DXVECTOR3				posTyutoBG;						// �w�i�̈ʒu

   VERTEX_2D				vertexWkTyutoBG2[NUM_VERTEX];	// ���_���i�[���[�N
   LPDIRECT3DTEXTURE9		D3DTextureTyutoBG2 = NULL;		// �e�N�X�`���ւ̃|�C���^
   D3DXVECTOR3				posTyutoBG2;					// �w�i�̈ʒu

   VERTEX_2D				vertexWkDescriptionLogo[NUM_VERTEX];		// ���_���i�[���[�N
   LPDIRECT3DTEXTURE9		D3DTextureDescriptionLogo = NULL;	// �e�N�X�`���ւ̃|�C���^


  extern LPDIRECTSOUNDBUFFER8	enemySE;			// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTyutoGame(HWND hWnd, BOOL bWindow)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TYUTOBG,			// �t�@�C���̖��O
		&D3DTextureTyutoBG);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(Device,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TYUTOBG2,			// �t�@�C���̖��O
		&D3DTextureTyutoBG2);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(Device,						// �f�o�C�X�ւ̃|�C���^
	TEXTURE_DESCRIPTION_LOGO,								// �t�@�C����
	&D3DTextureDescriptionLogo);							// �ǂݍ��ރ������[

	posTyutoBG = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posTyutoBG2 = D3DXVECTOR3(0.0f, -600.0f, 0.0f);

	// ���_���̍쐬
	MakeVertexDescription();

	posTyutoBG.x = -GetPlayer(0)->pos.x /4.0f;

	SetVertexTyutoBG();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTyutoGame(void)
{
	if (D3DTextureTyutoBG != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureTyutoBG->Release();
		D3DTextureTyutoBG = NULL;
	}

	if (D3DTextureTyutoBG2 != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureTyutoBG2->Release();
		D3DTextureTyutoBG2 = NULL;
	}

	if (D3DTextureDescriptionLogo != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureDescriptionLogo->Release();
		D3DTextureDescriptionLogo = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTyutoGame(void)
{
	// �X�N���[������
	posTyutoBG.y += 3.0f;
	posTyutoBG2.y += 3.0f;

	if (posTyutoBG.y == 600)
	{
		posTyutoBG = D3DXVECTOR3(0.0f, -600.0f, 0.0f);

	}

	if (posTyutoBG2.y == 600)
	{
		posTyutoBG2 = D3DXVECTOR3(0.0f, -600.0f, 0.0f);
	}
	UpdateBG();
		// �v���C���[�̍X�V����
		UpdatePlayer();

		// �o���b�g�̍X�V����
		UpdateBullet();

		//�@�{���̍X�V����
		UpdateBom();

		//�`���[�g�G�l�~�[�X�V����
		UpdateTyutoEnemy();

		// �G�t�F�N�g�X�V����
		UpdateEffect();

		// �G�t�F�N�g�Q�X�V����
		UpdateEffect2();

		// �����蔻��
		CheckHit();

		SetVertexTyutoBG();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTyutoGame(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTextureTyutoBG);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkTyutoBG, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTextureTyutoBG2);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkTyutoBG2, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTextureDescriptionLogo);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkDescriptionLogo, sizeof(VERTEX_2D));


	//�`���[�g�G�l�~�[�`�揈��
	DrawTyutoEnemy();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �o���b�g�̕`�揈��
	DrawBullet();

	// �G�t�F�N�g�̕`�揈��
	DrawEffect();

	// �G�t�F�N�g�Q�̕`�揈��
	DrawEffect2();

	//�{���̕`�揈��
	DrawBom();

}


//=============================================================================
// �����蔻�菈��
//=============================================================================
void CheckHit(void)
{
	PLAYER *player = GetPlayer(0);			//�v���C���[�̃|�C���^�[��������
	TYUTOENEMY *tyutoenemy = GetTyutoEnemy(0);  //�G�l�~�[�|�C���^�[������
	BULLET *bullet = GetBullet(0);			// �o���b�g�̃|�C���^�[��������
	BOM *bom = GetBom(0);					// �{���̃|�C���^�[��������
	int tyutoenemycnt = 0;					//�G�𐔂���

	/* �e�ƓG(BC)*/
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
 		if (bullet->use == false) continue;

		for (int j = 0; j<TYUTOENEMY_MAX; j++, tyutoenemy++)
		{
			if (tyutoenemy->use == false) continue;

			if (CheckHitBC(bullet->pos, tyutoenemy->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_TYUTOENEMY_SIZE_X))
			{
				PlaySound(enemySE, E_DS8_FLAG_NONE);	// ���������Ƃ��̉��Đ�
				bullet->use = false;				// �e�̏��ŏ������s��
				SetEffect(tyutoenemy->pos);			// ���j
				tyutoenemy->use = false;			// �G�͓|�����
			}
		}
	}

	for (int i = 0; i < BOM_MAX; i++, bom++)
	{
		if (bom->use == false) continue;

		for (int j = 0; j < TYUTOENEMY_MAX; j++, tyutoenemy++)
		{
			if (tyutoenemy->use == false) continue;

			if (CheckHitBC(bom->pos, tyutoenemy->pos, TEXTURE_BOM_SIZE_X, TEXTURE_TYUTOENEMY_SIZE_X))
			{
				PlaySound(enemySE, E_DS8_FLAG_NONE);	// ���������Ƃ��̉��Đ�
				bom->use = false;						// �e�̏��ŏ������s��
				SetEffect2(tyutoenemy->pos);			// ���j
				tyutoenemy->use = false;				// �G�͓|�����
			}
		}
	}

	//�G���S�ł������ʑJ��
	tyutoenemy = GetTyutoEnemy(0);			// �G�l�~�[�̃|�C���^�[��������
	for (int i = 0; i < TYUTOENEMY_MAX; i++, tyutoenemy++)
	{
		if (tyutoenemy->use == true)
		{
			tyutoenemycnt++;
		}
	}

	// ���������ʓG���S�ŁH
	if (tyutoenemycnt == 0)
	{
		InitGame();		// �Q�[���̍ď���������
		SetStage(STAGE_GAME_START);
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
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexDescription(void)
{
	// ���_���W�̐ݒ�
	vertexWkTyutoBG[0].vtx = D3DXVECTOR3(TYUTOBG_POS_X, TYUTOBG_POS_Y, 0.0f);
	vertexWkTyutoBG[1].vtx = D3DXVECTOR3(TYUTOBG_POS_X +TYUTOBG_SIZE_X, TYUTOBG_POS_Y, 0.0f);
	vertexWkTyutoBG[2].vtx = D3DXVECTOR3(TYUTOBG_POS_X, TYUTOBG_POS_Y + TYUTOBG_SIZE_Y, 0.0f);
	vertexWkTyutoBG[3].vtx = D3DXVECTOR3(TYUTOBG_POS_X +TYUTOBG_SIZE_X, TYUTOBG_POS_Y + TYUTOBG_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkTyutoBG[0].rhw =
	vertexWkTyutoBG[1].rhw =
	vertexWkTyutoBG[2].rhw =
	vertexWkTyutoBG[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkTyutoBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTyutoBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTyutoBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTyutoBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkTyutoBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkTyutoBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkTyutoBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkTyutoBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_���W�̐ݒ�
	vertexWkTyutoBG2[0].vtx = D3DXVECTOR3(TYUTOBG2_POS_X, TYUTOBG2_POS_Y, 0.0f);
	vertexWkTyutoBG2[1].vtx = D3DXVECTOR3(TYUTOBG2_POS_X +TYUTOBG2_SIZE_X, TYUTOBG2_POS_Y, 0.0f);
	vertexWkTyutoBG2[2].vtx = D3DXVECTOR3(TYUTOBG2_POS_X, TYUTOBG2_POS_Y + TYUTOBG2_SIZE_Y, 0.0f);
	vertexWkTyutoBG2[3].vtx = D3DXVECTOR3(TYUTOBG2_POS_X +TYUTOBG2_SIZE_X, TYUTOBG2_POS_Y + TYUTOBG2_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkTyutoBG2[0].rhw =
	vertexWkTyutoBG2[1].rhw =
	vertexWkTyutoBG2[2].rhw =
	vertexWkTyutoBG2[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkTyutoBG2[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTyutoBG2[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTyutoBG2[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTyutoBG2[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkTyutoBG2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkTyutoBG2[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkTyutoBG2[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkTyutoBG2[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_���W�̐ݒ�
	vertexWkDescriptionLogo[0].vtx = D3DXVECTOR3(DESCRIPTIONLOGO_POS_X, DESCRIPTIONLOGO_POS_Y, 0.0f);
	vertexWkDescriptionLogo[1].vtx = D3DXVECTOR3(DESCRIPTIONLOGO_POS_X + DESCRIPTIONLOGO_SIZE_X, DESCRIPTIONLOGO_POS_Y, 0.0f);
	vertexWkDescriptionLogo[2].vtx = D3DXVECTOR3(DESCRIPTIONLOGO_POS_X, DESCRIPTIONLOGO_POS_Y + DESCRIPTIONLOGO_SIZE_Y, 0.0f);
	vertexWkDescriptionLogo[3].vtx = D3DXVECTOR3(DESCRIPTIONLOGO_POS_X + DESCRIPTIONLOGO_SIZE_X, DESCRIPTIONLOGO_POS_Y + DESCRIPTIONLOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkDescriptionLogo[0].rhw =
	vertexWkDescriptionLogo[1].rhw =
	vertexWkDescriptionLogo[2].rhw =
	vertexWkDescriptionLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkDescriptionLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkDescriptionLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkDescriptionLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkDescriptionLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkDescriptionLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkDescriptionLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkDescriptionLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkDescriptionLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexTyutoBG(void)
{
	// ���_���W�̐ݒ�
	vertexWkTyutoBG[0].vtx = D3DXVECTOR3(TYUTOBG_POS_X, TYUTOBG_POS_Y, 0.0f) + posTyutoBG;
	vertexWkTyutoBG[1].vtx = D3DXVECTOR3(TYUTOBG_POS_X + TYUTOBG_SIZE_X, TYUTOBG_POS_Y, 0.0f) + posTyutoBG;
	vertexWkTyutoBG[2].vtx = D3DXVECTOR3(TYUTOBG_POS_X, TYUTOBG_POS_Y + TYUTOBG_SIZE_Y, 0.0f) + posTyutoBG;
	vertexWkTyutoBG[3].vtx = D3DXVECTOR3(TYUTOBG_POS_X + TYUTOBG_SIZE_X, TYUTOBG_POS_Y + TYUTOBG_SIZE_Y, 0.0f) + posTyutoBG;



	// ���_���W�̐ݒ�
	vertexWkTyutoBG2[0].vtx = D3DXVECTOR3(TYUTOBG2_POS_X, TYUTOBG2_POS_Y, 0.0f) + posTyutoBG2;
	vertexWkTyutoBG2[1].vtx = D3DXVECTOR3(TYUTOBG2_POS_X + TYUTOBG2_SIZE_X, TYUTOBG2_POS_Y, 0.0f) + posTyutoBG2;
	vertexWkTyutoBG2[2].vtx = D3DXVECTOR3(TYUTOBG2_POS_X, TYUTOBG2_POS_Y + TYUTOBG2_SIZE_Y, 0.0f) + posTyutoBG2;
	vertexWkTyutoBG2[3].vtx = D3DXVECTOR3(TYUTOBG2_POS_X + TYUTOBG2_SIZE_X, TYUTOBG2_POS_Y + TYUTOBG2_SIZE_Y, 0.0f) + posTyutoBG2;
}

//=============================================================================
// �Q�[���̍ď�������������
// �߂�l�F����
//=============================================================================
void InitGame(void)
{
	InitPlayer(1);		// �v���C���[�̍ď�����
	InitTyutoEnemy(1);	// �G�l�~�[�̍ď�����
	InitBullet(1);		// �o���b�g�̍ď�����
	InitBG(1);			// BG�̍ď�����
	InitEffect(1);		// �G�t�F�N�g�ď�����
	InitEffect2(1);		// �G�t�F�N�g�Q�ď�����
	InitBom(1);			// �{���ď�����
}
