#pragma once

#include "../effect.h"

class CHitEffect : public IEffect
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CHitEffect();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CHitEffect();

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
	static const int			m_fade_speed;
	static const float			m_move_speed;
	static const std::string	m_file_name;

	vivid::Vector2				m_Velocity;

};