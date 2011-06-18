INCLUDEPATH += $$PWD $$PWD/include
SOURCES     += $$PWD/*.cpp
SOURCES     += $$PWD/*.hpp

include($$PWD/dbg/dbg.pri)
include($$PWD/math/math.pri)
include($$PWD/render/render.pri)
include($$PWD/space/space.pri)
include($$PWD/tools/tools.pri)
