//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "bg.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBG(void);
void SetVertexBG(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureBG = NULL;	// �e�N�X�`���ւ̃|�C���^
VERTEX_2D				vertexWkBG[NUM_VERTEX];	// ���_���i�[���[�N
D3DXVECTOR3				posBG;					// �w�i�̈ʒu

LPDIRECT3DTEXTURE9		D3DBG = NULL;			// �e�N�X�`���ւ̃|�C���^
VERTEX_2D				vertexBG[NUM_VERTEX];	// ���_���i�[���[�N
D3DXVECTOR3				BG;						// �w�i�̈ʒu


//=============================================================================
// ����������
//=============================================================================
HRESULT InitBG(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	
	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAME_BG00,		// �t�@�C���̖��O
			&D3DTextureBG);			// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAME_BG01,		// �t�@�C���̖��O
			&D3DBG);				// �ǂݍ��ރ������[

	}

	posBG = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	BG = D3DXVECTOR3(0.0f, -600.0f, 0.0f);

	// ���_���̍쐬
	MakeVertexBG();

	posBG.x = -GetPlayer(0)->pos.x / 4.0f;

	SetVertexBG();

	return S_OK;


}

//=============================================================================
// �I������
//=============================================================================
void UninitBG(void)
{
	if (D3DTextureBG != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureBG->Release();
		D3DTextureBG = NULL;
	}

	if (D3DBG != NULL)
	{// �e�N�X�`���̊J��
		D3DBG->Release();
		D3DBG = NULL;
	}

}



//=============================================================================
// �X�V����
//=============================================================================
void UpdateBG(void)
{
	
	// ���t���[�����s���鏈��
	
	// �X�N���[������
	posBG.y += 3.0f;
	   BG.y += 3.0f;

	 if (posBG.y == 600)
	 {
		 	posBG = D3DXVECTOR3(0.0f,-600.0f, 0.0f);
		 
	 }

	 if (BG.y == 600)
	 {
		 	BG = D3DXVECTOR3(0.0f, -600.0f, 0.0f);
	 }

	SetVertexBG();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTextureBG);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkBG, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DBG);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexBG, sizeof(VERTEX_2D));

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBG(void)
{
	// ���_���W�̐ݒ�
	vertexWkBG[0].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y, 0.0f);
	vertexWkBG[1].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f);
	vertexWkBG[2].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f);
	vertexWkBG[3].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	vertexWkBG[0].rhw =
	vertexWkBG[1].rhw =
	vertexWkBG[2].rhw =
	vertexWkBG[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	// ���_���W�̐ݒ�
	vertexBG[0].vtx = D3DXVECTOR3(BG01_POS_X, BG01_POS_Y, 0.0f);
	vertexBG[1].vtx = D3DXVECTOR3(BG01_POS_X + BG01_SIZE_X, BG01_POS_Y, 0.0f);
	vertexBG[2].vtx = D3DXVECTOR3(BG01_POS_X, BG01_POS_Y + BG01_SIZE_Y, 0.0f);
	vertexBG[3].vtx = D3DXVECTOR3(BG01_POS_X + BG01_SIZE_X, BG01_POS_Y + BG01_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	vertexBG[0].rhw =
	vertexBG[1].rhw =
	vertexBG[2].rhw =
	vertexBG[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBG(void)
{
	// ���_���W�̐ݒ�
	vertexWkBG[0].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y, 0.0f) + posBG;
	vertexWkBG[1].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f) + posBG;
	vertexWkBG[2].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + posBG;
	vertexWkBG[3].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + posBG;



	// ���_���W�̐ݒ�
	vertexBG[0].vtx = D3DXVECTOR3(BG01_POS_X, BG01_POS_Y, 0.0f) + BG;
	vertexBG[1].vtx = D3DXVECTOR3(BG01_POS_X + BG01_SIZE_X, BG01_POS_Y, 0.0f) + BG;
	vertexBG[2].vtx = D3DXVECTOR3(BG01_POS_X, BG01_POS_Y + BG01_SIZE_Y, 0.0f) + BG;
	vertexBG[3].vtx = D3DXVECTOR3(BG01_POS_X + BG01_SIZE_X, BG01_POS_Y + BG01_SIZE_Y, 0.0f) + BG;

}
