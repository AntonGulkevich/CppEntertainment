#pragma once

#define _AKM_BEGIN	namespace akm {
#define _AKM_END		}
#define _AKM	::akm::

#define __CLR_OR_THIS_CALL

typedef unsigned int fmtFlags;

typedef enum _Fmtflags
{
	_os_err_flg = 0,
	_os_console = 0x0001,
	_os_trace = 0x0002,
	_os_test = 0x0004
} FormatFlag;

typedef enum class _Dstflags : unsigned long
{
	_dst_console = 0x0C04501E,
	_dst_trace = 0xEC04501E
} dest_flag;

