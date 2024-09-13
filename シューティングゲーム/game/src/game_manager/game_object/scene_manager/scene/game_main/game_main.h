
/*!
 *  @file       game_main.h
 *  @brief      �Q�[�����C���V�[��
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include"..\scene.h"
#include "..\..\..\space\space.h"

/*!
 *  @brief  �Q�[���̏��
 */
enum class GAME_STATE
{
    START,
    PLAY,
    GAMEOVER,
    GAMECLEAR,
};

/*!
 *  @class      CGameMain
 *
 *  @brief      �Q�[�����C���V�[��
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CGameMain
    : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CGameMain( void );

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CGameMain( void );

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

    /*!
     *  @brief      �Q�[���̏�Ԏ擾
     *
     *  @return     �Q�[���̏��ID
     */
    GAME_STATE  GetGameState( void );

    /*!
     *  @brief      �Q�[���̏�Ԑݒ�
     *
     *  @param[in]  state   �Q�[�����ID
     */
    void        SetGameState( GAME_STATE state );

private:
    /*!
     *  @brief      �X�^�[�g
     */
    void    Start( void );

    /*!
     *  @brief      �v���C
     */
    void    Play( void );

    /*!
     *  @brief      �Q�[���I�[�o�[
     */
    void    GameOver( void );

    /*!
     *  @brief      �Q�[���N���A
     */
    void    GameClear( void );

    static const int                m_fight_width;          //!< FIGHT�̕�
    static const int                m_fight_height;         //!< FIGHT�̍���
    static const int                m_gameclear_width;      //!< �Q�[���N���A�̕�
    static const int                m_gameclear_height;     //!< �Q�[���N���A�̍���
    static const int                m_gameover_width;       //!< �Q�[���I�[�o�[�̕�
    static const int                m_gameover_height;      //!< �Q�[���I�[�o�[�̍���
    static const vivid::Vector2     m_fight_position;       //!< �Q�[���J�n�ʒu
    static const vivid::Vector2     m_gameclear_position;   //!< �Q�[���N���A�J�n�ʒu
    static const vivid::Vector2     m_gameover_position;    //!< �Q�[���I�[�o�[�J�n�ʒu
    CSpace                          m_Space;                //!< �F���N���X
    GAME_STATE                      m_GameState;            //!< �Q�[���̏��
    int                             m_WaitTime;             //!< �ҋ@����
    int                             m_FihgtAlpha;           //!< FIGHT�A���t�@�l
    int                             m_GameOverAlpha;        //!< �Q�[���I�[�o�[�A���t�@�l
    int                             m_GameClearAlpha;       //!< �Q�[���N���A�A���t�@�l
    vivid::Vector2                  m_FightScale;           //!< FIGHT�g�嗦
    vivid::Vector2                  m_GameClearScale;       //!< �Q�[���N���A�g�嗦
    float                           m_GameClearRotation;    //!< �Q�[���N���A��]�l
};
