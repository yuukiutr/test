
/*!
 *  @file       csv_loader.cpp
 *  @brief      CSV���[�_�[
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "csv_loader.h"
#include <fstream>
#include <sstream>

 /*
 *  �R���X�g���N�^
 */
CCSVLoader::
CCSVLoader( void )
    : m_Cols( 0 )
    , m_Rows( 0 )
{
    m_Data.clear( );
}

/*
 *  �f�X�g���N�^
 */
CCSVLoader::
~CCSVLoader( void )
{
}

/*
 *  CSV�t�@�C���ǂݍ���
 */
void
CCSVLoader::
Load( const std::string& file_name )
{
    // �O�̂��߉������
    Unload( );

    FILE* fp = nullptr;

    fopen_s( &fp, file_name.c_str( ), "r" );

    std::string item;

    char t = '\0';

    // �����܂ŏ��ɒ��ׂ�
    do
    {
        t = (char)fgetc( fp );

        if( t == ',' )
        {
            m_Data.push_back( item );

            item.clear( );
        }
        else if( t == '\n' )
        {
            m_Data.push_back( item );

            item.clear( );

            ++m_Rows;
        }
        else
        {
            item += t;
        }
    }
    while( t != EOF );

    fclose( fp );

    // ���ɕ���ł��鐔���Z�o
    m_Cols = (int)m_Data.size( ) / m_Rows;
}

/*
 *  ���
 */
void
CCSVLoader::
Unload( void )
{
    m_Data.clear( );

    m_Cols = m_Rows = 0;
}

/*
 *  ���ɕ���ł��鐔���擾
 */
int
CCSVLoader::
GetCols( void )
{
    return m_Cols;
}

/*
 *  �c�ɕ���ł��鐔���擾
 */
int
CCSVLoader::
GetRows( void )
{
    return m_Rows;
}

/*
 *  �f�[�^�����擾
 */
int
CCSVLoader::
GetDataCount( void )
{
    return (int)m_Data.size( );
}

/*
 *  �w�肳�ꂽ�f�[�^�𕶎���Ŏ擾
 */
std::string
CCSVLoader::
GetString( int rows, int cols )
{
    return m_Data[( rows * m_Cols ) + cols];
}

/*
 *  �w�肳�ꂽ�f�[�^�𐮐��ɕϊ����Ď擾
 */
int
CCSVLoader::
GetInteger( int rows, int cols )
{
    return stoi( m_Data[( rows * m_Cols ) + cols] );
}

/*
 *  �w�肳�ꂽ�f�[�^�������ɕϊ����Ď擾
 */
float
CCSVLoader::
GetFloat( int rows, int cols )
{
    return stof( m_Data[( rows * m_Cols ) + cols] );
}
