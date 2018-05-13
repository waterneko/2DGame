//=============================================================================
//
// �A�C�R������ [icon.cpp]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#include "main.h"
#include "icon.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexIcon(int no);
void SetVertexIcon(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureIcon = NULL;		// �e�N�X�`���ւ̃|�C���^

ICON					iconWk[ICON_MAX];				// �A�C�R���\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitIcon(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ICON *icon = &iconWk[0];			// �A�C�R���̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAME_ICON,		// �t�@�C���̖��O
			&g_pD3DTextureIcon);	// �ǂݍ��ރ������[
	}


	// �A�C�R���̏���������
	for (int i = 0; i < ICON_MAX; i++, icon++)
	{
		icon->use = true;										// �g�p
		icon->pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);	// ���W�f�[�^��������
		icon->rot = D3DXVECTOR3(0.0f,0.0f, 0.0f);				// ��]�f�[�^��������
		icon->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		icon->CountAnim = 0;									// �A�j���J�E���g��������

		icon->Texture = g_pD3DTextureIcon;						// �e�N�X�`�����
		MakeVertexIcon(i);										// ���_���̍쐬

	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitIcon(void)
{
	if(g_pD3DTextureIcon != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureIcon->Release();
		g_pD3DTextureIcon = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateIcon(void)
{
	ICON *icon = &iconWk[0];				// �A�C�R���̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);			// �Q�b�g�v���C���[���
	for (int i = 0; i < ICON_MAX; i++, icon++)
	{
		if (icon->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// ���t���[�����s���鏈��

			// �v���C���[�̐�������

				
		}
		
		SetVertexIcon(i);				// �ړ���̍��W�Œ��_��ݒ�
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawIcon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ICON *icon = iconWk;				// �A�C�R���̃|�C���^�[��������
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ICON_MAX; i++, icon++)
	{
		if (icon->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureIcon);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, icon->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexIcon(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ICON *icon = &iconWk[no];			// �A�C�R���̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexIcon(no);

	// ���_���W�̐ݒ�
	icon->vertexWk[0].vtx = D3DXVECTOR3(ICON_POS_X, ICON_POS_Y, 0.0f);
	icon->vertexWk[1].vtx = D3DXVECTOR3(ICON_POS_X + ICON_SIZE_X, ICON_POS_Y, 0.0f);
	icon->vertexWk[2].vtx = D3DXVECTOR3(ICON_POS_X, ICON_POS_Y + ICON_SIZE_Y, 0.0f);
	icon->vertexWk[3].vtx = D3DXVECTOR3(ICON_POS_X + ICON_SIZE_X, ICON_POS_Y + ICON_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	icon->vertexWk[0].rhw =
	icon->vertexWk[1].rhw =
	icon->vertexWk[2].rhw =
	icon->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	icon->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	icon->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	icon->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	icon->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	icon->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	icon->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	icon->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	icon->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexIcon(int no)
{
	ICON *icon = &iconWk[no];			// �A�C�R���̃|�C���^�[��������

	// ���_���W�̐ݒ�
	icon->vertexWk[0].vtx = D3DXVECTOR3(ICON_POS_X, ICON_POS_Y, 0.0f) + icon->pos;
	icon->vertexWk[1].vtx = D3DXVECTOR3(ICON_POS_X + ICON_SIZE_X, ICON_POS_Y, 0.0f) + icon->pos;
	icon->vertexWk[2].vtx = D3DXVECTOR3(ICON_POS_X, ICON_POS_Y + ICON_SIZE_Y, 0.0f) + icon->pos;
	icon->vertexWk[3].vtx = D3DXVECTOR3(ICON_POS_X + ICON_SIZE_X, ICON_POS_Y + ICON_SIZE_Y, 0.0f) + icon->pos;

}

