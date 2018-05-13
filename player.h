//=============================================================================
//
// �v���C���[���� [player.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"


// �}�N����`
#define	NUM_PLAYER		(2)					// �|���S����

#define TEXTURE_READY_PLAYER	_T("data/TEXTURE/chara02_01idle1.png")	// �摜
#define TEXTURE_STABBING_PLAYER	_T("data/TEXTURE/chara02_08swinging1.png")
#define TEXTURE_RUN_PLAYER		_T("data/TEXTURE/chara02_00run.png")
#define TEXTURE_CHARGE_PLAYER	_T("data/TEXTURE/chara02_10skill.png")

//#define TEXTURE_PLAYER_SIZE_X	(60) // �e�N�X�`���T�C�Y
//#define TEXTURE_PLAYER_SIZE_Y	(80) // ����

#define TEXTURE_PLAYER_SIZE_X	(60) // �e�N�X�`���T�C�Y
#define TEXTURE_PLAYER_SIZE_Y	(60) // ����

#define TEXTURE_PATTERN_DIVIDE_X	(4)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION				(8)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define PLAYER_MAX					(1) // �v���C���[�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �v���C���[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				hp;							// �v���C���[��hp
	int				mp;							// �v���C���[��mp
	float			speedX;						// �v���C���[�̃X�s�[�h
	float			speedY;						// �v���C���[�̃X�s�[�h
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �v���C���[�̔��a
	float			BaseAngle;					// �v���C���[�̊p�x

} PLAYER;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(int no);


#endif
