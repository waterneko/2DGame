//=============================================================================
//
// portal���� [portal.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _PORTAL_H_
#define _PORTAL_H_


// �}�N����`
#define	NUM_PORTAL				(2)			// �|���S����

#define TEXTURE_GAME_PORTAL		_T("data/TEXTURE/shoukan_effect.png")	// �摜
#define TEXTURE_PORTAL_SIZE_X	(80)		// �e�N�X�`���T�C�Y
#define TEXTURE_PORTAL_SIZE_Y	(80)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_PORTAL	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_PORTAL	(7)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_PORTAL			(TEXTURE_PATTERN_DIVIDE_X_PORTAL*TEXTURE_PATTERN_DIVIDE_Y_PORTAL)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_PORTAL			(15)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define PORTAL_MAX						(1)			// �o���b�g�̍ő吔


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

} PORTAL;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPortal(int type);
void UninitPortal(void);
void UpdatePortal(void);
void DrawPortal(void);
PORTAL *GetPortal(int no);
void MovePortal(int no);

#endif
