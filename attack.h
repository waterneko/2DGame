//=============================================================================
//
// attack���� [attack.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _ATTACK_H_
#define _ATTACK_H_


// �}�N����`
#define	NUM_ATTACK				(2)			// �|���S����

#define TEXTURE_GAME_ATTACK		_T("data/TEXTURE/pipo-btleffect159.png")	// �摜
#define TEXTURE_ATTACK_SIZE_X		(50)		// �e�N�X�`���T�C�Y
#define TEXTURE_ATTACK_SIZE_Y		(50)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_ATTACK	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ATTACK	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ATTACK			(TEXTURE_PATTERN_DIVIDE_X_ATTACK*TEXTURE_PATTERN_DIVIDE_Y_ATTACK)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ATTACK			(8)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define ATTACK_MAX						(1)	// �A�^�b�N�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// ���C�t�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} ATTACK;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitAttack(int type);
void UninitAttack(void);
void UpdateAttack(void);
void DrawAttack(void);
ATTACK *GetAttack(int no);
void SetAttack(D3DXVECTOR3 pos);
void MoveAttack(int no);

#endif
