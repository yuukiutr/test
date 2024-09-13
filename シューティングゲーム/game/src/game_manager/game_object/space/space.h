
/*!
 *  @file       space.h
 *  @brief      �F��
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"

/*!
 *  @class      CSpace
 *
 *  @brief      �F���N���X
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CSpace
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSpace( void );

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSpace( void );

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
    static const int                m_width;                    //!< ��
    static const int                m_height;                   //!< ����
    static const int                m_max_bg_count;             //!< �w�i�̐�
    static const float              m_scroll_speed;             //!< �X�N���[�����x
    vivid::Vector2*                 m_Position;                 //!< �ʒu
    vivid::Vector2*                 m_Velocity;                 //!< ���x
};
