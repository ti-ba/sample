//=============================================================================
//
// ���U���g��ʏ��� [curea.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "curea.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexcurea(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTexturecurea = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		D3DTexturecureaLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				vertexWkcurea[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				vertexWkcureaLogo[NUM_VERTEX];		// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCurea(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_CUREA,			// �t�@�C���̖��O
								&D3DTexturecurea);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(Device,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_CUREA_LOGO,		// �t�@�C���̖��O
								&D3DTexturecureaLogo);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexcurea();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCurea(void)
{
	if(D3DTexturecurea != NULL)
	{// �e�N�X�`���̊J��
		D3DTexturecurea->Release();
		D3DTexturecurea = NULL;
	}

	if(D3DTexturecureaLogo != NULL)
	{// �e�N�X�`���̊J��
		D3DTexturecureaLogo->Release();
		D3DTexturecureaLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCurea(void)
{
	int stage = 5;
	if(GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetStage( STAGE_TITLE );
	}
	else if (IsButtonRepeat(0, BUTTON_B))
	{
		SetStage(STAGE_TITLE);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCurea(void)
{

	LPDIRECT3DDEVICE9 Device = GetDevice();
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTexturecurea);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkcurea, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTexturecureaLogo);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkcureaLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexcurea(void)
{	
	// ���_���W�̐ݒ�
	vertexWkcurea[0].vtx = D3DXVECTOR3(CUREA_POS_X, CUREA_POS_Y, 0.0f);
	vertexWkcurea[1].vtx = D3DXVECTOR3(CUREA_POS_X + CUREA_SIZE_X, CUREA_POS_Y, 0.0f);
	vertexWkcurea[2].vtx = D3DXVECTOR3(CUREA_POS_X, CUREA_POS_Y + CUREA_SIZE_Y, 0.0f);
	vertexWkcurea[3].vtx = D3DXVECTOR3(CUREA_POS_X + CUREA_SIZE_X, CUREA_POS_Y + CUREA_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkcurea[0].rhw =
	vertexWkcurea[1].rhw =
	vertexWkcurea[2].rhw =
	vertexWkcurea[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkcurea[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkcurea[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkcurea[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkcurea[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkcurea[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkcurea[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkcurea[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkcurea[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	vertexWkcureaLogo[0].vtx = D3DXVECTOR3(CUREALOGO_POS_X, CUREALOGO_POS_Y, 0.0f);
	vertexWkcureaLogo[1].vtx = D3DXVECTOR3(CUREALOGO_POS_X + CUREALOGO_SIZE_X, CUREALOGO_POS_Y, 0.0f);
	vertexWkcureaLogo[2].vtx = D3DXVECTOR3(CUREALOGO_POS_X, CUREALOGO_POS_Y + CUREALOGO_SIZE_Y, 0.0f);
	vertexWkcureaLogo[3].vtx = D3DXVECTOR3(CUREALOGO_POS_X + CUREALOGO_SIZE_X, CUREALOGO_POS_Y + CUREALOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkcureaLogo[0].rhw =
	vertexWkcureaLogo[1].rhw =
	vertexWkcureaLogo[2].rhw =
	vertexWkcureaLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkcureaLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkcureaLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkcureaLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkcureaLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkcureaLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkcureaLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkcureaLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkcureaLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

