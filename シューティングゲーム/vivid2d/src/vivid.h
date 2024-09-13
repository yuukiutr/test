
/*!
 *  @file       vivid.h
 *  @brief      Vivid2D Library
 *  @author     Kazuya Maruyama
 *  @date       2020/11/25
 *  @version    2.7
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. Shinya Kosugi. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include <string>
#include <cmath>
#include <ctime>
#include <tuple>

/*!
 *  @brief  WindowsAPI�Œ�`����Ă���}�N���𖳌���
 */
#undef CreateFont
#undef DrawText
#undef PlaySound

#ifdef  _DEBUG
/*!
 *  @brief  �f�o�b�O���s���}�N��<br>
 *          ���̃}�N�����L���Ȏ��ADebug�p�v���Z�X�Ńv���O���������s���܂��B
 */
#define VIVID_DEBUG
#else
/*!
 *  @brief  �������[�X���s���}�N��<br>
 *          ���̃}�N�����L���Ȏ��ARelease�p�v���Z�X�Ńv���O���������s���܂��B
 */
#define VIVID_RELEASE
#endif

/*!
 *  @brief      �|�C���^�ϐ�������ANULL��ݒ�
 *
 *  @param[in]  p   �������|�C���^
 */
#define VIVID_SAFE_DELETE( p )          if( ( p ) ) { delete ( p ); ( p ) = nullptr; }

/*!
 *  @brief      �|�C���^�ϐ�������ANULL��ݒ�
 *
 *  @param[in]  p   �������|�C���^
 */
#define VIVID_SAFE_DELETE_ARRAY( p )    if( ( p ) ) { delete[] ( p ); ( p ) = nullptr; }

/*!
 *  @brief      �C���^�[�t�F�[�X�N���X��������ANULL��ݒ�
 *
 *  @param[in]  p   �������C���^�[�t�F�[�X�|�C���^
 */
#define VIVID_SAFE_RELEASE( p )         if( ( p ) ) { ( p )->Release( ); ( p ) = nullptr; }

/*!
 *  @brief      DXLib�G���[�l
 */
#define VIVID_DX_ERROR          ( -1 )

/*!
 *  @brief      �g�p���Ă��Ȃ��n���h���l
 */
#define VIVID_UNUSED_HANDLE     ( -1 )

#ifdef  VIVID_DEBUG
/*!
 *  @brief      �R���\�[���ɕ�����l���o�͂���<br>
 *              C����ɂ�����printf�֐��Ɠ��l�̎g�����B
 *
 *  @param[in]  format  �����w�蕶����
 *  @param[in]  ...     �������ϐ��Ȃ�
 */
#define dprintf( format, ... )          printf( format, __VA_ARGS__ )

/*!
 *  @brief      �R���\�[���Ɍ��݂̃R�[�h���C����\������B
 */
#define dprint_line                     dprintf( "Line - %d\n", __LINE__ )

/*!
 *  @brief      �R���\�[���Ɍ��݂̃t�@�C������\������B
 */
#define dprint_file                     dprintf( "File - %s\n", __FILE__ )

/*!
 *  @brief      �R���\�[���ɕ������\������B
 *
 *  @param[in]  x   ������
 */
#define VIVID_OUT_MESSAGE( x )          dprintf( x )

/*!
 *  @brief      �R���\�[���ɕ�����l���o�͂���<br>
 *              C����ɂ�����printf�֐��Ɠ��l�̎g�����B
 *
 *  @param[in]  format  �����w�蕶����
 *  @param[in]  ...     �������ϐ��Ȃ�
 */
#define VIVID_TRACE( format, ... )      dprintf( format, __VA_ARGS__ )

/*!
 *  @brief      �A�T�[�g����
 *              �Q�[����ʏo�͗p
 *
 *  @param[in]  x       ������
 *  @param[in]  message �G���[���b�Z�[�W
 */
#define VIVID_ASSERT( x, message )      Assert( ( x ), ( message ), __FILE__, __LINE__ )

/*!
 *  @brief      �A�T�[�g����
 *              �Q�[����ʏo�͗p
 *
 *  @param[in]  x       ������
 *  @param[in]  message �G���[���b�Z�[�W
 */
#define VIVID_DX_ASSERT( x, message )   Assert( ( x ) != VIVID_DX_ERROR, ( message ), __FILE__, __LINE__ )

/*!
 *  @brief      ���������[�N�`�F�b�N
 */
#define VIVID_CHECK_MEMORY_LEAK         _CrtSetDbgFlag( _CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF )

/*!
 *  @brief      ���������[�N���Ƀt�@�C�����ƍs�ԍ���\������
 */
#define VIVID_NEW                       new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#else
#define dprintf( format, ... )
#define dprint_line
#define dprint_file
#define VIVID_OUT_MESSAGE( x )
#define VIVID_TRACE( format, ... )
#define VIVID_ASSERT( x, type )
#define VIVID_DX_ASSERT( x, type )
#define VIVID_CHECK_MEMORY_LEAK
#define VIVID_NEW                   new
#endif

