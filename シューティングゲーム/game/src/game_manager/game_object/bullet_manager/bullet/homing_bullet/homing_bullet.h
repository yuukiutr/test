
#pragma once

#include "vivid.h"
#include "../bullet.h"

class CHomingBullet : public IBullet
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CHomingBullet();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CHomingBullet();

	/*!
	 *  @brief      ������
	 *
	 *  @param[in]  category  ���j�b�g���ʎq
	 *  @param[in]  position    �ʒu
	 *  @param[in]  direction   ����
	 *  @param[in]  speed       ����
	 */
	void Initialize(UNIT_CATEGORY category, const vivid::Vector2& position, float direction, float speed)override;

	/*!
	 *	@brief	�X�V
	 */
	void Update()override;

	/*!
	 *	@brief	�`��
	 */
	void Draw()override;

private:

	static const int	m_width;			//!< ��
	static const int	m_height;			//!< ����
	static const float	m_radius;			//!< ���a
	static const float	m_accelerator;		//!< ����
	static const float	m_max_speed;		//!< �ō����x
	static const float	m_homing_angle;		//!< �z�[�~���O�p�x
	static const int	m_max_homing_time;	//!< �z�[�~���O����ő厞��
	static const int	m_effect_interval;	//!< �G�t�F�N�g�����Ԋu

	float				m_Speed;			//!< ����
	float				m_Angle;			//!< ����
	int					m_HomingTime;		//!< �z�[�~���O���鎞��1
	int					m_EffectTimer;		//!< �G�t�F�N�g�^�C�}�[

};
