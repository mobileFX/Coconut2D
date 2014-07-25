# Makefile for generating a Box2D library using Emscripten 1.21.0.

-include Makefile.local

O = Box2D_v2.2.1/Box2D
OBJECTS = \
$(O)/Collision/b2BroadPhase.obj \
$(O)/Collision/b2CollideCircle.obj \
$(O)/Collision/b2CollideEdge.obj \
$(O)/Collision/b2CollidePolygon.obj \
$(O)/Collision/b2Collision.obj \
$(O)/Collision/b2Distance.obj \
$(O)/Collision/b2DynamicTree.obj \
$(O)/Collision/b2TimeOfImpact.obj \
$(O)/Collision/Shapes/b2ChainShape.obj \
$(O)/Collision/Shapes/b2CircleShape.obj \
$(O)/Collision/Shapes/b2EdgeShape.obj \
$(O)/Collision/Shapes/b2PolygonShape.obj \
$(O)/Common/b2BlockAllocator.obj \
$(O)/Common/b2Draw.obj \
$(O)/Common/b2Math.obj \
$(O)/Common/b2Settings.obj \
$(O)/Common/b2StackAllocator.obj \
$(O)/Common/b2Timer.obj \
$(O)/Dynamics/b2Body.obj \
$(O)/Dynamics/b2ContactManager.obj \
$(O)/Dynamics/b2Fixture.obj \
$(O)/Dynamics/b2Island.obj \
$(O)/Dynamics/b2World.obj \
$(O)/Dynamics/b2WorldCallbacks.obj \
$(O)/Dynamics/Contacts/b2ChainAndCircleContact.obj \
$(O)/Dynamics/Contacts/b2ChainAndPolygonContact.obj \
$(O)/Dynamics/Contacts/b2CircleContact.obj \
$(O)/Dynamics/Contacts/b2Contact.obj \
$(O)/Dynamics/Contacts/b2ContactSolver.obj \
$(O)/Dynamics/Contacts/b2EdgeAndCircleContact.obj \
$(O)/Dynamics/Contacts/b2EdgeAndPolygonContact.obj \
$(O)/Dynamics/Contacts/b2PolygonAndCircleContact.obj \
$(O)/Dynamics/Contacts/b2PolygonContact.obj \
$(O)/Dynamics/Joints/b2DistanceJoint.obj \
$(O)/Dynamics/Joints/b2FrictionJoint.obj \
$(O)/Dynamics/Joints/b2GearJoint.obj \
$(O)/Dynamics/Joints/b2Joint.obj \
$(O)/Dynamics/Joints/b2MouseJoint.obj \
$(O)/Dynamics/Joints/b2PrismaticJoint.obj \
$(O)/Dynamics/Joints/b2PulleyJoint.obj \
$(O)/Dynamics/Joints/b2RevoluteJoint.obj \
$(O)/Dynamics/Joints/b2RopeJoint.obj \
$(O)/Dynamics/Joints/b2WeldJoint.obj \
$(O)/Dynamics/Joints/b2WheelJoint.obj \
$(O)/Rope/b2Rope.obj

all: clean box2d.js

%.obj: %.cpp
	@echo + Compiling $<
	@$(PYTHON) $(EMSCRIPTEN_ROOT)/em++ -O1 -IBox2D_v2.2.1 $< -o $@

box2d.clean.h:
	@$(LLVM_ROOT)/clang -E -DEM_NO_LIBCPP -O1 -IBox2D_v2.2.1 root.h > box2d.clean.h

box2d_bindings.cpp: box2d.clean.h
	@$(PYTHON) $(EMSCRIPTEN_ROOT)/tools/bindings_generator.py box2d_bindings box2d.clean.h -- '' > bindings.out

box2d_bindings.obj: box2d_bindings.cpp
	@$(PYTHON) $(EMSCRIPTEN_ROOT)/em++ -O1 -IBox2D_v2.2.1 -Wno-return-type-c-linkage -include root.h $< -o $@

box2d.obj: $(OBJECTS) box2d_bindings.obj
	@$(PYTHON) $(EMSCRIPTEN_ROOT)/em++ -std=c++11 -O1 $(OBJECTS) box2d_bindings.obj -o $@

box2d.js: box2d.obj
	@$(PYTHON) $(EMSCRIPTEN_ROOT)/em++ -O1 -s EXPORT_BINDINGS=1 -s RESERVED_FUNCTION_POINTERS=20 $< -o $@
	@del /F /Q /S *.obj

clean:
	@del /F /Q *bindings*.* *.clean.h *.map *.out *.js
	@del /F /Q /S *.obj