/*!
 *  @brief      vivid���O���
 */
namespace vivid
{
    const int WINDOW_WIDTH  = 480;     //! �E�B���h�E�̕�
    const int WINDOW_HEIGHT = 640;     //! �E�B���h�E�̍���

    /*!
     *  @brief      vivid::keyboard���O���
     */
    namespace keyboard
    {
        /*!
         *  @brief      �L�[ID<br>
         *              �L�[�{�[�h����Ŏg�p�\�ȃL�[ID
         */
        enum class KEY_ID
        {
              DUMMY         = 0x00  //! Dummy
            , ESCAPE        = 0x01  //! Escape
            , ONE           = 0x02  //! 1
            , TWO           = 0x03  //! 2
            , THREE         = 0x04  //! 3
            , FOUR          = 0x05  //! 4
            , FIVE          = 0x06  //! 5
            , SIX           = 0x07  //! 6
            , SEVEN         = 0x08  //! 7
            , EIGHT         = 0x09  //! 8
            , NINE          = 0x0A  //! 9
            , ZERO          = 0x0B  //! 0
            //, MINUS         = 0x0C  //! -
            //, EQUALS        = 0x0D  //! =
            , BACK          = 0x0E  //! BackSpace
            , TAB           = 0x0F  //! Tab
            , Q             = 0x10  //! Q
            , W             = 0x11  //! W
            , E             = 0x12  //! E
            , R             = 0x13  //! R
            , T             = 0x14  //! T
            , Y             = 0x15  //! Y
            , U             = 0x16  //! U
            , I             = 0x17  //! I
            , O             = 0x18  //! O
            , P             = 0x19  //! P
            //, LBRACKET      = 0x1A  //! [
            //, RBRACKET      = 0x1B  //! ]
            , RETURN        = 0x1C  //! Enter
            , LCONTROL      = 0x1D  //! Ctrl(����)
            , A             = 0x1E  //! A
            , S             = 0x1F  //! S
            , D             = 0x20  //! D
            , F             = 0x21  //! F
            , G             = 0x22  //! G
            , H             = 0x23  //! H
            , J             = 0x24  //! J
            , K             = 0x25  //! K
            , L             = 0x26  //! L
            //, SEMICOLON     = 0x27  //! ;(�Z�~�R����)
            //, APOSTROPHE    = 0x28  //! '(�V���O���N�H�[�e�[�V����)
            //, GRAVE         = 0x29  //! `
            , LSHIFT        = 0x2A  //! Shift(����)
            , BACKSLASH     = 0x2B  //! '\'(�o�b�N�X���b�V���܂��͉~�}�[�N)
            , Z             = 0x2C  //! Z
            , X             = 0x2D  //! X
            , C             = 0x2E  //! C
            , V             = 0x2F  //! V
            , B             = 0x30  //! B
            , N             = 0x31  //! N
            , M             = 0x32  //! M
            //, COMMA         = 0x33  //! ,(�J���})
            //, PERILD        = 0x34  //! .(�s���I�h)
            //, SLASH         = 0x35  //! '/'(�X���b�V��)
            //, RSHIFT        = 0x36  //! �V�t�g(�E��)
            //, MULTIPLY      = 0x37  //! *(NumPad)
            //, LMENU         = 0x38  //! Alt(����)
            , SPACE         = 0x39  //! Space
            //, CAPIRAL       = 0x3A  //! CapsLock
            , F1            = 0x3B  //! F1
            , F2            = 0x3C  //! F2
            , F3            = 0x3D  //! F3
            , F4            = 0x3E  //! F4
            , F5            = 0x3F  //! F5
            , F6            = 0x40  //! F6
            , F7            = 0x41  //! F7
            , F8            = 0x42  //! F8
            , F9            = 0x43  //! F9
            , F10           = 0x44  //! F10
            //, NUMLOCK       = 0x45  //! NumLock
            //, SCROLL        = 0x46  //! ScrollLock
            , NUMPAD7       = 0x47  //! 7(NumPad)
            , NUMPAD8       = 0x48  //! 8(NumPad)
            , NUMPAD9       = 0x49  //! 9(NumPad)
            , SUBTRACT      = 0x4A  //! -(NumPad)
            , NUMPAD4       = 0x4B  //! 4(NumPad)
            , NUMPAD5       = 0x4C  //! 5(NumPad)
            , NUMPAD6       = 0x4D  //! 6(NumPad)
            , ADD           = 0x4E  //! +(NumPad)
            , NUMPAD1       = 0x4F  //! 1(NumPad)
            , NUMPAD2       = 0x50  //! 2(NumPad)
            , NUMPAD3       = 0x51  //! 3(NumPad)
            , NUMPAD0       = 0x52  //! 0(NumPad)
            , NUMPADDECIMAL = 0x53  //! .(NumPad)
            , F11           = 0x57  //! F11
            , F12           = 0x58  //! F12
            , F13           = 0x64  //! F13
            , F14           = 0x65  //! F14
            , F15           = 0x66  //! F15
            //, KANA          = 0x70  //! �J�i
            //, CONVERT       = 0x79  //! �ϊ�
            //, NOCONVERT     = 0x7B  //! ���ϊ�
            //, YEN           = 0x7D  //! '\'
            //, NUMPADEQUALS  = 0x8D  //! =(NumPad)
            //, CIRCUMFLEX    = 0x90  //! ^(�n�b�g)
            //, AT            = 0x91  //! @(�A�b�g�}�[�N)
            //, COLON         = 0x92  //! :(�R����)
            //, UNDERLINE     = 0x93  //! _(�A���_�[���C��)
            //, KANJI         = 0x94  //! ����
            //, STOP          = 0x95  //! Stop
            //, AX            = 0x96  //! JapanAX
            //, UNLABELED     = 0x97  //! J3100
            , NUMPADENTER   = 0x9C  //! Enter(NumPad)
            , RCONTROL      = 0x9D  //! Ctrl(�E��)
            //, NUMPADCOMMA   = 0xB3  //! ,(NumPad)
            //, DIVIDE        = 0xB5  //! /(NumPad)
            //, SYSRQ         = 0xB7  //! SysRq
            //, RMENU         = 0xB8  //! Alt(�E��)
            //, PAUSE         = 0xC5  //! Pause
            //, HOME          = 0xC7  //! Home
            , UP            = 0xC8  //! ��
            //, PRIOR         = 0xC9  //! PageUp
            , LEFT          = 0xCB  //! ��
            , RIGHT         = 0xCD  //! ��
            //, END           = 0xCF  //! End
            , DOWN          = 0xD0  //! ��
            //, NEXT          = 0xD1  //! PageDown
            //, INSERT        = 0xD2  //! Insert
            //, DELETE        = 0xD3  //! Delete
            //, LWIN          = 0xDB  //! Windows
            //, RWIN          = 0xDC  //! Windows
            //, APPS          = 0xDD  //! Menu
            //, POWER         = 0xDE  //! Power
            //, SLEEP         = 0xDE  //! Windows
        };
    }

