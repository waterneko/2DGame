//=============================================================================
//
// �G���� [monster02.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _MONSTER02_H_
#define _MONSTER02_H_


// �}�N����`
#define	NUM_MONSTER02			(2)			// �|���S����

#define TEXTURE_GAME_MONSTER02		_T("data/TEXTURE/monster02.png")	// �摜
#define TEXTURE_GAME_MONSTER02DIE	_T("data/TEXTURE/monster02die.png")	// �摜
#define TEXTURE_MONSTER02_SIZE_X	(60)		// �e�N�X�`���T�C�Y
#define TEXTURE_MONSTER02_SIZE_Y	(70)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_MONSTER02	(4)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_MONSTER02	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_MONSTER02			(TEXTURE_PATTERN_DIVIDE_X_MONSTER02*TEXTURE_PATTERN_DIVIDE_Y_MONSTER02)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_MONSTER02			(15)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define MONSTER02_MAX						(1) // �G�̍ő吔
#define MONSTER02_SPEED						(1)	// �o���b�g�̃X�s�[�h
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

} MONSTER02;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMonster02(int type);
void UninitMonster02(void);
void UpdateMonster02(void);
void DrawMonster02(void);
MONSTER02 *GetMonster02(int no);
void MoveMonster02(int no);
void SetMonster02die(void);
#endif
