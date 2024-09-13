#pragma once

#include "vivid.h"
#include "../effect.h"

class CChargeParticle : public IEffect
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CChargeParticle();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CChargeParticle();

	/*!
	 *	@brief	������
	 */
	void Initialize(const vivid::Vector2& position, unsigned int color, float rotation)override;

	/*!
	 *	@brief	�X�V
	 */
	void Update()override;

	/*!
	 *	@brief	�`��
	 */
	void Draw()override;

private:

	static const int			m_width;			//!< ��
	static const int			m_height;			//!< ����
	static const int			m_fade_speed;		//!< �t�F�[�h���x
	static const float			m_move_speed;		//!< �ړ����x
	static const float			m_accelerator;		//!< �����x
	static const float			m_max_accelerator;	//!< �ő�����x
	static const float			m_max_create_length;//!< �Œ�����
	static const std::string	m_file_name;		//!< �t�@�C����

	vivid::Vector2				m_Velocity;			//!< ���x
	vivid::Vector2				m_Accelerator;		//!< �����x

};