
/*!
 *  @file       unit.h
 *  @brief      ���j�b�g
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include "unit_id.h"

class IBullet;

/*!
 *  @brief  ���j�b�g�̏��ID
 */
enum class UNIT_STATE
{
    APPEAR, //!< �o��
    ATTACK, //!< �U��
    DEAD,   //!< ���S
};

/*!
 *  @class      IUnit
 *
 *  @brief      ���j�b�g�x�[�X�N���X
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class IUnit
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  width       ��
     *  @param[in]  height      ����
     *  @param[in]  radius      ���a
     *  @param[in]  life        ���C�t
     *  @param[in]  category  ���j�b�g���ʎq
     *  @param[in]  unit_id     ���j�b�gID
     */
    IUnit(int width, int height, float radius, int life, UNIT_CATEGORY category, UNIT_ID unit_id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    virtual ~IUnit( void );

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �ʒu
     */
    virtual void    Initialize( const vivid::Vector2& position );

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
     *  @brief      �A�^������`�F�b�N
     *
     *  @param[in]  bullet  �e�N���X
     *
     *  @retval     true    �������Ă���
     *  @retval     false   �������Ă��Ȃ�
     */
    virtual bool    CheckHitBullet( IBullet* bullet );

    /*!
     *  @brief      ���j�b�gID�擾
     *
     *  @return     ���j�b�gID
     */
    UNIT_ID         GetUnitID( void );

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
    UNIT_CATEGORY   GetUnitCategory( void );

    /*!
     *  @brief      ���C�t�擾
     *
     *  @return     ���C�t
     */
    int             GetLife( void );

    /*!
     *  @brief      �ő僉�C�t�擾
     *
     *  @return     �ő僉�C�t
     */
    int             GetMaxLife( void );

    /*!
     *  @brief      ���G�t���O�擾
     *
     *  @return     ���G�t���O
     */
    bool            GetInvincibleFlag( void );

    /*!
     *  @brief      ���G�t���O�ݒ�
     *
     *  @param[in]  flag    ���G�t���O
     */
    void            SetInvincibleFlag( bool flag );

    /*!
     *  @brief      ��Ԏ擾
     *
     *  @return     ���ID
     */
    UNIT_STATE      GetUnitState( void );

    /*!
     *  @brief      ��Ԑݒ�
     *
     *  @param[in]  state    ���ID
     */
    void            SetUnitState( UNIT_STATE state );

protected:
    /*!
     *  @brief      ���C�g�J���[�̕ύX
     */
    void            ChangeLightColor( void );

    /*!
     *  @brief      �o��
     */
    virtual void    Appear( void );

    /*!
     *  @brief      �U��
     */
    virtual void    Attack( void );

    /*!
     *  @brief      ���S
     */
    virtual void    Dead( void );

    static const int        m_change_color_speed;   //!< �F�̕ύX���x
    static const float      m_bloom_fade_speed;     //!< �u���[���t�F�[�h���x
    int                     m_Width;                //!< ��
    int                     m_Height;               //!< ����
    float                   m_Radius;               //!< ���a
    vivid::Vector2          m_Position;             //!< �ʒu
    vivid::Vector2          m_Velocity;             //!< ���x
    unsigned int            m_LightColor;           //!< ���̐F
    unsigned int            m_BloomColor;           //!< ���̐F
    vivid::Vector2          m_Anchor;               //!< ��_
    vivid::Rect             m_Rect;                 //!< �ǂݍ��ݔ͈�
    vivid::Vector2          m_Scale;                //!< �g�嗦
    float                   m_Rotation;             //!< ��]�l
    bool                    m_ActiveFlag;           //!< �A�N�e�B�u�t���O
    int                     m_ColorFactor;          //!< ���̐F�̕ω��v�f
    float                   m_AlphaFactor;          //!< �A���t�@�l�ω��v�f
    int                     m_Life;                 //!< ���C�t
    int                     m_MaxLife;              //!< �ő僉�C�t
    UNIT_CATEGORY           m_Category;             //!< ���j�b�g���ʎq
    UNIT_ID                 m_UnitID;               //!< ���j�b�gID
    bool                    m_InvincibleFlag;       //!< ���G�t���O
    UNIT_STATE              m_UnitState;            //!< ���ID
};
