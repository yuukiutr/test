
#pragma once

#include "vivid.h"

/*!
 *	@brief	�t�@�C�^�[���C�t�Q�[�W�N���X
 */
class CFighterLifeGauge
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CFighterLifeGauge();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CFighterLifeGauge();

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

	static const int			m_width;		//!< ��
	static const int			m_height;		//!< ����
	static const vivid::Vector2	m_position;		//!< �ʒu
	static const vivid::Rect	m_frame_rect;	//!< �g�̓ǂݍ��ݔ͈�
	static const vivid::Rect	m_bar_rect;		//!< �o�[�̓ǂݍ��ݔ͈�
	static const int			m_bar_speed;	//!< �o�[�̈ړ����x
	
	vivid::Rect					m_Rect;			//!< �o�[�̓ǂݍ��ݔ͈�
};