
#pragma once

#include "../unit.h"

/*!
 *	@brief	UFO(��)�N���X
 */
class CUfoSmall : public IUnit
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CUfoSmall();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CUfoSmall();

	/*!
	 *	@brief	������
	 * 
	 *	@param[in]	position	�������W
	 */
	void Initialize(const vivid::Vector2& position)override;

	/*!
	 *	@brief	�`��
	 */
	void Draw()override;

private:

	/*!
	 *	@brief	�U��
	 */
	void Attack()override;

	static const int	m_width;			//!< ��
	static const int	m_height;			//!< ����
	static const float	m_radius;			//!< ���a
	static const int	m_max_life;			//!< �ő僉�C�t
	static const int	m_fire_interval;	//!< �U���Ԋu
	static const float	m_move_speed;		//!< �ړ����x
	int					m_FireTime;			//!< �U���^�C�}�[
};