    /*!
     *  @brief      vivid::mouse���O���
     */
    namespace mouse
    {
        /*!
         *  @brief      �}�E�X�{�^��ID<br>
         *              �N���b�N����Ŏg�p�\�ȃ{�^��ID
         */
        enum class BUTTON_ID
        {
              LEFT    = MOUSE_INPUT_LEFT      //! ���{�^��
            , RIGHT   = MOUSE_INPUT_RIGHT     //! �E�{�^��
            , MIDDLE  = MOUSE_INPUT_MIDDLE    //! ���{�^��
        };
    }

    /*!
     *  @brief      vivid::controller���O���
     */
    namespace controller
    {
        /*!
         *  @brief      �f�o�C�XID
         */
        enum class DEVICE_ID
        {
              PLAYER1       //! 1P�W���C�p�b�h
            , PLAYER2       //! 2P�W���C�p�b�h
            , PLAYER3       //! 3P�W���C�p�b�h
            , PLAYER4       //! 4P�W���C�p�b�h
            , MAX           //! �ő�f�o�C�X��
        };

        /*!
         *  @brief      �{�^��ID
         */
        enum class BUTTON_ID
        {
              UP              = XINPUT_BUTTON_DPAD_UP         //! �{�^����
            , DOWN            = XINPUT_BUTTON_DPAD_DOWN       //! �{�^����
            , LEFT            = XINPUT_BUTTON_DPAD_LEFT       //! �{�^����
            , RIGHT           = XINPUT_BUTTON_DPAD_RIGHT      //! �{�^���E
            , START           = XINPUT_BUTTON_START           //! START�{�^��
            , BACK            = XINPUT_BUTTON_BACK            //! BACK�{�^��
            , LEFT_THUMB      = XINPUT_BUTTON_LEFT_THUMB      //! ���X�e�B�b�N��������
            , RIGHT_THUMB     = XINPUT_BUTTON_RIGHT_THUMB     //! �E�X�e�B�b�N��������
            , LEFT_SHOULDER   = XINPUT_BUTTON_LEFT_SHOULDER   //! LB�{�^��
            , RIGHT_SHOULDER  = XINPUT_BUTTON_RIGHT_SHOULDER  //! RB�{�^��
            , A               = XINPUT_BUTTON_A               //! A�{�^��
            , B               = XINPUT_BUTTON_B               //! B�{�^��
            , X               = XINPUT_BUTTON_X               //! X�{�^��
            , Y               = XINPUT_BUTTON_Y               //! Y�{�^��
        };
    }
    /*!
     *  @brief      �A���t�@�u�����hID��`
     */
    enum class ALPHABLEND
    {
        NOBELEND = DX_BLENDMODE_NOBLEND,     //! �u�����h�Ȃ�
        ALPHA    = DX_BLENDMODE_ALPHA,       //! ������
        ADD      = DX_BLENDMODE_ADD,         //! ���Z����
        SUB      = DX_BLENDMODE_SUB,         //! ���Z����
        INVSRC   = DX_BLENDMODE_INVSRC,      //! ���]����
    };

