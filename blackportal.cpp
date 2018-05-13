//=============================================================================
//
// blackportal���� [blackportal.cpp]
// Author :GP11A243 29 �N�V�� 
//
//=============================================================================
#include "main.h"
#include "sound.h"
#include "input.h"
#include "player.h"
#include "blackportal.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBlackportal( int no );
void SetTextureBlackportal( int no, int cntPattern );
void SetVertexBlackportal( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBlackportal = NULL;		// �e�N�X�`���ւ̃|���S��

BLACKPORTAL				blackportalWk[BLACKPORTAL_MAX];			// �ÈŃ|�[�^���\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitBlackportal(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BLACKPORTAL *blackportal = &blackportalWk[0];		// �|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BLACKPORTAL,				// �t�@�C���̖��O
			&g_pD3DTextureBlackportal);				// �ǂݍ��ރ������̃|�C���^
		
	}

	// �o���b�g�̏���������
	for (int i = 0; i < BLACKPORTAL_MAX; i++, blackportal++)
	{
		blackportal->use = false;										// ���g�p
		blackportal->pos = D3DXVECTOR3(400.0f, 450.0f, 0.0f);			// ���W�f�[�^��������
		blackportal->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		blackportal->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		blackportal->CountAnim = 0;										// �A�j���J�E���g��������
		
		blackportal->Texture = g_pD3DTextureBlackportal;				// �e�N�X�`�����
		MakeVertexBlackportal(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBlackportal(void)
{
	if (g_pD3DTextureBlackportal != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBlackportal->Release();
		g_pD3DTextureBlackportal = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBlackportal(void)
{
	BLACKPORTAL *blackportal = blackportalWk;				// �o���b�g�̃|�C���^�[��������
	
	for (int i = 0; i < BLACKPORTAL_MAX; i++, blackportal++)
	{
		if (blackportal->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			blackportal->CountAnim++;
			if ((blackportal->CountAnim % TIME_ANIMATION_BLACKPORTAL) == 0)
			{
				// �p�^�[���̐؂�ւ�
				blackportal->PatternAnim = (blackportal->PatternAnim + 1) % ANIM_PATTERN_NUM_BLACKPORTAL;
				
				// �e�N�X�`�����W��ݒ�
				SetTextureBlackportal(i, blackportal->PatternAnim);
				

			}
			
			SetVertexBlackportal(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBlackportal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BLACKPORTAL *blackportal = blackportalWk;				// �|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BLACKPORTAL_MAX; i++, blackportal++)
	{
		if (blackportal->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, blackportal->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BLACKPORTAL, blackportal->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBlackportal( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BLACKPORTAL *blackportal = &blackportalWk[no];			// �|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexBlackportal( no );

	// rhw�̐ݒ�
	blackportal->vertexWk[0].rhw =
	blackportal->vertexWk[1].rhw =
	blackportal->vertexWk[2].rhw =
	blackportal->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	blackportal->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	blackportal->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	blackportal->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	blackportal->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	blackportal->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	blackportal->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL, 0.0f);
	blackportal->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BLACKPORTAL);
	blackportal->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BLACKPORTAL);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBlackportal( int no, int cntPattern )
{
	BLACKPORTAL *blackportal = &blackportalWk[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BLACKPORTAL;
	
	blackportal->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	blackportal->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	blackportal->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	blackportal->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBlackportal( int no )
{
	BLACKPORTAL *blackportal = &blackportalWk[no];			// �|�C���^�[��������

	// ���_���W�̐ݒ�
	blackportal->vertexWk[0].vtx.x = blackportal->pos.x - TEXTURE_BLACKPORTAL_SIZE_X;
	blackportal->vertexWk[0].vtx.y = blackportal->pos.y - TEXTURE_BLACKPORTAL_SIZE_Y;
	blackportal->vertexWk[0].vtx.z = 0.0f;

	blackportal->vertexWk[1].vtx.x = blackportal->pos.x + TEXTURE_BLACKPORTAL_SIZE_X;
	blackportal->vertexWk[1].vtx.y = blackportal->pos.y - TEXTURE_BLACKPORTAL_SIZE_Y;
	blackportal->vertexWk[1].vtx.z = 0.0f;

	blackportal->vertexWk[2].vtx.x = blackportal->pos.x - TEXTURE_BLACKPORTAL_SIZE_X;
	blackportal->vertexWk[2].vtx.y = blackportal->pos.y + TEXTURE_BLACKPORTAL_SIZE_Y;
	blackportal->vertexWk[2].vtx.z = 0.0f;

	blackportal->vertexWk[3].vtx.x = blackportal->pos.x + TEXTURE_BLACKPORTAL_SIZE_X;
	blackportal->vertexWk[3].vtx.y = blackportal->pos.y + TEXTURE_BLACKPORTAL_SIZE_Y;
	blackportal->vertexWk[3].vtx.z = 0.0f;
}



//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
BLACKPORTAL *GetBlackportal(int no)
{
	return(&blackportalWk[no]);
}
