// [assembly: Guid("3f54dc6b-a5e8-424f-8ace-f0cb67196ddd")] warning! do not delete this line
#pragma once
#include <jstruct.h>


/************************************************************************/
/* this is an example struct, you can delete
/************************************************************************/
template <typename user_t
    , typename number_t
    , typename struct_t>
struct struct_name
{
    USER_T                  user_t      user_field;                 // user data, serialize and vice-versal unrelated
    REQUIRED BOOL_T         bool        bool_field;                 // not support BOOL, because of typeid(int) == typeid(BOOL)

    REQUIRED NUMBER_T       number_t    number_field;               // now support short|unsigned short|int|unsigned int|long|unsigned long|__int64|float|double
    REQUIRED NUMBER_ARRAY_T number_t    number_array_field[2];

    REQUIRED WCHAR_ARRAY_T  wchar_t     wchar_array_field[1024];    // now support wchar_t only, because of the conversion from utf8 to utf16 was done internally
    REQUIRED WCHAR_TABLE_T  wchar_t     wchar_table_field[2][1024];

    REQUIRED STRUCT_T       struct_t    struct_field;               // user custom defined struct
    REQUIRED STRUCT_ARRAY_T struct_t    struct_array_field[2];
};