    /*!
     *  @brief      �`��p�֐��|�C���^�^
     */
//    typedef void(*DISPLAY_FUNC)(void);
    using DISPLAY_FUNC = void (*)(void);

    /*!
     *  @brief      �񎟌��x�N�g���N���X
     */
    class Vector2
    {
    public:
        float x;    //! X����
        float y;    //! Y����

        /*!
         *  @brief  �R���X�g���N�^
         */
        Vector2(void);

        /*!
         *  @brief  �R���X�g���N�^
         *
         *  @param[in]  x   X����
         *  @param[in]  y   Y����
         */
        Vector2(float x, float y);

        /*!
         *  @brief  �R���X�g���N�^
         *
         *  @param[in]  v  �x�N�g��
         */
        Vector2(const Vector2& v);

        /*!
         *  @brief  �f�X�g���N�^
         */
        ~Vector2(void);

        /*!
         *  @brief      �x�N�g���̐��K��<br>
         *              ���g�̃x�N�g�������K�������
         *
         *  @return     ���K�����ꂽ�x�N�g��
         */
        Vector2            Normalize(void);

        /*!
         *  @brief      �x�N�g���̐��K��
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     ���K�����ꂽ�x�N�g��
         */
        static Vector2     Normalize(const Vector2& v);

        /*!
         *  @brief      �x�N�g���̑傫���擾
         *
         *  @return     �x�N�g���̑傫��
         */
        float               Length(void);

        /*!
         *  @brief      �x�N�g���̑傫���擾
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���̑傫��
         */
        static float        Length(const Vector2& v);

        /*!
         *  @brief      2�̃x�N�g���̓���<br>
         *              dot = vA�EvB
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     ����
         */
        static float        Dot(const Vector2& vA, const Vector2& vB);

        /*!
         *  @brief      2�̃x�N�g���̊O��<br>
         *              cross = vA�~vB
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �O��
         */
        static float        Cross(const Vector2& vA, const Vector2& vB);

        /*!
         *  @brief      ������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        Vector2&           operator=(const Vector2& v);

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        Vector2&           operator+=(const Vector2& v);

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        Vector2&           operator-=(const Vector2& v);

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  scalar  �X�J���[�l
         *
         *  @return     �x�N�g���N���X
         */
        Vector2&           operator*=(float scalar);

        /*!
         *  @brief      �������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     ��̃x�N�g����������
         *  @retval     true    ������
         *  @retval     false   �������Ȃ�
         */
        bool                operator==(const Vector2& v) const;

        /*!
         *  @brief      �s�����Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     ��̃x�N�g�����������Ȃ�
         *  @retval     true    �������Ȃ�
         *  @retval     false   ������
         */
        bool                operator!=(const Vector2& v) const;

        /*!
         *  @brief      ���������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend Vector2     operator+(const Vector2& v);

        /*!
         *  @brief      ���������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend Vector2     operator-(const Vector2& v);

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend Vector2     operator+(const Vector2& vA, const Vector2& vB);

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend Vector2     operator-(const Vector2& vA, const Vector2& vB);

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend Vector2     operator*(const Vector2& vA, const Vector2& vB);

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v       �x�N�g���N���X
         *  @param[in]  scalar  �X�J���[�l
         *
         *  @return     �x�N�g���N���X
         */
        friend Vector2     operator*(const Vector2& v, float scalar);

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  scalar  �X�J���[�l
         *  @param[in]  v       �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend Vector2     operator*(float scalar, const Vector2& v);

        static const Vector2   ZERO;   //! ���������ׂ�0�̃x�N�g��
        static const Vector2   ONE;    //! ���������ׂ�1�̃x�N�g��
    };

    /*!
     *  @brief      ���������Z�q�̃I�[�o�[���[�h
     *
     *  @param[in]  v   �x�N�g���N���X
     *
     *  @return     �x�N�g���N���X
     */
    Vector2     operator+(const Vector2& v);

    /*!
     *  @brief      ���������Z�q�̃I�[�o�[���[�h
     *
     *  @param[in]  v   �x�N�g���N���X
     *
     *  @return     �x�N�g���N���X
     */
    Vector2     operator-(const Vector2& v);

    /*!
     *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
     *
     *  @param[in]  vA  �x�N�g���N���X
     *  @param[in]  vB  �x�N�g���N���X
     *
     *  @return     �x�N�g���N���X
     */
    Vector2     operator+(const Vector2& vA, const Vector2& vB);

    /*!
     *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
     *
     *  @param[in]  vA  �x�N�g���N���X
     *  @param[in]  vB  �x�N�g���N���X
     *
     *  @return     �x�N�g���N���X
     */
    Vector2     operator-(const Vector2& vA, const Vector2& vB);

    /*!
     *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
     *
     *  @param[in]  vA  �x�N�g���N���X
     *  @param[in]  vB  �x�N�g���N���X
     *
     *  @return     �x�N�g���N���X
     */
    Vector2     operator*(const Vector2& vA, const Vector2& vB);

