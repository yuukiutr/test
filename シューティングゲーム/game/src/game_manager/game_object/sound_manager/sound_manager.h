#pragma once

#include "vivid.h"

// �T�E���hID
enum class SOUND_ID
{
	BGM,
	SHOT,
	HOMING_SHOT,
	DESTORY,
	BOSS_DESTORY,
	FIGHTER_HIT,
	WARNING,
	WARNING_SHORT,
	GAMEOVER,
	GAMECLEAR,
	ZBUTTON,

	MAX,
};

/*!
 *	@brief	�T�E���h�}�l�[�W���[�N���X
 */
class CSoundManager
{
public:

	/*!
	 *	@brief	�C���X�^���X�̎擾
	 *
	 *	@return	�T�E���h�}�l�[�W���[�N���X�̃C���X�^���X
	 */
	static CSoundManager& GetInstance();

	/*!
	 *	@brief	�ǂݍ���
	 */
	void Load();

	/*!
	 *	@brief	�Đ�
	 */
	void Play(SOUND_ID id, bool loop);

private:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CSoundManager();

	/*!
	 *	@brief	�R�s�[�R���X�g���N�^
	 */
	CSoundManager(const CSoundManager& rhs);

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CSoundManager();

	/*!
	 *	@brief	�Q�Ɖ��Z�q
	 */
	CSoundManager& operator=(const CSoundManager& rhs);

	static const char* m_sound_file_names[(int)SOUND_ID::MAX];

};