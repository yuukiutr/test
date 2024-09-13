
/*!
 *  @file       game_manager.h
 *  @brief      �Q�[���Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"

/*!
 *  @class      CGameManager
 *
 *  @brief      �Q�[���Ǘ��N���X
 * 
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CGameManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CGameManager&   GetInstance( void );

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

private:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CGameManager( void );

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CGameManager( const CGameManager& rhs );

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CGameManager( void );

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CGameManager& operator=( const CGameManager& rhs );
};
