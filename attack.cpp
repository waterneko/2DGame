//=============================================================================
//
// Attack���� [Attack.cpp]
// Author :GP11A243 29 �N�V�� 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "attack.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexAttack( int no );
void SetTextureAttack( int no, int cntPattern );
void SetVertexAttack( int no );
void MoveAttack(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureAttack = NULL;		// �e�N�X�`���ւ̃|���S��

ATTACK					attackWk[ATTACK_MAX];			// �A�^�b�N�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitAttack(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ATTACK *attack = &attackWk[0];		// �A�^�b�N�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ATTACK,			// �t�@�C���̖��O
			&g_pD3DTextureAttack);			// �ǂݍ��ރ������̃|�C���^
		
	}

	// ���C�t�̏���������
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		attack->use = false;										// ���g�p
		attack->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);				// ���W�f�[�^��������
		attack->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		attack->PatternAnim = 0;									// �A�j���p�^�[���ԍ�������
		attack->CountAnim = 0;										// �A�j���J�E���g��������
		
		attack->Texture = g_pD3DTextureAttack;						// �e�N�X�`�����
		MakeVertexAttack(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitAttack(void)
{
	if (g_pD3DTextureAttack != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureAttack->Release();
		g_pD3DTextureAttack = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateAttack(void)
{
	ATTACK *attack = attackWk;				// �A�^�b�N�̃|�C���^�[��������
	
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			attack->CountAnim++;
			if ((attack->CountAnim % TIME_ANIMATION_ATTACK) == 0)
			{
				// �p�^�[���̐؂�ւ�
				attack->PatternAnim = (attack->PatternAnim + 1) % ANIM_PATTERN_NUM_ATTACK;

				// �������p�^�[���̐؂�ւ����I�������A�����܂�
				if (attack->PatternAnim >= 9)
				{
					attack->use = false;
					attack->pos.x = -100.0f;
				}

				// �e�N�X�`�����W��ݒ�
				SetTextureAttack(i, attack->PatternAnim);
				
			}

		}

		SetVertexAttack(i);				// �ړ���̍��W�Œ��_��ݒ�
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawAttack(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ATTACK *attack = attackWk;				// �A�^�b�N�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, attack->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ATTACK, attack->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexAttack( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ATTACK *attack = &attackWk[no];			// �A�^�b�N�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexAttack( no );

	// rhw�̐ݒ�
	attack->vertexWk[0].rhw =
	attack->vertexWk[1].rhw =
	attack->vertexWk[2].rhw =
	attack->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	attack->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	attack->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	attack->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	attack->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	attack->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	attack->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ATTACK, 0.0f);
	attack->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ATTACK);
	attack->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ATTACK, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ATTACK);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureAttack( int no, int cntPattern )
{
	ATTACK *attack = &attackWk[no];			// �A�^�b�N�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ATTACK;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ATTACK;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ATTACK;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ATTACK;
	
	attack->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	attack->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	attack->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	attack->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexAttack( int no )
{
	ATTACK *attack = &attackWk[no];			// �A�^�b�N�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	attack->vertexWk[0].vtx.x = attack->pos.x - TEXTURE_ATTACK_SIZE_X;
	attack->vertexWk[0].vtx.y = attack->pos.y - TEXTURE_ATTACK_SIZE_Y;
	attack->vertexWk[0].vtx.z = 0.0f;

	attack->vertexWk[1].vtx.x = attack->pos.x + TEXTURE_ATTACK_SIZE_X;
	attack->vertexWk[1].vtx.y = attack->pos.y - TEXTURE_ATTACK_SIZE_Y;
	attack->vertexWk[1].vtx.z = 0.0f;

	attack->vertexWk[2].vtx.x = attack->pos.x - TEXTURE_ATTACK_SIZE_X;
	attack->vertexWk[2].vtx.y = attack->pos.y + TEXTURE_ATTACK_SIZE_Y;
	attack->vertexWk[2].vtx.z = 0.0f;

	attack->vertexWk[3].vtx.x = attack->pos.x + TEXTURE_ATTACK_SIZE_X;
	attack->vertexWk[3].vtx.y = attack->pos.y + TEXTURE_ATTACK_SIZE_Y;
	attack->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �X�L���̔��ːݒ�
//=============================================================================
void SetAttack(D3DXVECTOR3 pos)
{
	ATTACK *attack = &attackWk[0];			// �A�^�b�N�̃|�C���^�[��������

	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			attack->use = true;				// �g�p��Ԃ֕ύX����
			attack->pos = pos;				// ���W���Z�b�g			
			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �A�^�b�N�擾�֐�
//=============================================================================
ATTACK *GetAttack(int no)
{
	return(&attackWk[no]);
}

//=============================================================================
// �A�^�b�N�ړ��֐�
//=============================================================================
void MoveAttack(int no)
{
	PLAYER *player = GetPlayer(0);
	ATTACK *attack = &attackWk[no];
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		attack->pos.x -= player->speedX;
	}
}