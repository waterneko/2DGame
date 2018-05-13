//=============================================================================
//
// life���� [life.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _MONSTER01LIFE_H_
#define _MONSTER01LIFE_H_


// �}�N����`
#define	NUM_MONSTER01LIFE				(2)			// �|���S����

#define TEXTURE_GAME_MONSTER01LIFE			_T("data/TEXTURE/life1.png")	// �摜
#define TEXTURE_MONSTER01LIFE_SIZE_X		(15)							// �e�N�X�`���T�C�Y
#define TEXTURE_MONSTER01LIFE_SIZE_Y		(15)							// ����

#define TEXTURE_PATTERN_DIVIDE_X_MONSTER01LIFE	(3)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_MONSTER01LIFE	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_MONSTER01LIFE			(TEXTURE_PATTERN_DIVIDE_X_MONSTER01LIFE*TEXTURE_PATTERN_DIVIDE_Y_MONSTER01LIFE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_MONSTER01LIFE			(10)// �A�j���[�V�����̐؂�ւ��J�E���g

#define MONSTER01LIFE_MAX						(8)	// ���C�t�̍ő吔


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

} MONSTER01LIFE;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitLife(int type);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
MONSTER01LIFE *GetLife(int no);


#endif
