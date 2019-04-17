#include "all.h"

oneObject(finalizers, new finalizers(), GetEndProcFinalizers); // EndProc()     で Flish() する。DxLib_End(); より前。error(); のとき呼ばれない。
oneObject(finalizers, new finalizers(), GetFinalizers);        // termination() で Flish() する。DxLib_End(); より後。error(); のとき呼ばれる。
