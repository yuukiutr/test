
/*!
 *  @file       game_manager.cpp
 *  @brief      �Q�[���Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "game_manager.h"
#include "game_object\game_object.h"
#include "game_object/container/container.h"

/*
 *  �C���X�^���X�̎擾
 */
CGameManager&
CGameManager::
GetInstance( void )
{
    static CGameManager instance;

    return instance;
}

/*
 *  ������
 */
void
CGameManager::
Initialize( void )
{
    CSoundManager& sound = CSoundManager::GetInstance();

    sound.Load();

    sound.Play(SOUND_ID::BGM, true);
    
    // �V�[���}�l�[�W���[������
    CSceneManager::GetInstance().Initialize();

    // �G�t�F�N�g�}�l�[�W���[������
    CEffectManager::GetInstance().Initialize();

    CContainer::GetInstance().Initialize();
}

/*
 *  �X�V
 */
void
CGameManager::
Update( void )
{
    // �V�[���}�l�[�W���[�X�V
    CSceneManager::GetInstance().Update();

    // �G�t�F�N�g�}�l�[�W���[�X�V
    CEffectManager::GetInstance().Update();
}

/*
 *  �`��
 */
void
CGameManager::
Draw( void )
{
    // �V�[���}�l�[�W���[�擾
    CSceneManager& sm = CSceneManager::GetInstance();

    // �V�[���`��
    sm.Draw();

    // �G�t�F�N�g�}�l�[�W���[�`��
    CEffectManager::GetInstance().Draw();

    // �V�[���G�t�F�N�g�`��
    sm.DrawSceneEffect();
}

/*
 *  ���
 */
void
CGameManager::
Finalize( void )
{
    // �G�t�F�N�g�}�l�[�W���[���
    CEffectManager::GetInstance().Finalize();

    // �V�[���}�l�[�W���[���
    CSceneManager::GetInstance().Finalize();
}

/*
 *  �R���X�g���N�^
 */
CGameManager::
CGameManager( void )
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CGameManager::
CGameManager( const CGameManager& rhs )
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CGameManager::
~CGameManager( void )
{
}

/*
 *  ������Z�q
 */
CGameManager&
CGameManager::
operator=( const CGameManager& rhs )
{
    (void)rhs;

    return *this;
}