    /*!
     *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
     *
     *  @param[in]  v       �x�N�g���N���X
     *  @param[in]  scalar  �X�J���[�l
     *
     *  @return     �x�N�g���N���X
     */
    Vector2     operator*(const Vector2& v, float scalar);

    /*!
     *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
     *
     *  @param[in]  scalar  �X�J���[�l
     *  @param[in]  v       �x�N�g���N���X
     *
     *  @return     �x�N�g���N���X
     */
    Vector2     operator*(float scalar, const Vector2& v);

    /*!
     *  @brief      �|�C���g�\����
     */
    struct Point
    {
        int x;          //! X���W
        int y;          //! Y���W
    };

    /*!
     *  @brief      ��`�\����
     */
    struct Rect
    {
        int left;       //! ���[
        int top;        //! ��[
        int right;      //! �E�[
        int bottom;     //! ���[
    };
    /*!
     *  @brief      �Đ��G�t�F�N�g�\���� s.kosugi
     */
    struct PLAYEFFECT_DATA
    {
        int handle;             //! �Đ��n���h��
        vivid::Vector2 pos;     //! �G�t�F�N�g�ʒu

        /*!
         *  @brief  �R���X�g���N�^
         */
        PLAYEFFECT_DATA(void);
    };

    /*!
     *  @brief      ������
     *
     *  @param[in]  hInst       �C���X�^���X�n���h��
     */
    void    Initialize(HINSTANCE hInst);

    /*!
     *  @brief      �`��֐��o�^
     *
     *  @param[in]  display     �`��p�֐�
     */
    void    DisplayFunction(DISPLAY_FUNC display);

    /*!
     *  @brief      ��ʓ]��
     */
    void    MainLoop(void);

    /*!
     *  @brief      ���
     */
    void    Finalize(void);

    /*!
     *  @brief      �E�B���h�E�̉����擾
     *
     *  @return     �E�B���h�E�̉���
     */
    int     GetWindowWidth(void);

    /*!
     *  @brief      �E�B���h�E�̏c���擾
     *
     *  @return     �E�B���h�E�̏c��
     */
    int     GetWindowHeight(void);

    /*!
     *  @brief      �f���^�^�C���擾
     *              �f���^�^�C���͑O��̍X�V����ǂꂭ�炢�̎��Ԃ��o�߂������̒l
     *
     *  @return     �f���^�^�C��
     */
    float   GetDeltaTime(void);

    /*!
     *  @brief      �f���^�^�C��(�^�C���X�P�[���Ȃ�)�擾
     *              �f���^�^�C���͑O��̍X�V����ǂꂭ�炢�̎��Ԃ��o�߂������̒l
     *
     *  @return     �f���^�^�C��
     */
    float   GetUnscaledDeltaTime(void);

    /*!
     *  @brief      �f���^�^�C���{���擾
     *
     *  @return     �f���^�^�C���{��
     */
    float   GetDeltaTimeScale(void);

    /*!
     *  @brief      �f���^�^�C���{���ݒ�
     *
     *  @param[in]  scale   �f���^�^�C���{��
     */
    void    SetDeltaTimeScale(float scale);

    /*!
     *  @brief      ���݂�FPS�擾
     *
     *  @return     ���݂�FPS
     */
    float   GetFPS(void);

    /*!
     *  @brief      �t���[�����[�g�̐ݒ�
     *
     *  @param[int] frame_rate  �t���[�����[�g
     */
    void    SetFrameRate(int fram_rate);

    /*!
     *  @brief      �e�N�X�`���ǂݍ���
     *
     *  @param[in]  file_name   �t�@�C����
     */
    void    LoadTexture(const std::string& file_name);

    /*!
     *  @brief      �e�N�X�`���`��
     *
     *  @param[in]  file_name   �t�@�C����
     *  @param[in]  position    �\���ʒu
     */
    void    DrawTexture(const std::string& file_name, const Vector2& position);

    /*!
     *  @brief      �e�N�X�`���`��
     *
     *  @param[in]  file_name   �t�@�C����
     *  @param[in]  position    �\���ʒu
     *  @param[in]  color       �F
     */
    void    DrawTexture(const std::string& file_name, const Vector2& position, unsigned int color);

    /*!
     *  @brief      �e�N�X�`���`��
     *
     *  @param[in]  file_name   �t�@�C����
     *  @param[in]  position    �\���ʒu
     *  @param[in]  color       �F
     *  @param[in]  rect        �ǂݍ��ݔ͈�
     */
    void    DrawTexture(const std::string& file_name, const Vector2& position, unsigned int color, const Rect& rect);

    /*!
     *  @brief      �e�N�X�`���`��
     *
     *  @param[in]  file_name   �t�@�C����
     *  @param[in]  position    �\���ʒu
     *  @param[in]  color       �F
     *  @param[in]  rect        �ǂݍ��ݔ͈�
     *  @param[in]  anchor      �g��E��]�̊�_
     *  @param[in]  scale       �g�嗦
     */
    void    DrawTexture(const std::string& file_name, const Vector2& position, unsigned int color, const Rect& rect, const Vector2& anchor, const Vector2& scale);

