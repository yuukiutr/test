
/*!
 *  @file       normal_bullet.h
 *  @brief      �ʏ�e
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include "..\bullet.h"

/*!
 *  @class      CNormalBullet
 *
 *  @brief      �ʏ�e�N���X
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CNormalBullet
    : public IBullet
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CNormalBullet( void );

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CNormalBullet( void );

    /*!
     *  @brief      �`��
     */
    void    Draw( void );

private:
    static const int    m_width;    //!< ��
    static const int    m_height;   //!< ����
    static const float  m_radius;   //!< ���a
};
