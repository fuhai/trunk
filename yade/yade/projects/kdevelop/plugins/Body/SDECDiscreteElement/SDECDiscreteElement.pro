# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/Body/SDECDiscreteElement
# Target is a library:  

LIBS += -lRigidBody \
        -lSerialization \
        -lMath \
        -lBody \
        -lEngine \
        -lGeometry \
        -lInteraction \
        -lMultiMethods \
        -rdynamic 
INCLUDEPATH = ../../../plugins/Body/RigidBody \
              ../../../yade/yade \
              ../../../yade/Body \
              ../../../yade/Engine \
              ../../../yade/Interaction \
              ../../../yade/Geometry \
              ../../../yade/MultiMethods \
              ../../../yade/Factory \
              ../../../toolboxes/Libraries/Math \
              ../../../toolboxes/Libraries/Serialization 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../plugins/Body/RigidBody/$(YADEDYNLIBPATH) \
               ../../../toolboxes/Libraries/Serialization/$(YADEDYNLIBPATH) \
               ../../../toolboxes/Libraries/Math/$(YADEDYNLIBPATH) \
               ../../../yade/Body/$(YADEDYNLIBPATH) \
               ../../../yade/Engine/$(YADEDYNLIBPATH) \
               ../../../yade/Geometry/$(YADEDYNLIBPATH) \
               ../../../yade/Interaction/$(YADEDYNLIBPATH) \
               ../../../yade/MultiMethods/$(YADEDYNLIBPATH) \
               $(YADEDYNLIBPATH) 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += SDECDiscreteElement.hpp 
SOURCES += SDECDiscreteElement.cpp 
