
/*!
 *  @file       unit_id.h
 *  @brief      ���j�b�gID
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

/*!
 *  @brief      ���j�b�g����ID
 */
enum class UNIT_CATEGORY
{
    UNKNOW,   //!< �����s��
    FIGHTER,  //!< �퓬�@
    UFO,      //!< UFO
};

/*!
 *  @brief      ���j�b�gID
 */
enum class UNIT_ID
{
    FIGHTER,        //!< �퓬�@
    UFO_SMALL,      //!< UFO(��)
    UFO_MIDDLE,     //!< UFO(��)
    UFO_LARGE,      //!< UFO(��)
    UFO_BOSS,       //!< UFO(�{�X)
};
