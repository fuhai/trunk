# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/DynamicEngine/MassSpringBody2RigidBodyDynamicEngine
# Target is a library:  

LIBS += -lMassSpringBody \
        -lRigidBody \
        -lDistances \
        -lSerialization \
        -lSimpleSpringDynamicEngine \
        -lMesh2D \
        -lClosestFeatures \
        -lMath \
        -lBody \
        -lEngine \
        -lGeometry \
        -lInteraction \
        -lMultiMethods \
        -rdynamic 
INCLUDEPATH = ../../../plugins/DynamicEngine/SimpleSpringDynamicEngine \
              ../../../plugins/Body/MassSpringBody \
              ../../../plugins/Body/RigidBody \
              ../../../plugins/GeometricalModel/Mesh2D \
              ../../../plugins/InteractionModel/ClosestFeatures \
              ../../../yade/yade \
              ../../../yade/Body \
              ../../../yade/Engine \
              ../../../yade/Interaction \
              ../../../yade/Geometry \
              ../../../yade/MultiMethods \
              ../../../yade/Factory \
              ../../../toolboxes/ComputationalGeometry/Distances \
              ../../../toolboxes/Libraries/Math \
              ../../../toolboxes/Libraries/Serialization 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../plugins/Body/MassSpringBody/$(YADEDYNLIBPATH) \
               ../../../plugins/Body/RigidBody/$(YADEDYNLIBPATH) \
               ../../../toolboxes/ComputationalGeometry/Distances/$(YADEDYNLIBPATH) \
               ../../../toolboxes/Libraries/Serialization/$(YADEDYNLIBPATH) \
               ../../../plugins/DynamicEngine/SimpleSpringDynamicEngine/$(YADEDYNLIBPATH) \
               ../../../plugins/GeometricalModel/Mesh2D/$(YADEDYNLIBPATH) \
               ../../../plugins/InteractionModel/ClosestFeatures/$(YADEDYNLIBPATH) \
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
HEADERS += MassSpringBody2RigidBodyDynamicEngine.hpp 
SOURCES += MassSpringBody2RigidBodyDynamicEngine.cpp 
