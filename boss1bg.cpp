//=============================================================================
//
// �w�i���� [boss1bg.cpp]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#include "main.h"
#include "boss1bg.h"
#include "input.h"
#include "player.h"
#include "portal.h"
#include "boss1.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBOSS1BG(int no);
void SetVertexBOSS1BG(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBOSS1BG = NULL;		// �e�N�X�`���ւ̃|�C���^

BOSS1BG					boss1bgWk[BOSS1BG_MAX];				// BG�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBOSS1BG(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1BG *boss1bg = &boss1bgWk[0];			// BG�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAME_BOSS1BG,							// �t�@�C���̖��O
			&g_pD3DTextureBOSS1BG);							// �ǂݍ��ރ������[
	}


	// BG�̏���������
	for (int i = 0; i < BOSS1BG_MAX; i++, boss1bg++)
	{
		boss1bg->use = true;										// �g�p
		boss1bg->pos = D3DXVECTOR3(0.0f + i*1920.0f,0.0f, 0.0f);	// ���W�f�[�^��������
		boss1bg->rot = D3DXVECTOR3(0.0f,0.0f, 0.0f);				// ��]�f�[�^��������
		boss1bg->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		boss1bg->CountAnim = 0;										// �A�j���J�E���g��������

		boss1bg->Texture = g_pD3DTextureBOSS1BG;					// �e�N�X�`�����
		MakeVertexBOSS1BG(i);										// ���_���̍쐬

	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBOSS1BG(void)
{
	if(g_pD3DTextureBOSS1BG != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBOSS1BG->Release();
		g_pD3DTextureBOSS1BG = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBOSS1BG(void)
{
	BOSS1BG *boss1bg = &boss1bgWk[0];			// BG�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);				// �Q�b�g�v���C���[���

	for (int i = 0; i < BOSS1BG_MAX; i++, boss1bg++)
	{
		if (boss1bg->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// ���t���[�����s���鏈��

			// �v���C���[�̐�������
			if (player->pos.y < 150.0f)
			{
				player->pos.y = 150.0f;
			}

		}
		
		SetVertexBOSS1BG(i);				// �ړ���̍��W�Œ��_��ݒ�
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBOSS1BG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1BG *boss1bg = boss1bgWk;				// BG�̃|�C���^�[��������
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSS1BG_MAX; i++, boss1bg++)
	{
		if (boss1bg->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureBOSS1BG);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, boss1bg->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBOSS1BG(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1BG *boss1bg = &boss1bgWk[no];			// BG�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexBOSS1BG(no);

	// ���_���W�̐ݒ�
	boss1bg->vertexWk[0].vtx = D3DXVECTOR3(BOSS1BG_POS_X, BOSS1BG_POS_Y, 0.0f);
	boss1bg->vertexWk[1].vtx = D3DXVECTOR3(BOSS1BG_POS_X + BOSS1BG_SIZE_X, BOSS1BG_POS_Y, 0.0f);
	boss1bg->vertexWk[2].vtx = D3DXVECTOR3(BOSS1BG_POS_X, BOSS1BG_POS_Y + BOSS1BG_SIZE_Y, 0.0f);
	boss1bg->vertexWk[3].vtx = D3DXVECTOR3(BOSS1BG_POS_X + BOSS1BG_SIZE_X, BOSS1BG_POS_Y + BOSS1BG_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	boss1bg->vertexWk[0].rhw =
	boss1bg->vertexWk[1].rhw =
	boss1bg->vertexWk[2].rhw =
	boss1bg->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	boss1bg->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1bg->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1bg->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1bg->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	boss1bg->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss1bg->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	boss1bg->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	boss1bg->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBOSS1BG(int no)
{
	BOSS1BG *boss1bg = &boss1bgWk[no];			// BG�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	boss1bg->vertexWk[0].vtx = D3DXVECTOR3(BOSS1BG_POS_X, BOSS1BG_POS_Y, 0.0f) + boss1bg->pos;
	boss1bg->vertexWk[1].vtx = D3DXVECTOR3(BOSS1BG_POS_X + BOSS1BG_SIZE_X, BOSS1BG_POS_Y, 0.0f) + boss1bg->pos;
	boss1bg->vertexWk[2].vtx = D3DXVECTOR3(BOSS1BG_POS_X, BOSS1BG_POS_Y + BOSS1BG_SIZE_Y, 0.0f) + boss1bg->pos;
	boss1bg->vertexWk[3].vtx = D3DXVECTOR3(BOSS1BG_POS_X + BOSS1BG_SIZE_X, BOSS1BG_POS_Y + BOSS1BG_SIZE_Y, 0.0f) + boss1bg->pos;

}

//=============================================================================
// BG�擾�֐�
//=============================================================================
BOSS1BG *GetBOSS1BG(int no)
{
	return(&boss1bgWk[no]);
}