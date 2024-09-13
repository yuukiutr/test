
/*!
 *  @file       bullet.cpp
 *  @brief      �e
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "bullet.h"
#include "..\..\..\..\utility\utility.h"

const unsigned int  IBullet::m_fighter_color    = 0xff008fff;
const unsigned int  IBullet::m_ufo_color        = 0xffff008f;
const int           IBullet::m_adjust_area      = 200;
const vivid::Rect   IBullet::m_enable_area      = { -m_adjust_area, -m_adjust_area, vivid::WINDOW_WIDTH + m_adjust_area, vivid::WINDOW_HEIGHT + m_adjust_area };

/*
 *  �R���X�g���N�^
 */
IBullet::
IBullet( int width, int height, float radius )
    : m_Width( width )
    , m_Height( height )
    , m_Radius( radius )
    , m_Category( UNIT_CATEGORY::UNKNOW )
    , m_Position( vivid::Vector2( 0.0f, 0.0f ) )
    , m_Velocity( vivid::Vector2( 0.0f, 0.0f ) )
    , m_Color( 0xffffffff )
    , m_Anchor( vivid::Vector2( (float)m_Width  / 2.0f, (float)m_Height / 2.0f ) )
    , m_Rect( { 0, 0, m_Width, m_Height } )
    , m_Scale( vivid::Vector2( 1.0f, 1.0f ) )
    , m_Rotation( 0.0f )
    , m_ActiveFlag( true )
{
}

/*
 *  �f�X�g���N�^
 */
IBullet::
~IBullet( void )
{
}

/*
 *  ������
 */
void
IBullet::
Initialize( UNIT_CATEGORY category, const vivid::Vector2& position, float direction, float speed )
{
    m_Category      = category;
    m_Position      = position - vivid::Vector2( (float)m_Width / 2.0f, 0.0f );
    m_Velocity.x    = cos( direction ) * speed;
    m_Velocity.y    = sin( direction ) * speed;
    m_Color         = ( category == UNIT_CATEGORY::FIGHTER ? m_fighter_color : m_ufo_color );
    m_ActiveFlag    = true;
}

/*
 *  �X�V
 */
void
IBullet::
Update( void )
{
    // �ړ��v�Z
    m_Position += m_Velocity;

    // ��ʊO�`�F�b�N
    CheckArea();

    // �ړ����x�ɍ��킹���ĉ�]�l���Z�o
    m_Rotation = atan2( m_Velocity.y, m_Velocity.x );
}

/*
 *  �`��
 */
void
IBullet::
Draw( void )
{
}

/*
 *  ���
 */
void
IBullet::
Finalize( void )
{
}

/*
 *  �ʒu�擾
 */
vivid::Vector2
IBullet::
GetPosition( void )
{
    return m_Position;
}

/*
 *  �ʒu�ݒ�
 */
void
IBullet::
SetPosition( const vivid::Vector2& positioin )
{
    m_Position = positioin;
}

/*
 *  ���S�ʒu�擾
 */
vivid::Vector2
IBullet::
GetCenterPosition( void )
{
    return m_Position + vivid::Vector2( (float)m_Width / 2.0f, (float)m_Height / 2.0f);
}

/*
 *  ���a�擾
 */
float
IBullet::
GetRadius( void )
{
    return m_Radius;
}

/*
 *  �A�N�e�B�u�t���O�擾
 */
bool
IBullet::
GetActive( void )
{
    return m_ActiveFlag;
}

/*
 *  �A�N�e�B�u�t���O�擾
 */
void
IBullet::
SetActive( bool active )
{
    m_ActiveFlag = active;
}

/*
 *  ���j�b�g���ʎq�擾
 */
UNIT_CATEGORY
IBullet::
GetBulletCategory( void )
{
    return m_Category;
}

/*
 *  �e�̐F�擾
 */
unsigned int
IBullet::
GetBulletColor(void)
{
    return m_Color;
}

/*
 *  �e�̗L���͈̓`�F�b�N
 */
void
IBullet::
CheckArea( void )
{
    if( m_Position.x < (float)m_enable_area.left || m_Position.x > (float)m_enable_area.right || m_Position.y < (float)m_enable_area.top || m_Position.y > (float)m_enable_area.bottom )
        m_ActiveFlag = false;
}
