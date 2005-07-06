# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./Engine/EngineUnit/FEMTetrahedronStiffness
# Target is a library:  

HEADERS += FEMTetrahedronStiffness.hpp 
SOURCES += FEMTetrahedronStiffness.cpp 
LIBS += -lFEMSetParameters \
        -lFEMTetrahedronData \
        -lPhysicalParametersMetaEngine \
        -lParticleParameters \
        -rdynamic 
QMAKE_LIBDIR = ../../../../../bin \
               ../../../../../bin \
               /usr/local/lib/yade/yade-libs/ 
QMAKE_CXXFLAGS_RELEASE += -lpthread \
                          -pthread 
QMAKE_CXXFLAGS_DEBUG += -lpthread \
                        -pthread 
DESTDIR = ../../../../../bin 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 