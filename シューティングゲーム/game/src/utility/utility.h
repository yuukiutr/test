
/*!
 *  @file       utility.h
 *  @brief      ���[�e�B���e�B
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "vivid.h"
#include "csv_loader\csv_loader.h"

/*!
 *  @brief      �p�x�����W�A���l�ɕϊ�
 *
 *  @param[in]  d   �p�x
 *
 *  @return     ���W�A���l
 */
#define DEG_TO_RAD( d )     (float)( (d) * 3.14f / 180.0f )

/*!
 *  @brief      �F������F���擾
 *
 *  @param[in]  hue         �F��
 *  @param[in]  saturation  �ʓx
 *  @param[in]  brightness  ���x
 *
 *  @return     �F
 */
unsigned int    ChangeHSVToColor(float hue, float saturation, float brightness);

/*!
 *  @brief      �F������F���擾
 *
 *  @param[in]  step    �ߖڂƂȂ�l
 *  @param[in]  number  �J���[�ɕϊ����鐔�l
 *
 *  @return     �F
 */
unsigned int    ChangeNumberToColor(int step, int number);
