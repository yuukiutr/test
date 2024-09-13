
#pragma once

#include "vivid.h"
#include "../bullet.h"

class CBossHomingBullet : public IBullet
{
public:
	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CBossHomingBullet();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CBossHomingBullet();

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

	/*!
	 *	@brief	�ҋ@�O
	 */
	void BeforeStandby();

	/*!
	 *	@brief	���ˑҋ@
	 */
	void Standby();

	/*!	
	 *	@brief	����
	 */
	void Launch();

	enum class BULLET_STATE
	{
		BEFORE_STANDBY,
		STANDBY,
		LAUNCH,
	};

	static const int	m_width;				//!< ��
	static const int	m_height;				//!< ����
	static const float	m_radius;				//!< ���a
	static const float	m_initail_velocity;		//!< ����
	static const float	m_accelerator;			//!< ����
	static const float	m_max_speed;			//!< �ō����x
	static const int	m_time_to_standby;		//!< �ҋ@�܂ł̎���
	static const int	m_max_time_to_launch;	//!< ���˂܂ł̍ő厞��
	const int			m_time_to_launch;		//!< ���˂܂ł̎���
	float				m_Speed;				//!< ����
	float				m_Angle;				//!< ����
	int					m_TimerToStandby;		//!< �ҋ@�܂ł̃^�C�}�[
	int					m_TimerToLaunch;		//!< ���˂܂ł̃^�C�}�[
	BULLET_STATE		m_BulletState;			//!< �e���
};