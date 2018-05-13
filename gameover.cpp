//=============================================================================
//
// GAMEOVER��ʏ��� [gameover.cpp]
// Author : GP11A243 29 �N�V��
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
LPDIRECT3DTEXTURE9		g_pD3DTextureGameover = NULL;		// �e�N�X�`���ւ̃|�C���^
//LPDIRECT3DTEXTURE9		g_pD3DTextureResultLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkGameover[NUM_VERTEX];			// ���_���i�[���[�N
//VERTEX_2D				g_vertexWkResultLogo[NUM_VERTEX];		// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGameover(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_GAMEOVER,				// �t�@�C���̖��O
								&g_pD3DTextureGameover);		// �ǂݍ��ރ������[

	//D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
	//							TEXTURE_RESULT_LOGO,		// �t�@�C���̖��O
	//							&g_pD3DTextureResultLogo);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexGameover();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGameover(void)
{
	if(g_pD3DTextureGameover != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureGameover->Release();
		g_pD3DTextureGameover = NULL;
	}

	//if(g_pD3DTextureResultLogo != NULL)
	//{// �e�N�X�`���̊J��
	//	g_pD3DTextureResultLogo->Release();
	//	g_pD3DTextureResultLogo = NULL;
	//}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGameover(void)
{
	if(GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetStage( STAGE_TITLE );
	}
	else if (IsButtonTriggered(0, BUTTON_B))
	{
		SetStage(STAGE_TITLE);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGameover(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureGameover);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkGameover, sizeof(VERTEX_2D));

	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pD3DTextureResultLogo);

	//// �|���S���̕`��
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResultLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexGameover(void)
{	
	// ���_���W�̐ݒ�
	g_vertexWkGameover[0].vtx = D3DXVECTOR3(GAMEOVER_POS_X, GAMEOVER_POS_Y, 0.0f);
	g_vertexWkGameover[1].vtx = D3DXVECTOR3(GAMEOVER_POS_X + GAMEOVER_SIZE_X, GAMEOVER_POS_Y, 0.0f);
	g_vertexWkGameover[2].vtx = D3DXVECTOR3(GAMEOVER_POS_X, GAMEOVER_POS_Y + GAMEOVER_SIZE_Y, 0.0f);
	g_vertexWkGameover[3].vtx = D3DXVECTOR3(GAMEOVER_POS_X + GAMEOVER_SIZE_X, GAMEOVER_POS_Y + GAMEOVER_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkGameover[0].rhw =
	g_vertexWkGameover[1].rhw =
	g_vertexWkGameover[2].rhw =
	g_vertexWkGameover[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkGameover[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGameover[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGameover[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGameover[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkGameover[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkGameover[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkGameover[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkGameover[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//// ���_���W�̐ݒ�
	//g_vertexWkResultLogo[0].vtx = D3DXVECTOR3(RESULTLOGO_POS_X, RESULTLOGO_POS_Y, 0.0f);
	//g_vertexWkResultLogo[1].vtx = D3DXVECTOR3(RESULTLOGO_POS_X + RESULTLOGO_SIZE_X, RESULTLOGO_POS_Y, 0.0f);
	//g_vertexWkResultLogo[2].vtx = D3DXVECTOR3(RESULTLOGO_POS_X, RESULTLOGO_POS_Y + RESULTLOGO_SIZE_Y, 0.0f);
	//g_vertexWkResultLogo[3].vtx = D3DXVECTOR3(RESULTLOGO_POS_X + RESULTLOGO_SIZE_X, RESULTLOGO_POS_Y + RESULTLOGO_SIZE_Y, 0.0f);

	//// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	//g_vertexWkResultLogo[0].rhw =
	//g_vertexWkResultLogo[1].rhw =
	//g_vertexWkResultLogo[2].rhw =
	//g_vertexWkResultLogo[3].rhw = 1.0f;

	//// ���ˌ��̐ݒ�
	//g_vertexWkResultLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkResultLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkResultLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkResultLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//// �e�N�X�`�����W�̐ݒ�
	//g_vertexWkResultLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//g_vertexWkResultLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//g_vertexWkResultLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//g_vertexWkResultLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

