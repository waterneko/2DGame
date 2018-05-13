//=============================================================================
//
// �G���� [boss1.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _BOSS1_H_
#define _BOSS1_H_


// �}�N����`
#define	NUM_BOSS1			(2)			// �|���S����

#define TEXTURE_GAME_BOSS1		_T("data/TEXTURE/dragon.png")	// �摜
#define TEXTURE_BOSS1_SIZE_X	(400)		// �e�N�X�`���T�C�Y
#define TEXTURE_BOSS1_SIZE_Y	(300)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BOSS1	(4)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSS1	(1)		// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BOSS1			(TEXTURE_PATTERN_DIVIDE_X_BOSS1*TEXTURE_PATTERN_DIVIDE_Y_BOSS1)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BOSS1			(15)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BOSS1_MAX						(1) // �G�̍ő吔

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

} BOSS1;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBoss1(int type);
void UninitBoss1(void);
void UpdateBoss1(void);
void DrawBoss1(void);
BOSS1 *GetBoss1(int no);
void MoveBoss1(int no);

#endif
