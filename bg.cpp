//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#include "main.h"
#include "bg.h"
#include "input.h"
#include "player.h"
#include "monster01.h"
#include "monster01bullet.h"
#include "monster02.h"
#include "enemy.h"
#include "attack.h"
#include "skill.h"
#include "portal.h"
#include "boss1.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBG(int no);
void SetVertexBG(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBG = NULL;		// �e�N�X�`���ւ̃|�C���^
//VERTEX_2D				g_vertexWkBG[NUM_VERTEX];	// ���_���i�[���[�N

BG						bgWk[BG_MAX];				// BG�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBG(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG *bg = &bgWk[0];			// BG�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAME_BG00,		// �t�@�C���̖��O
			&g_pD3DTextureBG);		// �ǂݍ��ރ������[
	}


	// BG�̏���������
	for (int i = 0; i < BG_MAX; i++, bg++)
	{
		bg->use = true;										// ���g�p�i���˂���Ă��Ȃ��e�j
		bg->pos = D3DXVECTOR3(0.0f + i*1920.0f,0.0f, 0.0f);	// ���W�f�[�^��������
		bg->rot = D3DXVECTOR3(0.0f,0.0f, 0.0f);				// ��]�f�[�^��������
		bg->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		bg->CountAnim = 0;									// �A�j���J�E���g��������

		bg->Texture = g_pD3DTextureBG;						// �e�N�X�`�����
		MakeVertexBG(i);									// ���_���̍쐬

	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBG(void)
{
	if(g_pD3DTextureBG != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBG->Release();
		g_pD3DTextureBG = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBG(void)
{
	BG *bg = &bgWk[0];					// BG�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);		// �Q�b�g�v���C���[���
	for (int i = 0; i < BG_MAX; i++, bg++)
	{
		if (bg->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// ���t���[�����s���鏈��

			// �v���C���[�̐�������
			if(player->pos.y < 300)
			{
				player->pos.y = 300.0f;
			}

			// �X�N���[������
			if (bgWk[0].pos.x > -(BG00_SIZE_X * BG_MAX - SCREEN_WIDTH))
			if (GetPlayer(0)->pos.x + GetPlayer(0)->speedX > SCREEN_CENTER_X)
			{
				GetPlayer(0)->pos.x = SCREEN_CENTER_X;
				if (GetKeyboardPress(DIK_D)|| IsButtonPressed(0, BUTTON_RIGHT))
				{
					if (bgWk[0].pos.x > -(BG00_SIZE_X * BG_MAX - SCREEN_WIDTH))
					{
						bg->pos.x -= GetPlayer(0)->speedX;
						MoveMonster01(0);
						MoveAttack(0);
						MoveSkill(0);
						MovePortal(0);
						MoveMonster01bullet(0);
						MoveMonster02(0);
						MoveEnemy(0);
						//MoveBoss1(0);
					}
					if (GetKeyboardPress(DIK_O))
					{
						//bg->pos.x += GetPlayer(0)->speedX;
					}
				}
			}


		}
		
		SetVertexBG(i);				// �ړ���̍��W�Œ��_��ݒ�
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG *bg = bgWk;				// BG�̃|�C���^�[��������
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BG_MAX; i++, bg++)
	{
		if (bg->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureBG);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, bg->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBG(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG *bg = &bgWk[no];			// BG�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexBG(no);

	// ���_���W�̐ݒ�
	bg->vertexWk[0].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y, 0.0f);
	bg->vertexWk[1].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f);
	bg->vertexWk[2].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f);
	bg->vertexWk[3].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	bg->vertexWk[0].rhw =
	bg->vertexWk[1].rhw =
	bg->vertexWk[2].rhw =
	bg->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bg->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bg->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bg->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bg->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bg->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bg->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bg->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bg->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBG(int no)
{
	BG *bg = &bgWk[no];			// BG�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	bg->vertexWk[0].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y, 0.0f) + bg->pos;
	bg->vertexWk[1].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f) + bg->pos;
	bg->vertexWk[2].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + bg->pos;
	bg->vertexWk[3].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + bg->pos;

}

//=============================================================================
// BG�擾�֐�
//=============================================================================
BG *GetBG(int no)
{
	return(&bgWk[no]);
}