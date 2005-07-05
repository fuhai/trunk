# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/Engine/Engine/PhysicalActionEngine/InteractionSolver/ElasticCohesiveLaw
# Target is a library:  

LIBS += -lyade-lib-serialization \
        -lyade-lib-wm3-math \
        -lyade-lib-multimethods \
        -lSDECLinkPhysics \
        -lElasticContactParameters \
        -lForce \
        -lMomentum \
        -lSphere \
        -lSDECLinkGeometry \
        -lRigidBodyParameters \
        -lMacroMicroContactGeometry \
        -lBodyMacroParameters \
        -rdynamic 
INCLUDEPATH += $(YADEINCLUDEPATH) 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = /usr/local/lib/yade/yade-libs/ \
               $(YADEDYNLIBPATH) 
QMAKE_CXXFLAGS_RELEASE += -lpthread \
                          -pthread 
QMAKE_CXXFLAGS_DEBUG += -lpthread \
                        -pthread 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += ElasticCohesiveLaw.hpp 
SOURCES += ElasticCohesiveLaw.cpp 