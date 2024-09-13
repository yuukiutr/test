#pragma once

#include <list>
#include "vivid.h"
#include "effect/effect_id.h"

class IEffect;

/*!
 *	@brief	�G�t�F�N�g�}�l�[�W���[�N���X
 */
class CEffectManager
{
public:

	/*!
	 *	@brief	�C���X�^���X�̎擾
	 */
	static CEffectManager& GetInstance();

	/*!
	 *	@brief	������
	 */
	void Initialize();

	/*!
	 *	@brief	�X�V
	 */
	void Update();

	/*!
	 *	@brief	�`��
	 */
	void Draw();

	/*!
	 *	@brief	���
	 */
	void Finalize();

	/*!
	 *	@brief	�G�t�F�N�g�̐���
	 */
	void Create(EFFECT_ID id, const vivid::Vector2& pos, unsigned int color, float rotation);

	/*!
	 *	@brief	�G�t�F�N�g�폜
	 */
	void Delete(EFFECT_ID id);

private:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CEffectManager() = default;

	/*!
	 *	@brief	�R�s�[�R���X�g���N�^
	 */
	CEffectManager(const CEffectManager& rhs) = delete;

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CEffectManager() = default;

	/*!
	 *	@brief	�Q�Ɖ��Z�q
	 */
	CEffectManager& operator=(const CEffectManager& rhs) = delete;

	// �G�t�F�N�g���X�g�^�̒�`
	using EFFECT_LIST = std::list<IEffect*>;
	EFFECT_LIST m_EffectList;	//!< �G�t�F�N�g���X�g
};