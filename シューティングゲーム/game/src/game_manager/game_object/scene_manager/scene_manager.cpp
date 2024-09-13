
/*!
 *  @file       scene_manager.cpp
 *  @brief      �V�[���Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "scene_manager.h"
#include "scene\title\title.h"
#include "scene\game_main\game_main.h"

const int               CSceneManager::m_fade_speed     = 5;
const vivid::Vector2    CSceneManager::m_fade_position  = { 0.0f, 0.0f };
const unsigned int      CSceneManager::m_fade_color     = 0xff000000;
const int               CSceneManager::m_min_fade_alpha = 0;
const int               CSceneManager::m_max_fade_alpha = 255;

/*
 *  �C���X�^���X�̎擾
 */
CSceneManager&
CSceneManager::
GetInstance( void )
{
    static CSceneManager instance;

    return instance;
}

/*
 *  ������
 */
void
CSceneManager::
Initialize( void )
{
    // ���[�g�V�[������
    m_NextSceneID = SCENE_ID::TITLE;

    // �V�[���ύX
    m_State = STATE::SCENE_CHANGE;
}

/*
 *  �X�V
 */
void
CSceneManager::
Update( void )
{
    switch( m_State )
    {
    case STATE::FADEIN:          FadeIn( );      break;
    case STATE::SCENE_UPDATE:    SceneUpdate( ); break;
    case STATE::FADEOUT:         FadeOut( );     break;
    case STATE::SCENE_CHANGE:    SceneChange( ); break;
    }
}

/*
 *  �`��
 */
void
CSceneManager::
Draw( void )
{
    // �V�[���`��
    if( m_Scene ) m_Scene->Draw( );
}

/*
 *  �V�[���G�t�F�N�g�`��
 */
void
CSceneManager::
DrawSceneEffect( void )
{
    // �A���t�@�l�ƃt�F�[�h�J���[�̍���
    unsigned int color = (m_FadeAlpha << 24) | (m_fade_color & 0x00ffffff );

    // �V�[���G�t�F�N�g��`��
    vivid::DrawTexture("data\\white.png", m_fade_position, color);
}

/*
 *  ���
 */
void
CSceneManager::
Finalize( void )
{
    // �V�[�����
    if( m_Scene )
    {
        m_Scene->Finalize( );

        delete m_Scene;

        m_Scene = nullptr;
    }
}

/*
 *  �V�[���؊���
 */
void
CSceneManager::
ChangeScene( SCENE_ID id )
{
    // ���̃V�[��ID��o�^
    m_NextSceneID = id;

    m_ChangeScene = true;
}

/*
 *  ���݂̃V�[�����擾
 */
IScene*
CSceneManager::
GetScene( void )
{
    return m_Scene;
}

/*
 *  �R���X�g���N�^
 */
CSceneManager::
CSceneManager( void )
    : m_Scene( nullptr )
    , m_CurrentSceneID( SCENE_ID::DUMMY )
    , m_NextSceneID( SCENE_ID::DUMMY )
    , m_ChangeScene( false )
    , m_FadeAlpha( m_max_fade_alpha )
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CSceneManager::
CSceneManager( const CSceneManager& rhs )
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CSceneManager::
~CSceneManager( void )
{
}

/*
 *  ������Z�q
 */
CSceneManager&
CSceneManager::
operator=( const CSceneManager& rhs )
{
    (void)rhs;

    return *this;
}

/*
 *  �V�[������
 */
void
CSceneManager::
CreateScene( SCENE_ID id )
{
    //ID����ɃV�[��������
    switch( id )
    {
    case SCENE_ID::TITLE:        m_Scene = new CTitle( );       break;
    case SCENE_ID::GAMEMAIN:     m_Scene = new CGameMain( );    break;
    }
}

/*
 *  �t�F�[�h�C��
 */
void
CSceneManager::
FadeIn( void )
{
    m_FadeAlpha -= m_fade_speed;

    if( m_FadeAlpha < m_min_fade_alpha )
    {
        m_FadeAlpha = m_min_fade_alpha;

        // �V�[���X�V
        m_State = STATE::SCENE_UPDATE;
    }
}

/*
 *  �V�[���X�V
 */
void
CSceneManager::
SceneUpdate( void )
{
    // �V�[���X�V
    if( m_Scene ) m_Scene->Update( );

    // �V�[���ύX������
    if( m_CurrentSceneID != m_NextSceneID || m_ChangeScene )
    {
        // �t�F�[�h�A�E�g
        m_State = STATE::FADEOUT;

        m_ChangeScene = false;
    }
}

/*
 *  �t�F�[�h�A�E�g
 */
void
CSceneManager::
FadeOut( void )
{
    m_FadeAlpha += m_fade_speed;

    if( m_FadeAlpha > m_max_fade_alpha )
    {
        m_FadeAlpha = m_max_fade_alpha;

        // �V�[���ύX
        m_State = STATE::SCENE_CHANGE;
    }
}

/*
 *  �V�[���ύX
 */
void
CSceneManager::
SceneChange( void )
{
    if( m_Scene )
    {
        m_Scene->Finalize( );

        delete m_Scene;

        m_Scene = nullptr;
    }

    // �V�����V�[������
    CreateScene( m_NextSceneID );

    // ������
    m_Scene->Initialize( );

    // �X�V
    m_Scene->Update( );

    m_CurrentSceneID = m_NextSceneID;

    // �t�F�[�h�C��
    m_State = STATE::FADEIN;
}
