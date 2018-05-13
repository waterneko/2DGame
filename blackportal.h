//=============================================================================
//
// blackportal���� [blackportal.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _BLACKPORTAL_H_
#define _BLACKPORTAL_H_


// �}�N����`
#define	NUM_BLACKPORTAL				(2)			// �|���S����

#define TEXTURE_GAME_BLACKPORTAL	_T("data/TEXTURE/pipo-mapeffect015_480.png")	// �摜
#define TEXTURE_BLACKPORTAL_SIZE_X	(80)									// �e�N�X�`���T�C�Y
#define TEXTURE_BLACKPORTAL_SIZE_Y	(80)									// ����

#define TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BLACKPORTAL	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BLACKPORTAL			(TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL*TEXTURE_PATTERN_DIVIDE_Y_BLACKPORTAL)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BLACKPORTAL				(15)// �A�j���[�V�����̐؂�ւ��J�E���g

#define BLACKPORTAL_MAX							(1)			// �o���b�g�̍ő吔


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

} BLACKPORTAL;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBlackportal(int type);
void UninitBlackportal(void);
void UpdateBlackportal(void);
void DrawBlackportal(void);
BLACKPORTAL *GetBlackportal(int no);

#endif
