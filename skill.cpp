//=============================================================================
//
// �X�L������ [skill.cpp]
// Author :GP11A243 29 �N�V�� 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "skill.h"
#include "sound.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexSkill( int no );
void SetTextureSkill( int no, int cntPattern );
void SetVertexSkill( int no );
void MoveSkill(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureSkill = NULL;		// �e�N�X�`���ւ̃|���S��

SKILL					skillWk[SKILL_MAX];			// �o���b�g�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitSkill(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SKILL *skill = &skillWk[0];		// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_SKILL,				// �t�@�C���̖��O
			&g_pD3DTextureSkill);			// �ǂݍ��ރ������̃|�C���^
		
	}

	// �o���b�g�̏���������
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		skill->use = false;										// ���g�p�i���˂���Ă��Ȃ��e�j
		skill->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		skill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		skill->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		skill->CountAnim = 0;									// �A�j���J�E���g��������
		
		skill->Texture = g_pD3DTextureSkill;					// �e�N�X�`�����
		MakeVertexSkill(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSkill(void)
{
	if (g_pD3DTextureSkill != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureSkill->Release();
		g_pD3DTextureSkill = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSkill(void)
{
	SKILL *skill = skillWk;				// �o���b�g�̃|�C���^�[��������
	
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			skill->CountAnim++;
			if ((skill->CountAnim % TIME_ANIMATION_SKILL) == 0)
			{
				// �p�^�[���̐؂�ւ�
				skill->PatternAnim = (skill->PatternAnim + 1) % ANIM_PATTERN_NUM_SKILL;
				
				// �������p�^�[���̐؂�ւ����I�������A�����܂�
				if (skill->PatternAnim >= 9)
				{
					skill->use = false;
					skill->pos.x = -100.0f;
				}
				// �e�N�X�`�����W��ݒ�
				SetTextureSkill(i, skill->PatternAnim);
				

			}
			
			SetVertexSkill(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SKILL *skill = skillWk;				// �o���b�g�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, skill->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_SKILL, skill->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexSkill( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SKILL *skill = &skillWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexSkill( no );

	// rhw�̐ݒ�
	skill->vertexWk[0].rhw =
	skill->vertexWk[1].rhw =
	skill->vertexWk[2].rhw =
	skill->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	skill->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	skill->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	skill->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	skill->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	skill->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	skill->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_SKILL, 0.0f);
	skill->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_SKILL);
	skill->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_SKILL, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_SKILL);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureSkill( int no, int cntPattern )
{
	SKILL *skill = &skillWk[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_SKILL;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_SKILL;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_SKILL;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_SKILL;
	
	skill->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	skill->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	skill->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	skill->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexSkill( int no )
{
	SKILL *skill = &skillWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	skill->vertexWk[0].vtx.x = skill->pos.x - TEXTURE_SKILL_SIZE_X;
	skill->vertexWk[0].vtx.y = skill->pos.y - TEXTURE_SKILL_SIZE_Y;
	skill->vertexWk[0].vtx.z = 0.0f;

	skill->vertexWk[1].vtx.x = skill->pos.x + TEXTURE_SKILL_SIZE_X;
	skill->vertexWk[1].vtx.y = skill->pos.y - TEXTURE_SKILL_SIZE_Y;
	skill->vertexWk[1].vtx.z = 0.0f;

	skill->vertexWk[2].vtx.x = skill->pos.x - TEXTURE_SKILL_SIZE_X;
	skill->vertexWk[2].vtx.y = skill->pos.y + TEXTURE_SKILL_SIZE_Y;
	skill->vertexWk[2].vtx.z = 0.0f;

	skill->vertexWk[3].vtx.x = skill->pos.x + TEXTURE_SKILL_SIZE_X;
	skill->vertexWk[3].vtx.y = skill->pos.y + TEXTURE_SKILL_SIZE_Y;
	skill->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �X�L���̔��ːݒ�
//=============================================================================
void SetSkill(D3DXVECTOR3 pos)
{
	SKILL *skill = &skillWk[0];			// �o���b�g�̃|�C���^�[��������

	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			skill->use = true;				// �g�p��Ԃ֕ύX����
			skill->pos = pos;				// ���W���Z�b�g			
			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
SKILL *GetSkill(int no)
{
	return(&skillWk[no]);
}
//=============================================================================
// �X�L���̈ړ��֐�
//=============================================================================
void MoveSkill(int no)
{
	PLAYER *player = GetPlayer(0);
	SKILL *skill = &skillWk[0];			// �o���b�g�̃|�C���^�[��������
	for (int i = 0; i < SKILL_MAX;i++,skill++)
	{
		skill->pos.x -= player->speedX;
	}

}