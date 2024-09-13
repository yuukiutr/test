
/*!
 *  @file       scene.h
 *  @brief      �V�[���x�[�X
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

/*!
 *  @class      IScene
 *
 *  @brief      �V�[���x�[�X�N���X
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    IScene( void );

    /*!
     *  @brief      �f�X�g���N�^
     */
    virtual ~IScene( void );

    /*!
     *  @brief      ������
     */
    virtual void        Initialize( void );

    /*!
     *  @brief      �X�V
     */
    virtual void        Update( void );

    /*!
     *  @brief      �`��
     */
    virtual void        Draw( void );

    /*!
     *  @brief      ���
     */
    virtual void        Finalize( void );
};
