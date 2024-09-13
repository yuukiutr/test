
#pragma once

#include "vivid.h"
#include "../bullet.h"

class CBossBullet : public IBullet
{
public:
	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CBossBullet();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CBossBullet();

	/*!
	 *	@brief	�`��
	 */
	void Draw()override;

private:
	static const int    m_width;    //!< ��
	static const int    m_height;   //!< ����
	static const float  m_radius;   //!< ���a

};