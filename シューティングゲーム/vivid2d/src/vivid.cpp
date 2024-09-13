
/*!
 *  @file       vivid.cpp
 *  @brief      Vivid2D Library
 *  @author     Kazuya Maruyama
 *  @date       2020/11/25
 *  @version    2.7
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. Shinya Kosugi. All rights reserved.
 */

#pragma comment( lib, "imm32.lib" )
#pragma comment( lib, "Shlwapi.lib" )

#include "vivid.h"
#include <imm.h>
#include <shlwapi.h>
#include <map>
#include <list>
#include <iomanip>
#include <sstream>

#pragma warning(disable: 4100)      // effekseer.h�̌x����� s.kosugi
#include <EffekseerForDXLib.h>      // effekseer���C�u�����̓ǂݍ��� s.kosugi

 /*!
  *  @brief      vivid���O���
  */
namespace vivid
{
    /*!
     *  @brief      vivid::core���O���
     */
    namespace core
    {
        static const int            g_window_width                  = WINDOW_WIDTH;                         //!< �E�B���h�E�̉���
        static const int            g_window_height                 = WINDOW_HEIGHT;                        //!< �E�B���h�E�̏c��
        static const char*          g_class_name                    = "vivid2D 2.7 with Effekseer";         //!< �N���X�l�[��
        static const int            g_color_bit                     = 32;                                   //!< �J���[�r�b�g
        static const unsigned int   g_button_state_num              = 9;                                    //!< ���͔���p�{�^����
        static const unsigned int   g_max_key_count                 = 256;                                  //!< �{�^���̍ő吔
        static const float          g_one_millisecond               = 1000.0f;                              //!< 1�~���b
        static const float          g_max_delta_time                = 0.16f;                                //!< �ő�f���^�^�C��
        static const float          g_default_delta_time_scale      = 1.0f;                                 //!< �����̃f���^�^�C���X�P�[��
        static const int            g_default_frame_rate            = 60;                                   //!< �f�t�H���g�̃t���[�����[�g
        static const int            g_calc_frame_count              = 60;                                   //!< ���ς��v�Z����t���[���̐�
        static const int            g_limit_cant_analog             = 30000;                                //!< �A�i���O�X�e�B�b�N���͂̌��E�l
        static const int            g_max_trigger                   = 255;                                  //!< �g���K�[���͂̍ő�l
        static const int            g_analog_dead_zone              = 15000;                                //!< �A�i���O�X�e�B�b�N�̌������͈�
        HINSTANCE                   g_InstanceHandle                = NULL;                                 //!< �C���X�^���X�n���h��
        DISPLAY_FUNC                g_DisplayFunction               = nullptr;                              //!< �X�V�p�֐�
        int                         g_FrameRate                     = g_default_frame_rate;                 //!< �t���[�����[�g
        float                       g_Fps                           = 0.0f;                                 //!< ���݂�FPS
        int                         g_FrameCount                    = 0;                                    //!< �t���[���J�E���g
        int                         g_StartTime                     = 0;                                    //!< �t���[���v���J�n����
        int                         g_PrevTime                      = 0;                                    //!< 1�t���[���O�̎���
        float                       g_DeltaTime                     = 0.0f;                                 //!< �Q�[���X�V�p�f���^�^�C��
        float                       g_DeltaTimeScale                = g_default_delta_time_scale;           //!< �f���^�^�C���{��
        std::map<std::string, int>  g_TextureList;                                                          //!< �e�N�X�`�����X�g
        std::map<std::string, int>  g_SoundList;                                                            //!< �T�E���h���X�g
        std::map<int, int>          g_FontList;                                                             //!< �t�H���g���X�g
        char                        g_KeyState[g_max_key_count]     = { 0 };                                //!< ���̓f�[�^
        char                        g_PrevKeyState[g_max_key_count] = { 0 };                                //!< �O��̓��̓f�[�^
        int                         g_MouseState                    = 0;                                    //!< �}�E�X�̓��͏��
        int                         g_PrevMouseState                = 0;                                    //!< �O�̃}�E�X�̓��͏��
        std::map<std::string, int>  g_EffekseerList;                                                        //!< �G�t�F�N�g�ǂݍ��݃��X�g s.kosugi
        std::list<PLAYEFFECT_DATA>  g_EffectPlayList;                                                       //!< �G�t�F�N�g�S�Đ����X�g s.kosugi
        bool                        g_UseEffectListFlag             = true;                                 //!< �G�t�F�N�g���X�g�̑S�Đ����s�����ǂ��� s.kosugi
        XINPUT_STATE                g_ControllerState[static_cast<int>(controller::DEVICE_ID::MAX)];        //!< �R���g���[���[�̓��͏��
        XINPUT_STATE                g_PrevControllerState[static_cast<int>(controller::DEVICE_ID::MAX)];    //!< 1�t���[���O�̓��͏��

#ifdef VIVID_DEBUG
        bool                        g_DebugShowFps                  = true;                                 //!< �f�o�b�O�pFPS�\���t���O
#endif
    }
};

const vivid::Vector2 vivid::Vector2::ZERO = Vector2(0.0f, 0.0f);
const vivid::Vector2 vivid::Vector2::ONE  = Vector2(1.0f, 1.0f);

/*
 *  �R���X�g���N�^
 */
vivid::Vector2::
Vector2(void)
    : x(0.0f), y(0.0f)
{
}

/*
 *  �R���X�g���N�^
 */
