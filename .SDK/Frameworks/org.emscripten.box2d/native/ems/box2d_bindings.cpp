extern "C" {

b2ContactFilter * __attribute__((used, noinline)) emscripten_bind_b2ContactManager__get_m_contactFilter_p0(b2ContactManager * self) {
  return self->m_contactFilter;
}
signed int __attribute__((used, noinline)) emscripten_bind_b2ContactManager__get_m_contactCount_p0(b2ContactManager * self) {
  return self->m_contactCount;
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactManager__set_m_contactFilter_p1(b2ContactManager * self, b2ContactFilter * arg0) {
  self->m_contactFilter = arg0;
}
b2ContactManager * __attribute__((used, noinline)) emscripten_bind_b2ContactManager__b2ContactManager_p0() {
  return new b2ContactManager();
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactManager__AddPair_p2(b2ContactManager * self, void * arg0, void * arg1) {
  self->AddPair(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactManager__set_m_allocator_p1(b2ContactManager * self, b2BlockAllocator * arg0) {
  self->m_allocator = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactManager__set_m_contactCount_p1(b2ContactManager * self, signed int arg0) {
  self->m_contactCount = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactManager__Collide_p0(b2ContactManager * self) {
  self->Collide();
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactManager__set_m_contactList_p1(b2ContactManager * self, b2Contact * arg0) {
  self->m_contactList = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactManager__FindNewContacts_p0(b2ContactManager * self) {
  self->FindNewContacts();
}
b2ContactListener * __attribute__((used, noinline)) emscripten_bind_b2ContactManager__get_m_contactListener_p0(b2ContactManager * self) {
  return self->m_contactListener;
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactManager____destroy___p0(b2ContactManager * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactManager__set_m_contactListener_p1(b2ContactManager * self, b2ContactListener * arg0) {
  self->m_contactListener = arg0;
}
b2BroadPhase& __attribute__((used, noinline)) emscripten_bind_b2ContactManager__get_m_broadPhase_p0(b2ContactManager * self) {
  return self->m_broadPhase;
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactManager__Destroy_p1(b2ContactManager * self, b2Contact * arg0) {
  self->Destroy(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactManager__set_m_broadPhase_p1(b2ContactManager * self, b2BroadPhase& arg0) {
  self->m_broadPhase = arg0;
}
b2Contact * __attribute__((used, noinline)) emscripten_bind_b2ContactManager__get_m_contactList_p0(b2ContactManager * self) {
  return self->m_contactList;
}
b2BlockAllocator * __attribute__((used, noinline)) emscripten_bind_b2ContactManager__get_m_allocator_p0(b2ContactManager * self) {
  return self->m_allocator;
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetBodyA_p0(b2DistanceJoint * self) {
  return self->GetBodyA();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetBodyB_p0(b2DistanceJoint * self) {
  return self->GetBodyB();
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__SetFrequency_p1(b2DistanceJoint * self, float arg0) {
  self->SetFrequency(arg0);
}
void* __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetUserData_p0(b2DistanceJoint * self) {
  return self->GetUserData();
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__SetUserData_p1(b2DistanceJoint * self, void * arg0) {
  self->SetUserData(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetAnchorB_p0(b2DistanceJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorB();
  return ret;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetAnchorA_p0(b2DistanceJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorA();
  return ret;
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetNext_p0(b2DistanceJoint * self) {
  return self->GetNext();
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetLocalAnchorA_p0(b2DistanceJoint * self) {
  return self->GetLocalAnchorA();
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetLocalAnchorB_p0(b2DistanceJoint * self) {
  return self->GetLocalAnchorB();
}
float __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetFrequency_p0(b2DistanceJoint * self) {
  return self->GetFrequency();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetReactionForce_p1(b2DistanceJoint * self, float arg0) {
  static b2Vec2 ret; ret = self->GetReactionForce(arg0);
  return ret;
}
float __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetLength_p0(b2DistanceJoint * self) {
  return self->GetLength();
}
float __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetDampingRatio_p0(b2DistanceJoint * self) {
  return self->GetDampingRatio();
}
bool __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetCollideConnected_p0(b2DistanceJoint * self) {
  return self->GetCollideConnected();
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint____destroy___p0(b2DistanceJoint * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__Dump_p0(b2DistanceJoint * self) {
  self->Dump();
}
int __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetType_p0(b2DistanceJoint * self) {
  return self->GetType();
}
b2DistanceJoint * __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__b2DistanceJoint_p1(const b2DistanceJointDef * arg0) {
  return new b2DistanceJoint(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__SetDampingRatio_p1(b2DistanceJoint * self, float arg0) {
  self->SetDampingRatio(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__GetReactionTorque_p1(b2DistanceJoint * self, float arg0) {
  return self->GetReactionTorque(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__SetLength_p1(b2DistanceJoint * self, float arg0) {
  self->SetLength(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2DistanceJoint__IsActive_p0(b2DistanceJoint * self) {
  return self->IsActive();
}
float __attribute__((used, noinline)) emscripten_bind_b2Fixture__GetRestitution_p0(b2Fixture * self) {
  return self->GetRestitution();
}
void __attribute__((used, noinline)) emscripten_bind_b2Fixture__SetFilterData_p1(b2Fixture * self, const b2Filter & arg0) {
  self->SetFilterData(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Fixture__SetFriction_p1(b2Fixture * self, float arg0) {
  self->SetFriction(arg0);
}
b2Fixture * __attribute__((used, noinline)) emscripten_bind_b2Fixture__b2Fixture_p0() {
  return new b2Fixture();
}
b2Shape* __attribute__((used, noinline)) emscripten_bind_b2Fixture__GetShape_p0(b2Fixture * self) {
  return self->GetShape();
}
void __attribute__((used, noinline)) emscripten_bind_b2Fixture__SetRestitution_p1(b2Fixture * self, float arg0) {
  self->SetRestitution(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2Fixture__GetBody_p0(b2Fixture * self) {
  return self->GetBody();
}
b2Fixture* __attribute__((used, noinline)) emscripten_bind_b2Fixture__GetNext_p0(b2Fixture * self) {
  return self->GetNext();
}
float __attribute__((used, noinline)) emscripten_bind_b2Fixture__GetFriction_p0(b2Fixture * self) {
  return self->GetFriction();
}
void* __attribute__((used, noinline)) emscripten_bind_b2Fixture__GetUserData_p0(b2Fixture * self) {
  return self->GetUserData();
}
void __attribute__((used, noinline)) emscripten_bind_b2Fixture__SetDensity_p1(b2Fixture * self, float arg0) {
  self->SetDensity(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Fixture__GetMassData_p1(b2Fixture * self, b2MassData * arg0) {
  self->GetMassData(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Fixture__SetSensor_p1(b2Fixture * self, bool arg0) {
  self->SetSensor(arg0);
}
const b2AABB& __attribute__((used, noinline)) emscripten_bind_b2Fixture__GetAABB_p1(b2Fixture * self, signed int arg0) {
  return self->GetAABB(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2Fixture__TestPoint_p1(b2Fixture * self, const b2Vec2 & arg0) {
  return self->TestPoint(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Fixture__SetUserData_p1(b2Fixture * self, void * arg0) {
  self->SetUserData(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Fixture____destroy___p0(b2Fixture * self) {
  delete self;
}
bool __attribute__((used, noinline)) emscripten_bind_b2Fixture__RayCast_p3(b2Fixture * self, b2RayCastOutput * arg0, const b2RayCastInput & arg1, signed int arg2) {
  return self->RayCast(arg0, arg1, arg2);
}
void __attribute__((used, noinline)) emscripten_bind_b2Fixture__Refilter_p0(b2Fixture * self) {
  self->Refilter();
}
void __attribute__((used, noinline)) emscripten_bind_b2Fixture__Dump_p1(b2Fixture * self, signed int arg0) {
  self->Dump(arg0);
}
const b2Filter& __attribute__((used, noinline)) emscripten_bind_b2Fixture__GetFilterData_p0(b2Fixture * self) {
  return self->GetFilterData();
}
bool __attribute__((used, noinline)) emscripten_bind_b2Fixture__IsSensor_p0(b2Fixture * self) {
  return self->IsSensor();
}
int __attribute__((used, noinline)) emscripten_bind_b2Fixture__GetType_p0(b2Fixture * self) {
  return self->GetType();
}
float __attribute__((used, noinline)) emscripten_bind_b2Fixture__GetDensity_p0(b2Fixture * self) {
  return self->GetDensity();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetBodyA_p0(b2MouseJoint * self) {
  return self->GetBodyA();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetBodyB_p0(b2MouseJoint * self) {
  return self->GetBodyB();
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__SetFrequency_p1(b2MouseJoint * self, float arg0) {
  self->SetFrequency(arg0);
}
void* __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetUserData_p0(b2MouseJoint * self) {
  return self->GetUserData();
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__SetMaxForce_p1(b2MouseJoint * self, float arg0) {
  self->SetMaxForce(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__SetUserData_p1(b2MouseJoint * self, void * arg0) {
  self->SetUserData(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetAnchorB_p0(b2MouseJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorB();
  return ret;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetAnchorA_p0(b2MouseJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorA();
  return ret;
}
b2MouseJoint * __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__b2MouseJoint_p1(const b2MouseJointDef * arg0) {
  return new b2MouseJoint(arg0);
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetNext_p0(b2MouseJoint * self) {
  return self->GetNext();
}
float __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetMaxForce_p0(b2MouseJoint * self) {
  return self->GetMaxForce();
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetTarget_p0(b2MouseJoint * self) {
  return self->GetTarget();
}
float __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetFrequency_p0(b2MouseJoint * self) {
  return self->GetFrequency();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetReactionForce_p1(b2MouseJoint * self, float arg0) {
  static b2Vec2 ret; ret = self->GetReactionForce(arg0);
  return ret;
}
float __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetDampingRatio_p0(b2MouseJoint * self) {
  return self->GetDampingRatio();
}
bool __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetCollideConnected_p0(b2MouseJoint * self) {
  return self->GetCollideConnected();
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJoint____destroy___p0(b2MouseJoint * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__Dump_p0(b2MouseJoint * self) {
  self->Dump();
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__SetTarget_p1(b2MouseJoint * self, const b2Vec2 & arg0) {
  self->SetTarget(arg0);
}
int __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetType_p0(b2MouseJoint * self) {
  return self->GetType();
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__SetDampingRatio_p1(b2MouseJoint * self, float arg0) {
  self->SetDampingRatio(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__GetReactionTorque_p1(b2MouseJoint * self, float arg0) {
  return self->GetReactionTorque(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2MouseJoint__IsActive_p0(b2MouseJoint * self) {
  return self->IsActive();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetBodyA_p0(b2PulleyJoint * self) {
  return self->GetBodyA();
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint____destroy___p0(b2PulleyJoint * self) {
  delete self;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetAnchorA_p0(b2PulleyJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorA();
  return ret;
}
int __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetType_p0(b2PulleyJoint * self) {
  return self->GetType();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetGroundAnchorB_p0(b2PulleyJoint * self) {
  static b2Vec2 ret; ret = self->GetGroundAnchorB();
  return ret;
}
float __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetReactionTorque_p1(b2PulleyJoint * self, float arg0) {
  return self->GetReactionTorque(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__Dump_p0(b2PulleyJoint * self) {
  self->Dump();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetGroundAnchorA_p0(b2PulleyJoint * self) {
  static b2Vec2 ret; ret = self->GetGroundAnchorA();
  return ret;
}
float __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetLengthB_p0(b2PulleyJoint * self) {
  return self->GetLengthB();
}
void* __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetUserData_p0(b2PulleyJoint * self) {
  return self->GetUserData();
}
float __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetLengthA_p0(b2PulleyJoint * self) {
  return self->GetLengthA();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetBodyB_p0(b2PulleyJoint * self) {
  return self->GetBodyB();
}
bool __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetCollideConnected_p0(b2PulleyJoint * self) {
  return self->GetCollideConnected();
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__SetUserData_p1(b2PulleyJoint * self, void * arg0) {
  self->SetUserData(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetAnchorB_p0(b2PulleyJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorB();
  return ret;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetReactionForce_p1(b2PulleyJoint * self, float arg0) {
  static b2Vec2 ret; ret = self->GetReactionForce(arg0);
  return ret;
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetNext_p0(b2PulleyJoint * self) {
  return self->GetNext();
}
b2PulleyJoint * __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__b2PulleyJoint_p1(const b2PulleyJointDef * arg0) {
  return new b2PulleyJoint(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__IsActive_p0(b2PulleyJoint * self) {
  return self->IsActive();
}
float __attribute__((used, noinline)) emscripten_bind_b2PulleyJoint__GetRatio_p0(b2PulleyJoint * self) {
  return self->GetRatio();
}
float __attribute__((used, noinline)) emscripten_bind_b2BroadPhase__GetTreeQuality_p0(b2BroadPhase * self) {
  return self->GetTreeQuality();
}
const b2AABB& __attribute__((used, noinline)) emscripten_bind_b2BroadPhase__GetFatAABB_p1(b2BroadPhase * self, signed int arg0) {
  return self->GetFatAABB(arg0);
}
void* __attribute__((used, noinline)) emscripten_bind_b2BroadPhase__GetUserData_p1(b2BroadPhase * self, signed int arg0) {
  return self->GetUserData(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2BroadPhase____destroy___p0(b2BroadPhase * self) {
  delete self;
}
int __attribute__((used, noinline)) emscripten_bind_b2BroadPhase__GetTreeHeight_p0(b2BroadPhase * self) {
  return self->GetTreeHeight();
}
b2BroadPhase * __attribute__((used, noinline)) emscripten_bind_b2BroadPhase__b2BroadPhase_p0() {
  return new b2BroadPhase();
}
int __attribute__((used, noinline)) emscripten_bind_b2BroadPhase__GetProxyCount_p0(b2BroadPhase * self) {
  return self->GetProxyCount();
}
int __attribute__((used, noinline)) emscripten_bind_b2BroadPhase__GetTreeBalance_p0(b2BroadPhase * self) {
  return self->GetTreeBalance();
}
bool __attribute__((used, noinline)) emscripten_bind_b2BroadPhase__TestOverlap_p2(b2BroadPhase * self, signed int arg0, signed int arg1) {
  return self->TestOverlap(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2BroadPhase__TouchProxy_p1(b2BroadPhase * self, signed int arg0) {
  self->TouchProxy(arg0);
}
int __attribute__((used, noinline)) emscripten_bind_b2BroadPhase__CreateProxy_p2(b2BroadPhase * self, const b2AABB & arg0, void * arg1) {
  return self->CreateProxy(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2BroadPhase__MoveProxy_p3(b2BroadPhase * self, signed int arg0, const b2AABB & arg1, const b2Vec2 & arg2) {
  self->MoveProxy(arg0, arg1, arg2);
}
void __attribute__((used, noinline)) emscripten_bind_b2BroadPhase__DestroyProxy_p1(b2BroadPhase * self, signed int arg0) {
  self->DestroyProxy(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2World__QueryAABB_p2(b2World * self, b2QueryCallback * arg0, const b2AABB & arg1) {
  self->QueryAABB(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2World__SetSubStepping_p1(b2World * self, bool arg0) {
  self->SetSubStepping(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2World__GetTreeQuality_p0(b2World * self) {
  return self->GetTreeQuality();
}
int __attribute__((used, noinline)) emscripten_bind_b2World__GetTreeHeight_p0(b2World * self) {
  return self->GetTreeHeight();
}
const b2Profile& __attribute__((used, noinline)) emscripten_bind_b2World__GetProfile_p0(b2World * self) {
  return self->GetProfile();
}
int __attribute__((used, noinline)) emscripten_bind_b2World__GetTreeBalance_p0(b2World * self) {
  return self->GetTreeBalance();
}
bool __attribute__((used, noinline)) emscripten_bind_b2World__GetSubStepping_p0(b2World * self) {
  return self->GetSubStepping();
}
const b2ContactManager& __attribute__((used, noinline)) emscripten_bind_b2World__GetContactManager_p0(b2World * self) {
  return self->GetContactManager();
}
void __attribute__((used, noinline)) emscripten_bind_b2World__SetContactListener_p1(b2World * self, b2ContactListener * arg0) {
  self->SetContactListener(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2World__DrawDebugData_p0(b2World * self) {
  self->DrawDebugData();
}
void __attribute__((used, noinline)) emscripten_bind_b2World__SetContinuousPhysics_p1(b2World * self, bool arg0) {
  self->SetContinuousPhysics(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2World__SetGravity_p1(b2World * self, const b2Vec2 & arg0) {
  self->SetGravity(arg0);
}
int __attribute__((used, noinline)) emscripten_bind_b2World__GetBodyCount_p0(b2World * self) {
  return self->GetBodyCount();
}
bool __attribute__((used, noinline)) emscripten_bind_b2World__GetAutoClearForces_p0(b2World * self) {
  return self->GetAutoClearForces();
}
bool __attribute__((used, noinline)) emscripten_bind_b2World__GetContinuousPhysics_p0(b2World * self) {
  return self->GetContinuousPhysics();
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2World__GetJointList_p0(b2World * self) {
  return self->GetJointList();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2World__CreateBody_p1(b2World * self, const b2BodyDef * arg0) {
  return self->CreateBody(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2World__GetBodyList_p0(b2World * self) {
  return self->GetBodyList();
}
void __attribute__((used, noinline)) emscripten_bind_b2World__SetDestructionListener_p1(b2World * self, b2DestructionListener * arg0) {
  self->SetDestructionListener(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2World__DestroyJoint_p1(b2World * self, b2Joint * arg0) {
  self->DestroyJoint(arg0);
}
b2World * __attribute__((used, noinline)) emscripten_bind_b2World__b2World_p1(const b2Vec2 & arg0) {
  return new b2World(arg0);
}
int __attribute__((used, noinline)) emscripten_bind_b2World__GetJointCount_p0(b2World * self) {
  return self->GetJointCount();
}
void __attribute__((used, noinline)) emscripten_bind_b2World__Step_p3(b2World * self, float arg0, signed int arg1, signed int arg2) {
  self->Step(arg0, arg1, arg2);
}
void __attribute__((used, noinline)) emscripten_bind_b2World__ClearForces_p0(b2World * self) {
  self->ClearForces();
}
bool __attribute__((used, noinline)) emscripten_bind_b2World__GetWarmStarting_p0(b2World * self) {
  return self->GetWarmStarting();
}
void __attribute__((used, noinline)) emscripten_bind_b2World__SetAllowSleeping_p1(b2World * self, bool arg0) {
  self->SetAllowSleeping(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2World__DestroyBody_p1(b2World * self, b2Body * arg0) {
  self->DestroyBody(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2World__GetAllowSleeping_p0(b2World * self) {
  return self->GetAllowSleeping();
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2World__CreateJoint_p1(b2World * self, const b2JointDef * arg0) {
  return self->CreateJoint(arg0);
}
int __attribute__((used, noinline)) emscripten_bind_b2World__GetProxyCount_p0(b2World * self) {
  return self->GetProxyCount();
}
void __attribute__((used, noinline)) emscripten_bind_b2World__RayCast_p3(b2World * self, b2RayCastCallback * arg0, const b2Vec2 & arg1, const b2Vec2 & arg2) {
  self->RayCast(arg0, arg1, arg2);
}
bool __attribute__((used, noinline)) emscripten_bind_b2World__IsLocked_p0(b2World * self) {
  return self->IsLocked();
}
b2Contact* __attribute__((used, noinline)) emscripten_bind_b2World__GetContactList_p0(b2World * self) {
  return self->GetContactList();
}
void __attribute__((used, noinline)) emscripten_bind_b2World__SetDebugDraw_p1(b2World * self, b2Draw * arg0) {
  self->SetDebugDraw(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2World____destroy___p0(b2World * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2World__Dump_p0(b2World * self) {
  self->Dump();
}
void __attribute__((used, noinline)) emscripten_bind_b2World__SetAutoClearForces_p1(b2World * self, bool arg0) {
  self->SetAutoClearForces(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2World__GetGravity_p0(b2World * self) {
  static b2Vec2 ret; ret = self->GetGravity();
  return ret;
}
int __attribute__((used, noinline)) emscripten_bind_b2World__GetContactCount_p0(b2World * self) {
  return self->GetContactCount();
}
void __attribute__((used, noinline)) emscripten_bind_b2World__SetWarmStarting_p1(b2World * self, bool arg0) {
  self->SetWarmStarting(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2World__SetContactFilter_p1(b2World * self, b2ContactFilter * arg0) {
  self->SetContactFilter(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetBodyA_p0(b2PrismaticJoint * self) {
  return self->GetBodyA();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetBodyB_p0(b2PrismaticJoint * self) {
  return self->GetBodyB();
}
void* __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetUserData_p0(b2PrismaticJoint * self) {
  return self->GetUserData();
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetLocalAxisA_p0(b2PrismaticJoint * self) {
  return self->GetLocalAxisA();
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetLowerLimit_p0(b2PrismaticJoint * self) {
  return self->GetLowerLimit();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetAnchorA_p0(b2PrismaticJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorA();
  return ret;
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetNext_p0(b2PrismaticJoint * self) {
  return self->GetNext();
}
b2PrismaticJoint * __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__b2PrismaticJoint_p1(const b2PrismaticJointDef * arg0) {
  return new b2PrismaticJoint(arg0);
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetLocalAnchorA_p0(b2PrismaticJoint * self) {
  return self->GetLocalAnchorA();
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__SetMotorSpeed_p1(b2PrismaticJoint * self, float arg0) {
  self->SetMotorSpeed(arg0);
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetLocalAnchorB_p0(b2PrismaticJoint * self) {
  return self->GetLocalAnchorB();
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetMotorSpeed_p0(b2PrismaticJoint * self) {
  return self->GetMotorSpeed();
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__SetMaxMotorForce_p1(b2PrismaticJoint * self, float arg0) {
  self->SetMaxMotorForce(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__EnableLimit_p1(b2PrismaticJoint * self, bool arg0) {
  self->EnableLimit(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__IsMotorEnabled_p0(b2PrismaticJoint * self) {
  return self->IsMotorEnabled();
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__SetUserData_p1(b2PrismaticJoint * self, void * arg0) {
  self->SetUserData(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetReactionForce_p1(b2PrismaticJoint * self, float arg0) {
  static b2Vec2 ret; ret = self->GetReactionForce(arg0);
  return ret;
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetMaxMotorForce_p0(b2PrismaticJoint * self) {
  return self->GetMaxMotorForce();
}
bool __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetCollideConnected_p0(b2PrismaticJoint * self) {
  return self->GetCollideConnected();
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetJointSpeed_p0(b2PrismaticJoint * self) {
  return self->GetJointSpeed();
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__EnableMotor_p1(b2PrismaticJoint * self, bool arg0) {
  self->EnableMotor(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint____destroy___p0(b2PrismaticJoint * self) {
  delete self;
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetReferenceAngle_p0(b2PrismaticJoint * self) {
  return self->GetReferenceAngle();
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__Dump_p0(b2PrismaticJoint * self) {
  self->Dump();
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetMotorForce_p1(b2PrismaticJoint * self, float arg0) {
  return self->GetMotorForce(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetJointTranslation_p0(b2PrismaticJoint * self) {
  return self->GetJointTranslation();
}
int __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetType_p0(b2PrismaticJoint * self) {
  return self->GetType();
}
bool __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__IsLimitEnabled_p0(b2PrismaticJoint * self) {
  return self->IsLimitEnabled();
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetReactionTorque_p1(b2PrismaticJoint * self, float arg0) {
  return self->GetReactionTorque(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__SetLimits_p2(b2PrismaticJoint * self, float arg0, float arg1) {
  self->SetLimits(arg0, arg1);
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetUpperLimit_p0(b2PrismaticJoint * self) {
  return self->GetUpperLimit();
}
bool __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__IsActive_p0(b2PrismaticJoint * self) {
  return self->IsActive();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PrismaticJoint__GetAnchorB_p0(b2PrismaticJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorB();
  return ret;
}
void __attribute__((used, noinline)) emscripten_bind_b2CircleShape____destroy___p0(b2CircleShape * self) {
  delete self;
}
int __attribute__((used, noinline)) emscripten_bind_b2CircleShape__GetType_p0(b2CircleShape * self) {
  return self->GetType();
}
void __attribute__((used, noinline)) emscripten_bind_b2CircleShape__ComputeMass_p2(b2CircleShape * self, b2MassData * arg0, float arg1) {
  self->ComputeMass(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2CircleShape__set_m_radius_p1(b2CircleShape * self, float arg0) {
  self->m_radius = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2CircleShape__get_m_radius_p0(b2CircleShape * self) {
  return self->m_radius;
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2CircleShape__GetVertex_p1(b2CircleShape * self, signed int arg0) {
  return self->GetVertex(arg0);
}
b2Shape* __attribute__((used, noinline)) emscripten_bind_b2CircleShape__Clone_p1(b2CircleShape * self, b2BlockAllocator * arg0) {
  return self->Clone(arg0);
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2CircleShape__GetSupportVertex_p1(b2CircleShape * self, const b2Vec2 & arg0) {
  return self->GetSupportVertex(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2CircleShape__RayCast_p4(b2CircleShape * self, b2RayCastOutput * arg0, const b2RayCastInput & arg1, const b2Transform & arg2, signed int arg3) {
  return self->RayCast(arg0, arg1, arg2, arg3);
}
void __attribute__((used, noinline)) emscripten_bind_b2CircleShape__ComputeAABB_p3(b2CircleShape * self, b2AABB * arg0, const b2Transform & arg1, signed int arg2) {
  self->ComputeAABB(arg0, arg1, arg2);
}
int __attribute__((used, noinline)) emscripten_bind_b2CircleShape__GetVertexCount_p0(b2CircleShape * self) {
  return self->GetVertexCount();
}
int __attribute__((used, noinline)) emscripten_bind_b2CircleShape__GetChildCount_p0(b2CircleShape * self) {
  return self->GetChildCount();
}
bool __attribute__((used, noinline)) emscripten_bind_b2CircleShape__TestPoint_p2(b2CircleShape * self, const b2Transform & arg0, const b2Vec2 & arg1) {
  return self->TestPoint(arg0, arg1);
}
b2CircleShape * __attribute__((used, noinline)) emscripten_bind_b2CircleShape__b2CircleShape_p0() {
  return new b2CircleShape();
}
int __attribute__((used, noinline)) emscripten_bind_b2CircleShape__GetSupport_p1(b2CircleShape * self, const b2Vec2 & arg0) {
  return self->GetSupport(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2CircleShape__set_m_p_p1(b2CircleShape * self, b2Vec2& arg0) {
  self->m_p = arg0;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2CircleShape__get_m_p_p0(b2CircleShape * self) {
  return self->m_p;
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetBodyA_p0(b2WheelJoint * self) {
  return self->GetBodyA();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetBodyB_p0(b2WheelJoint * self) {
  return self->GetBodyB();
}
void* __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetUserData_p0(b2WheelJoint * self) {
  return self->GetUserData();
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetDefinition_p1(b2WheelJoint * self, b2WheelJointDef * arg0) {
  self->GetDefinition(arg0);
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetLocalAxisA_p0(b2WheelJoint * self) {
  return self->GetLocalAxisA();
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__SetSpringDampingRatio_p1(b2WheelJoint * self, float arg0) {
  self->SetSpringDampingRatio(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetAnchorB_p0(b2WheelJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorB();
  return ret;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetAnchorA_p0(b2WheelJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorA();
  return ret;
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetNext_p0(b2WheelJoint * self) {
  return self->GetNext();
}
float __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetSpringFrequencyHz_p0(b2WheelJoint * self) {
  return self->GetSpringFrequencyHz();
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetLocalAnchorA_p0(b2WheelJoint * self) {
  return self->GetLocalAnchorA();
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__SetMotorSpeed_p1(b2WheelJoint * self, float arg0) {
  self->SetMotorSpeed(arg0);
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetLocalAnchorB_p0(b2WheelJoint * self) {
  return self->GetLocalAnchorB();
}
float __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetMotorSpeed_p0(b2WheelJoint * self) {
  return self->GetMotorSpeed();
}
float __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetMotorTorque_p1(b2WheelJoint * self, float arg0) {
  return self->GetMotorTorque(arg0);
}
b2WheelJoint * __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__b2WheelJoint_p1(const b2WheelJointDef * arg0) {
  return new b2WheelJoint(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__IsMotorEnabled_p0(b2WheelJoint * self) {
  return self->IsMotorEnabled();
}
float __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetJointTranslation_p0(b2WheelJoint * self) {
  return self->GetJointTranslation();
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__SetUserData_p1(b2WheelJoint * self, void * arg0) {
  self->SetUserData(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetReactionForce_p1(b2WheelJoint * self, float arg0) {
  static b2Vec2 ret; ret = self->GetReactionForce(arg0);
  return ret;
}
float __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetSpringDampingRatio_p0(b2WheelJoint * self) {
  return self->GetSpringDampingRatio();
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__SetMaxMotorTorque_p1(b2WheelJoint * self, float arg0) {
  self->SetMaxMotorTorque(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetCollideConnected_p0(b2WheelJoint * self) {
  return self->GetCollideConnected();
}
float __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetJointSpeed_p0(b2WheelJoint * self) {
  return self->GetJointSpeed();
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__EnableMotor_p1(b2WheelJoint * self, bool arg0) {
  self->EnableMotor(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJoint____destroy___p0(b2WheelJoint * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__Dump_p0(b2WheelJoint * self) {
  self->Dump();
}
float __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetMaxMotorTorque_p0(b2WheelJoint * self) {
  return self->GetMaxMotorTorque();
}
int __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetType_p0(b2WheelJoint * self) {
  return self->GetType();
}
float __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__GetReactionTorque_p1(b2WheelJoint * self, float arg0) {
  return self->GetReactionTorque(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__SetSpringFrequencyHz_p1(b2WheelJoint * self, float arg0) {
  self->SetSpringFrequencyHz(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2WheelJoint__IsActive_p0(b2WheelJoint * self) {
  return self->IsActive();
}
void __attribute__((used, noinline)) emscripten_bind_b2Draw____destroy___p0(b2Draw * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2Draw__AppendFlags_p1(b2Draw * self, unsigned int arg0) {
  self->AppendFlags(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Draw__DrawTransform_p1(b2Draw * self, const b2Transform & arg0) {
  self->DrawTransform(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Draw__ClearFlags_p1(b2Draw * self, unsigned int arg0) {
  self->ClearFlags(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Draw__DrawPolygon_p3(b2Draw * self, const b2Vec2 * arg0, signed int arg1, const b2Color & arg2) {
  self->DrawPolygon(arg0, arg1, arg2);
}
void __attribute__((used, noinline)) emscripten_bind_b2Draw__DrawSolidCircle_p4(b2Draw * self, const b2Vec2 & arg0, float arg1, const b2Vec2 & arg2, const b2Color & arg3) {
  self->DrawSolidCircle(arg0, arg1, arg2, arg3);
}
void __attribute__((used, noinline)) emscripten_bind_b2Draw__DrawSolidPolygon_p3(b2Draw * self, const b2Vec2 * arg0, signed int arg1, const b2Color & arg2) {
  self->DrawSolidPolygon(arg0, arg1, arg2);
}
void __attribute__((used, noinline)) emscripten_bind_b2Draw__DrawCircle_p3(b2Draw * self, const b2Vec2 & arg0, float arg1, const b2Color & arg2) {
  self->DrawCircle(arg0, arg1, arg2);
}
void __attribute__((used, noinline)) emscripten_bind_b2Draw__SetFlags_p1(b2Draw * self, unsigned int arg0) {
  self->SetFlags(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Draw__DrawSegment_p3(b2Draw * self, const b2Vec2 & arg0, const b2Vec2 & arg1, const b2Color & arg2) {
  self->DrawSegment(arg0, arg1, arg2);
}
b2Draw * __attribute__((used, noinline)) emscripten_bind_b2Draw__b2Draw_p0() {
  return new b2Draw();
}
unsigned int __attribute__((used, noinline)) emscripten_bind_b2Draw__GetFlags_p0(b2Draw * self) {
  return self->GetFlags();
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2Joint__GetNext_p0(b2Joint * self) {
  return self->GetNext();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2Joint__GetBodyA_p0(b2Joint * self) {
  return self->GetBodyA();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2Joint__GetBodyB_p0(b2Joint * self) {
  return self->GetBodyB();
}
float __attribute__((used, noinline)) emscripten_bind_b2Joint__GetReactionTorque_p1(b2Joint * self, float arg0) {
  return self->GetReactionTorque(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Joint__GetAnchorA_p0(b2Joint * self) {
  static b2Vec2 ret; ret = self->GetAnchorA();
  return ret;
}
void* __attribute__((used, noinline)) emscripten_bind_b2Joint__GetUserData_p0(b2Joint * self) {
  return self->GetUserData();
}
int __attribute__((used, noinline)) emscripten_bind_b2Joint__GetType_p0(b2Joint * self) {
  return self->GetType();
}
void __attribute__((used, noinline)) emscripten_bind_b2Joint__SetUserData_p1(b2Joint * self, void * arg0) {
  self->SetUserData(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2Joint__GetCollideConnected_p0(b2Joint * self) {
  return self->GetCollideConnected();
}
void __attribute__((used, noinline)) emscripten_bind_b2Joint__Dump_p0(b2Joint * self) {
  self->Dump();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Joint__GetAnchorB_p0(b2Joint * self) {
  static b2Vec2 ret; ret = self->GetAnchorB();
  return ret;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Joint__GetReactionForce_p1(b2Joint * self, float arg0) {
  static b2Vec2 ret; ret = self->GetReactionForce(arg0);
  return ret;
}
bool __attribute__((used, noinline)) emscripten_bind_b2Joint__IsActive_p0(b2Joint * self) {
  return self->IsActive();
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2GearJoint__GetJoint1_p0(b2GearJoint * self) {
  return self->GetJoint1();
}
b2GearJoint * __attribute__((used, noinline)) emscripten_bind_b2GearJoint__b2GearJoint_p1(const b2GearJointDef * arg0) {
  return new b2GearJoint(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2GearJoint__GetAnchorA_p0(b2GearJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorA();
  return ret;
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2GearJoint__GetJoint2_p0(b2GearJoint * self) {
  return self->GetJoint2();
}
float __attribute__((used, noinline)) emscripten_bind_b2GearJoint__GetReactionTorque_p1(b2GearJoint * self, float arg0) {
  return self->GetReactionTorque(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2GearJoint__Dump_p0(b2GearJoint * self) {
  self->Dump();
}
void __attribute__((used, noinline)) emscripten_bind_b2GearJoint____destroy___p0(b2GearJoint * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2GearJoint__SetRatio_p1(b2GearJoint * self, float arg0) {
  self->SetRatio(arg0);
}
int __attribute__((used, noinline)) emscripten_bind_b2GearJoint__GetType_p0(b2GearJoint * self) {
  return self->GetType();
}
void* __attribute__((used, noinline)) emscripten_bind_b2GearJoint__GetUserData_p0(b2GearJoint * self) {
  return self->GetUserData();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2GearJoint__GetBodyB_p0(b2GearJoint * self) {
  return self->GetBodyB();
}
bool __attribute__((used, noinline)) emscripten_bind_b2GearJoint__GetCollideConnected_p0(b2GearJoint * self) {
  return self->GetCollideConnected();
}
void __attribute__((used, noinline)) emscripten_bind_b2GearJoint__SetUserData_p1(b2GearJoint * self, void * arg0) {
  self->SetUserData(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2GearJoint__GetAnchorB_p0(b2GearJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorB();
  return ret;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2GearJoint__GetReactionForce_p1(b2GearJoint * self, float arg0) {
  static b2Vec2 ret; ret = self->GetReactionForce(arg0);
  return ret;
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2GearJoint__GetBodyA_p0(b2GearJoint * self) {
  return self->GetBodyA();
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2GearJoint__GetNext_p0(b2GearJoint * self) {
  return self->GetNext();
}
bool __attribute__((used, noinline)) emscripten_bind_b2GearJoint__IsActive_p0(b2GearJoint * self) {
  return self->IsActive();
}
float __attribute__((used, noinline)) emscripten_bind_b2GearJoint__GetRatio_p0(b2GearJoint * self) {
  return self->GetRatio();
}
float __attribute__((used, noinline)) emscripten_bind_b2RayCastCallback__ReportFixture_p4(b2RayCastCallback * self, b2Fixture * arg0, const b2Vec2 & arg1, const b2Vec2 & arg2, float arg3) {
  return self->ReportFixture(arg0, arg1, arg2, arg3);
}
b2RayCastCallback * __attribute__((used, noinline)) emscripten_bind_b2RayCastCallback__b2RayCastCallback_p0() {
  return new b2RayCastCallback();
}
void __attribute__((used, noinline)) emscripten_bind_b2RayCastCallback____destroy___p0(b2RayCastCallback * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2DynamicTree____destroy___p0(b2DynamicTree * self) {
  delete self;
}
b2DynamicTree * __attribute__((used, noinline)) emscripten_bind_b2DynamicTree__b2DynamicTree_p0() {
  return new b2DynamicTree();
}
const b2AABB& __attribute__((used, noinline)) emscripten_bind_b2DynamicTree__GetFatAABB_p1(b2DynamicTree * self, signed int arg0) {
  return self->GetFatAABB(arg0);
}
void* __attribute__((used, noinline)) emscripten_bind_b2DynamicTree__GetUserData_p1(b2DynamicTree * self, signed int arg0) {
  return self->GetUserData(arg0);
}
int __attribute__((used, noinline)) emscripten_bind_b2DynamicTree__GetMaxBalance_p0(b2DynamicTree * self) {
  return self->GetMaxBalance();
}
int __attribute__((used, noinline)) emscripten_bind_b2DynamicTree__GetHeight_p0(b2DynamicTree * self) {
  return self->GetHeight();
}
float __attribute__((used, noinline)) emscripten_bind_b2DynamicTree__GetAreaRatio_p0(b2DynamicTree * self) {
  return self->GetAreaRatio();
}
void __attribute__((used, noinline)) emscripten_bind_b2DynamicTree__RebuildBottomUp_p0(b2DynamicTree * self) {
  self->RebuildBottomUp();
}
int __attribute__((used, noinline)) emscripten_bind_b2DynamicTree__CreateProxy_p2(b2DynamicTree * self, const b2AABB & arg0, void * arg1) {
  return self->CreateProxy(arg0, arg1);
}
bool __attribute__((used, noinline)) emscripten_bind_b2DynamicTree__MoveProxy_p3(b2DynamicTree * self, signed int arg0, const b2AABB & arg1, const b2Vec2 & arg2) {
  return self->MoveProxy(arg0, arg1, arg2);
}
void __attribute__((used, noinline)) emscripten_bind_b2DynamicTree__Validate_p0(b2DynamicTree * self) {
  self->Validate();
}
void __attribute__((used, noinline)) emscripten_bind_b2DynamicTree__DestroyProxy_p1(b2DynamicTree * self, signed int arg0) {
  self->DestroyProxy(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetBodyA_p0(b2WeldJoint * self) {
  return self->GetBodyA();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetBodyB_p0(b2WeldJoint * self) {
  return self->GetBodyB();
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__SetFrequency_p1(b2WeldJoint * self, float arg0) {
  self->SetFrequency(arg0);
}
void* __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetUserData_p0(b2WeldJoint * self) {
  return self->GetUserData();
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__SetUserData_p1(b2WeldJoint * self, void * arg0) {
  self->SetUserData(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetAnchorB_p0(b2WeldJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorB();
  return ret;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetAnchorA_p0(b2WeldJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorA();
  return ret;
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetNext_p0(b2WeldJoint * self) {
  return self->GetNext();
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetLocalAnchorA_p0(b2WeldJoint * self) {
  return self->GetLocalAnchorA();
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetLocalAnchorB_p0(b2WeldJoint * self) {
  return self->GetLocalAnchorB();
}
float __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetFrequency_p0(b2WeldJoint * self) {
  return self->GetFrequency();
}
b2WeldJoint * __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__b2WeldJoint_p1(const b2WeldJointDef * arg0) {
  return new b2WeldJoint(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetReactionForce_p1(b2WeldJoint * self, float arg0) {
  static b2Vec2 ret; ret = self->GetReactionForce(arg0);
  return ret;
}
float __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetDampingRatio_p0(b2WeldJoint * self) {
  return self->GetDampingRatio();
}
bool __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetCollideConnected_p0(b2WeldJoint * self) {
  return self->GetCollideConnected();
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJoint____destroy___p0(b2WeldJoint * self) {
  delete self;
}
float __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetReferenceAngle_p0(b2WeldJoint * self) {
  return self->GetReferenceAngle();
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__Dump_p0(b2WeldJoint * self) {
  self->Dump();
}
int __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetType_p0(b2WeldJoint * self) {
  return self->GetType();
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__SetDampingRatio_p1(b2WeldJoint * self, float arg0) {
  self->SetDampingRatio(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__GetReactionTorque_p1(b2WeldJoint * self, float arg0) {
  return self->GetReactionTorque(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2WeldJoint__IsActive_p0(b2WeldJoint * self) {
  return self->IsActive();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetBodyA_p0(b2RevoluteJoint * self) {
  return self->GetBodyA();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetBodyB_p0(b2RevoluteJoint * self) {
  return self->GetBodyB();
}
void* __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetUserData_p0(b2RevoluteJoint * self) {
  return self->GetUserData();
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetLowerLimit_p0(b2RevoluteJoint * self) {
  return self->GetLowerLimit();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetAnchorA_p0(b2RevoluteJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorA();
  return ret;
}
b2RevoluteJoint * __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__b2RevoluteJoint_p1(const b2RevoluteJointDef * arg0) {
  return new b2RevoluteJoint(arg0);
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetNext_p0(b2RevoluteJoint * self) {
  return self->GetNext();
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetLocalAnchorA_p0(b2RevoluteJoint * self) {
  return self->GetLocalAnchorA();
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__SetMotorSpeed_p1(b2RevoluteJoint * self, float arg0) {
  self->SetMotorSpeed(arg0);
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetLocalAnchorB_p0(b2RevoluteJoint * self) {
  return self->GetLocalAnchorB();
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetJointAngle_p0(b2RevoluteJoint * self) {
  return self->GetJointAngle();
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetMotorSpeed_p0(b2RevoluteJoint * self) {
  return self->GetMotorSpeed();
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetMotorTorque_p1(b2RevoluteJoint * self, float arg0) {
  return self->GetMotorTorque(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__IsLimitEnabled_p0(b2RevoluteJoint * self) {
  return self->IsLimitEnabled();
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__EnableLimit_p1(b2RevoluteJoint * self, bool arg0) {
  self->EnableLimit(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__IsMotorEnabled_p0(b2RevoluteJoint * self) {
  return self->IsMotorEnabled();
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__SetUserData_p1(b2RevoluteJoint * self, void * arg0) {
  self->SetUserData(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetReactionForce_p1(b2RevoluteJoint * self, float arg0) {
  static b2Vec2 ret; ret = self->GetReactionForce(arg0);
  return ret;
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__SetMaxMotorTorque_p1(b2RevoluteJoint * self, float arg0) {
  self->SetMaxMotorTorque(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetCollideConnected_p0(b2RevoluteJoint * self) {
  return self->GetCollideConnected();
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetJointSpeed_p0(b2RevoluteJoint * self) {
  return self->GetJointSpeed();
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__EnableMotor_p1(b2RevoluteJoint * self, bool arg0) {
  self->EnableMotor(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint____destroy___p0(b2RevoluteJoint * self) {
  delete self;
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetReferenceAngle_p0(b2RevoluteJoint * self) {
  return self->GetReferenceAngle();
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__Dump_p0(b2RevoluteJoint * self) {
  self->Dump();
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__SetLimits_p2(b2RevoluteJoint * self, float arg0, float arg1) {
  self->SetLimits(arg0, arg1);
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetMaxMotorTorque_p0(b2RevoluteJoint * self) {
  return self->GetMaxMotorTorque();
}
int __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetType_p0(b2RevoluteJoint * self) {
  return self->GetType();
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetReactionTorque_p1(b2RevoluteJoint * self, float arg0) {
  return self->GetReactionTorque(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetUpperLimit_p0(b2RevoluteJoint * self) {
  return self->GetUpperLimit();
}
bool __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__IsActive_p0(b2RevoluteJoint * self) {
  return self->IsActive();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RevoluteJoint__GetAnchorB_p0(b2RevoluteJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorB();
  return ret;
}
b2Timer * __attribute__((used, noinline)) emscripten_bind_b2Timer__b2Timer_p0() {
  return new b2Timer();
}
void __attribute__((used, noinline)) emscripten_bind_b2Timer__Reset_p0(b2Timer * self) {
  self->Reset();
}
void __attribute__((used, noinline)) emscripten_bind_b2Timer____destroy___p0(b2Timer * self) {
  delete self;
}
float __attribute__((used, noinline)) emscripten_bind_b2Timer__GetMilliseconds_p0(b2Timer * self) {
  return self->GetMilliseconds();
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactListener____destroy___p0(b2ContactListener * self) {
  delete self;
}
b2ContactListener * __attribute__((used, noinline)) emscripten_bind_b2ContactListener__b2ContactListener_p0() {
  return new b2ContactListener();
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactListener__EndContact_p1(b2ContactListener * self, b2Contact * arg0) {
  self->EndContact(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactListener__BeginContact_p1(b2ContactListener * self, b2Contact * arg0) {
  self->BeginContact(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactListener__PreSolve_p2(b2ContactListener * self, b2Contact * arg0, const b2Manifold * arg1) {
  self->PreSolve(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactListener__PostSolve_p2(b2ContactListener * self, b2Contact * arg0, const b2ContactImpulse * arg1) {
  self->PostSolve(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2ChainShape____destroy___p0(b2ChainShape * self) {
  delete self;
}
int __attribute__((used, noinline)) emscripten_bind_b2ChainShape__GetType_p0(b2ChainShape * self) {
  return self->GetType();
}
void __attribute__((used, noinline)) emscripten_bind_b2ChainShape__CreateChain_p2(b2ChainShape * self, const b2Vec2 * arg0, signed int arg1) {
  self->CreateChain(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2ChainShape__set_m_radius_p1(b2ChainShape * self, float arg0) {
  self->m_radius = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2ChainShape__get_m_radius_p0(b2ChainShape * self) {
  return self->m_radius;
}
b2Vec2 * __attribute__((used, noinline)) emscripten_bind_b2ChainShape__get_m_vertices_p0(b2ChainShape * self) {
  return self->m_vertices;
}
void __attribute__((used, noinline)) emscripten_bind_b2ChainShape__ComputeMass_p2(b2ChainShape * self, b2MassData * arg0, float arg1) {
  self->ComputeMass(arg0, arg1);
}
b2Shape* __attribute__((used, noinline)) emscripten_bind_b2ChainShape__Clone_p1(b2ChainShape * self, b2BlockAllocator * arg0) {
  return self->Clone(arg0);
}
signed int __attribute__((used, noinline)) emscripten_bind_b2ChainShape__get_m_count_p0(b2ChainShape * self) {
  return self->m_count;
}
void __attribute__((used, noinline)) emscripten_bind_b2ChainShape__GetChildEdge_p2(b2ChainShape * self, b2EdgeShape * arg0, signed int arg1) {
  self->GetChildEdge(arg0, arg1);
}
b2ChainShape * __attribute__((used, noinline)) emscripten_bind_b2ChainShape__b2ChainShape_p0() {
  return new b2ChainShape();
}
void __attribute__((used, noinline)) emscripten_bind_b2ChainShape__ComputeAABB_p3(b2ChainShape * self, b2AABB * arg0, const b2Transform & arg1, signed int arg2) {
  self->ComputeAABB(arg0, arg1, arg2);
}
bool __attribute__((used, noinline)) emscripten_bind_b2ChainShape__RayCast_p4(b2ChainShape * self, b2RayCastOutput * arg0, const b2RayCastInput & arg1, const b2Transform & arg2, signed int arg3) {
  return self->RayCast(arg0, arg1, arg2, arg3);
}
int __attribute__((used, noinline)) emscripten_bind_b2ChainShape__GetChildCount_p0(b2ChainShape * self) {
  return self->GetChildCount();
}
bool __attribute__((used, noinline)) emscripten_bind_b2ChainShape__TestPoint_p2(b2ChainShape * self, const b2Transform & arg0, const b2Vec2 & arg1) {
  return self->TestPoint(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2ChainShape__SetPrevVertex_p1(b2ChainShape * self, const b2Vec2 & arg0) {
  self->SetPrevVertex(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2ChainShape__CreateLoop_p2(b2ChainShape * self, const b2Vec2 * arg0, signed int arg1) {
  self->CreateLoop(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2ChainShape__set_m_vertices_p1(b2ChainShape * self, b2Vec2 * arg0) {
  self->m_vertices = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2ChainShape__SetNextVertex_p1(b2ChainShape * self, const b2Vec2 & arg0) {
  self->SetNextVertex(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2ChainShape__set_m_count_p1(b2ChainShape * self, signed int arg0) {
  self->m_count = arg0;
}
bool __attribute__((used, noinline)) emscripten_bind_b2QueryCallback__ReportFixture_p1(b2QueryCallback * self, b2Fixture * arg0) {
  return self->ReportFixture(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2QueryCallback____destroy___p0(b2QueryCallback * self) {
  delete self;
}
b2QueryCallback * __attribute__((used, noinline)) emscripten_bind_b2QueryCallback__b2QueryCallback_p0() {
  return new b2QueryCallback();
}
void __attribute__((used, noinline)) emscripten_bind_b2BlockAllocator____destroy___p0(b2BlockAllocator * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2BlockAllocator__Clear_p0(b2BlockAllocator * self) {
  self->Clear();
}
void __attribute__((used, noinline)) emscripten_bind_b2BlockAllocator__Free_p2(b2BlockAllocator * self, void * arg0, signed int arg1) {
  self->Free(arg0, arg1);
}
void* __attribute__((used, noinline)) emscripten_bind_b2BlockAllocator__Allocate_p1(b2BlockAllocator * self, signed int arg0) {
  return self->Allocate(arg0);
}
b2BlockAllocator * __attribute__((used, noinline)) emscripten_bind_b2BlockAllocator__b2BlockAllocator_p0() {
  return new b2BlockAllocator();
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetNext_p0(b2RopeJoint * self) {
  return self->GetNext();
}
void __attribute__((used, noinline)) emscripten_bind_b2RopeJoint____destroy___p0(b2RopeJoint * self) {
  delete self;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetAnchorA_p0(b2RopeJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorA();
  return ret;
}
float __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetReactionTorque_p1(b2RopeJoint * self, float arg0) {
  return self->GetReactionTorque(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetMaxLength_p0(b2RopeJoint * self) {
  return self->GetMaxLength();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetBodyA_p0(b2RopeJoint * self) {
  return self->GetBodyA();
}
bool __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetCollideConnected_p0(b2RopeJoint * self) {
  return self->GetCollideConnected();
}
void* __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetUserData_p0(b2RopeJoint * self) {
  return self->GetUserData();
}
int __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetType_p0(b2RopeJoint * self) {
  return self->GetType();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetBodyB_p0(b2RopeJoint * self) {
  return self->GetBodyB();
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetLocalAnchorA_p0(b2RopeJoint * self) {
  return self->GetLocalAnchorA();
}
void __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__Dump_p0(b2RopeJoint * self) {
  self->Dump();
}
void __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__SetMaxLength_p1(b2RopeJoint * self, float arg0) {
  self->SetMaxLength(arg0);
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetLocalAnchorB_p0(b2RopeJoint * self) {
  return self->GetLocalAnchorB();
}
void __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__SetUserData_p1(b2RopeJoint * self, void * arg0) {
  self->SetUserData(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetAnchorB_p0(b2RopeJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorB();
  return ret;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetReactionForce_p1(b2RopeJoint * self, float arg0) {
  static b2Vec2 ret; ret = self->GetReactionForce(arg0);
  return ret;
}
b2RopeJoint * __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__b2RopeJoint_p1(const b2RopeJointDef * arg0) {
  return new b2RopeJoint(arg0);
}
int __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__GetLimitState_p0(b2RopeJoint * self) {
  return self->GetLimitState();
}
bool __attribute__((used, noinline)) emscripten_bind_b2RopeJoint__IsActive_p0(b2RopeJoint * self) {
  return self->IsActive();
}
void __attribute__((used, noinline)) emscripten_bind_b2PolygonShape____destroy___p0(b2PolygonShape * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__Set_p2(b2PolygonShape * self, const b2Vec2 * arg0, signed int arg1) {
  self->Set(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__ComputeMass_p2(b2PolygonShape * self, b2MassData * arg0, float arg1) {
  self->ComputeMass(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__set_m_radius_p1(b2PolygonShape * self, float arg0) {
  self->m_radius = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__get_m_radius_p0(b2PolygonShape * self) {
  return self->m_radius;
}
b2Shape* __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__Clone_p1(b2PolygonShape * self, b2BlockAllocator * arg0) {
  return self->Clone(arg0);
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__GetVertex_p1(b2PolygonShape * self, signed int arg0) {
  return self->GetVertex(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__RayCast_p4(b2PolygonShape * self, b2RayCastOutput * arg0, const b2RayCastInput & arg1, const b2Transform & arg2, signed int arg3) {
  return self->RayCast(arg0, arg1, arg2, arg3);
}
void __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__SetAsBox_p2(b2PolygonShape * self, float arg0, float arg1) {
  self->SetAsBox(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__SetAsBox_p4(b2PolygonShape * self, float arg0, float arg1, const b2Vec2 & arg2, float arg3) {
  self->SetAsBox(arg0, arg1, arg2, arg3);
}
void __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__set_m_centroid_p1(b2PolygonShape * self, b2Vec2& arg0) {
  self->m_centroid = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__ComputeAABB_p3(b2PolygonShape * self, b2AABB * arg0, const b2Transform & arg1, signed int arg2) {
  self->ComputeAABB(arg0, arg1, arg2);
}
void __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__set_m_vertexCount_p1(b2PolygonShape * self, signed int arg0) {
  self->m_vertexCount = arg0;
}
int __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__GetVertexCount_p0(b2PolygonShape * self) {
  return self->GetVertexCount();
}
int __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__GetChildCount_p0(b2PolygonShape * self) {
  return self->GetChildCount();
}
bool __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__TestPoint_p2(b2PolygonShape * self, const b2Transform & arg0, const b2Vec2 & arg1) {
  return self->TestPoint(arg0, arg1);
}
int __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__GetType_p0(b2PolygonShape * self) {
  return self->GetType();
}
b2PolygonShape * __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__b2PolygonShape_p0() {
  return new b2PolygonShape();
}
signed int __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__get_m_vertexCount_p0(b2PolygonShape * self) {
  return self->m_vertexCount;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PolygonShape__get_m_centroid_p0(b2PolygonShape * self) {
  return self->m_centroid;
}
void __attribute__((used, noinline)) emscripten_bind_b2EdgeShape____destroy___p0(b2EdgeShape * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2EdgeShape__Set_p2(b2EdgeShape * self, const b2Vec2 & arg0, const b2Vec2 & arg1) {
  self->Set(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2EdgeShape__ComputeMass_p2(b2EdgeShape * self, b2MassData * arg0, float arg1) {
  self->ComputeMass(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2EdgeShape__set_m_radius_p1(b2EdgeShape * self, float arg0) {
  self->m_radius = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2EdgeShape__get_m_radius_p0(b2EdgeShape * self) {
  return self->m_radius;
}
b2Shape* __attribute__((used, noinline)) emscripten_bind_b2EdgeShape__Clone_p1(b2EdgeShape * self, b2BlockAllocator * arg0) {
  return self->Clone(arg0);
}
int __attribute__((used, noinline)) emscripten_bind_b2EdgeShape__GetType_p0(b2EdgeShape * self) {
  return self->GetType();
}
bool __attribute__((used, noinline)) emscripten_bind_b2EdgeShape__RayCast_p4(b2EdgeShape * self, b2RayCastOutput * arg0, const b2RayCastInput & arg1, const b2Transform & arg2, signed int arg3) {
  return self->RayCast(arg0, arg1, arg2, arg3);
}
void __attribute__((used, noinline)) emscripten_bind_b2EdgeShape__ComputeAABB_p3(b2EdgeShape * self, b2AABB * arg0, const b2Transform & arg1, signed int arg2) {
  self->ComputeAABB(arg0, arg1, arg2);
}
int __attribute__((used, noinline)) emscripten_bind_b2EdgeShape__GetChildCount_p0(b2EdgeShape * self) {
  return self->GetChildCount();
}
bool __attribute__((used, noinline)) emscripten_bind_b2EdgeShape__TestPoint_p2(b2EdgeShape * self, const b2Transform & arg0, const b2Vec2 & arg1) {
  return self->TestPoint(arg0, arg1);
}
b2EdgeShape * __attribute__((used, noinline)) emscripten_bind_b2EdgeShape__b2EdgeShape_p0() {
  return new b2EdgeShape();
}
b2Contact* __attribute__((used, noinline)) emscripten_bind_b2Contact__GetNext_p0(b2Contact * self) {
  return self->GetNext();
}
void __attribute__((used, noinline)) emscripten_bind_b2Contact__SetEnabled_p1(b2Contact * self, bool arg0) {
  self->SetEnabled(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Contact__GetWorldManifold_p1(b2Contact * self, b2WorldManifold * arg0) {
  self->GetWorldManifold(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2Contact__GetRestitution_p0(b2Contact * self) {
  return self->GetRestitution();
}
void __attribute__((used, noinline)) emscripten_bind_b2Contact__ResetFriction_p0(b2Contact * self) {
  self->ResetFriction();
}
float __attribute__((used, noinline)) emscripten_bind_b2Contact__GetFriction_p0(b2Contact * self) {
  return self->GetFriction();
}
bool __attribute__((used, noinline)) emscripten_bind_b2Contact__IsTouching_p0(b2Contact * self) {
  return self->IsTouching();
}
bool __attribute__((used, noinline)) emscripten_bind_b2Contact__IsEnabled_p0(b2Contact * self) {
  return self->IsEnabled();
}
b2Fixture* __attribute__((used, noinline)) emscripten_bind_b2Contact__GetFixtureB_p0(b2Contact * self) {
  return self->GetFixtureB();
}
void __attribute__((used, noinline)) emscripten_bind_b2Contact__SetFriction_p1(b2Contact * self, float arg0) {
  self->SetFriction(arg0);
}
b2Fixture* __attribute__((used, noinline)) emscripten_bind_b2Contact__GetFixtureA_p0(b2Contact * self) {
  return self->GetFixtureA();
}
int __attribute__((used, noinline)) emscripten_bind_b2Contact__GetChildIndexA_p0(b2Contact * self) {
  return self->GetChildIndexA();
}
int __attribute__((used, noinline)) emscripten_bind_b2Contact__GetChildIndexB_p0(b2Contact * self) {
  return self->GetChildIndexB();
}
void __attribute__((used, noinline)) emscripten_bind_b2Contact__Evaluate_p3(b2Contact * self, b2Manifold * arg0, const b2Transform & arg1, const b2Transform & arg2) {
  self->Evaluate(arg0, arg1, arg2);
}
void __attribute__((used, noinline)) emscripten_bind_b2Contact__SetRestitution_p1(b2Contact * self, float arg0) {
  self->SetRestitution(arg0);
}
b2Manifold* __attribute__((used, noinline)) emscripten_bind_b2Contact__GetManifold_p0(b2Contact * self) {
  return self->GetManifold();
}
void __attribute__((used, noinline)) emscripten_bind_b2Contact__ResetRestitution_p0(b2Contact * self) {
  self->ResetRestitution();
}
float __attribute__((used, noinline)) emscripten_bind_b2Shape__get_m_radius_p0(b2Shape * self) {
  return self->m_radius;
}
void __attribute__((used, noinline)) emscripten_bind_b2Shape__ComputeMass_p2(b2Shape * self, b2MassData * arg0, float arg1) {
  self->ComputeMass(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2Shape__set_m_radius_p1(b2Shape * self, float arg0) {
  self->m_radius = arg0;
}
b2Shape* __attribute__((used, noinline)) emscripten_bind_b2Shape__Clone_p1(b2Shape * self, b2BlockAllocator * arg0) {
  return self->Clone(arg0);
}
int __attribute__((used, noinline)) emscripten_bind_b2Shape__GetType_p0(b2Shape * self) {
  return self->GetType();
}
bool __attribute__((used, noinline)) emscripten_bind_b2Shape__RayCast_p4(b2Shape * self, b2RayCastOutput * arg0, const b2RayCastInput & arg1, const b2Transform & arg2, signed int arg3) {
  return self->RayCast(arg0, arg1, arg2, arg3);
}
void __attribute__((used, noinline)) emscripten_bind_b2Shape__ComputeAABB_p3(b2Shape * self, b2AABB * arg0, const b2Transform & arg1, signed int arg2) {
  self->ComputeAABB(arg0, arg1, arg2);
}
int __attribute__((used, noinline)) emscripten_bind_b2Shape__GetChildCount_p0(b2Shape * self) {
  return self->GetChildCount();
}
bool __attribute__((used, noinline)) emscripten_bind_b2Shape__TestPoint_p2(b2Shape * self, const b2Transform & arg0, const b2Vec2 & arg1) {
  return self->TestPoint(arg0, arg1);
}
float __attribute__((used, noinline)) emscripten_bind_b2Body__GetAngle_p0(b2Body * self) {
  return self->GetAngle();
}
void* __attribute__((used, noinline)) emscripten_bind_b2Body__GetUserData_p0(b2Body * self) {
  return self->GetUserData();
}
bool __attribute__((used, noinline)) emscripten_bind_b2Body__IsSleepingAllowed_p0(b2Body * self) {
  return self->IsSleepingAllowed();
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetAngularDamping_p1(b2Body * self, float arg0) {
  self->SetAngularDamping(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetActive_p1(b2Body * self, bool arg0) {
  self->SetActive(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetGravityScale_p1(b2Body * self, float arg0) {
  self->SetGravityScale(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetUserData_p1(b2Body * self, void * arg0) {
  self->SetUserData(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2Body__GetAngularVelocity_p0(b2Body * self) {
  return self->GetAngularVelocity();
}
b2Fixture* __attribute__((used, noinline)) emscripten_bind_b2Body__GetFixtureList_p0(b2Body * self) {
  return self->GetFixtureList();
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__ApplyForce_p2(b2Body * self, const b2Vec2 & arg0, const b2Vec2 & arg1) {
  self->ApplyForce(arg0, arg1);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Body__GetLocalPoint_p1(b2Body * self, const b2Vec2 & arg0) {
  static b2Vec2 ret; ret = self->GetLocalPoint(arg0);
  return ret;
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetLinearVelocity_p1(b2Body * self, const b2Vec2 & arg0) {
  self->SetLinearVelocity(arg0);
}
b2JointEdge* __attribute__((used, noinline)) emscripten_bind_b2Body__GetJointList_p0(b2Body * self) {
  return self->GetJointList();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Body__GetLinearVelocity_p0(b2Body * self) {
  static b2Vec2 ret; ret = self->GetLinearVelocity();
  return ret;
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2Body__GetNext_p0(b2Body * self) {
  return self->GetNext();
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetSleepingAllowed_p1(b2Body * self, bool arg0) {
  self->SetSleepingAllowed(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetTransform_p2(b2Body * self, const b2Vec2 & arg0, float arg1) {
  self->SetTransform(arg0, arg1);
}
float __attribute__((used, noinline)) emscripten_bind_b2Body__GetMass_p0(b2Body * self) {
  return self->GetMass();
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetAngularVelocity_p1(b2Body * self, float arg0) {
  self->SetAngularVelocity(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__GetMassData_p1(b2Body * self, b2MassData * arg0) {
  self->GetMassData(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Body__GetLinearVelocityFromWorldPoint_p1(b2Body * self, const b2Vec2 & arg0) {
  static b2Vec2 ret; ret = self->GetLinearVelocityFromWorldPoint(arg0);
  return ret;
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__ResetMassData_p0(b2Body * self) {
  self->ResetMassData();
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__ApplyForceToCenter_p1(b2Body * self, const b2Vec2 & arg0) {
  self->ApplyForceToCenter(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__ApplyTorque_p1(b2Body * self, float arg0) {
  self->ApplyTorque(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2Body__IsAwake_p0(b2Body * self) {
  return self->IsAwake();
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetType_p1(b2Body * self, b2BodyType arg0) {
  self->SetType(arg0);
}
b2Fixture* __attribute__((used, noinline)) emscripten_bind_b2Body__CreateFixture_p1(b2Body * self, const b2FixtureDef * arg0) {
  return self->CreateFixture(arg0);
}
b2Fixture* __attribute__((used, noinline)) emscripten_bind_b2Body__CreateFixture_p2(b2Body * self, const b2Shape * arg0, float arg1) {
  return self->CreateFixture(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetMassData_p1(b2Body * self, const b2MassData * arg0) {
  self->SetMassData(arg0);
}
const b2Transform& __attribute__((used, noinline)) emscripten_bind_b2Body__GetTransform_p0(b2Body * self) {
  return self->GetTransform();
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Body__GetWorldCenter_p0(b2Body * self) {
  return self->GetWorldCenter();
}
float __attribute__((used, noinline)) emscripten_bind_b2Body__GetAngularDamping_p0(b2Body * self) {
  return self->GetAngularDamping();
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__ApplyLinearImpulse_p2(b2Body * self, const b2Vec2 & arg0, const b2Vec2 & arg1) {
  self->ApplyLinearImpulse(arg0, arg1);
}
bool __attribute__((used, noinline)) emscripten_bind_b2Body__IsFixedRotation_p0(b2Body * self) {
  return self->IsFixedRotation();
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Body__GetLocalCenter_p0(b2Body * self) {
  return self->GetLocalCenter();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Body__GetWorldVector_p1(b2Body * self, const b2Vec2 & arg0) {
  static b2Vec2 ret; ret = self->GetWorldVector(arg0);
  return ret;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Body__GetLinearVelocityFromLocalPoint_p1(b2Body * self, const b2Vec2 & arg0) {
  static b2Vec2 ret; ret = self->GetLinearVelocityFromLocalPoint(arg0);
  return ret;
}
b2ContactEdge* __attribute__((used, noinline)) emscripten_bind_b2Body__GetContactList_p0(b2Body * self) {
  return self->GetContactList();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Body__GetWorldPoint_p1(b2Body * self, const b2Vec2 & arg0) {
  static b2Vec2 ret; ret = self->GetWorldPoint(arg0);
  return ret;
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetAwake_p1(b2Body * self, bool arg0) {
  self->SetAwake(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2Body__GetLinearDamping_p0(b2Body * self) {
  return self->GetLinearDamping();
}
bool __attribute__((used, noinline)) emscripten_bind_b2Body__IsBullet_p0(b2Body * self) {
  return self->IsBullet();
}
b2World* __attribute__((used, noinline)) emscripten_bind_b2Body__GetWorld_p0(b2Body * self) {
  return self->GetWorld();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Body__GetLocalVector_p1(b2Body * self, const b2Vec2 & arg0) {
  static b2Vec2 ret; ret = self->GetLocalVector(arg0);
  return ret;
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetLinearDamping_p1(b2Body * self, float arg0) {
  self->SetLinearDamping(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__Dump_p0(b2Body * self) {
  self->Dump();
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetBullet_p1(b2Body * self, bool arg0) {
  self->SetBullet(arg0);
}
int __attribute__((used, noinline)) emscripten_bind_b2Body__GetType_p0(b2Body * self) {
  return self->GetType();
}
float __attribute__((used, noinline)) emscripten_bind_b2Body__GetGravityScale_p0(b2Body * self) {
  return self->GetGravityScale();
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__DestroyFixture_p1(b2Body * self, b2Fixture * arg0) {
  self->DestroyFixture(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2Body__GetInertia_p0(b2Body * self) {
  return self->GetInertia();
}
bool __attribute__((used, noinline)) emscripten_bind_b2Body__IsActive_p0(b2Body * self) {
  return self->IsActive();
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__SetFixedRotation_p1(b2Body * self, bool arg0) {
  self->SetFixedRotation(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2Body__ApplyAngularImpulse_p1(b2Body * self, float arg0) {
  self->ApplyAngularImpulse(arg0);
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Body__GetPosition_p0(b2Body * self) {
  return self->GetPosition();
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__SetMaxTorque_p1(b2FrictionJoint * self, float arg0) {
  self->SetMaxTorque(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetMaxForce_p0(b2FrictionJoint * self) {
  return self->GetMaxForce();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetAnchorA_p0(b2FrictionJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorA();
  return ret;
}
float __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetReactionTorque_p1(b2FrictionJoint * self, float arg0) {
  return self->GetReactionTorque(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__Dump_p0(b2FrictionJoint * self) {
  self->Dump();
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint____destroy___p0(b2FrictionJoint * self) {
  delete self;
}
bool __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetCollideConnected_p0(b2FrictionJoint * self) {
  return self->GetCollideConnected();
}
void* __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetUserData_p0(b2FrictionJoint * self) {
  return self->GetUserData();
}
int __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetType_p0(b2FrictionJoint * self) {
  return self->GetType();
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__SetMaxForce_p1(b2FrictionJoint * self, float arg0) {
  self->SetMaxForce(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetBodyB_p0(b2FrictionJoint * self) {
  return self->GetBodyB();
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetLocalAnchorA_p0(b2FrictionJoint * self) {
  return self->GetLocalAnchorA();
}
b2FrictionJoint * __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__b2FrictionJoint_p1(const b2FrictionJointDef * arg0) {
  return new b2FrictionJoint(arg0);
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetLocalAnchorB_p0(b2FrictionJoint * self) {
  return self->GetLocalAnchorB();
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__SetUserData_p1(b2FrictionJoint * self, void * arg0) {
  self->SetUserData(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetAnchorB_p0(b2FrictionJoint * self) {
  static b2Vec2 ret; ret = self->GetAnchorB();
  return ret;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetReactionForce_p1(b2FrictionJoint * self, float arg0) {
  static b2Vec2 ret; ret = self->GetReactionForce(arg0);
  return ret;
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetBodyA_p0(b2FrictionJoint * self) {
  return self->GetBodyA();
}
b2Joint* __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetNext_p0(b2FrictionJoint * self) {
  return self->GetNext();
}
float __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__GetMaxTorque_p0(b2FrictionJoint * self) {
  return self->GetMaxTorque();
}
bool __attribute__((used, noinline)) emscripten_bind_b2FrictionJoint__IsActive_p0(b2FrictionJoint * self) {
  return self->IsActive();
}
int __attribute__((used, noinline)) emscripten_bind_b2StackAllocator__GetMaxAllocation_p0(b2StackAllocator * self) {
  return self->GetMaxAllocation();
}
void __attribute__((used, noinline)) emscripten_bind_b2StackAllocator____destroy___p0(b2StackAllocator * self) {
  delete self;
}
b2StackAllocator * __attribute__((used, noinline)) emscripten_bind_b2StackAllocator__b2StackAllocator_p0() {
  return new b2StackAllocator();
}
void* __attribute__((used, noinline)) emscripten_bind_b2StackAllocator__Allocate_p1(b2StackAllocator * self, signed int arg0) {
  return self->Allocate(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2StackAllocator__Free_p1(b2StackAllocator * self, void * arg0) {
  self->Free(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2DestructionListener____destroy___p0(b2DestructionListener * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2DestructionListener__SayGoodbye_p1(b2DestructionListener * self, b2Joint * arg0) {
  self->SayGoodbye(arg0);
}
b2DestructionListener * __attribute__((used, noinline)) emscripten_bind_b2DestructionListener__b2DestructionListener_p0() {
  return new b2DestructionListener();
}
void __attribute__((used, noinline)) emscripten_bind_b2Filter____destroy___p0(b2Filter * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2Filter__set_maskBits_p1(b2Filter * self, unsigned short arg0) {
  self->maskBits = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2Filter__set_categoryBits_p1(b2Filter * self, unsigned short arg0) {
  self->categoryBits = arg0;
}
signed short __attribute__((used, noinline)) emscripten_bind_b2Filter__get_groupIndex_p0(b2Filter * self) {
  return self->groupIndex;
}
void __attribute__((used, noinline)) emscripten_bind_b2Filter__set_groupIndex_p1(b2Filter * self, signed short arg0) {
  self->groupIndex = arg0;
}
unsigned short __attribute__((used, noinline)) emscripten_bind_b2Filter__get_maskBits_p0(b2Filter * self) {
  return self->maskBits;
}
b2Filter * __attribute__((used, noinline)) emscripten_bind_b2Filter__b2Filter_p0() {
  return new b2Filter();
}
unsigned short __attribute__((used, noinline)) emscripten_bind_b2Filter__get_categoryBits_p0(b2Filter * self) {
  return self->categoryBits;
}
void __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef__set_localAnchorA_p1(b2RopeJointDef * self, b2Vec2& arg0) {
  self->localAnchorA = arg0;
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef__get_bodyA_p1(b2RopeJointDef * self, b2Body * arg0) {
  return self->get_bodyA(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef__get_bodyB_p1(b2RopeJointDef * self, b2Body * arg0) {
  return self->get_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef__set_localAnchorB_p1(b2RopeJointDef * self, b2Vec2& arg0) {
  self->localAnchorB = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef__set_bodyA_p1(b2RopeJointDef * self, b2Body * arg0) {
  self->set_bodyA(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef__set_bodyB_p1(b2RopeJointDef * self, b2Body * arg0) {
  self->set_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef____destroy___p0(b2RopeJointDef * self) {
  delete self;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef__get_localAnchorA_p0(b2RopeJointDef * self) {
  return self->localAnchorA;
}
float __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef__get_maxLength_p0(b2RopeJointDef * self) {
  return self->maxLength;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef__get_localAnchorB_p0(b2RopeJointDef * self) {
  return self->localAnchorB;
}
bool __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef__get_collideConnected_p1(b2RopeJointDef * self, bool arg0) {
  return self->get_collideConnected(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef__set_collideConnected_p1(b2RopeJointDef * self, bool arg0) {
  self->set_collideConnected(arg0);
}
b2RopeJointDef * __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef__b2RopeJointDef_p0() {
  return new b2RopeJointDef();
}
void __attribute__((used, noinline)) emscripten_bind_b2RopeJointDef__set_maxLength_p1(b2RopeJointDef * self, float arg0) {
  self->maxLength = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__set_localAnchorA_p1(b2FrictionJointDef * self, b2Vec2& arg0) {
  self->localAnchorA = arg0;
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__get_bodyA_p1(b2FrictionJointDef * self, b2Body * arg0) {
  return self->get_bodyA(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__get_bodyB_p1(b2FrictionJointDef * self, b2Body * arg0) {
  return self->get_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__set_localAnchorB_p1(b2FrictionJointDef * self, b2Vec2& arg0) {
  self->localAnchorB = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__set_bodyA_p1(b2FrictionJointDef * self, b2Body * arg0) {
  self->set_bodyA(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__set_bodyB_p1(b2FrictionJointDef * self, b2Body * arg0) {
  self->set_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef____destroy___p0(b2FrictionJointDef * self) {
  delete self;
}
float __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__get_maxForce_p0(b2FrictionJointDef * self) {
  return self->maxForce;
}
b2FrictionJointDef * __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__b2FrictionJointDef_p0() {
  return new b2FrictionJointDef();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__get_localAnchorA_p0(b2FrictionJointDef * self) {
  return self->localAnchorA;
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__set_maxForce_p1(b2FrictionJointDef * self, float arg0) {
  self->maxForce = arg0;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__get_localAnchorB_p0(b2FrictionJointDef * self) {
  return self->localAnchorB;
}
bool __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__get_collideConnected_p1(b2FrictionJointDef * self, bool arg0) {
  return self->get_collideConnected(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__set_maxTorque_p1(b2FrictionJointDef * self, float arg0) {
  self->maxTorque = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__set_collideConnected_p1(b2FrictionJointDef * self, bool arg0) {
  self->set_collideConnected(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__Initialize_p3(b2FrictionJointDef * self, b2Body * arg0, b2Body * arg1, const b2Vec2 & arg2) {
  self->Initialize(arg0, arg1, arg2);
}
float __attribute__((used, noinline)) emscripten_bind_b2FrictionJointDef__get_maxTorque_p0(b2FrictionJointDef * self) {
  return self->maxTorque;
}
float __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_linearDamping_p0(b2BodyDef * self) {
  return self->linearDamping;
}
bool __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_awake_p0(b2BodyDef * self) {
  return self->awake;
}
b2BodyType __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_type_p0(b2BodyDef * self) {
  return self->type;
}
bool __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_allowSleep_p0(b2BodyDef * self) {
  return self->allowSleep;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_position_p1(b2BodyDef * self, b2Vec2& arg0) {
  self->position = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_linearVelocity_p1(b2BodyDef * self, b2Vec2& arg0) {
  self->linearVelocity = arg0;
}
b2BodyDef * __attribute__((used, noinline)) emscripten_bind_b2BodyDef__b2BodyDef_p0() {
  return new b2BodyDef();
}
bool __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_bullet_p0(b2BodyDef * self) {
  return self->bullet;
}
void * __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_userData_p0(b2BodyDef * self) {
  return self->userData;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_angularDamping_p1(b2BodyDef * self, float arg0) {
  self->angularDamping = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_fixedRotation_p1(b2BodyDef * self, bool arg0) {
  self->fixedRotation = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_allowSleep_p1(b2BodyDef * self, bool arg0) {
  self->allowSleep = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_gravityScale_p0(b2BodyDef * self) {
  return self->gravityScale;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_angularVelocity_p1(b2BodyDef * self, float arg0) {
  self->angularVelocity = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_userData_p1(b2BodyDef * self, void * arg0) {
  self->userData = arg0;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_position_p0(b2BodyDef * self) {
  return self->position;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef____destroy___p0(b2BodyDef * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_type_p1(b2BodyDef * self, b2BodyType arg0) {
  self->type = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_gravityScale_p1(b2BodyDef * self, float arg0) {
  self->gravityScale = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_angularDamping_p0(b2BodyDef * self) {
  return self->angularDamping;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_bullet_p1(b2BodyDef * self, bool arg0) {
  self->bullet = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_active_p1(b2BodyDef * self, bool arg0) {
  self->active = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_angle_p1(b2BodyDef * self, float arg0) {
  self->angle = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_angle_p0(b2BodyDef * self) {
  return self->angle;
}
float __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_angularVelocity_p0(b2BodyDef * self) {
  return self->angularVelocity;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_linearVelocity_p0(b2BodyDef * self) {
  return self->linearVelocity;
}
bool __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_active_p0(b2BodyDef * self) {
  return self->active;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_linearDamping_p1(b2BodyDef * self, float arg0) {
  self->linearDamping = arg0;
}
bool __attribute__((used, noinline)) emscripten_bind_b2BodyDef__get_fixedRotation_p0(b2BodyDef * self) {
  return self->fixedRotation;
}
void __attribute__((used, noinline)) emscripten_bind_b2BodyDef__set_awake_p1(b2BodyDef * self, bool arg0) {
  self->awake = arg0;
}
float32 __attribute__((used, noinline)) emscripten_bind_b2Vec2__Normalize_p0(b2Vec2 * self) {
  return self->Normalize();
}
void __attribute__((used, noinline)) emscripten_bind_b2Vec2__set_x_p1(b2Vec2 * self, float arg0) {
  self->x = arg0;
}
b2Vec2 * __attribute__((used, noinline)) emscripten_bind_b2Vec2__b2Vec2_p0() {
  return new b2Vec2();
}
b2Vec2 * __attribute__((used, noinline)) emscripten_bind_b2Vec2__b2Vec2_p2(float arg0, float arg1) {
  return new b2Vec2(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2Vec2__Set_p2(b2Vec2 * self, float arg0, float arg1) {
  self->Set(arg0, arg1);
}
float __attribute__((used, noinline)) emscripten_bind_b2Vec2__get_x_p0(b2Vec2 * self) {
  return self->x;
}
float __attribute__((used, noinline)) emscripten_bind_b2Vec2__get_y_p0(b2Vec2 * self) {
  return self->y;
}
void __attribute__((used, noinline)) emscripten_bind_b2Vec2__set_y_p1(b2Vec2 * self, float arg0) {
  self->y = arg0;
}
bool __attribute__((used, noinline)) emscripten_bind_b2Vec2__IsValid_p0(b2Vec2 * self) {
  return self->IsValid();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Vec2__Skew_p0(b2Vec2 * self) {
  static b2Vec2 ret; ret = self->Skew();
  return ret;
}
float32 __attribute__((used, noinline)) emscripten_bind_b2Vec2__LengthSquared_p0(b2Vec2 * self) {
  return self->LengthSquared();
}
void __attribute__((used, noinline)) emscripten_bind_b2Vec2__op_add_p1(b2Vec2 * self, const b2Vec2 & arg0) {
  return *self += arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2Vec2__SetZero_p0(b2Vec2 * self) {
  self->SetZero();
}
float32 __attribute__((used, noinline)) emscripten_bind_b2Vec2__Length_p0(b2Vec2 * self) {
  return self->Length();
}
void __attribute__((used, noinline)) emscripten_bind_b2Vec2____destroy___p0(b2Vec2 * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2Vec2__op_mul_p1(b2Vec2 * self, float arg0) {
  return *self *= arg0;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Vec2__op_sub_p0(b2Vec2 * self) {
  static b2Vec2 ret; ret = -*self; return ret;
}
void __attribute__((used, noinline)) emscripten_bind_b2Vec3____destroy___p0(b2Vec3 * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2Vec3__set_z_p1(b2Vec3 * self, float arg0) {
  self->z = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2Vec3__Set_p3(b2Vec3 * self, float arg0, float arg1, float arg2) {
  self->Set(arg0, arg1, arg2);
}
float __attribute__((used, noinline)) emscripten_bind_b2Vec3__get_z_p0(b2Vec3 * self) {
  return self->z;
}
void __attribute__((used, noinline)) emscripten_bind_b2Vec3__op_add_p1(b2Vec3 * self, const b2Vec3 & arg0) {
  return *self += arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2Vec3__SetZero_p0(b2Vec3 * self) {
  self->SetZero();
}
b2Vec3 * __attribute__((used, noinline)) emscripten_bind_b2Vec3__b2Vec3_p0() {
  return new b2Vec3();
}
b2Vec3 * __attribute__((used, noinline)) emscripten_bind_b2Vec3__b2Vec3_p3(float arg0, float arg1, float arg2) {
  return new b2Vec3(arg0, arg1, arg2);
}
void __attribute__((used, noinline)) emscripten_bind_b2Vec3__op_mul_p1(b2Vec3 * self, float arg0) {
  return *self *= arg0;
}
b2Vec3& __attribute__((used, noinline)) emscripten_bind_b2Vec3__op_sub_p0(b2Vec3 * self) {
  static b2Vec3 ret; ret = -*self; return ret;
}
void __attribute__((used, noinline)) emscripten_bind_b2AABB____destroy___p0(b2AABB * self) {
  delete self;
}
b2AABB * __attribute__((used, noinline)) emscripten_bind_b2AABB__b2AABB_p0() {
  return new b2AABB();
}
void __attribute__((used, noinline)) emscripten_bind_b2AABB__set_upperBound_p1(b2AABB * self, b2Vec2& arg0) {
  self->upperBound = arg0;
}
bool __attribute__((used, noinline)) emscripten_bind_b2AABB__IsValid_p0(b2AABB * self) {
  return self->IsValid();
}
bool __attribute__((used, noinline)) emscripten_bind_b2AABB__Contains_p1(b2AABB * self, const b2AABB & arg0) {
  return self->Contains(arg0);
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2AABB__GetExtents_p0(b2AABB * self) {
  static b2Vec2 ret; ret = self->GetExtents();
  return ret;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2AABB__GetCenter_p0(b2AABB * self) {
  static b2Vec2 ret; ret = self->GetCenter();
  return ret;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2AABB__get_upperBound_p0(b2AABB * self) {
  return self->upperBound;
}
float32 __attribute__((used, noinline)) emscripten_bind_b2AABB__GetPerimeter_p0(b2AABB * self) {
  return self->GetPerimeter();
}
void __attribute__((used, noinline)) emscripten_bind_b2AABB__Combine_p1(b2AABB * self, const b2AABB & arg0) {
  self->Combine(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2AABB__Combine_p2(b2AABB * self, const b2AABB & arg0, const b2AABB & arg1) {
  self->Combine(arg0, arg1);
}
bool __attribute__((used, noinline)) emscripten_bind_b2AABB__RayCast_p2(b2AABB * self, b2RayCastOutput * arg0, const b2RayCastInput & arg1) {
  return self->RayCast(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2AABB__set_lowerBound_p1(b2AABB * self, b2Vec2& arg0) {
  self->lowerBound = arg0;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2AABB__get_lowerBound_p0(b2AABB * self) {
  return self->lowerBound;
}
void __attribute__((used, noinline)) emscripten_bind_b2FixtureDef____destroy___p0(b2FixtureDef * self) {
  delete self;
}
bool __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__get_isSensor_p0(b2FixtureDef * self) {
  return self->isSensor;
}
void __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__set_userData_p1(b2FixtureDef * self, void * arg0) {
  self->userData = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__set_shape_p1(b2FixtureDef * self, const b2Shape * arg0) {
  self->shape = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__get_density_p0(b2FixtureDef * self) {
  return self->density;
}
const b2Shape * __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__get_shape_p0(b2FixtureDef * self) {
  return self->shape;
}
b2FixtureDef * __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__b2FixtureDef_p0() {
  return new b2FixtureDef();
}
void __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__set_density_p1(b2FixtureDef * self, float arg0) {
  self->density = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__set_restitution_p1(b2FixtureDef * self, float arg0) {
  self->restitution = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__get_restitution_p0(b2FixtureDef * self) {
  return self->restitution;
}
void __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__set_isSensor_p1(b2FixtureDef * self, bool arg0) {
  self->isSensor = arg0;
}
b2Filter& __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__get_filter_p0(b2FixtureDef * self) {
  return self->filter;
}
float __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__get_friction_p0(b2FixtureDef * self) {
  return self->friction;
}
void __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__set_friction_p1(b2FixtureDef * self, float arg0) {
  self->friction = arg0;
}
void * __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__get_userData_p0(b2FixtureDef * self) {
  return self->userData;
}
void __attribute__((used, noinline)) emscripten_bind_b2FixtureDef__set_filter_p1(b2FixtureDef * self, b2Filter& arg0) {
  self->filter = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__set_localAnchorA_p1(b2PrismaticJointDef * self, b2Vec2& arg0) {
  self->localAnchorA = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__set_localAnchorB_p1(b2PrismaticJointDef * self, b2Vec2& arg0) {
  self->localAnchorB = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__get_motorSpeed_p0(b2PrismaticJointDef * self) {
  return self->motorSpeed;
}
bool __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__get_enableMotor_p0(b2PrismaticJointDef * self) {
  return self->enableMotor;
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__get_referenceAngle_p0(b2PrismaticJointDef * self) {
  return self->referenceAngle;
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__set_enableLimit_p1(b2PrismaticJointDef * self, bool arg0) {
  self->enableLimit = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__set_motorSpeed_p1(b2PrismaticJointDef * self, float arg0) {
  self->motorSpeed = arg0;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__get_localAxisA_p0(b2PrismaticJointDef * self) {
  return self->localAxisA;
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__set_bodyA_p1(b2PrismaticJointDef * self, b2Body * arg0) {
  self->set_bodyA(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__set_bodyB_p1(b2PrismaticJointDef * self, b2Body * arg0) {
  self->set_bodyB(arg0);
}
b2PrismaticJointDef * __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__b2PrismaticJointDef_p0() {
  return new b2PrismaticJointDef();
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__Initialize_p4(b2PrismaticJointDef * self, b2Body * arg0, b2Body * arg1, const b2Vec2 & arg2, const b2Vec2 & arg3) {
  self->Initialize(arg0, arg1, arg2, arg3);
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__set_lowerTranslation_p1(b2PrismaticJointDef * self, float arg0) {
  self->lowerTranslation = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__get_upperTranslation_p0(b2PrismaticJointDef * self) {
  return self->upperTranslation;
}
bool __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__get_enableLimit_p0(b2PrismaticJointDef * self) {
  return self->enableLimit;
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef____destroy___p0(b2PrismaticJointDef * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__set_referenceAngle_p1(b2PrismaticJointDef * self, float arg0) {
  self->referenceAngle = arg0;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__get_localAnchorA_p0(b2PrismaticJointDef * self) {
  return self->localAnchorA;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__get_localAnchorB_p0(b2PrismaticJointDef * self) {
  return self->localAnchorB;
}
bool __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__get_collideConnected_p1(b2PrismaticJointDef * self, bool arg0) {
  return self->get_collideConnected(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__get_bodyA_p1(b2PrismaticJointDef * self, b2Body * arg0) {
  return self->get_bodyA(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__get_bodyB_p1(b2PrismaticJointDef * self, b2Body * arg0) {
  return self->get_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__set_upperTranslation_p1(b2PrismaticJointDef * self, float arg0) {
  self->upperTranslation = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__get_maxMotorForce_p0(b2PrismaticJointDef * self) {
  return self->maxMotorForce;
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__set_maxMotorForce_p1(b2PrismaticJointDef * self, float arg0) {
  self->maxMotorForce = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__set_enableMotor_p1(b2PrismaticJointDef * self, bool arg0) {
  self->enableMotor = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__set_collideConnected_p1(b2PrismaticJointDef * self, bool arg0) {
  self->set_collideConnected(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__get_lowerTranslation_p0(b2PrismaticJointDef * self) {
  return self->lowerTranslation;
}
void __attribute__((used, noinline)) emscripten_bind_b2PrismaticJointDef__set_localAxisA_p1(b2PrismaticJointDef * self, b2Vec2& arg0) {
  self->localAxisA = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__set_localAnchorA_p1(b2WheelJointDef * self, b2Vec2& arg0) {
  self->localAnchorA = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__set_localAnchorB_p1(b2WheelJointDef * self, b2Vec2& arg0) {
  self->localAnchorB = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__get_motorSpeed_p0(b2WheelJointDef * self) {
  return self->motorSpeed;
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__set_maxMotorTorque_p1(b2WheelJointDef * self, float arg0) {
  self->maxMotorTorque = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__set_frequencyHz_p1(b2WheelJointDef * self, float arg0) {
  self->frequencyHz = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__set_motorSpeed_p1(b2WheelJointDef * self, float arg0) {
  self->motorSpeed = arg0;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__get_localAxisA_p0(b2WheelJointDef * self) {
  return self->localAxisA;
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__set_bodyA_p1(b2WheelJointDef * self, b2Body * arg0) {
  self->set_bodyA(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__set_bodyB_p1(b2WheelJointDef * self, b2Body * arg0) {
  self->set_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__Initialize_p4(b2WheelJointDef * self, b2Body * arg0, b2Body * arg1, const b2Vec2 & arg2, const b2Vec2 & arg3) {
  self->Initialize(arg0, arg1, arg2, arg3);
}
b2WheelJointDef * __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__b2WheelJointDef_p0() {
  return new b2WheelJointDef();
}
float __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__get_frequencyHz_p0(b2WheelJointDef * self) {
  return self->frequencyHz;
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__set_dampingRatio_p1(b2WheelJointDef * self, float arg0) {
  self->dampingRatio = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef____destroy___p0(b2WheelJointDef * self) {
  delete self;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__get_localAnchorA_p0(b2WheelJointDef * self) {
  return self->localAnchorA;
}
float __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__get_maxMotorTorque_p0(b2WheelJointDef * self) {
  return self->maxMotorTorque;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__get_localAnchorB_p0(b2WheelJointDef * self) {
  return self->localAnchorB;
}
bool __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__get_collideConnected_p1(b2WheelJointDef * self, bool arg0) {
  return self->get_collideConnected(arg0);
}
bool __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__get_enableMotor_p0(b2WheelJointDef * self) {
  return self->enableMotor;
}
float __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__get_dampingRatio_p0(b2WheelJointDef * self) {
  return self->dampingRatio;
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__get_bodyA_p1(b2WheelJointDef * self, b2Body * arg0) {
  return self->get_bodyA(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__get_bodyB_p1(b2WheelJointDef * self, b2Body * arg0) {
  return self->get_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__set_enableMotor_p1(b2WheelJointDef * self, bool arg0) {
  self->enableMotor = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__set_collideConnected_p1(b2WheelJointDef * self, bool arg0) {
  self->set_collideConnected(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2WheelJointDef__set_localAxisA_p1(b2WheelJointDef * self, b2Vec2& arg0) {
  self->localAxisA = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__set_localAnchorA_p1(b2RevoluteJointDef * self, b2Vec2& arg0) {
  self->localAnchorA = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__get_lowerAngle_p0(b2RevoluteJointDef * self) {
  return self->lowerAngle;
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__set_localAnchorB_p1(b2RevoluteJointDef * self, b2Vec2& arg0) {
  self->localAnchorB = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__set_lowerAngle_p1(b2RevoluteJointDef * self, float arg0) {
  self->lowerAngle = arg0;
}
bool __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__get_enableMotor_p0(b2RevoluteJointDef * self) {
  return self->enableMotor;
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__set_upperAngle_p1(b2RevoluteJointDef * self, float arg0) {
  self->upperAngle = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__get_referenceAngle_p0(b2RevoluteJointDef * self) {
  return self->referenceAngle;
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__set_enableLimit_p1(b2RevoluteJointDef * self, bool arg0) {
  self->enableLimit = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__get_motorSpeed_p0(b2RevoluteJointDef * self) {
  return self->motorSpeed;
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__set_motorSpeed_p1(b2RevoluteJointDef * self, float arg0) {
  self->motorSpeed = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__get_maxMotorTorque_p0(b2RevoluteJointDef * self) {
  return self->maxMotorTorque;
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__set_bodyA_p1(b2RevoluteJointDef * self, b2Body * arg0) {
  self->set_bodyA(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__set_bodyB_p1(b2RevoluteJointDef * self, b2Body * arg0) {
  self->set_bodyB(arg0);
}
b2RevoluteJointDef * __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__b2RevoluteJointDef_p0() {
  return new b2RevoluteJointDef();
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__Initialize_p3(b2RevoluteJointDef * self, b2Body * arg0, b2Body * arg1, const b2Vec2 & arg2) {
  self->Initialize(arg0, arg1, arg2);
}
bool __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__get_enableLimit_p0(b2RevoluteJointDef * self) {
  return self->enableLimit;
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef____destroy___p0(b2RevoluteJointDef * self) {
  delete self;
}
float __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__get_upperAngle_p0(b2RevoluteJointDef * self) {
  return self->upperAngle;
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__set_referenceAngle_p1(b2RevoluteJointDef * self, float arg0) {
  self->referenceAngle = arg0;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__get_localAnchorA_p0(b2RevoluteJointDef * self) {
  return self->localAnchorA;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__get_localAnchorB_p0(b2RevoluteJointDef * self) {
  return self->localAnchorB;
}
bool __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__get_collideConnected_p1(b2RevoluteJointDef * self, bool arg0) {
  return self->get_collideConnected(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__get_bodyA_p1(b2RevoluteJointDef * self, b2Body * arg0) {
  return self->get_bodyA(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__get_bodyB_p1(b2RevoluteJointDef * self, b2Body * arg0) {
  return self->get_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__set_maxMotorTorque_p1(b2RevoluteJointDef * self, float arg0) {
  self->maxMotorTorque = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__set_enableMotor_p1(b2RevoluteJointDef * self, bool arg0) {
  self->enableMotor = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2RevoluteJointDef__set_collideConnected_p1(b2RevoluteJointDef * self, bool arg0) {
  self->set_collideConnected(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__set_localAnchorA_p1(b2PulleyJointDef * self, b2Vec2& arg0) {
  self->localAnchorA = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__set_localAnchorB_p1(b2PulleyJointDef * self, b2Vec2& arg0) {
  self->localAnchorB = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__set_ratio_p1(b2PulleyJointDef * self, float arg0) {
  self->ratio = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__set_groundAnchorB_p1(b2PulleyJointDef * self, b2Vec2& arg0) {
  self->groundAnchorB = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__set_groundAnchorA_p1(b2PulleyJointDef * self, b2Vec2& arg0) {
  self->groundAnchorA = arg0;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__get_groundAnchorB_p0(b2PulleyJointDef * self) {
  return self->groundAnchorB;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__get_groundAnchorA_p0(b2PulleyJointDef * self) {
  return self->groundAnchorA;
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__set_bodyA_p1(b2PulleyJointDef * self, b2Body * arg0) {
  self->set_bodyA(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__set_bodyB_p1(b2PulleyJointDef * self, b2Body * arg0) {
  self->set_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__Initialize_p7(b2PulleyJointDef * self, b2Body * arg0, b2Body * arg1, const b2Vec2 & arg2, const b2Vec2 & arg3, const b2Vec2 & arg4, const b2Vec2 & arg5, float arg6) {
  self->Initialize(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}
float __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__get_ratio_p0(b2PulleyJointDef * self) {
  return self->ratio;
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef____destroy___p0(b2PulleyJointDef * self) {
  delete self;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__get_localAnchorA_p0(b2PulleyJointDef * self) {
  return self->localAnchorA;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__get_localAnchorB_p0(b2PulleyJointDef * self) {
  return self->localAnchorB;
}
bool __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__get_collideConnected_p1(b2PulleyJointDef * self, bool arg0) {
  return self->get_collideConnected(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__set_lengthB_p1(b2PulleyJointDef * self, float arg0) {
  self->lengthB = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__set_lengthA_p1(b2PulleyJointDef * self, float arg0) {
  self->lengthA = arg0;
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__get_bodyA_p1(b2PulleyJointDef * self, b2Body * arg0) {
  return self->get_bodyA(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__get_bodyB_p1(b2PulleyJointDef * self, b2Body * arg0) {
  return self->get_bodyB(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__get_lengthB_p0(b2PulleyJointDef * self) {
  return self->lengthB;
}
float __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__get_lengthA_p0(b2PulleyJointDef * self) {
  return self->lengthA;
}
void __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__set_collideConnected_p1(b2PulleyJointDef * self, bool arg0) {
  self->set_collideConnected(arg0);
}
b2PulleyJointDef * __attribute__((used, noinline)) emscripten_bind_b2PulleyJointDef__b2PulleyJointDef_p0() {
  return new b2PulleyJointDef();
}
b2Body * __attribute__((used, noinline)) emscripten_bind_b2JointDef__get_bodyA_p0(b2JointDef * self) {
  return self->bodyA;
}
void __attribute__((used, noinline)) emscripten_bind_b2JointDef__set_userData_p1(b2JointDef * self, void * arg0) {
  self->userData = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2JointDef__set_bodyA_p1(b2JointDef * self, b2Body * arg0) {
  self->bodyA = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2JointDef__set_bodyB_p1(b2JointDef * self, b2Body * arg0) {
  self->bodyB = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2JointDef____destroy___p0(b2JointDef * self) {
  delete self;
}
b2Body * __attribute__((used, noinline)) emscripten_bind_b2JointDef__get_bodyB_p0(b2JointDef * self) {
  return self->bodyB;
}
void __attribute__((used, noinline)) emscripten_bind_b2JointDef__set_type_p1(b2JointDef * self, b2JointType arg0) {
  self->type = arg0;
}
bool __attribute__((used, noinline)) emscripten_bind_b2JointDef__get_collideConnected_p0(b2JointDef * self) {
  return self->collideConnected;
}
b2JointType __attribute__((used, noinline)) emscripten_bind_b2JointDef__get_type_p0(b2JointDef * self) {
  return self->type;
}
void __attribute__((used, noinline)) emscripten_bind_b2JointDef__set_collideConnected_p1(b2JointDef * self, bool arg0) {
  self->collideConnected = arg0;
}
b2JointDef * __attribute__((used, noinline)) emscripten_bind_b2JointDef__b2JointDef_p0() {
  return new b2JointDef();
}
void * __attribute__((used, noinline)) emscripten_bind_b2JointDef__get_userData_p0(b2JointDef * self) {
  return self->userData;
}
void __attribute__((used, noinline)) emscripten_bind_b2Transform____destroy___p0(b2Transform * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2Transform__Set_p2(b2Transform * self, const b2Vec2 & arg0, float arg1) {
  self->Set(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2Transform__set_p_p1(b2Transform * self, b2Vec2& arg0) {
  self->p = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2Transform__set_q_p1(b2Transform * self, b2Rot& arg0) {
  self->q = arg0;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Transform__get_p_p0(b2Transform * self) {
  return self->p;
}
b2Rot& __attribute__((used, noinline)) emscripten_bind_b2Transform__get_q_p0(b2Transform * self) {
  return self->q;
}
b2Transform * __attribute__((used, noinline)) emscripten_bind_b2Transform__b2Transform_p0() {
  return new b2Transform();
}
b2Transform * __attribute__((used, noinline)) emscripten_bind_b2Transform__b2Transform_p2(const b2Vec2 & arg0, const b2Rot & arg1) {
  return new b2Transform(arg0, arg1);
}
void __attribute__((used, noinline)) emscripten_bind_b2Transform__SetIdentity_p0(b2Transform * self) {
  self->SetIdentity();
}
void __attribute__((used, noinline)) emscripten_bind_b2Color____destroy___p0(b2Color * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2Color__Set_p3(b2Color * self, float arg0, float arg1, float arg2) {
  self->Set(arg0, arg1, arg2);
}
void __attribute__((used, noinline)) emscripten_bind_b2Color__set_r_p1(b2Color * self, float arg0) {
  self->r = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2Color__get_r_p0(b2Color * self) {
  return self->r;
}
b2Color * __attribute__((used, noinline)) emscripten_bind_b2Color__b2Color_p0() {
  return new b2Color();
}
b2Color * __attribute__((used, noinline)) emscripten_bind_b2Color__b2Color_p3(float arg0, float arg1, float arg2) {
  return new b2Color(arg0, arg1, arg2);
}
void __attribute__((used, noinline)) emscripten_bind_b2Color__set_b_p1(b2Color * self, float arg0) {
  self->b = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2Color__get_g_p0(b2Color * self) {
  return self->g;
}
float __attribute__((used, noinline)) emscripten_bind_b2Color__get_b_p0(b2Color * self) {
  return self->b;
}
void __attribute__((used, noinline)) emscripten_bind_b2Color__set_g_p1(b2Color * self, float arg0) {
  self->g = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2Rot____destroy___p0(b2Rot * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2Rot__Set_p1(b2Rot * self, float arg0) {
  self->Set(arg0);
}
float32 __attribute__((used, noinline)) emscripten_bind_b2Rot__GetAngle_p0(b2Rot * self) {
  return self->GetAngle();
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Rot__GetYAxis_p0(b2Rot * self) {
  static b2Vec2 ret; ret = self->GetYAxis();
  return ret;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2Rot__GetXAxis_p0(b2Rot * self) {
  static b2Vec2 ret; ret = self->GetXAxis();
  return ret;
}
void __attribute__((used, noinline)) emscripten_bind_b2Rot__set_c_p1(b2Rot * self, float arg0) {
  self->c = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2Rot__SetIdentity_p0(b2Rot * self) {
  self->SetIdentity();
}
b2Rot * __attribute__((used, noinline)) emscripten_bind_b2Rot__b2Rot_p0() {
  return new b2Rot();
}
b2Rot * __attribute__((used, noinline)) emscripten_bind_b2Rot__b2Rot_p1(float arg0) {
  return new b2Rot(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2Rot__get_c_p0(b2Rot * self) {
  return self->c;
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__set_localAnchorA_p1(b2WeldJointDef * self, b2Vec2& arg0) {
  self->localAnchorA = arg0;
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__get_bodyA_p1(b2WeldJointDef * self, b2Body * arg0) {
  return self->get_bodyA(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__get_bodyB_p1(b2WeldJointDef * self, b2Body * arg0) {
  return self->get_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__set_localAnchorB_p1(b2WeldJointDef * self, b2Vec2& arg0) {
  self->localAnchorB = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__get_frequencyHz_p0(b2WeldJointDef * self) {
  return self->frequencyHz;
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__set_bodyA_p1(b2WeldJointDef * self, b2Body * arg0) {
  self->set_bodyA(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__set_bodyB_p1(b2WeldJointDef * self, b2Body * arg0) {
  self->set_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef____destroy___p0(b2WeldJointDef * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__set_referenceAngle_p1(b2WeldJointDef * self, float arg0) {
  self->referenceAngle = arg0;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__get_localAnchorA_p0(b2WeldJointDef * self) {
  return self->localAnchorA;
}
float __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__get_referenceAngle_p0(b2WeldJointDef * self) {
  return self->referenceAngle;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__get_localAnchorB_p0(b2WeldJointDef * self) {
  return self->localAnchorB;
}
bool __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__get_collideConnected_p1(b2WeldJointDef * self, bool arg0) {
  return self->get_collideConnected(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__get_dampingRatio_p0(b2WeldJointDef * self) {
  return self->dampingRatio;
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__set_collideConnected_p1(b2WeldJointDef * self, bool arg0) {
  self->set_collideConnected(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__set_frequencyHz_p1(b2WeldJointDef * self, float arg0) {
  self->frequencyHz = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__Initialize_p3(b2WeldJointDef * self, b2Body * arg0, b2Body * arg1, const b2Vec2 & arg2) {
  self->Initialize(arg0, arg1, arg2);
}
void __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__set_dampingRatio_p1(b2WeldJointDef * self, float arg0) {
  self->dampingRatio = arg0;
}
b2WeldJointDef * __attribute__((used, noinline)) emscripten_bind_b2WeldJointDef__b2WeldJointDef_p0() {
  return new b2WeldJointDef();
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__get_bodyA_p1(b2MouseJointDef * self, b2Body * arg0) {
  return self->get_bodyA(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__get_bodyB_p1(b2MouseJointDef * self, b2Body * arg0) {
  return self->get_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__set_dampingRatio_p1(b2MouseJointDef * self, float arg0) {
  self->dampingRatio = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__set_bodyA_p1(b2MouseJointDef * self, b2Body * arg0) {
  self->set_bodyA(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__set_bodyB_p1(b2MouseJointDef * self, b2Body * arg0) {
  self->set_bodyB(arg0);
}
b2MouseJointDef * __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__b2MouseJointDef_p0() {
  return new b2MouseJointDef();
}
float __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__get_maxForce_p0(b2MouseJointDef * self) {
  return self->maxForce;
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__set_target_p1(b2MouseJointDef * self, b2Vec2& arg0) {
  self->target = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__set_maxForce_p1(b2MouseJointDef * self, float arg0) {
  self->maxForce = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__get_frequencyHz_p0(b2MouseJointDef * self) {
  return self->frequencyHz;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__get_target_p0(b2MouseJointDef * self) {
  return self->target;
}
bool __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__get_collideConnected_p1(b2MouseJointDef * self, bool arg0) {
  return self->get_collideConnected(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef____destroy___p0(b2MouseJointDef * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__set_collideConnected_p1(b2MouseJointDef * self, bool arg0) {
  self->set_collideConnected(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__set_frequencyHz_p1(b2MouseJointDef * self, float arg0) {
  self->frequencyHz = arg0;
}
float __attribute__((used, noinline)) emscripten_bind_b2MouseJointDef__get_dampingRatio_p0(b2MouseJointDef * self) {
  return self->dampingRatio;
}
float __attribute__((used, noinline)) emscripten_bind_b2DistanceProxy__get_m_radius_p0(b2DistanceProxy * self) {
  return self->m_radius;
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceProxy__Set_p2(b2DistanceProxy * self, const b2Shape * arg0, signed int arg1) {
  self->Set(arg0, arg1);
}
b2DistanceProxy * __attribute__((used, noinline)) emscripten_bind_b2DistanceProxy__b2DistanceProxy_p0() {
  return new b2DistanceProxy();
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceProxy__set_m_radius_p1(b2DistanceProxy * self, float arg0) {
  self->m_radius = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceProxy____destroy___p0(b2DistanceProxy * self) {
  delete self;
}
const b2Vec2 * __attribute__((used, noinline)) emscripten_bind_b2DistanceProxy__get_m_vertices_p0(b2DistanceProxy * self) {
  return self->m_vertices;
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2DistanceProxy__GetSupportVertex_p1(b2DistanceProxy * self, const b2Vec2 & arg0) {
  return self->GetSupportVertex(arg0);
}
signed int __attribute__((used, noinline)) emscripten_bind_b2DistanceProxy__get_m_count_p0(b2DistanceProxy * self) {
  return self->m_count;
}
int32 __attribute__((used, noinline)) emscripten_bind_b2DistanceProxy__GetVertexCount_p0(b2DistanceProxy * self) {
  return self->GetVertexCount();
}
const b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2DistanceProxy__GetVertex_p1(b2DistanceProxy * self, signed int arg0) {
  return self->GetVertex(arg0);
}
int32 __attribute__((used, noinline)) emscripten_bind_b2DistanceProxy__GetSupport_p1(b2DistanceProxy * self, const b2Vec2 & arg0) {
  return self->GetSupport(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceProxy__set_m_vertices_p1(b2DistanceProxy * self, const b2Vec2 * arg0) {
  self->m_vertices = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceProxy__set_m_count_p1(b2DistanceProxy * self, signed int arg0) {
  self->m_count = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__set_localAnchorA_p1(b2DistanceJointDef * self, b2Vec2& arg0) {
  self->localAnchorA = arg0;
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__get_bodyA_p1(b2DistanceJointDef * self, b2Body * arg0) {
  return self->get_bodyA(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__get_bodyB_p1(b2DistanceJointDef * self, b2Body * arg0) {
  return self->get_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__set_localAnchorB_p1(b2DistanceJointDef * self, b2Vec2& arg0) {
  self->localAnchorB = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__set_dampingRatio_p1(b2DistanceJointDef * self, float arg0) {
  self->dampingRatio = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__set_bodyA_p1(b2DistanceJointDef * self, b2Body * arg0) {
  self->set_bodyA(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__set_bodyB_p1(b2DistanceJointDef * self, b2Body * arg0) {
  self->set_bodyB(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__get_length_p0(b2DistanceJointDef * self) {
  return self->length;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__get_localAnchorA_p0(b2DistanceJointDef * self) {
  return self->localAnchorA;
}
float __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__get_frequencyHz_p0(b2DistanceJointDef * self) {
  return self->frequencyHz;
}
b2Vec2& __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__get_localAnchorB_p0(b2DistanceJointDef * self) {
  return self->localAnchorB;
}
bool __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__get_collideConnected_p1(b2DistanceJointDef * self, bool arg0) {
  return self->get_collideConnected(arg0);
}
float __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__get_dampingRatio_p0(b2DistanceJointDef * self) {
  return self->dampingRatio;
}
b2DistanceJointDef * __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__b2DistanceJointDef_p0() {
  return new b2DistanceJointDef();
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef____destroy___p0(b2DistanceJointDef * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__set_collideConnected_p1(b2DistanceJointDef * self, bool arg0) {
  self->set_collideConnected(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__set_length_p1(b2DistanceJointDef * self, float arg0) {
  self->length = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__set_frequencyHz_p1(b2DistanceJointDef * self, float arg0) {
  self->frequencyHz = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2DistanceJointDef__Initialize_p4(b2DistanceJointDef * self, b2Body * arg0, b2Body * arg1, const b2Vec2 & arg2, const b2Vec2 & arg3) {
  self->Initialize(arg0, arg1, arg2, arg3);
}
void __attribute__((used, noinline)) emscripten_bind_b2GearJointDef____destroy___p0(b2GearJointDef * self) {
  delete self;
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2GearJointDef__get_bodyA_p1(b2GearJointDef * self, b2Body * arg0) {
  return self->get_bodyA(arg0);
}
b2Body* __attribute__((used, noinline)) emscripten_bind_b2GearJointDef__get_bodyB_p1(b2GearJointDef * self, b2Body * arg0) {
  return self->get_bodyB(arg0);
}
b2Joint * __attribute__((used, noinline)) emscripten_bind_b2GearJointDef__get_joint1_p0(b2GearJointDef * self) {
  return self->joint1;
}
void __attribute__((used, noinline)) emscripten_bind_b2GearJointDef__set_bodyA_p1(b2GearJointDef * self, b2Body * arg0) {
  self->set_bodyA(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2GearJointDef__set_bodyB_p1(b2GearJointDef * self, b2Body * arg0) {
  self->set_bodyB(arg0);
}
void __attribute__((used, noinline)) emscripten_bind_b2GearJointDef__set_joint2_p1(b2GearJointDef * self, b2Joint * arg0) {
  self->joint2 = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2GearJointDef__set_ratio_p1(b2GearJointDef * self, float arg0) {
  self->ratio = arg0;
}
bool __attribute__((used, noinline)) emscripten_bind_b2GearJointDef__get_collideConnected_p1(b2GearJointDef * self, bool arg0) {
  return self->get_collideConnected(arg0);
}
b2Joint * __attribute__((used, noinline)) emscripten_bind_b2GearJointDef__get_joint2_p0(b2GearJointDef * self) {
  return self->joint2;
}
void __attribute__((used, noinline)) emscripten_bind_b2GearJointDef__set_collideConnected_p1(b2GearJointDef * self, bool arg0) {
  self->set_collideConnected(arg0);
}
b2GearJointDef * __attribute__((used, noinline)) emscripten_bind_b2GearJointDef__b2GearJointDef_p0() {
  return new b2GearJointDef();
}
float __attribute__((used, noinline)) emscripten_bind_b2GearJointDef__get_ratio_p0(b2GearJointDef * self) {
  return self->ratio;
}
void __attribute__((used, noinline)) emscripten_bind_b2GearJointDef__set_joint1_p1(b2GearJointDef * self, b2Joint * arg0) {
  self->joint1 = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactEdge____destroy___p0(b2ContactEdge * self) {
  delete self;
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactEdge__set_contact_p1(b2ContactEdge * self, b2Contact * arg0) {
  self->contact = arg0;
}
b2ContactEdge * __attribute__((used, noinline)) emscripten_bind_b2ContactEdge__get_prev_p0(b2ContactEdge * self) {
  return self->prev;
}
b2Body * __attribute__((used, noinline)) emscripten_bind_b2ContactEdge__get_other_p0(b2ContactEdge * self) {
  return self->other;
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactEdge__set_prev_p1(b2ContactEdge * self, b2ContactEdge * arg0) {
  self->prev = arg0;
}
b2ContactEdge * __attribute__((used, noinline)) emscripten_bind_b2ContactEdge__get_next_p0(b2ContactEdge * self) {
  return self->next;
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactEdge__set_other_p1(b2ContactEdge * self, b2Body * arg0) {
  self->other = arg0;
}
void __attribute__((used, noinline)) emscripten_bind_b2ContactEdge__set_next_p1(b2ContactEdge * self, b2ContactEdge * arg0) {
  self->next = arg0;
}
b2ContactEdge * __attribute__((used, noinline)) emscripten_bind_b2ContactEdge__b2ContactEdge_p0() {
  return new b2ContactEdge();
}
b2Contact * __attribute__((used, noinline)) emscripten_bind_b2ContactEdge__get_contact_p0(b2ContactEdge * self) {
  return self->contact;
}

}
