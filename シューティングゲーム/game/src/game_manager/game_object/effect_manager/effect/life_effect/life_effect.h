#pragma once

#include "../effect.h"

class CLifeEffect : public IEffect
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CLifeEffect();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CLifeEffect();

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

	static const int			m_width;
	static const int			m_height;
	static const int			m_one_rotation;
	static const int			m_max_rotation;
	static const int			m_min_rotation;
	static const float			m_speed;
	static const int			m_fade_speed;
	static const std::string	m_file_name;	//!< �t�@�C����

	vivid::Vector2				m_Velocity;
	float						m_RotationSpeed;

};