vivid::Vector2::
Vector2(float x, float y)
    : x(x), y(y)
{
}

/*
 *  �R���X�g���N�^
 */
vivid::Vector2::
Vector2(const Vector2& v)
    : x(v.x), y(v.y)
{
}

/*
 *  �f�X�g���N�^
 */
vivid::Vector2::
~Vector2(void)
{
}

/*
 *  ���K��
 */
vivid::Vector2
vivid::Vector2::
Normalize(void)
{
    return Normalize(*this);
}

/*
 *  ���K��
 */
vivid::Vector2
vivid::Vector2::
Normalize(const Vector2& v)
{
    Vector2 t = v;

    float inv = 1.0f / t.Length();

    t.x *= inv;
    t.y *= inv;

    return t;
}

/*
 *  �x�N�g���̑傫���擾
 */
float
vivid::Vector2::
Length(void)
{
    return Length(*this);
}

/*
 *  �x�N�g���̑傫���擾
 */
float
vivid::Vector2::
Length(const Vector2& v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

/*
 *  ����
 */
float
vivid::Vector2::
Dot(const Vector2& vA, const Vector2& vB)
{
    return (vA.x * vB.x + vA.y * vB.y);
}

/*
 *  �O��
 */
float
vivid::Vector2::
Cross(const Vector2& vA, const Vector2& vB)
{
    return (vA.x * vB.y) - (vA.y * vB.x);
}

/*
 *  ������Z�q�̃I�[�o�[���[�h
 */
vivid::Vector2&
vivid::Vector2::
operator=(const Vector2& v)
{
    x = v.x;
    y = v.y;

    return *this;
}

/*
 *  ���Z���Z�q�̃I�[�o�[���[�h
 */
vivid::Vector2&
vivid::Vector2::
operator+=(const Vector2& v)
{
    x += v.x;
    y += v.y;

    return *this;
}

/*
 *  ���Z���Z�q�̃I�[�o�[���[�h
 */
vivid::Vector2&
vivid::Vector2::
operator-=(const Vector2& v)
{
    x -= v.x;
    y -= v.y;

    return *this;
}

/*
 *  ��Z���Z�q�̃I�[�o�[���[�h
 */
vivid::Vector2&
vivid::Vector2::
operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

/*
 *  �������Z�q�̃I�[�o�[���[�h
 */
bool
vivid::Vector2::
operator==(const Vector2& v) const
{
    return (x == v.x && y == v.y);
}

/*
 *  �s�����Z�q�̃I�[�o�[���[�h
 */
bool
vivid::Vector2::
operator!=(const Vector2& v) const
{
    return (x != v.x || y != v.y);
}

/*
 *  ���������Z�q�̃I�[�o�[���[�h
 */
vivid::Vector2
vivid::operator+(const vivid::Vector2& v)
{
    return v;
}

/*
 *  ���������Z�q�̃I�[�o�[���[�h
 */
vivid::Vector2
vivid::operator-(const vivid::Vector2& v)
{
    return vivid::Vector2(-v.x, -v.y);
}

/*
 *  ���Z���Z�q�̃I�[�o�[���[�h
 */
vivid::Vector2
vivid::operator+(const vivid::Vector2& vA, const vivid::Vector2& vB)
{
    return vivid::Vector2(vA.x + vB.x, vA.y + vB.y);
}

/*
 *  ���Z���Z�q�̃I�[�o�[���[�h
 */
vivid::Vector2
vivid::operator-(const vivid::Vector2& vA, const vivid::Vector2& vB)
{
    return vivid::Vector2(vA.x - vB.x, vA.y - vB.y);
}

/*
 *  ��Z���Z�q�̃I�[�o�[���[�h
 */
vivid::Vector2
vivid::operator*(const vivid::Vector2& vA, const vivid::Vector2& vB)
{
    return vivid::Vector2(vA.x * vB.x, vA.y * vB.y);
}

/*
 *  ��Z���Z�q�̃I�[�o�[���[�h
 */
vivid::Vector2
vivid::operator*(const vivid::Vector2& v, float scalar)
{
    return vivid::Vector2(v.x * scalar, v.y * scalar);
}

/*
 *  ��Z���Z�q�̃I�[�o�[���[�h
 */
vivid::Vector2
vivid::operator*(float scalar, const vivid::Vector2& v)
{
    return vivid::Vector2(v.x * scalar, v.y * scalar);
}

/*
 *  �R���X�g���N�^
 */
vivid::PLAYEFFECT_DATA::
PLAYEFFECT_DATA(void)
    : handle(0)
{
}

using namespace vivid::core;

/*
 * ������
 */
void
vivid::
Initialize(HINSTANCE hInst)
{
    // �C���X�^���X�n���h��
    g_InstanceHandle = hInst;

    // IME���֎~����
    ImmDisableIME(0xffffffff);

    // �����̏�����
    srand((unsigned int)time(NULL));

    // Log.txt�𐶐����Ȃ�
    SetOutApplicationLogValidFlag(FALSE);

    // �E�B���h�E����A�N�e�B�u�����X�V����
    SetAlwaysRunFlag(TRUE);

    // �E�B���h�E�e�L�X�g�̕ύX
    SetMainWindowText(g_class_name);

    // �o�b�N�o�b�t�@�T�C�Y�w��
    SetGraphMode(g_window_width, g_window_height, g_color_bit);

    // �E�B���h�E�T�C�Y�w��
    SetWindowSize(g_window_width, g_window_height);

    // �E�B���h�E���[�h�ŋN��
    ChangeWindowMode(TRUE);

    // DirectX11�̃o�[�W�������w�肷��
    if (SetUseDirect3DVersion(DX_DIRECT3D_11) == VIVID_DX_ERROR)
        return;

    // DX���C�u����������
    if (DxLib_Init() == VIVID_DX_ERROR)
        return;

    // �o�b�N�o�b�t�@�ɏ�������
    SetDrawScreen(DX_SCREEN_BACK);

    // �f�t�H���g�t�H���g���G�b�W�t���ɐݒ肷��
    ChangeFontType(DX_FONTTYPE_EDGE);

    // ���ߐF�w��(�}�[���^)
    SetTransColor(0xff, 0x00, 0xff);

    // �e�N�X�`�����X�g���N���A
    g_TextureList.clear();

    // �T�E���h���X�g���N���A
    g_SoundList.clear();

    // �t�H���g���X�g���N���A
    g_FontList.clear();

    // �R���g���[���[�̃X�e�[�g���N���A
    ZeroMemory(g_ControllerState, sizeof(XINPUT_STATE) * static_cast<int>(controller::DEVICE_ID::MAX));
    ZeroMemory(g_PrevControllerState, sizeof(XINPUT_STATE) * static_cast<int>(controller::DEVICE_ID::MAX));

    // �o�C�u���[�V�������g�p����
    SetUseJoypadVibrationFlag(TRUE);

    // �G�t�F�N�V�A�̏����� s.kosugi
    effekseer::InitEffekseer();

    // �G�t�F�N�g���X�g���N���A s.kosugi
    g_EffekseerList.clear();
    g_EffectPlayList.clear();
}

/*
 *  �`��֐��o�^
 */
void
vivid::
DisplayFunction(DISPLAY_FUNC display)
{
    // �֐��|�C���^��ۑ�
    g_DisplayFunction = display;
}

/*
 *  ���C�����[�v
 */
void
vivid::
MainLoop(void)
{
    // Windows����̖��߂�����
    while (ProcessMessage() != VIVID_DX_ERROR)
    {
        // �t���[���J�E���g�Z�o
        CalcFrameCount();

        // ���͏����X�V
        // �O��̃f�[�^�R�s�[
        memcpy(g_PrevKeyState, g_KeyState, g_max_key_count);

        // ���݂̓��͏��擾
        GetHitKeyStateAll(g_KeyState);

        // �O�̃t���[���̓��͏�Ԃ�ۑ�
        g_PrevMouseState = g_MouseState;

        // �}�E�X�̓��͏��擾
        g_MouseState = GetMouseInput();

        // �ڑ�����Ă���䐔�������A�R���g���[���[�̓��͏��擾
        for (int i = 0; i < controller::GetConnectCount(); ++i)
        {
            // 1�t���[���O�̏�Ԃ�ۑ�
            g_PrevControllerState[i] = g_ControllerState[i];

            // ���݂̓��͏�Ԃ��擾
            GetJoypadXInputState(i + DX_INPUT_PAD1, &g_ControllerState[i]);
        }

        // ��ʂ̔w�i�F��ݒ�
        SetBackgroundColor(0x80, 0x80, 0x80);

        // ��ʂ̃N���A
        ClearDrawScreen();

        // �X�V/�`��
        g_DisplayFunction();

        // effekseer���C�u�����̍X�V  s.kosugi
        UpdateEffekseer2D();
        // �G�t�F�N�g�̕`��  s.kosugi
        if (g_UseEffectListFlag)
            effekseer::DrawEffectList();

        // �X�N���[���V���b�g�̎B�e
        if (keyboard::Trigger(vivid::keyboard::KEY_ID::F9))
            ScreenShot();

#ifdef VIVID_DEBUG
        // FPS�̕\��/��\���؂�ւ�
        if (keyboard::Trigger(vivid::keyboard::KEY_ID::F6))
            g_DebugShowFps = !g_DebugShowFps;

        if (g_DebugShowFps)
        {
            std::stringstream fps;

            fps << "[FPS]" << std::fixed << std::setprecision(2) << GetFPS();

            int x = g_window_width - GetDrawStringWidth(fps.str().c_str(), (int)fps.str().length());

            DrawString(x, g_window_height - GetFontSize(), fps.str().c_str(), 0xff00ff00, 0xff004000);
        }
#endif
        // �o�b�N�o�b�t�@�̓]��
        ScreenFlip();

        // �t���[������
        FrameSync();

        // Esc�L�[�ŏI��
        if (keyboard::Trigger(vivid::keyboard::KEY_ID::ESCAPE))
            break;
    }
}

/*
 *  ���
 */
void
vivid::
Finalize(void)
{
    // ���ׂẴO���t�B�b�N�X�����
    InitGraph();

    // ���ׂẴt�H���g���������
    InitFontToHandle();

    // ���ׂẴT�E���h�����
    InitSoundMem();

    // �G�t�F�N�V�A���C�u�����̏I�� s.kosugi
    Effkseer_End();

    // DX���C�u�������
    DxLib_End();
}

/*
 *  �E�B���h�E�̉����擾
 */
int
vivid::
GetWindowWidth(void)
{
    return g_window_width;
}

/*
 *  �E�B���h�E�̏c���擾
 */
int
vivid::
GetWindowHeight(void)
{
    return g_window_height;
}

/*
 *  �f���^�^�C���擾
 */
float
vivid::
GetDeltaTime(void)
{
    return g_DeltaTime * g_DeltaTimeScale;
}

/*
 *  �f���^�^�C��(�{���Ȃ�)�擾
 */
float
vivid::
GetUnscaledDeltaTime(void)
{
    return g_DeltaTime;
}

/*
 *  �f���^�^�C���{���擾
 */
float
vivid::
GetDeltaTimeScale(void)
{
    return g_DeltaTimeScale;
}

/*
 *  �f���^�^�C���{���ݒ�
 */
void
vivid::
SetDeltaTimeScale(float scale)
{
    g_DeltaTimeScale = scale;
}

/*
 *  ���݂�FPS�擾
 */
float
vivid::
GetFPS(void)
{
    return g_Fps;
}

/*
 *  �t���[�����[�g�ݒ�
 */
void
vivid::
SetFrameRate(int frame_rate)
{
    g_FrameRate = frame_rate;
}

/*
 *  �e�N�X�`���ǂݍ���
 */
void
vivid::
LoadTexture(const std::string& file_name)
{
    // ���[�h�ς݂̃e�N�X�`������
    int texture = FindLoadedTexture(file_name);

    // �e�N�X�`������������
    if (texture != VIVID_DX_ERROR)
        return;

    // �e�N�X�`���̓ǂݍ���
    texture = LoadGraph(file_name.c_str());

    VIVID_DX_ASSERT(texture, file_name + "�̓ǂݍ��݂Ɏ��s���܂����B");

    // �e�N�X�`����o�^
    g_TextureList.insert(std::map<std::string, int>::value_type(file_name, texture));
}

/*
 *  �e�N�X�`���`��
 */
void
vivid::
DrawTexture(const std::string& file_name, const Vector2& position)
{
    DrawTexture(file_name, position, 0xffffffff);
}

/*
 *  �e�N�X�`���`��
 */
void
vivid::
DrawTexture(const std::string& file_name, const Vector2& position, unsigned int color)
{
    // �e�N�X�`��������
    int texture = FindLoadedTexture(file_name);

    // �e�N�X�`�����Ȃ�����΃��[�h����
    if (texture == VIVID_DX_ERROR)
    {
        LoadTexture(file_name);

        // ���[�h�ς݂̃e�N�X�`�����ēx����
        texture = FindLoadedTexture(file_name);
    }

    int width = 0, height = 0;

    // �e�N�X�`���̃T�C�Y�擾
    GetGraphSize(texture, &width, &height);

    vivid::Rect rect = { 0, 0, width, height };

    DrawTexture(file_name, position, color, rect);
}

/*
 *  �e�N�X�`���`��
 */
void
vivid::
DrawTexture(const std::string& file_name, const Vector2& position, unsigned int color, const Rect& rect)
{
    vivid::Vector2 anchor = { 0.0f, 0.0f };
    vivid::Vector2 scale = { 1.0f, 1.0f };

    DrawTexture(file_name, position, color, rect, anchor, scale);
}

/*
 *  �e�N�X�`���`��
 */
void
vivid::
DrawTexture(const std::string& file_name, const Vector2& position, unsigned int color, const Rect& rect, const Vector2& anchor, const Vector2& scale)
{
    DrawTexture(file_name, position, color, rect, anchor, scale, 0.0f);
}

/*
 *  �e�N�X�`���`��
 */
void
vivid::
DrawTexture(const std::string& file_name, const Vector2& position, unsigned int color, const Rect& rect, const Vector2& anchor, float rotation)
{
    vivid::Vector2 scale = { 1.0f, 1.0f };

    DrawTexture(file_name, position, color, rect, anchor, scale, rotation);
}

/*
 *  �e�N�X�`���`��
 */
void
vivid::
DrawTexture(const std::string& file_name, const Vector2& position, unsigned int color, const Rect& rect, const Vector2& anchor, const Vector2& scale, float rotation)
{
    DrawTexture(file_name, position, color, rect, anchor, scale, rotation, vivid::ALPHABLEND::ALPHA);
}

/*
 *  �e�N�X�`���`��
 */
void
vivid::
DrawTexture(const std::string& file_name, const Vector2& position, unsigned int color, const Rect& rect, const Vector2& anchor, const Vector2& scale, float rotation, ALPHABLEND blend_mode)
{
    // ���[�h�ς݂̃e�N�X�`��������
    int texture = FindLoadedTexture(file_name);

    // �e�N�X�`�����Ȃ���΃��[�h����
    if (texture == VIVID_DX_ERROR)
    {
        LoadTexture(file_name);

        texture = FindLoadedTexture(file_name);
    }

    // ���炩�ɕ`��
    SetDrawMode(DX_DRAWMODE_BILINEAR);

    // �A���t�@�u�����h�ݒ�
    SetDrawBlendMode(static_cast<int>(blend_mode), ((color & 0xff000000) >> 24));

    // �P�x�ݒ�
    SetDrawBright(((color & 0x00ff0000) >> 16), ((color & 0x0000ff00) >> 8), (color & 0x000000ff));

    // �`��
    DrawRectRotaGraph3F(position.x + anchor.x, position.y + anchor.y, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, anchor.x, anchor.y, scale.x, scale.y, rotation, texture, TRUE);

    // �P�x���f�t�H���g�ɖ߂�
    SetDrawBright(0xff, 0xff, 0xff);

    // �A���t�@�u�����h���[�h���f�t�H���g�ɖ߂�
    SetDrawBlendMode(static_cast<int>(vivid::ALPHABLEND::ALPHA), 0xff);
}

/*
 *  �e�N�X�`���̕����擾
 */
int
vivid::
GetTextureWidth(const std::string& file_name)
{
    // �e�N�X�`��������
    int texture = FindLoadedTexture(file_name);

    // �e�N�X�`����������Ȃ�����
    if (texture == VIVID_DX_ERROR)
        return 0;

    int width = 0, height = 0;

    // �O���t�B�b�N�T�C�Y�擾
    GetGraphSize(texture, &width, &height);

    return width;
}

/*
 *  �e�N�X�`���̍������擾
 */
int
vivid::
GetTextureHeight(const std::string& file_name)
{
    // �e�N�X�`��������
    int texture = FindLoadedTexture(file_name);

    // �e�N�X�`����������Ȃ�����
    if (texture == VIVID_DX_ERROR)
        return 0;

    int width = 0, height = 0;

    // �O���t�B�b�N�T�C�Y�擾
    GetGraphSize(texture, &width, &height);

    return height;
}

/*
 *  �t�H���g�̐���
 */
void
vivid::
CreateFont(int size)
{
    CreateFont(size, 0);
}

/*
 *  �t�H���g�̐���
 */
void
vivid::
CreateFont(int size, int edge_size)
{
    // �t�H���g������
    int font = FindCreatedFont(size);

    // �t�H���g����������
    if (font != VIVID_DX_ERROR)
        return;

    // �t�H���g����
    font = CreateFontToHandle("���C���I", size, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, edge_size);

    VIVID_DX_ASSERT(font, "�t�H���g�̐����Ɏ��s���܂����B");

    // �t�H���g��o�^
    g_FontList.insert(std::map<int, int>::value_type(size, font));
}

/*
 *  �e�L�X�g�`��
 */
void
vivid::
DrawText(int size, const std::string& text, const Vector2& position)
{
    DrawText(size, text, position, 0xffffffff);
}

/*
 *  �e�L�X�g�`��
 */
void
vivid::
DrawText(int size, const std::string& text, const Vector2& position, unsigned int color)
{
    DrawText(size, text, position, color, 0xff000000);
}

/*
 *  �e�L�X�g�`��
 */
void
vivid::
DrawText(int size, const std::string& text, const Vector2& position, unsigned int color, unsigned int edge_color)
{
    DrawText(size, text, position, color, edge_color, vivid::ALPHABLEND::ALPHA);
}

/*
 *  �e�L�X�g�`��
 */
void
vivid::
DrawText(int size, const std::string& text, const Vector2& position, unsigned int color, ALPHABLEND blend_mode)
{
    DrawText(size, text, position, color, 0xff000000, blend_mode);
}

/*
 *  �e�L�X�g�`��
 */
void
vivid::
DrawText(int size, const std::string& text, const Vector2& position, unsigned int color, unsigned int edge_color, ALPHABLEND blend_mode)
{
    // �t�H���g������
    int font = FindCreatedFont(size);

    // �t�H���g��������Ȃ�����
    if (font == VIVID_DX_ERROR)
    {
        CreateFont(size);

        font = FindCreatedFont(size);
    }

    // ���炩�ɕ`��
    SetDrawMode(DX_DRAWMODE_BILINEAR);

    // �A���t�@�u�����h�ݒ�
    SetDrawBlendMode(static_cast<int>(blend_mode), (color & 0xff000000) >> 24);

    // ������`��
    DrawStringToHandle((int)position.x, (int)position.y, text.c_str(), color, font, edge_color);

    // �A���t�@�u�����h���[�h���f�t�H���g�ɖ߂�
    SetDrawBlendMode(static_cast<int>(ALPHABLEND::ALPHA), 0xff);
}

/*
 *  ������̕����擾
 */
int
vivid::
GetTextWidth(int size, const std::string& text)
{
    // �t�H���g������
    int font = FindCreatedFont(size);

    // �t�H���g��������Ȃ�����
    if (font == VIVID_DX_ERROR)
        return 0;

    return GetDrawStringWidthToHandle(text.c_str(), (int)text.length(), font);
}

/*
 *  �{�^������
 */
bool
vivid::keyboard::
Button(vivid::keyboard::KEY_ID key)
{
    return g_KeyState[static_cast<int>(key)];
}

/*
 *  �g���K�[����
 */
bool
vivid::keyboard::
Trigger(vivid::keyboard::KEY_ID key)
{
    return (g_KeyState[static_cast<int>(key)] && !g_PrevKeyState[static_cast<int>(key)]);
}

/*
 *  �����[�X����
 */
bool
vivid::keyboard::
Released(vivid::keyboard::KEY_ID key)
{
    return (!g_KeyState[static_cast<int>(key)] && g_PrevKeyState[static_cast<int>(key)]);
}

/*
 *  �{�^������
 */
bool
vivid::mouse::
Button(vivid::mouse::BUTTON_ID button)
{
    return (g_MouseState & static_cast<int>(button));
}

/*
 *  �g���K�[����
 */
bool
vivid::mouse::
Trigger(vivid::mouse::BUTTON_ID button)
{
    return (g_MouseState & static_cast<int>(button)) && !(g_PrevMouseState & static_cast<int>(button));
}

/*
 *  �����[�X����
 */
bool
vivid::mouse::
Released(vivid::mouse::BUTTON_ID button)
{
    return !(g_MouseState & static_cast<int>(button)) && (g_PrevMouseState & static_cast<int>(button));
}

/*
 *  �}�E�X�J�[�\���̈ʒu�擾
 */
vivid::Point
vivid::mouse::
GetCursorPos(void)
{
    vivid::Point t;

    // �J�[�\���ʒu�擾
    GetMousePoint(&t.x, &t.y);

    return t;
}

/*
 *  �}�E�X�z�C�[���l�擾
 */
int
vivid::mouse::
GetWheel(void)
{
    return GetMouseWheelRotVol();
}

/*
 *  �{�^������
 */
bool
vivid::controller::
Button(vivid::controller::DEVICE_ID device, vivid::controller::BUTTON_ID button)
{
    return (g_ControllerState[static_cast<int>(device)].Buttons[static_cast<int>(button)]);
}

/*
 *  �g���K�[����
 */
bool
vivid::controller::
Trigger(vivid::controller::DEVICE_ID device, vivid::controller::BUTTON_ID button)
{
    return (g_ControllerState[static_cast<int>(device)].Buttons[static_cast<int>(button)]) && !(g_PrevControllerState[static_cast<int>(device)].Buttons[static_cast<int>(button)]);
}

/*
 *  �����[�X����
 */
bool
vivid::controller::
Released(vivid::controller::DEVICE_ID device, vivid::controller::BUTTON_ID button)
{
    return !(g_ControllerState[static_cast<int>(device)].Buttons[static_cast<int>(button)]) && (g_PrevControllerState[static_cast<int>(device)].Buttons[static_cast<int>(button)]);
}

/*
 *  ���A�i���O�X�e�B�b�N�擾
 */
vivid::Vector2
vivid::controller::
GetAnalogStickLeft(vivid::controller::DEVICE_ID device)
{
    int x = g_ControllerState[static_cast<int>(device)].ThumbLX;
    int y = g_ControllerState[static_cast<int>(device)].ThumbLY;

    float ax = (abs(x) < g_analog_dead_zone ? 0.0f : x );
    float ay = (abs(y) < g_analog_dead_zone ? 0.0f : y );

    if (x < 0.0f)
        ax = max((float)x, -g_limit_cant_analog);
    else if (x > 0.0f)
        ax = min((float)x, g_limit_cant_analog);

    if (y < 0.0f)
        ay = max((float)y, -g_limit_cant_analog);
    else if (y > 0.0f)
        ay = min((float)y, g_limit_cant_analog);

    // Y�������𔽓]
    return vivid::Vector2(ax, -ay) * ( 1.0f / (float)g_limit_cant_analog );
}

/*
 *  �E�A�i���O�X�e�B�b�N�擾
 */
vivid::Vector2
vivid::controller::
GetAnalogStickRight(vivid::controller::DEVICE_ID device)
{
    int x = g_ControllerState[static_cast<int>(device)].ThumbRX;
    int y = g_ControllerState[static_cast<int>(device)].ThumbRY;

    float ax = (abs(x) < g_analog_dead_zone ? 0.0f : x);
    float ay = (abs(y) < g_analog_dead_zone ? 0.0f : y);

    if (x < 0.0f)
        ax = max((float)x, -g_limit_cant_analog);
    else if (x > 0.0f)
        ax = min((float)x, g_limit_cant_analog);

    if (y < 0.0f)
        ay = max((float)y, -g_limit_cant_analog);
    else if (y > 0.0f)
        ay = min((float)y, g_limit_cant_analog);

    // Y�������𔽓]
    return vivid::Vector2(ax, -ay) * (1.0f / (float)g_limit_cant_analog);
}

/*
 *  ���g���K�[�擾
 */
float
vivid::controller::
GetTriggerLeft(vivid::controller::DEVICE_ID device)
{
    return (float)g_ControllerState[static_cast<int>(device)].LeftTrigger / (float)g_max_trigger;
}

/*
 *  �E�g���K�[�擾
 */
float
vivid::controller::
GetTriggerRight(vivid::controller::DEVICE_ID device)
{
    return (float)g_ControllerState[static_cast<int>(device)].RightTrigger / (float)g_max_trigger;
}

/*
 *  �o�C�u���[�V�����̊J�n
 */
void
vivid::controller::
StartVibration(vivid::controller::DEVICE_ID device, int power, float time)
{
    StartJoypadVibration(static_cast<int>(device) + 1, power, (int)(time * 1000.0f));
}

/*
 *  �ڑ����擾
 */
int
vivid::controller::
GetConnectCount(void)
{
    return GetJoypadNum();
}

/*
 *  �T�E���h�t�@�C���̓ǂݍ���
 */
void
vivid::
LoadSound(const std::string& file_name)
{
    // ���[�h�ς݂̃T�E���h����
    int sound = FindLoadedSound(file_name);

    // �T�E���h����������
    if (sound != VIVID_DX_ERROR)
        return;

    // �T�E���h�̓ǂݍ���
    sound = LoadSoundMem(file_name.c_str());

    VIVID_DX_ASSERT(sound, file_name + "�̓ǂݍ��݂Ɏ��s���܂����B");

    // �T�E���h��o�^
    g_SoundList.insert(std::map<std::string, int>::value_type(file_name, sound));
}

/*
 *  �T�E���h�Đ�
 */
void
vivid::
PlaySound(const std::string& file_name, bool loop)
{
    // ���[�h�ς݂̃T�E���h����
    int sound = FindLoadedSound(file_name);

    if (sound == VIVID_DX_ERROR)
        return;

    PlaySoundMem(sound, (loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK));
}

/*
 *  �T�E���h��~
 */
void
vivid::
StopSound(const std::string& file_name)
{
    // ���[�h�ς݂̃T�E���h����
    int sound = FindLoadedSound(file_name);

    if (sound == VIVID_DX_ERROR)
        return;

    StopSoundMem(sound);
}

/*
 *  �X�V����t���[���J�E���g�̌v�Z
 */
void
vivid::core::
CalcFrameCount(void)
{
    // ���݂̎��Ԃ��擾
    int now_time = GetNowCount();

    // �v�Z�J�n��
    if (g_FrameCount == 0)
    {
        g_StartTime = now_time;
    }
    // �w�肳�ꂽ�t���[���J�E���g��
    else if (g_FrameCount == g_calc_frame_count)
    {
        // �t���[���̕��ς��Z�o����FPS�����߂�
        g_Fps = g_one_millisecond / ((now_time - g_StartTime) / (float)g_calc_frame_count);

        g_FrameCount = 0;

        g_StartTime = now_time;
    }

    // �t���[���J�E���g���X�V
    ++g_FrameCount;

    // �O�̏����Ƃ̎��Ԃ̍�
    int sub_time = now_time - g_PrevTime;

    // �f���^�^�C�����Z�o
    g_DeltaTime = (float)sub_time / g_one_millisecond;

    // �ő�f���^�^�C���Ő�������
    if (g_DeltaTime > g_max_delta_time)
        g_DeltaTime = g_max_delta_time;

    // ���̎��Ԃ�ۑ�
    g_PrevTime = now_time;
}

/*
 *  �X�V�t���[���̑ҋ@����
 */
void
vivid::core::
FrameSync(void)
{
    // ���ƃt���[���v���J�n���̍����Z�o
    int tookTime = GetNowCount() - g_StartTime;

    // �ҋ@���Ԃ��Z�o
    int waitTime = g_FrameCount * (int)g_one_millisecond / g_FrameRate - tookTime;

    // �ҋ@���Ԃ�����΂��̕��҂��ē�������
    if (waitTime > 0)
        WaitTimer(waitTime);
}

/*
 *  �X�N���[���V���b�g�̎B�e
 */
void
vivid::core::
ScreenShot(void)
{
    DATEDATA dd;

    // ���݂̎��Ԏ擾
    GetDateTime(&dd);

    // �t�H���_�̗L���`�F�b�N
    // �Ȃ���΍쐬
    if (!PathIsDirectory("capture"))
        CreateDirectory("capture", NULL);

    // ���t���t�@�C�����ɂ���
    std::string file_name = "capture\\";

    file_name += std::to_string(dd.Year) + std::to_string(dd.Mon) + std::to_string(dd.Day) + "_";

    file_name += std::to_string(dd.Hour) + std::to_string(dd.Min) + std::to_string(dd.Sec) + ".bmp";

    // �X�N���[���V���b�g�̏����o��
    SaveDrawScreenToBMP(0, 0, g_window_width, g_window_height, file_name.c_str());
}

/*
 *  �A�T�[�g����
 */
void
vivid::core::
Assert(bool result, const std::string& message, const std::string& file, int line)
{
    if (result) return;

    // �A���t�@�u�����h�ݒ�
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0xee);

    // �w�i�`��
    DrawBox(0, 0, g_window_width, g_window_height, 0xff000000, TRUE);

    // �A���t�@�u�����h��߂�
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // �`�惁�b�Z�[�W�̍쐬
    std::string t = "[ASSERT] " + message + "\n[ FILE ] " + file.substr(file.rfind("\\") + 1) + "\n[ LINE ] " + std::to_string(line);

    // �G���[���b�Z�[�W�̕`��
    DrawString(0, 0, t.c_str(), 0xff00ff00, 0xff004000);

    // ��ʂ��X�V
    ScreenFlip();

    // ���b�Z�[�W�����m
    while (ProcessMessage() != VIVID_DX_ERROR)
    {
        // Esc�L�[�ŏI��
        if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE)
            break;
    }

    // ���C�u�����̉��
    Finalize();

    // �A�v���P�[�V�����̏I��
    exit(-1);
}

