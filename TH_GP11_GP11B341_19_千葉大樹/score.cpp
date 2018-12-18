//=============================================================================
//
// �X�R�A���� [score.cpp]
//  GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "score.h"
#include <stdio.h>
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureScore = NULL;			// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		D3DTextureScoreLogo = NULL;		// �e�N�X�`���ւ̃|���S��

VERTEX_2D				vertexWkScore[NUM_VERTEX];					// ���_���i�[���[�N
VERTEX_2D				vertexWkScoreLogo[SCORE_LOGO_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N

D3DXVECTOR3				posScore;						// �|���S���̈ړ���
int						Score;							// �X�R�A

//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	
	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAME_SCORE,					// �t�@�C���̖��O
			&D3DTextureScore);					// �ǂݍ��ރ������[


		
		D3DXCreateTextureFromFile(Device,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_SCORE_LOGO,			// �t�@�C���̖��O
			&D3DTextureScoreLogo);				// �ǂݍ��ރ������̃|�C���^
	}

	posScore = D3DXVECTOR3((float)SCORE_LOGO_POS_X, (float)SCORE_LOGO_POS_Y, 0.0f);
	Score = 0;

	// ���_���̍쐬
	MakeVertexScore();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	if( D3DTextureScore != NULL )
	{	// �e�N�X�`���̊J��
		D3DTextureScore->Release();
		D3DTextureScore = NULL;
	}

	if (D3DTextureScore != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureScoreLogo->Release();
		D3DTextureScoreLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetStage(STAGE_CUREA);
	}
	// ���t���[�����s����鏈�����L�q����
	
	SetTextureScore();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	int i;

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture( 0, D3DTextureScore );

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkScore, sizeof(VERTEX_2D));

	// �X�R�A
	for( i = 0; i < SCORE_LOGO_DIGIT; i++ )
	{
		int date = Score;
		int num = date % 10;
		// ���_�t�H�[�}�b�g�̐ݒ�
		Device->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		Device->SetTexture(0, D3DTextureScoreLogo);

		// �|���S���̕`��
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkScoreLogo[i], sizeof(VERTEX_2D));
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScore(void)
{
	int i;
	float habaX = 16.0f;	// �����̉���
	
							// ���_���W�̐ݒ�
	vertexWkScore[0].vtx = D3DXVECTOR3(SCORE_POS_X, SCORE_POS_Y, 0.0f);
	vertexWkScore[1].vtx = D3DXVECTOR3(SCORE_POS_X + SCORE_SIZE_X, SCORE_POS_Y, 0.0f);
	vertexWkScore[2].vtx = D3DXVECTOR3(SCORE_POS_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
	vertexWkScore[3].vtx = D3DXVECTOR3(SCORE_POS_X + SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkScore[0].rhw =
		vertexWkScore[1].rhw =
		vertexWkScore[2].rhw =
		vertexWkScore[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkScore[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkScore[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkScore[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkScore[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkScore[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkScore[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkScore[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkScore[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ��������������
	for( i = 0; i < SCORE_LOGO_DIGIT; i++ )
	{
		// ���_���W�̐ݒ�
		vertexWkScoreLogo[i][0].vtx.x = -habaX * i + posScore.x;
		vertexWkScoreLogo[i][0].vtx.y = posScore.y;
		vertexWkScoreLogo[i][0].vtx.z = 0.0f;
		vertexWkScoreLogo[i][1].vtx.x = -habaX * i + posScore.x + TEXTURE_SCORE_LOGO_SIZE_X;
		vertexWkScoreLogo[i][1].vtx.y = posScore.y;
		vertexWkScoreLogo[i][1].vtx.z = 0.0f;
		vertexWkScoreLogo[i][2].vtx.x = -habaX * i + posScore.x;
		vertexWkScoreLogo[i][2].vtx.y = posScore.y + TEXTURE_SCORE_LOGO_SIZE_Y;
		vertexWkScoreLogo[i][2].vtx.z = 0.0f;
		vertexWkScoreLogo[i][3].vtx.x = -habaX * i + posScore.x + TEXTURE_SCORE_LOGO_SIZE_X;
		vertexWkScoreLogo[i][3].vtx.y = posScore.y + TEXTURE_SCORE_LOGO_SIZE_Y;
		vertexWkScoreLogo[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		vertexWkScoreLogo[i][0].rhw =
		vertexWkScoreLogo[i][1].rhw =
		vertexWkScoreLogo[i][2].rhw =
		vertexWkScoreLogo[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		vertexWkScoreLogo[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexWkScoreLogo[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexWkScoreLogo[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexWkScoreLogo[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		vertexWkScoreLogo[i][0].tex = D3DXVECTOR2( 0.0f, 0.0f );
		vertexWkScoreLogo[i][1].tex = D3DXVECTOR2( 1.0f, 0.0f );
		vertexWkScoreLogo[i][2].tex = D3DXVECTOR2( 0.0f, 1.0f );
		vertexWkScoreLogo[i][3].tex = D3DXVECTOR2( 1.0f, 1.0f );
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureScore(void)
{
	int i;
	int number = Score;
	
	for( i = 0; i < SCORE_LOGO_DIGIT; i++ )
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		vertexWkScoreLogo[i][0].tex = D3DXVECTOR2( 0.1f * x, 0.0f );
		vertexWkScoreLogo[i][1].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 0.0f );
		vertexWkScoreLogo[i][2].tex = D3DXVECTOR2( 0.1f * x, 1.0f );
		vertexWkScoreLogo[i][3].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 1.0f );
		number /= 10;
	}

}
//=============================================================================
// HP�f�[�^���Z�b�g����
// ����:add :�ǉ�����_���B�}�C�i�X���\�A�������ȂǂɁB
//=============================================================================
void AddScore( int add )
{
	Score += add;

	if(Score > SCORE_LOGO_MAX )
	{
		Score = SCORE_LOGO_MAX;
	}
	else if( Score < 0 )
	{
		Score = 0;
	}

}
