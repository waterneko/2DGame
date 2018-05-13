//=============================================================================
//
// �X�R�A���� [score.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

// �}�N����`
#define TEXTURE_GAME_SCORE00	_T("data/TEXTURE/number16x32.png")	// �T���v���p�摜
#define TEXTURE_SCORE00_SIZE_X	(16)	// �e�N�X�`���T�C�Y
#define TEXTURE_SCORE00_SIZE_Y	(32)	// ����
#define SCORE_POS_X			(760)		// �|���S���̏����ʒuX
#define SCORE_POS_Y			(20)		// ����
#define SCORE_MAX			(99999)		// �X�R�A�̍ő�l
#define SCORE_DIGIT			(5)			// ����


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore( int add );

#endif
