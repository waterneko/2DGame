//=============================================================================
//
// MP���� [mp.cpp]
// Author :GP11A243 29 �N�V�� 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "mp.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexMP( int no );
void SetTextureMP( int no, int cntPattern );
void SetVertexMP( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMP = NULL;		// �e�N�X�`���ւ̃|���S��

MP						mpWk[MP_MAX];				// MP�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMP(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MP *mp = &mpWk[0];		// MP�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_MP,				// �t�@�C���̖��O
			&g_pD3DTextureMP);				// �ǂݍ��ރ������̃|�C���^
		
	}
	
	PLAYER *player = GetPlayer(0);		//�v���C���[�̏��Q�b�g

	// ���C�t�̏���������
	for (int i = 0; i < player->mp / 100; i++, mp++)
	{
		mp->use = true;											// �g�p
		mp->pos = D3DXVECTOR3(100.0f + i* 30.0f, 55.0f, 0.0f);	// ���W�f�[�^��������
		mp->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		mp->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		mp->CountAnim = 0;										// �A�j���J�E���g��������
		
		mp->Texture = g_pD3DTextureMP;							// �e�N�X�`�����
		MakeVertexMP(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMP(void)
{
	if (g_pD3DTextureMP != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureMP->Release();
		g_pD3DTextureMP = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMP(void)
{
	MP *mp = mpWk;						// MP�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);		// �v���C���[�̏��Q�b�g
	
	for (int i = 0; i < player->mp / 100; i++, mp++)
	{
		if (mp->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			mp->CountAnim++;
			if ((mp->CountAnim % TIME_ANIMATION_MP) == 0)
			{
				// �p�^�[���̐؂�ւ�
				mp->PatternAnim = (mp->PatternAnim + 1) % ANIM_PATTERN_NUM_MP;

				// �e�N�X�`�����W��ݒ�
				SetTextureMP(i, mp->PatternAnim);
				}

			}
			
			SetVertexMP(i);				// �ړ���̍��W�Œ��_��ݒ�
		}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMP(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MP *mp = mpWk;				// ���C�t�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);		//�v���C���[�̏��Q�b�g

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int i = 0; i < player->mp / 100; i++, mp++)
	{
		if (mp->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, mp->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MP, mp->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexMP( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MP *mp = &mpWk[no];			// ���C�t�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexMP( no );

	// rhw�̐ݒ�
	mp->vertexWk[0].rhw =
	mp->vertexWk[1].rhw =
	mp->vertexWk[2].rhw =
	mp->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	mp->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	mp->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	mp->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	mp->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	mp->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	mp->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_MP, 0.0f);
	mp->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MP);
	mp->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_MP, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MP);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureMP( int no, int cntPattern )
{
	MP *mp = &mpWk[no];			// ���C�t�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MP;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MP;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MP;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MP;
	
	mp->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	mp->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	mp->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	mp->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexMP( int no )
{
	MP *mp = &mpWk[no];			// ���C�t�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	mp->vertexWk[0].vtx.x = mp->pos.x - TEXTURE_MP_SIZE_X;
	mp->vertexWk[0].vtx.y = mp->pos.y - TEXTURE_MP_SIZE_Y;
	mp->vertexWk[0].vtx.z = 0.0f;

	mp->vertexWk[1].vtx.x = mp->pos.x + TEXTURE_MP_SIZE_X;
	mp->vertexWk[1].vtx.y = mp->pos.y - TEXTURE_MP_SIZE_Y;
	mp->vertexWk[1].vtx.z = 0.0f;

	mp->vertexWk[2].vtx.x = mp->pos.x - TEXTURE_MP_SIZE_X;
	mp->vertexWk[2].vtx.y = mp->pos.y + TEXTURE_MP_SIZE_Y;
	mp->vertexWk[2].vtx.z = 0.0f;

	mp->vertexWk[3].vtx.x = mp->pos.x + TEXTURE_MP_SIZE_X;
	mp->vertexWk[3].vtx.y = mp->pos.y + TEXTURE_MP_SIZE_Y;
	mp->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ���C�t�擾�֐�
//=============================================================================
MP *GetMP(int no)
{
	return(&mpWk[no]);
}

