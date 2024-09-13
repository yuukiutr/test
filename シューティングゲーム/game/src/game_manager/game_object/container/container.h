#pragma once

/*
 *	@file	container.h
 *	@brief	�ϐ��u����
 *	@author	RyuheiKoizumi
 *	@date	2024/9/13
 */

#include "../unit_manager/unit/fighter/fighter.h"

class CContainer
{
private:

	struct DATA
	{
		CFighter::DATA m_fighter_data;
	};

public:

	DATA m_Data;

	/*!
	 *	@brief	�C���X�^���X�̎擾
	 */
	static CContainer& GetInstance(void);

	/*!
	 *	@brief	������
	 */
	void Initialize(void);

	/*!
	 *	@brief	�t�@�C�^�[�f�[�^�擾
	 */
	CFighter::DATA& GetFighterData(void) { return m_Data.m_fighter_data; }

};