//=============================================================================
//
// �A�C�R������ [boss1icon.cpp]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#include "main.h"
#include "boss1icon.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBoss1icon(int no);
void SetVertexBoss1icon(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBoss1icon = NULL;	// �e�N�X�`���ւ̃|�C���^

BOSS1ICON				boss1iconWk[BOSS1ICON_MAX];		// �A�C�R���\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBoss1icon(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1ICON *boss1icon = &boss1iconWk[0];			// �A�C�R���̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAME_BOSS1ICON,		// �t�@�C���̖��O
			&g_pD3DTextureBoss1icon);	// �ǂݍ��ރ������[
	}


	// �A�C�R���̏���������
	for (int i = 0; i < BOSS1ICON_MAX; i++, boss1icon++)
	{
		boss1icon->use = false;										// ���g�p
		boss1icon->pos = D3DXVECTOR3(700.0f,0.0f, 0.0f);			// ���W�f�[�^��������
		boss1icon->rot = D3DXVECTOR3(0.0f,0.0f, 0.0f);				// ��]�f�[�^��������
		boss1icon->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		boss1icon->CountAnim = 0;									// �A�j���J�E���g��������

		boss1icon->Texture = g_pD3DTextureBoss1icon;				// �e�N�X�`�����
		MakeVertexBoss1icon(i);										// ���_���̍쐬

	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBoss1icon(void)
{
	if(g_pD3DTextureBoss1icon != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBoss1icon->Release();
		g_pD3DTextureBoss1icon = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss1icon(void)
{
	BOSS1ICON *boss1icon = &boss1iconWk[0];				// �A�C�R���̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);						// �Q�b�g�v���C���[���
	for (int i = 0; i < BOSS1ICON_MAX; i++, boss1icon++)
	{
		if (boss1icon->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// ���t���[�����s���鏈��

			// �v���C���[�̐�������

				
		}
		
		SetVertexBoss1icon(i);				// �ړ���̍��W�Œ��_��ݒ�
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss1icon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1ICON *boss1icon = boss1iconWk;				// �A�C�R���̃|�C���^�[��������
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSS1ICON_MAX; i++, boss1icon++)
	{
		if (boss1icon->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureBoss1icon);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, boss1icon->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBoss1icon(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1ICON *boss1icon = &boss1iconWk[no];			// �A�C�R���̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexBoss1icon(no);

	// ���_���W�̐ݒ�
	boss1icon->vertexWk[0].vtx = D3DXVECTOR3(BOSS1ICON_POS_X, BOSS1ICON_POS_Y, 0.0f);
	boss1icon->vertexWk[1].vtx = D3DXVECTOR3(BOSS1ICON_POS_X + BOSS1ICON_SIZE_X, BOSS1ICON_POS_Y, 0.0f);
	boss1icon->vertexWk[2].vtx = D3DXVECTOR3(BOSS1ICON_POS_X, BOSS1ICON_POS_Y + BOSS1ICON_SIZE_Y, 0.0f);
	boss1icon->vertexWk[3].vtx = D3DXVECTOR3(BOSS1ICON_POS_X + BOSS1ICON_SIZE_X, BOSS1ICON_POS_Y + BOSS1ICON_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	boss1icon->vertexWk[0].rhw =
	boss1icon->vertexWk[1].rhw =
	boss1icon->vertexWk[2].rhw =
	boss1icon->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	boss1icon->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1icon->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1icon->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1icon->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	boss1icon->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss1icon->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	boss1icon->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	boss1icon->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBoss1icon(int no)
{
	BOSS1ICON *boss1icon = &boss1iconWk[no];			// �A�C�R���̃|�C���^�[��������

	// ���_���W�̐ݒ�
	boss1icon->vertexWk[0].vtx = D3DXVECTOR3(BOSS1ICON_POS_X, BOSS1ICON_POS_Y, 0.0f) + boss1icon->pos;
	boss1icon->vertexWk[1].vtx = D3DXVECTOR3(BOSS1ICON_POS_X + BOSS1ICON_SIZE_X, BOSS1ICON_POS_Y, 0.0f) + boss1icon->pos;
	boss1icon->vertexWk[2].vtx = D3DXVECTOR3(BOSS1ICON_POS_X, BOSS1ICON_POS_Y + BOSS1ICON_SIZE_Y, 0.0f) + boss1icon->pos;
	boss1icon->vertexWk[3].vtx = D3DXVECTOR3(BOSS1ICON_POS_X + BOSS1ICON_SIZE_X, BOSS1ICON_POS_Y + BOSS1ICON_SIZE_Y, 0.0f) + boss1icon->pos;

}

//=============================================================================
// �擾�֐�
//=============================================================================
BOSS1ICON *GetBoss1icon(int no)
{
	return(&boss1iconWk[no]);
}
