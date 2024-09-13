
#pragma once

#include "vivid.h"
#include <list>
#include "unit/unit_id.h"
#include "unit/unit.h"
#include "../bullet_manager/bullet/bullet.h"

using namespace std;

/*!
 *	@brief	���j�b�g�Ǘ��N���X
 */
class CUnitManager
{
public:

	/*!
	 *	@brief	�C���X�^���X�̎擾
	 * 
	 *	@return	�C���X�^���X
	 */
	static CUnitManager& GetInstance();

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
	 *	@brief	���j�b�g����
	 * 
	 *	@param[in]	id	���j�b�gID
	 *	@param[in]	pos	�������W
	 */
	void Create(UNIT_ID id, const vivid::Vector2& pos);

	/*!
	 *	@brief	���j�b�g�ƒe�̓����蔻��
	 * 
	 *	@param[in]	bullet	�e�N���X�|�C���^
	 */
	void CheckHitBullet(IBullet* bullet);

	/*!
	 *	@brief	�e�Ɉ�ԋ߂����j�b�g��T��
	 * 
	 *	@param[in]	bullet	�e�N���X�|�C���^
	 * 
	 *	@return	�e�Ɉ�ԋ߂����j�b�g�̃A�h���X
	 */
	IUnit* FindNearUnit(IBullet* bullet);

	/*!
	 *	@brief	�퓬�@�擾
	 * 
	 *	@return	���j�b�g�̃A�h���X
	 */
	IUnit* GetFighter();

	/*!
	 *	@brief	�c���UFO�𒲂ׂ�
	 * 
	 *	@return	�c���Ă��Ȃ����false
	 */
	bool CheckRemainingUfo();

private:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CUnitManager();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CUnitManager();

	/*!
	 *	@brief	�R�s�[�R���X�g���N�^
	 */
	CUnitManager(const CUnitManager& rhs);

	/*!
	 *	@brief	������Z�q
	 */
	CUnitManager& operator=(const CUnitManager& rhs);

	/*!
	 *	@brief	UFO�̔z�u
	 */
	void DeployUfo();

	/*!
	 *	@brief	UFO�e�[�u���X�V
	 */
	void UpdateUfoTable();

	/*!
	 *	@brief	�S���j�b�g�̍X�V
	 */
	void UpdateUnit();

	/*!
	 *	@brief	UFO�e�[�u���p�\����ID
	 */
	enum class UFO_TABLE_DATA_PARAM
	{
		ID,
		X,
		Y,
		CREATE_TIME,
	};

	/*!
	 *	@brief	UFO�e�[�u���p�\����
	 */
	struct UFO_TABLE_DATA
	{
		UNIT_ID	id;
		int		x;
		int		y;
		int		create_frame;
	};

	// UFO�e�[�u�����X�g
	using UFO_TABLE = list<UFO_TABLE_DATA>;

	// ���j�b�g���X�g�^
	using UNIT_LIST = list<IUnit*>;

	static const float	m_dummy_length;			//!< �ŒZ�����v�Z�p�_�~�[�f�[�^

	UNIT_LIST			m_UnitList;				//!< ���j�b�g���X�g
	int					m_CreateTimer;			//!< ��������
	UFO_TABLE			m_UfoTable;				//!< UFO�e�[�u�����X�g

};