    /*!
     *  @brief      �e�N�X�`���`��
     *
     *  @param[in]  file_name   �t�@�C����
     *  @param[in]  position    �\���ʒu
     *  @param[in]  color       �F
     *  @param[in]  rect        �ǂݍ��ݔ͈�
     *  @param[in]  anchor      �g��E��]�̊�_
     *  @param[in]  rotation    ��]�l(���W�A��)
     */
    void    DrawTexture(const std::string& file_name, const Vector2& position, unsigned int color, const Rect& rect, const Vector2& anchor, float rotation);

    /*!
     *  @brief      �e�N�X�`���`��
     *
     *  @param[in]  file_name   �t�@�C����
     *  @param[in]  position    �\���ʒu
     *  @param[in]  color       �F
     *  @param[in]  rect        �ǂݍ��ݔ͈�
     *  @param[in]  anchor      �g��E��]�̊�_
     *  @param[in]  scale       �g�嗦
     *  @param[in]  rotation    ��]�l(���W�A��)
     */
    void    DrawTexture(const std::string& file_name, const Vector2& position, unsigned int color, const Rect& rect, const Vector2& anchor, const Vector2& scale, float rotation);

    /*!
     *  @brief      �e�N�X�`���`��
     *
     *  @param[in]  file_name   �t�@�C����
     *  @param[in]  position    �\���ʒu
     *  @param[in]  color       �F
     *  @param[in]  rect        �ǂݍ��ݔ͈�
     *  @param[in]  anchor      �g��E��]�̊�_
     *  @param[in]  scale       �g�嗦
     *  @param[in]  rotation    ��]�l(���W�A��)
     *  @param[in]  blend_mode  �A���t�@�u�����h���[�h
     */
    void    DrawTexture(const std::string& file_name, const Vector2& position, unsigned int color, const Rect& rect, const Vector2& anchor, const Vector2& scale, float rotation, ALPHABLEND blend_mode);

    /*!
     *  @brief      �e�N�X�`���̕����擾
     *
     *  @param[in]  file_name   �t�@�C����
     */
    int     GetTextureWidth(const std::string& file_name);

    /*!
     *  @brief      �e�N�X�`���̍������擾
     *
     *  @param[in]  file_name   �t�@�C����
     */
    int     GetTextureHeight(const std::string& file_name);

    /*!
     *  @brief      �t�H���g�̐���
     *
     *  @param[in]  size            �t�H���g�T�C�Y
     */
    void    CreateFont(int size);

    /*!
     *  @brief      �t�H���g�̐���
     *
     *  @param[in]  size            �t�H���g�T�C�Y
     *  @param[in]  edge_size       �G�b�W�T�C�Y
     */
    void    CreateFont(int size, int edge_size);

    /*!
     *  @brief      �e�L�X�g�`��
     *
     *  @param[in]  size        �t�H���g�T�C�Y
     *  @param[in]  text        �e�L�X�g
     *  @param[in]  position    �\���ʒu
     */
    void    DrawText(int size, const std::string& text, const Vector2& position);

    /*!
     *  @brief      �e�L�X�g�`��
     *
     *  @param[in]  size        �t�H���g�T�C�Y
     *  @param[in]  text        �e�L�X�g
     *  @param[in]  position    �\���ʒu
     *  @param[in]  color       �����F
     */
    void    DrawText(int size, const std::string& text, const Vector2& position, unsigned int color);

    /*!
     *  @brief      �e�L�X�g�`��
     *
     *  @param[in]  size        �t�H���g�T�C�Y
     *  @param[in]  text        �e�L�X�g
     *  @param[in]  position    �\���ʒu
     *  @param[in]  color       �����F
     *  @param[in]  edge_color  �G�b�W�̐F
     */
    void    DrawText(int size, const std::string& text, const Vector2& position, unsigned int color, unsigned int edge_color);

    /*!
     *  @brief      �e�L�X�g�`��
     *
     *  @param[in]  size        �t�H���g�T�C�Y
     *  @param[in]  text        �e�L�X�g
     *  @param[in]  position    �\���ʒu
     *  @param[in]  color       �����F
     *  @param[in]  blend_mode  �A���t�@�u�����h���[�h
     */
    void    DrawText(int size, const std::string& text, const Vector2& position, unsigned int color, ALPHABLEND blend_mode);

    /*!
     *  @brief      �e�L�X�g�`��
     *
     *  @param[in]  size        �t�H���g�T�C�Y
     *  @param[in]  text        �e�L�X�g
     *  @param[in]  position    �\���ʒu
     *  @param[in]  color       �����F
     *  @param[in]  edge_color  �G�b�W�̐F
     *  @param[in]  blend_mode  �A���t�@�u�����h���[�h
     */
    void    DrawText(int size, const std::string& text, const Vector2& position, unsigned int color, unsigned int edge_color, ALPHABLEND blend_mode);

