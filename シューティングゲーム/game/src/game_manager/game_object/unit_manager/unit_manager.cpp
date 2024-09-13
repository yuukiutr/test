#include "unit_manager.h"
#include <string>
#include "../scene_manager//scene_manager.h"
#include "../scene_manager/scene/game_main/game_main.h"
#include "../bullet_manager/bullet_manager.h"
#include "../../../utility/utility.h"
#include "unit/fighter/fighter.h"
#include "unit/ufo_small/ufo_small.h"
#include "unit/ufo_middle/ufo_middle.h"
#include "unit/ufo_large/ufo_large.h"
#include "unit//ufo_boss/ufo_boss.h"

const float CUnitManager::m_dummy_length = 99999999.0f;

/*!
 *  �C���X�^���X�̎擾
 */
CUnitManager& 
CUnitManager::GetInstance()
{
    static CUnitManager instance;
    return instance;
}

/*!
 *  ������
 */
void 
CUnitManager::
Initialize()
{
    m_UfoTable.clear();
    m_UnitList.clear();
    m_CreateTimer = 0;
    DeployUfo();
}

/*!
 *  �X�V
 */
void 
CUnitManager::
Update()
{
    UpdateUfoTable();

    UpdateUnit();
}

/*!
 *  �`��
 */
void 
CUnitManager::
Draw()
{
    if (m_UnitList.empty())return;
    UNIT_LIST::iterator it = m_UnitList.begin();
    while (it != m_UnitList.end())
    {
        (*it)->Draw();

        ++it;
    }
}

/*!
 *  ���
 */
void 
CUnitManager::
Finalize()
{
    if (m_UnitList.empty())return;
    UNIT_LIST::iterator it = m_UnitList.begin();
    while (it != m_UnitList.end())
    {
        (*it)->Finalize();
        delete(*it);
        ++it;
    }
}

/*!
 *  ���j�b�g����
 */
void 
CUnitManager::
Create(UNIT_ID id, const vivid::Vector2& pos)
{
    IUnit* unit = nullptr;

    switch (id)
    {
    case UNIT_ID::FIGHTER:    unit = new CFighter();     break;
    case UNIT_ID::UFO_SMALL:  unit = new CUfoSmall();    break;
    case UNIT_ID::UFO_MIDDLE: unit = new CUfoMiddle();   break;
    case UNIT_ID::UFO_LARGE:  unit = new CUfoLarge();    break;
    case UNIT_ID::UFO_BOSS:   unit = new CUfoBoss();     break;
    }

    if (!unit)return;
    unit->Initialize(pos);
    m_UnitList.push_back(unit);
}

/*!
 *  ���j�b�g�ƒe�̓����蔻��
 */
void 
CUnitManager::
CheckHitBullet(IBullet* bullet)
{
    if (m_UnitList.empty())return;
    UNIT_LIST::iterator it = m_UnitList.begin();
    while (it != m_UnitList.end())
    {
        if ((*it)->CheckHitBullet(bullet))
            return;

        ++it;
    }
}

/*!
 *  �e�ƈ�ԋ߂����j�b�g��T��
 */
IUnit* 
CUnitManager::
FindNearUnit(IBullet* bullet)
{
    if (m_UnitList.empty())return nullptr;
    UNIT_LIST::iterator it = m_UnitList.begin();
    vivid::Vector2 v;
    float min = m_dummy_length;
    IUnit* unit = nullptr;
    while (it != m_UnitList.end())
    {
        if ((*it)->GetUnitCategory() != bullet->GetBulletCategory())
        {
            v = (*it)->GetCenterPosition() - bullet->GetCenterPosition();
            if (v.Length() <= min)
            {
                min = v.Length();
                unit = (*it);
            }
        }

        ++it;
    }
    return unit;
}

/*!
 *  �퓬�@�擾
 */
IUnit* 
CUnitManager::
GetFighter()
{
    if (m_UnitList.empty())return nullptr;
    UNIT_LIST::iterator it = m_UnitList.begin();
    while (it != m_UnitList.end())
    {
        if ((*it)->GetUnitID() == UNIT_ID::FIGHTER)
            return(*it);
        ++it;
    }
    return nullptr;
}

/*!
 *  �c���UFO�𒲂ׂ�
 */
bool 
CUnitManager::
CheckRemainingUfo()
{
    if (m_UnitList.empty())return false;
    if (!m_UfoTable.empty())return true;
    UNIT_LIST::iterator it = m_UnitList.begin();

    int count = 0;

    while (it != m_UnitList.end())
    {
        if ((*it)->GetUnitCategory() == UNIT_CATEGORY::UFO)
            ++count;
        ++it;
    }

    return (count > 0) ? true : false;
}

/*!
 *  �R���X�g���N�^
 */
CUnitManager::
CUnitManager()
{
}

/*!
 *  �f�X�g���N�^
 */
CUnitManager::
~CUnitManager()
{
}

/*!
 *  �R�s�[�R���X�g���N�^
 */
CUnitManager::
CUnitManager(const CUnitManager& rhs)
{
    (void)rhs;
}

/*!
 *  �Q�Ɖ��Z�q
 */
CUnitManager& 
CUnitManager::
operator=(const CUnitManager& rhs)
{
    (void)rhs;
    return *this;
}

/*!
 *  UFO�̔z�u
 */
void 
CUnitManager::
DeployUfo()
{
    // CSV���[�_�[�̐錾
    CCSVLoader csv_loader;
    //CSV�t�@�C�����[�h
    csv_loader.Load("data/ufo_table.csv");
    for (int i = 0; i < csv_loader.GetRows(); ++i)
    {
        UFO_TABLE_DATA t;
        t.id = (UNIT_ID)csv_loader.GetInteger(i, (int)UFO_TABLE_DATA_PARAM::ID);
        t.x = csv_loader.GetInteger(i, (int)UFO_TABLE_DATA_PARAM::X);
        t.y = csv_loader.GetInteger(i, (int)UFO_TABLE_DATA_PARAM::Y);
        t.create_frame = csv_loader.GetInteger(i, (int)UFO_TABLE_DATA_PARAM::CREATE_TIME);
        m_UfoTable.push_back(t);
    }

    // ���
    csv_loader.Unload();
}

/*!
 *  UFO�e�[�u���X�V
 */
void 
CUnitManager::
UpdateUfoTable()
{
    if (m_UfoTable.empty())return;
    UFO_TABLE::iterator it = m_UfoTable.begin();
    UFO_TABLE_DATA t = *it;
#if _DEBUG
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::T))
        m_CreateTimer += 500;
#endif
    if (++m_CreateTimer > t.create_frame)
    {
        vivid::Vector2 pos((float)(t.x), (float)(t.y));
        Create(t.id, pos);
        m_UfoTable.erase(it);
    }
}

/*!
 *  ���j�b�g�X�V
 */
void 
CUnitManager::
UpdateUnit()
{
    if (m_UnitList.empty())return;
    UNIT_LIST::iterator it = m_UnitList.begin();
    while (it != m_UnitList.end())
    {
        IUnit* unit = (IUnit*)(*it);
        unit->Update();
        if (!unit->GetActive())
        {
            unit->Finalize();
            delete unit;
            it = m_UnitList.erase(it);
            continue;
        }

        ++it;
    }
}
