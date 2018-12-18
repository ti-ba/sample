//=============================================================================
//
// �^�C�g����ʏ��� [gameover.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "gameover.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexGameover(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureGameover = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		D3DTextureGameoverLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				vertexWkGameover[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				vertexWkGameoverLogo[NUM_VERTEX];		// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGameover(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_GAMEOVER,				// �t�@�C���̖��O
		&D3DTextureGameover);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(Device,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_GAMEOVER_LOGO,			// �t�@�C���̖��O
		&D3DTextureGameoverLogo);	// �ǂݍ��ރ������[

									// ���_���̍쐬
	MakeVertexGameover();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGameover(void)
{
	if (D3DTextureGameover != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureGameover->Release();
		D3DTextureGameover = NULL;
	}

	if (D3DTextureGameoverLogo != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureGameoverLogo->Release();
		D3DTextureGameoverLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGameover(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetStage(STAGE_TITLE);
	}
	// �Q�[���p�b�h�ňړ�����
	else if (IsButtonRepeat(0, BUTTON_START))
	{
		SetStage(STAGE_TITLE);
	}
	else if (IsButtonRepeat(0, BUTTON_B))
	{
		SetStage(STAGE_TITLE);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGameover(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTextureGameover);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkGameover, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTextureGameoverLogo);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkGameoverLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexGameover(void)
{

	// ���_���W�̐ݒ�
	vertexWkGameover[0].vtx = D3DXVECTOR3(GAMEOVER_POS_X, GAMEOVER_POS_Y, 0.0f);
	vertexWkGameover[1].vtx = D3DXVECTOR3(GAMEOVER_POS_X + GAMEOVER_SIZE_X, GAMEOVER_POS_Y, 0.0f);
	vertexWkGameover[2].vtx = D3DXVECTOR3(GAMEOVER_POS_X, GAMEOVER_POS_Y + GAMEOVER_SIZE_Y, 0.0f);
	vertexWkGameover[3].vtx = D3DXVECTOR3(GAMEOVER_POS_X + GAMEOVER_SIZE_X, GAMEOVER_POS_Y + GAMEOVER_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkGameover[0].rhw =
		vertexWkGameover[1].rhw =
		vertexWkGameover[2].rhw =
		vertexWkGameover[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkGameover[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameover[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameover[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameover[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkGameover[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkGameover[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkGameover[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkGameover[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	vertexWkGameoverLogo[0].vtx = D3DXVECTOR3(GAMEOVERLOGO_POS_X, GAMEOVERLOGO_POS_Y, 0.0f);
	vertexWkGameoverLogo[1].vtx = D3DXVECTOR3(GAMEOVERLOGO_POS_X + GAMEOVERLOGO_SIZE_X, GAMEOVERLOGO_POS_Y, 0.0f);
	vertexWkGameoverLogo[2].vtx = D3DXVECTOR3(GAMEOVERLOGO_POS_X, GAMEOVERLOGO_POS_Y + GAMEOVERLOGO_SIZE_Y, 0.0f);
	vertexWkGameoverLogo[3].vtx = D3DXVECTOR3(GAMEOVERLOGO_POS_X + GAMEOVERLOGO_SIZE_X, GAMEOVERLOGO_POS_Y + GAMEOVERLOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		vertexWkGameoverLogo[0].rhw =
		vertexWkGameoverLogo[1].rhw =
		vertexWkGameoverLogo[2].rhw =
		vertexWkGameoverLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkGameoverLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameoverLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameoverLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameoverLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkGameoverLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkGameoverLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkGameoverLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkGameoverLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