    /*!
     *  @brief      �e�L�X�g�̕����擾
     *
     *  @param[in]  size        �t�H���g�T�C�Y
     *  @param[in]  text        �e�L�X�g
     */
    int     GetTextWidth(int size, const std::string& text);

    /*!
     *  @brief      vivid::keyboard���O���
     */
    namespace keyboard
    {
        /*!
         *  @brief      �{�^�����͔���
         *
         *  @param[in]  key  �L�[ID
         *
         *  @return     ������Ă����true��Ԃ�
         */
        bool    Button(KEY_ID key);

        /*!
         *  @brief      �g���K�[���͔���
         *
         *  @param[in]  key  �L�[ID
         *
         *  @return     �����ꂽ�u�Ԃ���true��Ԃ�
         */
        bool    Trigger(KEY_ID key);

        /*!
         *  @brief      �����[�X�h���͔���
         *
         *  @param[in]  key  �L�[ID
         *
         *  @return     �����ꂽ�u�Ԃ���true��Ԃ�
         */
        bool    Released(KEY_ID key);
    }

    /*!
     *  @brief      vivid::mouse���O���
     */
    namespace mouse
    {
        /*!
         *  @brief      �{�^�����͔���
         *
         *  @param[in]  button  �{�^��ID
         *
         *  @return     ������Ă����true��Ԃ�
         */
        bool    Button(BUTTON_ID button);

        /*!
         *  @brief      �g���K�[���͔���
         *
         *  @param[in]  button  �{�^��ID
         *
         *  @return     �����ꂽ�u�Ԃ���true��Ԃ�
         */
        bool    Trigger(BUTTON_ID button);

        /*!
         *  @brief      �����[�X�h���͔���
         *
         *  @param[in]  button  �{�^��ID
         *
         *  @return     �����ꂽ�u�Ԃ���true��Ԃ�
         */
        bool    Released(BUTTON_ID button);

        /*!
         *  @brief      �}�E�X�J�[�\���̍��W�擾
         *
         *  @return     �}�E�X�J�[�\�����W
         */
        Point   GetCursorPos(void);

        /*!
         *  @brief      �}�E�X�z�C�[���l�擾
         *
         *  @return     �z�C�[���l
         *  @retval     ���̐�     ���Ƀz�C�[�����ꂽ
         *  @retval     ���̐�     ��O�Ƀz�C�[�����ꂽ
         *  @retval     0          �z�C�[������Ă��Ȃ�
         */
        int     GetWheel(void);
    }

    /*!
     *  @brief      vivid::controller���O���
     */
    namespace controller
    {
        /*!
         *  @brief      �{�^�����͔���
         *
         *  @param[in]  device  �f�o�C�XID
         *  @param[in]  button  �{�^��ID
         *
         *  @return     ������Ă����true��Ԃ�
         */
        bool    Button(DEVICE_ID device, BUTTON_ID button );

        /*!
         *  @brief      �g���K�[���͔���
         *
         *  @param[in]  device  �f�o�C�XID
         *  @param[in]  button  �{�^��ID
         *
         *  @return     �����ꂽ�u�Ԃ���true��Ԃ�
         */
        bool    Trigger(DEVICE_ID device, BUTTON_ID button);

        /*!
         *  @brief      �����[�X�h���͔���
         *
         *  @param[in]  device  �f�o�C�XID
         *  @param[in]  button  �{�^��ID
         *
         *  @return     �����ꂽ�u�Ԃ���true��Ԃ�
         */
        bool    Released(DEVICE_ID device, BUTTON_ID button);

        /*!
         *  @brief      ���A�i���O�X�e�B�b�N�擾
         *
         *  @param[in]  device      �f�o�C�XID
         *
         *  @return     ���A�i���O�X�e�B�b�N�̏��(-1.0f�`1.0f)
         */
        vivid::Vector2  GetAnalogStickLeft(DEVICE_ID device);

        /*!
         *  @brief      �E�A�i���O�X�e�B�b�N�擾
         *
         *  @param[in]  device      �f�o�C�XID
         *
         *  @return     �E�A�i���O�X�e�B�b�N�̏��(-1.0f�`1.0f)
         */
        vivid::Vector2  GetAnalogStickRight(DEVICE_ID device);

        /*!
         *  @brief      ���g���K�[�擾
         *
         *  @param[in]  device      �f�o�C�XID
         *
         *  @return     ���g���K�[�̏��(0.0f�`1.0f)
         */
        float           GetTriggerLeft(DEVICE_ID device);

        /*!
         *  @brief      �E�g���K�[�擾
         *
         *  @param[in]  device      �f�o�C�XID
         *
         *  @return     �E�g���K�[�̏��(0.0f�`1.0f)
         */
        float           GetTriggerRight(DEVICE_ID device);

        /*!
         *  @brief      �o�C�u���[�V�����̊J�n
         *
         *  @param[in]  device      �f�o�C�XID
         *  @param[in]  power       �U���̋���(0�`1000)
         *  @param[in]  time        �U�����鎞��(�b�P��)
         */
        void            StartVibration(DEVICE_ID device, int power, float time);