/*
 *  ���[�h�ς݂̃e�N�X�`������
 */
int
vivid::core::
FindLoadedTexture(const std::string& file_name)
{
    int  texture = VIVID_UNUSED_HANDLE;

    // �e�N�X�`�����X�g����łȂ�
    if (!g_TextureList.empty())
    {
        std::map<std::string, int>::iterator it = g_TextureList.begin();
        std::map<std::string, int>::iterator end = g_TextureList.end();

        for (; it != end; ++it)
        {
            // ��v����t�@�C���������邩����
            if (it->first == file_name)
            {
                // �������̂�����Γǂݍ��ݍς݂̃e�N�X�`����o�^
                texture = it->second;

                break;
            }
        }
    }

    return texture;
}

/*
 *  ���[�h�ς݂̃T�E���h����
 */
int
vivid::core::
FindLoadedSound(const std::string& file_name)
{
    int sound = VIVID_UNUSED_HANDLE;

    // �T�E���h���X�g����łȂ�
    if (!g_SoundList.empty())
    {
        std::map<std::string, int>::iterator it = g_SoundList.begin();
        std::map<std::string, int>::iterator end = g_SoundList.end();

        for (; it != end; ++it)
        {
            // ��v����t�@�C���������邩����
            if (it->first == file_name)
            {
                // �������̂�����Γǂݍ��ݍς݂̃T�E���h��o�^
                sound = it->second;

                break;
            }
        }
    }

    return sound;
}

