#pragma once

namespace xarch::origin {

class xarch_origin_x64;

#ifndef EMU_FFI
#define EMU_FFI(x) void x(xarch_origin_x64 *arch)
#endif

EMU_FFI(setq); // 0001

EMU_FFI(phlt); // FFFF

} // namespace xarch::origin
