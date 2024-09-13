#pragma once

#include "../effect.h"

class CBossWhiteEffect : public IEffect
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CBossWhiteEffect();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CBossWhiteEffect();

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

	enum class FADE_STATE
	{
		FADE_IN,
		FADE_OUT,
	};

	static const int			m_width;
	static const int			m_height;
	static const int			m_max_alpha;
	static const int			m_min_alpha;
	static const int			m_flash_interval;
	static const int			m_dec_flash_interval;
	static const std::string	m_file_name;

	FADE_STATE					m_FadeState;
	int							m_FlashTimer;
	int							m_FlashCounter;

};