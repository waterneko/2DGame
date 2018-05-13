//=============================================================================
//
// ���󏈗� [hoshizora.cpp]
// Author :GP11A243 29 �N�V�� 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "hoshizora.h"
#include "sound.h"
#include "input.h"
#include "player.h"
#include "boss1.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexHoshizora( int no );
void SetTextureHoshizora( int no, int cntPattern );
void SetVertexHoshizora( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureHoshizora = NULL;		// �e�N�X�`���ւ̃|���S��

HOSHIZORA				hoshizoraWk[HOSHIZORA_MAX];			// ����\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitHoshizora(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOSHIZORA *hoshizora = &hoshizoraWk[0];		// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_HOSHIZORA,				// �t�@�C���̖��O
			&g_pD3DTextureHoshizora);			// �ǂݍ��ރ������̃|�C���^
		
	}

	// �o���b�g�̏���������
	for (int i = 0; i < HOSHIZORA_MAX; i++, hoshizora++)
	{
		hoshizora->use = false;										// ���g�p
		hoshizora->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		hoshizora->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		hoshizora->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		hoshizora->CountAnim = 0;									// �A�j���J�E���g��������
		
		hoshizora->Texture = g_pD3DTextureHoshizora;				// �e�N�X�`�����
		MakeVertexHoshizora(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitHoshizora(void)
{
	if (g_pD3DTextureHoshizora != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureHoshizora->Release();
		g_pD3DTextureHoshizora = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateHoshizora(void)
{
	HOSHIZORA *hoshizora = hoshizoraWk;				// �o���b�g�̃|�C���^�[��������
	BOSS1 *boss1 = GetBoss1(0);						// �{�X�P�̏����Q�b�g
	
	for (int i = 0; i < HOSHIZORA_MAX; i++, hoshizora++)
	{
		if (hoshizora->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			hoshizora->CountAnim++;
			if ((hoshizora->CountAnim % TIME_ANIMATION_HOSHIZORA) == 0)
			{
				// �p�^�[���̐؂�ւ�
				hoshizora->PatternAnim = (hoshizora->PatternAnim + 1) % ANIM_PATTERN_NUM_HOSHIZORA;
				
				// �������p�^�[���̐؂�ւ����I�������A�����܂�
				if (hoshizora->PatternAnim >= 19)
				{
					hoshizora->use = false;
					hoshizora->pos.x = -100.0f;
					boss1->use = true;			// �{�X�P�̎g�p��Ԃ��g�p�ɕύX
				}
				// �e�N�X�`�����W��ݒ�
				SetTextureHoshizora(i, hoshizora->PatternAnim);
				

			}
			
			SetVertexHoshizora(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawHoshizora(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOSHIZORA *hoshizora = hoshizoraWk;				// �|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < HOSHIZORA_MAX; i++, hoshizora++)
	{
		if (hoshizora->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, hoshizora->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_HOSHIZORA, hoshizora->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexHoshizora( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOSHIZORA *hoshizora = &hoshizoraWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexHoshizora( no );

	// rhw�̐ݒ�
	hoshizora->vertexWk[0].rhw =
	hoshizora->vertexWk[1].rhw =
	hoshizora->vertexWk[2].rhw =
	hoshizora->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	hoshizora->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hoshizora->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hoshizora->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hoshizora->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	hoshizora->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	hoshizora->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA, 0.0f);
	hoshizora->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_HOSHIZORA);
	hoshizora->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_HOSHIZORA);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureHoshizora( int no, int cntPattern )
{
	HOSHIZORA *hoshizora = &hoshizoraWk[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_HOSHIZORA;
	
	hoshizora->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	hoshizora->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	hoshizora->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	hoshizora->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexHoshizora( int no )
{
	HOSHIZORA *hoshizora = &hoshizoraWk[no];			// �|�C���^�[��������

	// ���_���W�̐ݒ�
	hoshizora->vertexWk[0].vtx.x = hoshizora->pos.x - TEXTURE_HOSHIZORA_SIZE_X;
	hoshizora->vertexWk[0].vtx.y = hoshizora->pos.y - TEXTURE_HOSHIZORA_SIZE_Y;
	hoshizora->vertexWk[0].vtx.z = 0.0f;

	hoshizora->vertexWk[1].vtx.x = hoshizora->pos.x + TEXTURE_HOSHIZORA_SIZE_X;
	hoshizora->vertexWk[1].vtx.y = hoshizora->pos.y - TEXTURE_HOSHIZORA_SIZE_Y;
	hoshizora->vertexWk[1].vtx.z = 0.0f;

	hoshizora->vertexWk[2].vtx.x = hoshizora->pos.x - TEXTURE_HOSHIZORA_SIZE_X;
	hoshizora->vertexWk[2].vtx.y = hoshizora->pos.y + TEXTURE_HOSHIZORA_SIZE_Y;
	hoshizora->vertexWk[2].vtx.z = 0.0f;

	hoshizora->vertexWk[3].vtx.x = hoshizora->pos.x + TEXTURE_HOSHIZORA_SIZE_X;
	hoshizora->vertexWk[3].vtx.y = hoshizora->pos.y + TEXTURE_HOSHIZORA_SIZE_Y;
	hoshizora->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �X�L���̔��ːݒ�
//=============================================================================
void SetHoshizora(D3DXVECTOR3 pos)
{
	HOSHIZORA *hoshizora = &hoshizoraWk[0];			// �o���b�g�̃|�C���^�[��������

	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < HOSHIZORA_MAX; i++, hoshizora++)
	{
		if (hoshizora->use == false)			// ���g�p��Ԃ̐����������
		{
			hoshizora->use = true;				// �g�p��Ԃ֕ύX����
			hoshizora->pos = pos;				// ���W���Z�b�g			
			return;								// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
HOSHIZORA *GetHoshizora(int no)
{
	return(&hoshizoraWk[no]);
}
