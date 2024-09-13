#pragma once

/*
 *	@file	setting.h
 *	@brief	�ݒ�
 *	@author	RyuheiKoizumi
 *	@date	2024/9/13
 */

#include "vivid.h"

class CSetting
{
public:

	/*!
	 *	@brief	�C���X�^���X�̎擾
	 */
	static CSetting& GetInstance(void);

	/*!
	 *	@brief	������
	 */
	void Initialize(void);

	/*!
	 *	@brief	�`��
	 */
	void Draw(void);

	/*!
	 *	@brief	�ϐ��̐ݒ�
	 */
	void Setting(void);

private:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CSetting();

	/*!
	 *	@brief	�R�s�[�R���X�g���N�^
	 */
	CSetting(const CSetting& rhs);

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CSetting();

	/*!
	 *	@brief	�Q�Ɖ��Z�q
	 */
	CSetting& operator=(const CSetting& rhs);

	/*!
	 *	@brief	�|�C���g�Ƃ̓����蔻��
	 */
	void CheckPointCollision(vivid::Vector2 pos);

	static const int			m_var_width;
	static const int			m_var_height;
	static const int			m_point_width;
	static const int			m_point_height;
	static const vivid::Vector2 m_accelerator_var_position;
	static const vivid::Vector2 m_max_accelerator_var_position;
	static const vivid::Vector2 m_point_anchor;
	static const float			m_point_radius;

	vivid::Vector2				m_AcceleratorPointPosition;
	vivid::Vector2				m_MaxAcceleratorPointPosition;
	bool						m_SelectAcceleratorPoint;
	bool						m_SelectMaxAcceleratorPoint;

};