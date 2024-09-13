
/*!
 *  @file       fighter.h
 *  @brief      �퓬�@
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include "..\unit.h"

class CFighterOption;

/*!
 *  @class      CFighter
 *
 *  @brief      �퓬�@�N���X
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CFighter
    : public IUnit
{
public:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CFighter( void );

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CFighter( void );

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �����ʒu
     */
    void        Initialize( const vivid::Vector2& position )override;

    /*!
     *  @brief      �X�V
     */
    void        Update( void )override;

    /*!
     *  @brief      �`��
     */
    void        Draw( void )override;

    /*!
     *  @brief      ���
     */
    void        Finalize( void )override;

    /*!
     *  @brief      �A�^������`�F�b�N
     *
     *  @param[in]  bullet  �e�N���X
     *
     *  @retval     true    �������Ă���
     *  @retval     false   �������Ă��Ȃ�
     */
    bool        CheckHitBullet( IBullet* bullet )override;

    struct DATA
    {
        const float m_up_limit_move_accelerator         = 0.09f;
        const float m_down_limit_move_accelerator       = 0.01f;
        const float m_up_limit_max_move_accelerator     = 0.5f;
        const float m_down_limit_max_move_accelerator   = 0.1f;
        float m_move_accelerator;
        float m_max_move_accelerator;
    };

private:

    /*!
     *  @brief      �o��
     */
    void        Appear( void )override;

    /*!
     *  @brief      �U��
     */
    void        Attack( void )override;

    /*!
     *  @brief      ���S
     */
    void        Dead( void )override;

    /*!
     *  @brief      ����
     */
    void        Control( void );

    /*!
     *  @brief      �ˌ�
     */
    void        Fire( void );

    /*!
     *  @brief      �ړ�����
     */
    void        Move( void );

    /*!
     *  @brief      �ړ��͈̓`�F�b�N
     */
    void        CheckMoveArea( void );

    /*!
     *  @brief      �O�ՃG�t�F�N�g
     */
    void        Effect( void );

    static const int                m_width;                        //!< ��
    static const int                m_height;                       //!< ����
    static const float              m_radius;                       //!< ���a
    static const vivid::Vector2     m_start_position;               //!< �����ʒu
    static const float              m_move_friction;                //!< �ړ��p������
    //static const float              m_max_move_accelerator;         //!< �ړ����̉����x
    //static const float              m_move_accelerator;             //!< �ړ����̉����x
    static const float              m_create_effect_length;         //!< �G�t�F�N�g���o����̑傫��
    static const int                m_max_fire_time;                //!< ���ˎ���
    static const int                m_max_life;                     //!< �ő僉�C�t
    static const int                m_nbullet_fire_interval;        //!< �ʏ�e���ˊԊu
    static const int                m_charge_shot_time;             //!< �`���[�W�V���b�g�^�C��
    static const int                m_max_invincible_time;          //!< ���G����
    static const int                m_invincible_visible_interval;  //!< ���G���Ԓ��̓_�ŊԊu

    DATA                            m_Data;                         //!< �����x�f�[�^
    vivid::Vector2                  m_Accelerator;                  //!< �����x
    float                           m_MoveAccelerator;              //!< �ړ��p�����x
    int                             m_NBulletFireTimer;             //!< �m�[�}���e���˃^�C�}�[
    int                             m_HBulletFireTimer;             //!< �z�[�~���O�e���˃^�C�}�[
    int                             m_InvincibleTime;               //!< ���G����
    CFighterOption*                 m_Option1;
    CFighterOption*                 m_Option2;

};