        /*!
         *  @brief      �ڑ����擾
         *
         *  @return     �ڑ���
         */
        int             GetConnectCount(void);
    }

    /*!
     *  @brief      �T�E���h�t�@�C���̓ǂݍ���
     *
     *  @param[in]  file_name   �t�@�C����
     */
    void    LoadSound(const std::string& file_name);

    /*!
     *  @brief      �T�E���h�Đ�
     *
     *  @param[in]  file_name   �t�@�C����
     *  @param[in]  loop        ���[�v�Đ�
     */
    void    PlaySound(const std::string& file_name, bool loop);

    /*!
     *  @brief      �T�E���h��~
     *
     *  @param[in]  file_name   �t�@�C����
     */
    void    StopSound(const std::string& file_name);

    /*!
     *  @brief      vivid::core���O���
     */
    namespace core
    {
        /*!
         *  @brief      �X�V����t���[���J�E���g�̌v�Z
         */
        void    CalcFrameCount(void);

        /*!
         *  @brief      �X�V�t���[���̑ҋ@����
         */
        void    FrameSync(void);

        /*!
         *  @brief      �X�N���[���V���b�g�̎B�e
         */
        void    ScreenShot(void);

        /*!
         *  @brief      �A�T�[�g����
         *              �Q�[����ʏo�͗p
         *
         *  @param[in]  result      �����⌋�ʂ�n���Bfalse�ɂȂ�ƃA�T�[�g����������
         *  @param[in]  message     �G���[���b�Z�[�W
         *  @param[in]  file        �t�@�C����
         *  @param[in]  line        �s�ԍ�
         */
        void    Assert(bool result, const std::string& message, const std::string& file, int line);

        /*!
         *  @brief      �ǂݍ��ݍς݂̃e�N�X�`������
         *
         *  @param[in]  file_name   �t�@�C����
         */
        int     FindLoadedTexture(const std::string& file_name);

        /*!
         *  @brief      �ǂݍ��ݍς݂̃T�E���h����
         *
         *  @param[in]  file_name   �t�@�C����
         */
        int     FindLoadedSound(const std::string& file_name);

        /*!
         *  @brief      �����ς݂̃t�H���g����
         *
         *  @param[in]  size        �t�H���g�T�C�Y
         */
        int     FindCreatedFont(int size);
    }

    /*!
     *  @brief      vivid::effekseer���O���
     *  @author     s.kosugi
     */
    namespace effekseer
    {
        /*!
         *  @brief      �G�t�F�N�V�A���C�u�����̏�����
         *
         *  @return     ����I��:0  �G���[:-1
         */
        int InitEffekseer(void);

        /*!
         *  @brief      �G�t�F�N�g�t�@�C���ǂݍ���
         *
         *  @param[in]  file_name   �t�@�C����
         *
         *  @return     ����I��:0  �G���[:-1
         */
        int LoadEffect(const std::string& file_name);

        /*!
         *  @brief      �G�t�F�N�g�̍Đ��J�n
         *              ��������ƃG�t�F�N�g�n���h�����Ԃ�
         *
         *  @param[in]  file_name   �t�@�C����
         *  @param[in]  pos         �Đ��ʒu
         *
         *  @return     �G���[:-1   ����I��:����ȊO
         */
        int StartEffect(const std::string& file_name, const vivid::Vector2& pos);

        /*!
         *  @brief      �G�t�F�N�g�̍Đ��J�n
         *              ��������ƃG�t�F�N�g�n���h�����Ԃ�
         *
         *  @param[in]  file_name   �t�@�C����
         *  @param[in]  pos         �Đ��ʒu
         *  @param[in]  scale       �g�嗦
         *
         *  @return     �G���[:-1   ����I��:����ȊO
         */
        int StartEffect(const std::string& file_name, const vivid::Vector2& pos,float scale);

        /*!
         *  @brief      �G�t�F�N�g�̕`��
         *
         *  @param[in]  handle      �G�t�F�N�g�̍Đ��n���h��
         *  @param[in]  pos         �G�t�F�N�g�̍Đ��ʒu
         *
         *  @return     �`�搬��:true  �Đ��I����:false
         */
        bool DrawEffect(const int handle, const vivid::Vector2& pos);

        /*!
         *  @brief      �G�t�F�N�g�̍Đ��I���`�F�b�N
         *
         *  @param[in]  handle      �G�t�F�N�g�̍Đ��n���h��
         *
         *  @return     �Đ���:true  �Đ��I��:false
         */
        bool IsEffectPlaying(const int handle);

        /*!
         *  @brief      �Đ����X�g����G�t�F�N�g�S�`��
         *
         */
        void DrawEffectList(void);

        /*!
         *  @brief      �G�t�F�N�g���X�g����S�`������邩�ǂ���
         *
         *  @param[in]  flag        �`�悷�� : true  �`�悵�Ȃ� : false
         *
         */
        void SetUseEffectListFlag(bool flag);
    }
}
