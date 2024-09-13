#pragma once

/*
 *	@file	fighter_option.h
 *	@brief	���^�퓬�@
 *	@author	RyuheiKoizumi
 *	@date	2024/9/10
 */

#include "vivid.h"
#include "../../unit.h"

class CFighterOption : public IUnit
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CFighterOption();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CFighterOption();

	/*!
	 *	@brief	������
	 */
	void	Initialize(const vivid::Vector2& pos)override;

	/*!
	 *	@brief	�X�V
	 */
	void	Update(void)override;

	/*!
	 *	@brief	�`��
	 */
	void	Draw(void)override;

	/*!
	 *	@brief	���
	 */
	void	Finalize(void)override;

	/*!
	 *	@brief	�ǔ��^�[�Q�b�g�̃Z�b�g
	 */
	void	SetFollowTarget(IUnit* target) { m_FollowTarget = target; }

	/*!
	 *	@brief	�ˌ�
	 */
	void	Fire();

private:

	/*!
	 *  @brief      �o��
	 */
	void	Appear(void)override;

	/*!
	 *  @brief      �U��
	 */
	void    Attack(void)override;

	/*!
	 *  @brief      ���S
	 */
	void    Dead(void)override;

	static const int	m_width;		//!< ��
	static const int	m_height;		//!< ����
	static const float	m_radius;		//!< ���a
	static const float	m_move_speed;	//!< �ړ����x
	static const float	m_follow_angle;	//!< �ǔ��p�x

	IUnit*				m_FollowTarget;	//!< �ǔ��^�[�Q�b�g
	float				m_Angle;		//!< �p�x

};