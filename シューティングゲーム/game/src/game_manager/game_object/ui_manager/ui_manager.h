
#pragma once

#include "vivid.h"
#include "fighter_life_gauge/fighter_life_gauge.h"

/*!
 *	@brief	UI�}�l�[�W���[�N���X
 */
class CUIManager
{
public:

	/*!
	 *	@brief	�C���X�^���X�̎擾
	 * 
	 *	@return	UI�}�l�[�W���[�N���X�C���X�^���X
	 */
	static CUIManager& GetInstance();

	/*!
	 *	@brief	������
	 */
	void Initialize();

	/*!
	 *	@brief	�X�V
	 */
	void Update();

	/*!
	 *	@brief	�`��
	 */
	void Draw();

	/*!
	 *	@brief	���
	 */
	void Finalize();

private:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CUIManager();

	/*!
	 *	@brief	�R�s�[�R���X�g���N�^
	 */
	CUIManager(const CUIManager& rhs);

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CUIManager();

	/*!
	 *	@brief	������Z�q
	 */
	CUIManager& operator=(const CUIManager& rhs);

	CFighterLifeGauge m_FighterLifeGauge;	//!< �퓬�@�̃��C�t�Q�[�W�I�u�W�F�N�g
};