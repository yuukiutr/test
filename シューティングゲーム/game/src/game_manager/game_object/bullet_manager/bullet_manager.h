
/*!
 *  @file       bullet_manager.h
 *  @brief      �e�Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <list>
#include "vivid.h"
#include "bullet\bullet_id.h"
#include "bullet\bullet.h"
#include "..\unit_manager\unit\unit_id.h"

using namespace std;

/*!
 *  @class      CBulletManager
 *
 *  @brief      �e�Ǘ��N���X
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CBulletManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CBulletManager&   GetInstance( void );

    /*!
     *  @brief      ������
     */
    void        Initialize( void );

    /*!
     *  @brief      �X�V
     */
    void        Update( void );

    /*!
     *  @brief      �`��
     */
    void        Draw( void );

    /*!
     *  @brief      ���
     */
    void        Finalize( void );

    /*!
     *  @brief      �e����
     *
     *  @param[in]  category  ���j�b�g���ʎq
     *  @param[in]  id          �eID
     *  @param[in]  pos         �ʒu
     *  @param[in]  dir         ����
     *  @param[in]  speed       ����
     */
    void        Create( UNIT_CATEGORY category, BULLET_ID id, const vivid::Vector2& pos, float dir, float speed );

private:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CBulletManager( void );

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CBulletManager( const CBulletManager& rhs );

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CBulletManager( void );

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CBulletManager& operator=( const CBulletManager& rhs );

    /*!
     *  @brief      �e���X�g�^
     */
    using BULLET_LIST = list<IBullet*>;

    BULLET_LIST     m_BulletList;   //!< �e���X�g
};
