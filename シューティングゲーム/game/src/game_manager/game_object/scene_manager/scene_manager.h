
/*!
 *  @file       scene_manager.h
 *  @brief      �V�[���Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include"scene\scene_id.h"

class IScene;

/*!
 *  @class      CSceneManager
 *
 *  @brief      �V�[���Ǘ��N���X
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CSceneManager
{
public:
   /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CSceneManager&   GetInstance( void );

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
     *  @brief      �V�[���G�t�F�N�g�`��
     */
    void        DrawSceneEffect( void );

    /*!
     *  @brief      ���
     */
    void        Finalize( void );

    /*!
     *  @brief      �V�[���؂芷��
     *
     *  @param[in]  id  �V�[��ID
     */
    void        ChangeScene( SCENE_ID id );

    /*!
     *  @brief      ���݂̃V�[�����擾
     *
     *  @return     ���݂̃V�[��
     */
    IScene*     GetScene( void );

private:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSceneManager( void );

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CSceneManager( const CSceneManager& rhs );

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSceneManager( void );

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CSceneManager& operator=( const CSceneManager& rhs );

    /*!
     *  @brief      �V�[������
     *
     *  @param[in]  id  �V�[��ID
     */
    void    CreateScene( SCENE_ID id );

    /*!
     *  @brief      �t�F�[�h�C��
     */
    void    FadeIn( void );

    /*!
     *  @brief      �V�[���X�V
     */
    void    SceneUpdate( void );

    /*!
     *  @brief      �t�F�[�h�A�E�g
     */
    void    FadeOut( void );

    /*!
     *  @brief      �V�[���ύX
     */
    void    SceneChange( void );

    /*!
     *  @brief      ���ID
     */
    enum class STATE
    {
          FADEIN          //!< �t�F�[�h�C��
        , SCENE_UPDATE    //!< �V�[���X�V
        , FADEOUT         //!< �t�F�[�h�A�E�g
        , SCENE_CHANGE    //!< �V�[���ύX
    };

    static const int            m_fade_speed;       //!< �t�F�[�h���x
    static const vivid::Vector2 m_fade_position;    //!< �t�F�[�h�\���ʒu
    static const unsigned int   m_fade_color;       //!< �t�F�[�h�F
    static const int            m_min_fade_alpha;   //!< �t�F�[�h�p�A���t�@�̍ŏ��l
    static const int            m_max_fade_alpha;   //!< �t�F�[�h�p�A���t�@�̍ő�l
    SCENE_ID                    m_CurrentSceneID;   //!< ���݂̃V�[��ID
    SCENE_ID                    m_NextSceneID;      //!< ���̃V�[��ID
    IScene*                     m_Scene;            //!< �V�[���N���X
    STATE                       m_State;            //!< ���
    bool                        m_ChangeScene;      //!< �V�[���ύX�t���O
    int                         m_FadeAlpha;        //!< �t�F�[�h���̃A���t�@�l
};
