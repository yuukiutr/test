
/*!
 *  @file       main.cpp
 *  @brief      �G���g���[�|�C���g
 *  @author     Kazuya Maruyama
 *  @date       2020/11/25
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "vivid.h"
#include "game_manager/game_manager.h"

/*!
 *  @brief      �`��֐�
 */
void
Display(void)
{
    // �Q�[���}�l�[�W���[�X�V
    CGameManager::GetInstance().Update();

    // �Q�[���}�l�[�W���[�`��
    CGameManager::GetInstance().Draw();
}

/*!
 *  @brief      ���C���֐�
 *
 *  @param[in]  hInst       �C���X�^���X�n���h��
 *  @param[in]  hPrevInst   Win16����̈╨
 *  @param[in]  lpCmdLine   �R�}���h���C��������
 *  @param[in]  nCmdShow    �E�B���h�̕\�����@
 *
 *  @return     ���C���֐��̐���
 */
int WINAPI
WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, char* lpCmdLine, int nCmdShow )
{
    (void)hPrevInst;
    (void)lpCmdLine;
    (void)nCmdShow;

    // vivid���C�u����������
    vivid::Initialize(hInst);

    // �Q�[���}�l�[�W���[������
    CGameManager::GetInstance().Initialize();

    // �X�V/�`��֐��o�^
    vivid::DisplayFunction(Display);

    // �Q�[�����[�v
    vivid::MainLoop();

    // �Q�[���}�l�[�W���[���
    CGameManager::GetInstance().Finalize();

    // vivid���C�u�������
    vivid::Finalize();
}
