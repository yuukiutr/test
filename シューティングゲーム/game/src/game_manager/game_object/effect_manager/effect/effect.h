#pragma once

#include "vivid.h"
#include "effect_id.h"
#include "../../../../utility/utility.h"

#define RAND_IN_360	rand() % 360

/*!
 *	@brief	�G�t�F�N�g���N���X
 */
class IEffect
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	IEffect();

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	IEffect(EFFECT_ID id, int width, int height);

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	virtual ~IEffect();

	/*!
	 *	@brief	������
	 */
	virtual void Initialize(const vivid::Vector2& position, unsigned int color, float rotation);

	/*!
	 *	@brief	�X�V
	 */
	virtual void Update();

	/*!
	 *	@brief	�`��
	 */
	virtual void Draw();

	/*!
	 *	@brief	���
	 */
	virtual void Finalize();

	/*!
	 *	@brief	�ʒu�̎擾
	 */
	vivid::Vector2 GetPosition();

	/*!
	 *	@brief	�ʒu�̐ݒ�
	 */
	void SetPosition(const vivid::Vector2& position);

	/*!
	 *	@brief	�A�N�e�B�u�t���O�̎擾
	 */
	bool GetActive();

	/*!
	 *	@brief	�A�N�e�B�u�t���O�̐ݒ�
	 */
	void SetActive(bool active);

	/*!
	 *	@brief	���ʔԍ��擾
	 */
	EFFECT_ID GetID() { return m_id; }

protected:

	/*!
	 *	@brief	�t�F�[�h�A�E�g
	 * 
	 *	@param[in]	speed	�t�F�[�h���x
	 */
	void FadeOut(const int& speed);

	const EFFECT_ID m_id;			//!< ���ʔԍ�

	int				m_Width;		//!< ��
	int				m_Height;		//!< ����
	vivid::Vector2	m_Position;		//!< �ʒu
	unsigned int	m_Color;		//!< �F
	vivid::Vector2	m_Anchor;		//!< ��_
	vivid::Rect		m_Rect;			//!< �ǂݍ��ݔ͈�
	vivid::Vector2	m_Scale;		//!< �g�嗦
	float			m_Rotation;		//!< ��]�l
	bool			m_ActiveFlag;	//!< �A�N�e�B�u�t���O
};