/*
 *  �����ς݂̃t�H���g����
 */
int
vivid::core::
FindCreatedFont(int size)
{
    int font = VIVID_UNUSED_HANDLE;

    // �t�H���g���X�g����łȂ�
    if (!g_FontList.empty())
    {
        std::map<int, int>::iterator it = g_FontList.begin();
        std::map<int, int>::iterator end = g_FontList.end();

        for (; it != end; ++it)
        {
            // ��v����t�H���g�����邩����
            if (it->first == size)
            {
                // �������̂�����ΐ����ς݂̃t�H���g��o�^
                font = it->second;

                break;
            }
        }
    }

    return font;
}
/*!
 *  @brief      vivid���O���
 */
namespace vivid
{
    /*!
     *  @brief      vivid::effekseer���O���
     */
    namespace effekseer
    {
        static const float g_DefaultEffectScale = 25.0f;
    }
}
/*
 *  �G�t�F�N�V�A���C�u�����̏�����
 *  s.kosugi
 */
int vivid::effekseer::InitEffekseer(void)
{
    // Effekseer������������B
    // �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
    if (Effkseer_Init(8000) == -1)
    {
        return -1;
    }

    // �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
    // Effekseer���g�p����ꍇ�͕K���ݒ肷��B
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
    // �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
    // �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    // Effekseer��2D�`��̐ݒ������B
    Effekseer_Set2DSetting(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Z�o�b�t�@��L���ɂ���B
    // Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
    SetUseZBuffer3D(TRUE);

    // Z�o�b�t�@�ւ̏������݂�L���ɂ���B
    // Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
    SetWriteZBuffer3D(TRUE);

    return 0;
}

/*
 *  �G�t�F�N�g�ǂݍ���
 *  s.kosugi
 */
int vivid::effekseer::LoadEffect(const std::string& file_name)
{
    // �ǂݍ��ݍς�
    if (g_EffekseerList.end() != g_EffekseerList.find(file_name))
        return 0;

    int handle = LoadEffekseerEffect(file_name.c_str());

    // �ǂݍ��ݎ��s
    if (-1 == handle) return -1;

    // �ǂݍ��ݍς݃��X�g�ɒǉ�
    g_EffekseerList[file_name] = handle;

    return 0;
}

/*
 *  �G�t�F�N�g�Đ��J�n
 *  s.kosugi
 */
int vivid::effekseer::StartEffect(const std::string& file_name, const vivid::Vector2& pos)
{
    return StartEffect(file_name,pos, g_DefaultEffectScale);
}
/*
 *  �G�t�F�N�g�Đ��J�n
 *  s.kosugi
 */
int vivid::effekseer::StartEffect(const std::string& file_name, const vivid::Vector2& pos,const float scale)
{
    // �G�t�F�N�g�ǂݍ���
    if (-1 == LoadEffect(file_name))
        return -1;
    int PlayHandle = PlayEffekseer2DEffect(g_EffekseerList[file_name]);

    // �G�t�F�N�g�̊g�嗦���w��
    SetScalePlayingEffekseer2DEffect(PlayHandle, scale, scale, scale);

    PLAYEFFECT_DATA effect;
    effect.handle = PlayHandle;
    effect.pos = pos;
    // �G�t�F�N�g�Đ����X�g�ɒǉ�
    g_EffectPlayList.push_back(effect);

    return PlayHandle;
}
/*
 *  �G�t�F�N�g�`��
 *  s.kosugi
 */
bool vivid::effekseer::DrawEffect(const int handle, const vivid::Vector2& pos)
{
    if (IsEffekseer2DEffectPlaying(handle)) return false;

    // �G�t�F�N�g�̈ʒu��ύX����
    SetPosPlayingEffekseer2DEffect(handle, pos.x, pos.y, 0.0f);
    // �G�t�F�N�g��`�悷��
    DrawEffekseer2D_Begin();
    DrawEffekseer2D_Draw(handle);
    DrawEffekseer2D_End();

    return true;
}
/*
 *  �G�t�F�N�g�Đ��I���`�F�b�N
 *  s.kosugi
 */
bool vivid::effekseer::IsEffectPlaying(const int handle)
{
    if (IsEffekseer2DEffectPlaying(handle)) return false;
    return true;
}
/*
 *  �Đ����X�g����G�t�F�N�g�S�`��
 *  s.kosugi
 */
void vivid::effekseer::DrawEffectList(void)
{
    if (g_EffectPlayList.empty()) return;

    auto it = g_EffectPlayList.begin();
    while (it != g_EffectPlayList.end())
    {
        PLAYEFFECT_DATA effect = (PLAYEFFECT_DATA)(*it);
        if (!DrawEffect(effect.handle, effect.pos))
        {
            // �G�t�F�N�g�Đ��I���ς݂̂��ߍ폜
            it = g_EffectPlayList.erase(it);
            continue;
        }
        it++;
    }
}
/*
*  �G�t�F�N�g���X�g����S�`������邩�ǂ���
*  s.kosugi
*/
void vivid::effekseer::SetUseEffectListFlag(bool flag)
{
    g_UseEffectListFlag = flag;
}
