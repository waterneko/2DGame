//=============================================================================
//
// �X�L������ [skill.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _SKILL_H_
#define _SKILL_H_


// �}�N����`
#define	NUM_SKILL				(2)			// �|���S����

#define TEXTURE_GAME_SKILL		_T("data/TEXTURE/pipo-btleffect161.png")	// �摜
#define TEXTURE_SKILL_SIZE_X	(100)		// �e�N�X�`���T�C�Y
#define TEXTURE_SKILL_SIZE_Y	(100)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_SKILL	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_SKILL	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_SKILL			(TEXTURE_PATTERN_DIVIDE_X_SKILL*TEXTURE_PATTERN_DIVIDE_Y_SKILL)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_SKILL			(6)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define SKILL_MAX						(1)			// �o���b�g�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �o���b�g�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} SKILL;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSkill(int type);
void UninitSkill(void);
void UpdateSkill(void);
void DrawSkill(void);
void SetSkill(D3DXVECTOR3 pos);
SKILL *GetSkill(int no);
void MoveSkill(int no);

#endif
