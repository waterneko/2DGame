//=============================================================================
//
// �G���� [monster01.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _MONSTER01_H_
#define _MONSTER01_H_


// �}�N����`
#define	NUM_MONSTER01			(2)			// �|���S����

#define TEXTURE_GAME_MONSTER01		_T("data/TEXTURE/monster01.png")	// �摜
#define TEXTURE_GAME_MONSTER01DIE	_T("data/TEXTURE/monster01die.png")	// �摜
#define TEXTURE_MONSTER01_SIZE_X	(50)		// �e�N�X�`���T�C�Y
#define TEXTURE_MONSTER01_SIZE_Y	(50)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_MONSTER01	(4)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_MONSTER01	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_MONSTER01			(TEXTURE_PATTERN_DIVIDE_X_MONSTER01*TEXTURE_PATTERN_DIVIDE_Y_MONSTER01)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_MONSTER01			(15)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define MONSTER01_MAX						(4) // �G�̍ő吔

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				hp;							// �G�l�~�[��HP
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} MONSTER01;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMonster01(int type);
void UninitMonster01(void);
void UpdateMonster01(void);
void DrawMonster01(void);
MONSTER01 *GetMonster01(int no);
void MoveMonster01(int no);
void SetMonster01die(void);
#endif
