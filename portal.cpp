//=============================================================================
//
// portal���� [portal.cpp]
// Author :GP11A243 29 �N�V�� 
//
//=============================================================================
#include "main.h"
#include "sound.h"
#include "input.h"
#include "player.h"
#include "portal.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPortal( int no );
void SetTexturePortal( int no, int cntPattern );
void SetVertexPortal( int no );
void MovePortal(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePortal = NULL;		// �e�N�X�`���ւ̃|���S��

PORTAL					portalWk[PORTAL_MAX];			// �o���b�g�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitPortal(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PORTAL *portal = &portalWk[0];		// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_PORTAL,				// �t�@�C���̖��O
			&g_pD3DTexturePortal);			// �ǂݍ��ރ������̃|�C���^
		
	}

	// �o���b�g�̏���������
	for (int i = 0; i < PORTAL_MAX; i++, portal++)
	{
		portal->use = true;											// �g�p
		portal->pos = D3DXVECTOR3(1850.0f + i*1800, 500.0f, 0.0f);	// ���W�f�[�^��������
		portal->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		portal->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		portal->CountAnim = 0;										// �A�j���J�E���g��������
		
		portal->Texture = g_pD3DTexturePortal;						// �e�N�X�`�����
		MakeVertexPortal(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPortal(void)
{
	if (g_pD3DTexturePortal != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexturePortal->Release();
		g_pD3DTexturePortal = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePortal(void)
{
	PORTAL *portal = portalWk;				// �o���b�g�̃|�C���^�[��������
	
	for (int i = 0; i < PORTAL_MAX; i++, portal++)
	{
		if (portal->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			portal->CountAnim++;
			if ((portal->CountAnim % TIME_ANIMATION_PORTAL) == 0)
			{
				// �p�^�[���̐؂�ւ�
				portal->PatternAnim = (portal->PatternAnim + 1) % ANIM_PATTERN_NUM_PORTAL;
				
				// �e�N�X�`�����W��ݒ�
				SetTexturePortal(i, portal->PatternAnim);
				

			}
			
			SetVertexPortal(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPortal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PORTAL *portal = portalWk;				// �o���b�g�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PORTAL_MAX; i++, portal++)
	{
		if (portal->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, portal->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PORTAL, portal->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPortal( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PORTAL *portal = &portalWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexPortal( no );

	// rhw�̐ݒ�
	portal->vertexWk[0].rhw =
	portal->vertexWk[1].rhw =
	portal->vertexWk[2].rhw =
	portal->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	portal->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	portal->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	portal->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	portal->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	portal->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	portal->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_PORTAL ,0.0f);
	portal->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PORTAL);
	portal->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_PORTAL, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PORTAL);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePortal( int no, int cntPattern )
{
	PORTAL *portal = &portalWk[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_PORTAL;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_PORTAL;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_PORTAL;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PORTAL;
	
	portal->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	portal->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	portal->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	portal->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPortal( int no )
{
	PORTAL *portal = &portalWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	portal->vertexWk[0].vtx.x = portal->pos.x - TEXTURE_PORTAL_SIZE_X;
	portal->vertexWk[0].vtx.y = portal->pos.y - TEXTURE_PORTAL_SIZE_Y;
	portal->vertexWk[0].vtx.z = 0.0f;

	portal->vertexWk[1].vtx.x = portal->pos.x + TEXTURE_PORTAL_SIZE_X;
	portal->vertexWk[1].vtx.y = portal->pos.y - TEXTURE_PORTAL_SIZE_Y;
	portal->vertexWk[1].vtx.z = 0.0f;

	portal->vertexWk[2].vtx.x = portal->pos.x - TEXTURE_PORTAL_SIZE_X;
	portal->vertexWk[2].vtx.y = portal->pos.y + TEXTURE_PORTAL_SIZE_Y;
	portal->vertexWk[2].vtx.z = 0.0f;

	portal->vertexWk[3].vtx.x = portal->pos.x + TEXTURE_PORTAL_SIZE_X;
	portal->vertexWk[3].vtx.y = portal->pos.y + TEXTURE_PORTAL_SIZE_Y;
	portal->vertexWk[3].vtx.z = 0.0f;
}



//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
PORTAL *GetPortal(int no)
{
	return(&portalWk[no]);
}
//=============================================================================
// �X�L���̈ړ��֐�
//=============================================================================
void MovePortal(int no)
{
	PLAYER *player = GetPlayer(0);
	PORTAL *portal = &portalWk[0];			// �o���b�g�̃|�C���^�[��������
	for (int i = 0; i < PORTAL_MAX;i++,portal++)
	{
		portal->pos.x -= player->speedX;
	}

}