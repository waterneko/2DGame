//=============================================================================
//
// MP���� [mp.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _MP_H_
#define _MP_H_


// �}�N����`
#define	NUM_MP				(2)			// �|���S����

#define TEXTURE_GAME_MP		_T("data/TEXTURE/mp.png")	// �摜
#define TEXTURE_MP_SIZE_X		(30)		// �e�N�X�`���T�C�Y
#define TEXTURE_MP_SIZE_Y		(30)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_MP	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_MP	(6)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_MP			(TEXTURE_PATTERN_DIVIDE_X_MP*TEXTURE_PATTERN_DIVIDE_Y_MP)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_MP			(10)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define MP_MAX						(99)	// MP�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// MP�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} MP;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMP(int type);
void UninitMP(void);
void UpdateMP(void);
void DrawMP(void);
MP *GetMP(int no);


#endif
