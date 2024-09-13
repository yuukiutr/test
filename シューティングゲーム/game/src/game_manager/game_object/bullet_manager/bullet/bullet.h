
/*!
 *  @file       bullet.h
 *  @brief      �e
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include "bullet_id.h"
#include "..\..\unit_manager\unit\unit_id.h"

/*!
 *  @class      IBullet
 *
 *  @brief      �e�x�[�X�N���X
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class IBullet
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  width   ��
     *  @param[in]  height  ����
     *  @param[in]  radius  ���a
     */
    IBullet( int width, int height, float radius );

    /*!
     *  @brief      �f�X�g���N�^
     */
    virtual ~IBullet( void );

    /*!
     *  @brief      ������
     *
     *  @param[in]  category  ���j�b�g���ʎq
     *  @param[in]  position    �ʒu
     *  @param[in]  direction   ����
     *  @param[in]  speed       ����
     */
    virtual void    Initialize( UNIT_CATEGORY category, const vivid::Vector2& position, float direction, float speed );

    /*!
     *  @brief      �X�V
     */
    virtual void    Update( void );

    /*!
     *  @brief      �`��
     */
    virtual void    Draw( void );

    /*!
     *  @brief      ���
     */
    virtual void    Finalize( void );

    /*!
     *  @brief      �ʒu�擾
     *
     *  @return     �ʒu
     */
    vivid::Vector2  GetPosition( void );

    /*!
     *  @brief      �ʒu�ݒ�
     *
     *  @param[in]  position    �ʒu
     */
    void            SetPosition( const vivid::Vector2& position );

    /*!
     *  @brief      ���S�ʒu�擾
     *
     *  @return     ���S�ʒu
     */
    vivid::Vector2  GetCenterPosition( void );

    /*!
     *  @brief      ���a�擾
     *
     *  @return     ���a
     */
    float           GetRadius( void );

    /*!
     *  @brief      �A�N�e�B�u�t���O�擾
     *
     *  @return     �A�N�e�B�u�t���O
     */
    bool            GetActive( void );

    /*!
     *  @brief      �A�N�e�B�u�t���O�ݒ�
     *
     *  @param[in]  active  �A�N�e�B�u�t���O
     */
    void            SetActive( bool active );

    /*!
     *  @brief      ���j�b�g���ʎq�擾
     *
     *  @return     ���j�b�g���ʎq
     */
    UNIT_CATEGORY   GetBulletCategory( void );

    /*!
     *  @brief      �e�̐F�擾
     *
     *  @return     �e�̐F
     */
    unsigned int    GetBulletColor( void );

protected:
    /*!
     *  @brief      �e�̗L���͈̓`�F�b�N
     */
    void    CheckArea( void );

    static const unsigned int   m_fighter_color;    //!< �퓬�@�̒e�̐F
    static const unsigned int   m_ufo_color;        //!< UFO�e�̐F
    static const int            m_adjust_area;      //!< �e�̐����\�G���A�͈�
    static const vivid::Rect    m_enable_area;      //!< �e�̐����\�G���A
    int                         m_Width;            //!< ��
    int                         m_Height;           //!< ����
    float                       m_Radius;           //!< ���a
    vivid::Vector2              m_Position;         //!< �ʒu
    vivid::Vector2              m_Velocity;         //!< ���x
    unsigned int                m_Color;            //!< �F
    vivid::Vector2              m_Anchor;           //!< ��_
    vivid::Rect                 m_Rect;             //!< �ǂݍ��ݔ͈�
    vivid::Vector2              m_Scale;            //!< �g�嗦
    float                       m_Rotation;         //!< ��]�l
    bool                        m_ActiveFlag;       //!< �A�N�e�B�u�t���O
    UNIT_CATEGORY               m_Category;         //!< �e���ʎq
};
