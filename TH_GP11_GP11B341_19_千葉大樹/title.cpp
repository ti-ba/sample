//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "player.h"
#include "BG.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTitle(void);
void SetVertexTitle(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureTitle = NULL;		// �e�N�X�`���ւ̃|�C���^
VERTEX_2D				vertexWkTitle[NUM_VERTEX];	// ���_���i�[���[�N
D3DXVECTOR3				posTitle;					// �w�i�̈ʒu

VERTEX_2D				vertexWkTitle2[NUM_VERTEX];		// ���_���i�[���[�N
LPDIRECT3DTEXTURE9		D3DTextureTitle2 = NULL;		// �e�N�X�`���ւ̃|�C���^
D3DXVECTOR3				posTitle2;						// �w�i�̈ʒu


VERTEX_2D				vertexWkTitleLogo[NUM_VERTEX];		// ���_���i�[���[�N
LPDIRECT3DTEXTURE9		D3DTextureTitleLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				vertexWkpushLogo[NUM_VERTEX];		// ���_���i�[���[�N
LPDIRECT3DTEXTURE9		D3DTexturepushLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TITLE,			// �t�@�C���̖��O
								&D3DTextureTitle);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(Device,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TITLE_LOGO,		// �t�@�C���̖��O
								&D3DTextureTitleLogo);	// �ǂݍ��ރ������[
	
	D3DXCreateTextureFromFile(Device,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TITLE2,			// �t�@�C���̖��O
								&D3DTextureTitle2);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(Device,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PUSH_LOGO,		// �t�@�C���̖��O
								&D3DTexturepushLogo);	// �ǂݍ��ރ������[

	posTitle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posTitle2 = D3DXVECTOR3(0.0f, -600.0f, 0.0f);


	// ���_���̍쐬
	MakeVertexTitle();

	posTitle.x = 4.0f;

	SetVertexTitle();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	if(D3DTextureTitle != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureTitle->Release();
		D3DTextureTitle = NULL;
	}

	if(D3DTextureTitleLogo != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureTitleLogo->Release();
		D3DTextureTitleLogo = NULL;
	}

	if (D3DTextureTitle2 != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureTitle2->Release();
		D3DTextureTitle2 = NULL;
	}

	if (D3DTexturepushLogo != NULL)
	{// �e�N�X�`���̊J��
		D3DTexturepushLogo->Release();
		D3DTexturepushLogo = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	if(GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetStage(STAGE_TYUTO_GAME);
	}
	// �Q�[���p�b�h�ňړ�����
	else if (IsButtonRepeat(0, BUTTON_START))
	{
		SetStage(STAGE_TYUTO_GAME);
	}
	else if (IsButtonRepeat(0, BUTTON_B))
	{
		SetStage(STAGE_TYUTO_GAME);
	}

	// ���t���[�����s���鏈��

	// �X�N���[������
	posTitle.y += 3.0f;
	posTitle2.y += 3.0f;

	if (posTitle.y == 600)
	{
		posTitle = D3DXVECTOR3(0.0f, -600.0f, 0.0f);

	}

	if (posTitle2.y == 600)
	{
		posTitle2 = D3DXVECTOR3(0.0f, -600.0f, 0.0f);
	}

	SetVertexTitle();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0,D3DTextureTitle);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkTitle, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTextureTitle2);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkTitle2, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTextureTitleLogo);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkTitleLogo, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTexturepushLogo);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkpushLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTitle(void)
{
	// ���_���W�̐ݒ�
	vertexWkTitle[0].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	vertexWkTitle[1].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y, 0.0f);
	vertexWkTitle[2].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);
	vertexWkTitle[3].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkTitle[0].rhw =
	vertexWkTitle[1].rhw =
	vertexWkTitle[2].rhw =
	vertexWkTitle[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkTitle[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkTitle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkTitle[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_���W�̐ݒ�
	vertexWkTitle2[0].vtx = D3DXVECTOR3(TITLE2_POS_X, TITLE2_POS_Y, 0.0f);
	vertexWkTitle2[1].vtx = D3DXVECTOR3(TITLE2_POS_X + TITLE2_SIZE_X, TITLE2_POS_Y, 0.0f);
	vertexWkTitle2[2].vtx = D3DXVECTOR3(TITLE2_POS_X, TITLE2_POS_Y + TITLE2_SIZE_Y, 0.0f);
	vertexWkTitle2[3].vtx = D3DXVECTOR3(TITLE2_POS_X + TITLE2_SIZE_X, TITLE2_POS_Y + TITLE2_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkTitle2[0].rhw =
	vertexWkTitle2[1].rhw =
	vertexWkTitle2[2].rhw =
	vertexWkTitle2[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkTitle2[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle2[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle2[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle2[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkTitle2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkTitle2[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkTitle2[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkTitle2[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_���W�̐ݒ�
	vertexWkTitleLogo[0].vtx = D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y, 0.0f);
	vertexWkTitleLogo[1].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y, 0.0f);
	vertexWkTitleLogo[2].vtx = D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);
	vertexWkTitleLogo[3].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkTitleLogo[0].rhw =
	vertexWkTitleLogo[1].rhw =
	vertexWkTitleLogo[2].rhw =
	vertexWkTitleLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkTitleLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitleLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitleLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitleLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkTitleLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkTitleLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkTitleLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkTitleLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_���W�̐ݒ�
	vertexWkpushLogo[0].vtx = D3DXVECTOR3(PUSHLOGO_POS_X, PUSHLOGO_POS_Y, 0.0f);
	vertexWkpushLogo[1].vtx = D3DXVECTOR3(PUSHLOGO_POS_X + PUSHLOGO_SIZE_X, PUSHLOGO_POS_Y, 0.0f);
	vertexWkpushLogo[2].vtx = D3DXVECTOR3(PUSHLOGO_POS_X, PUSHLOGO_POS_Y + PUSHLOGO_SIZE_Y, 0.0f);
	vertexWkpushLogo[3].vtx = D3DXVECTOR3(PUSHLOGO_POS_X + PUSHLOGO_SIZE_X, PUSHLOGO_POS_Y + PUSHLOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkpushLogo[0].rhw =
	vertexWkpushLogo[1].rhw =
	vertexWkpushLogo[2].rhw =
	vertexWkpushLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkpushLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkpushLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkpushLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkpushLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkpushLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkpushLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkpushLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkpushLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexTitle(void)
{
	// ���_���W�̐ݒ�
	vertexWkTitle[0].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f) + posTitle;
	vertexWkTitle[1].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y, 0.0f) + posTitle;
	vertexWkTitle[2].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f) + posTitle;
	vertexWkTitle[3].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f) + posTitle;



	// ���_���W�̐ݒ�
	vertexWkTitle2[0].vtx = D3DXVECTOR3(TITLE2_POS_X, TITLE2_POS_Y, 0.0f) + posTitle2;
	vertexWkTitle2[1].vtx = D3DXVECTOR3(TITLE2_POS_X + TITLE2_SIZE_X, TITLE2_POS_Y, 0.0f) + posTitle2;
	vertexWkTitle2[2].vtx = D3DXVECTOR3(TITLE2_POS_X, TITLE2_POS_Y + TITLE2_SIZE_Y, 0.0f) + posTitle2;
	vertexWkTitle2[3].vtx = D3DXVECTOR3(TITLE2_POS_X + TITLE2_SIZE_X, TITLE2_POS_Y + TITLE2_SIZE_Y, 0.0f) + posTitle2;
}