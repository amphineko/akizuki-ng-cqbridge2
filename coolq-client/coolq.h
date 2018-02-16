#pragma once

#include "stdafx.h"

// Event functions exported and called by CoolQ
// @args_size: size of argument list, in bytes
#define CLIENT_EVENT(return_type, function_name, exported_name, args_size) \
    __pragma(comment(linker, "/EXPORT:" #exported_name "=_" #exported_name "@" #args_size) )\
    extern "C" __declspec(dllexport) return_type __stdcall function_name
