
/*!
 *  @file       title.h
 *  @brief      �^�C�g���V�[��
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include"..\scene.h"

/*!
 *  @class      CTitle
 *
 *  @brief      �^�C�g���V�[���N���X
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CTitle
    : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CTitle( void );

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CTitle( void );

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
     *  @brief      �ݒ�
     */
    void        Setting();

    /*!
     *  @brief  ���ID
     */
    enum class STATE
    {
        WAIT,
        SHINE,
        APPEAR,
        SETTING,
    };

    static const int            m_shine_width;          //!< ���̕�
    static const int            m_shine_height;         //!< ���̍���
    static const int            m_shine_time;           //!< ���鎞��
    static const int            m_blink_time;           //!< �_�Ŏ���
    static const float          m_shine_rotation_speed; //!< ���̉�]���x
    static const float          m_shine_speed;          //!< ���̈ړ����x
    static const vivid::Vector2 m_title_positon;        //!< �^�C�g�����S�ʒu
    static const vivid::Vector2 m_message_positon;      //!< ���b�Z�[�W�̈ʒu
    static const vivid::Vector2 m_copyright_positon;    //!< �R�s�[���C�g�̈ʒu
    vivid::Vector2              m_ShinePosition;        //!< ���̈ʒu
    float                       m_ShineRotation;        //!< ���̉�]�l
    STATE                       m_State;                //!< ���ID
    int                         m_ShineTime;            //!< ���鎞��
    int                         m_BlinkTime;            //!< �_�Ŏ���
};
