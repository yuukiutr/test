#pragma once

#include "vivid.h"
#include "../effect.h"

class CChargeEffect : public IEffect
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CChargeEffect();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CChargeEffect();

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

	static const int			m_width;		//!< ��
	static const int			m_height;		//!< ����
	static const int			m_fade_speed;	//!< �t�F�[�h���x
	static const float			m_scale_speed;	//!< �g�呬�x
	static const std::string	m_file_name;	//!< �t�@�C����
};