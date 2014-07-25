
// Bindings utilities

var Object__cache = {}; // we do it this way so we do not modify |Object|
function wrapPointer(ptr, __class__) {
  var cache = __class__ ? __class__.prototype.__cache__ : Object__cache;
  var ret = cache[ptr];
  if (ret) return ret;
  __class__ = __class__ || Object;
  ret = Object.create(__class__.prototype);
  ret.ptr = ptr;
  ret.__class__ = __class__;
  return cache[ptr] = ret;
}
Module['wrapPointer'] = wrapPointer;

function castObject(obj, __class__) {
  return wrapPointer(obj.ptr, __class__);
}
Module['castObject'] = castObject;

Module['NULL'] = wrapPointer(0);

function destroy(obj) {
  if (!obj['__destroy__']) throw 'Error: Cannot destroy object. (Did you create it yourself?)';
  obj['__destroy__']();
  // Remove from cache, so the object can be GC'd and refs added onto it released
  if (obj.__class__ !== Object) {
    delete obj.__class__.prototype.__cache__[obj.ptr];
  } else {
    delete Object__cache[obj.ptr];
  }
}
Module['destroy'] = destroy;

function compare(obj1, obj2) {
  return obj1.ptr === obj2.ptr;
}
Module['compare'] = compare;

function getPointer(obj) {
  return obj.ptr;
}
Module['getPointer'] = getPointer;

function getClass(obj) {
  return obj.__class__;
}
Module['getClass'] = getClass;

function customizeVTable(object, replacementPairs) {
  // Does not handle multiple inheritance

  // Find out vtable size
  var vTable = getValue(object.ptr, 'void*');
  // This assumes our modification where we null-terminate vtables
  var size = 0;
  while (getValue(vTable + Runtime.QUANTUM_SIZE*size, 'void*')) {
    size++;
  }

  // Prepare replacement lookup table and add replacements.
  // There is actually no good way to do this! So we do the following hack:
  // We create a fake vtable with canary functions, to detect which actual
  // function is being called
  var vTable2 = _malloc(size*Runtime.QUANTUM_SIZE);
  setValue(object.ptr, vTable2, 'void*');
  var canaryValue;
  var tempFuncs = [];
  for (var i = 0; i < size; i++) {
    (function(j) {
      var index = Runtime.addFunction(function() {
        canaryValue = j;
      });
      setValue(vTable2 + Runtime.QUANTUM_SIZE*i, index, 'void*');
      tempFuncs.push(index);
    })(i);
  }
  var args = [{ptr: 0}];
  replacementPairs.forEach(function(pair) {
    // We need the wrapper function that converts arguments to not fail. Keep adding arguments til it works.
    while(1) {
      try {
        pair['original'].apply(object, args);
        break;
      } catch(e) {
        args.push(args[0]);
      }
    }
    pair.originalIndex = getValue(vTable + canaryValue*Runtime.QUANTUM_SIZE, 'void*');
  });
  for (var i = 0; i < size; i++) {
    Runtime.removeFunction(tempFuncs[i]);
  }

  // Do the replacements

  var replacements = {};
  replacementPairs.forEach(function(pair) {
    replacements[pair.originalIndex] = Runtime.addFunction(pair['replacement']);
  });

  // Copy and modify vtable
  for (var i = 0; i < size; i++) {
    var value = getValue(vTable + Runtime.QUANTUM_SIZE*i, 'void*');
    if (value in replacements) value = replacements[value];
    setValue(vTable2 + Runtime.QUANTUM_SIZE*i, value, 'void*');
  }
  return object;
}
Module['customizeVTable'] = customizeVTable;

// Converts a value into a C-style string.
function ensureString(value) {
  if (typeof value == 'number') return value;
  return allocate(intArrayFromString(value), 'i8', ALLOC_STACK);
}

b2ContactManager.prototype['get_m_contactFilter'] = function() {
    return wrapPointer(_emscripten_bind_b2ContactManager__get_m_contactFilter_p0(this.ptr), Module['b2ContactFilter']);
}

b2ContactManager.prototype['get_m_contactCount'] = function() {
    return _emscripten_bind_b2ContactManager__get_m_contactCount_p0(this.ptr);
}

b2ContactManager.prototype['set_m_contactFilter'] = function(arg0) {
    _emscripten_bind_b2ContactManager__set_m_contactFilter_p1(this.ptr, arg0.ptr);
}

function b2ContactManager() {
    this.ptr = _emscripten_bind_b2ContactManager__b2ContactManager_p0();
  b2ContactManager.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2ContactManager;
}
b2ContactManager.prototype.__cache__ = {};
Module['b2ContactManager'] = b2ContactManager;

b2ContactManager.prototype['AddPair'] = function(arg0, arg1) {
    _emscripten_bind_b2ContactManager__AddPair_p2(this.ptr, arg0, arg1);
}

b2ContactManager.prototype['set_m_allocator'] = function(arg0) {
    _emscripten_bind_b2ContactManager__set_m_allocator_p1(this.ptr, arg0.ptr);
}

b2ContactManager.prototype['set_m_contactCount'] = function(arg0) {
    _emscripten_bind_b2ContactManager__set_m_contactCount_p1(this.ptr, arg0);
}

b2ContactManager.prototype['Collide'] = function() {
    _emscripten_bind_b2ContactManager__Collide_p0(this.ptr);
}

b2ContactManager.prototype['set_m_contactList'] = function(arg0) {
    _emscripten_bind_b2ContactManager__set_m_contactList_p1(this.ptr, arg0.ptr);
}

b2ContactManager.prototype['FindNewContacts'] = function() {
    _emscripten_bind_b2ContactManager__FindNewContacts_p0(this.ptr);
}

b2ContactManager.prototype['get_m_contactListener'] = function() {
    return wrapPointer(_emscripten_bind_b2ContactManager__get_m_contactListener_p0(this.ptr), Module['b2ContactListener']);
}

b2ContactManager.prototype['__destroy__'] = function() {
    _emscripten_bind_b2ContactManager____destroy___p0(this.ptr);
}

b2ContactManager.prototype['set_m_contactListener'] = function(arg0) {
    _emscripten_bind_b2ContactManager__set_m_contactListener_p1(this.ptr, arg0.ptr);
}

b2ContactManager.prototype['get_m_broadPhase'] = function() {
    return wrapPointer(_emscripten_bind_b2ContactManager__get_m_broadPhase_p0(this.ptr), Module['b2BroadPhase']);
}

b2ContactManager.prototype['Destroy'] = function(arg0) {
    _emscripten_bind_b2ContactManager__Destroy_p1(this.ptr, arg0.ptr);
}

b2ContactManager.prototype['set_m_broadPhase'] = function(arg0) {
    _emscripten_bind_b2ContactManager__set_m_broadPhase_p1(this.ptr, arg0.ptr);
}

b2ContactManager.prototype['get_m_contactList'] = function() {
    return wrapPointer(_emscripten_bind_b2ContactManager__get_m_contactList_p0(this.ptr), Module['b2Contact']);
}

b2ContactManager.prototype['get_m_allocator'] = function() {
    return wrapPointer(_emscripten_bind_b2ContactManager__get_m_allocator_p0(this.ptr), Module['b2BlockAllocator']);
}

b2DistanceJoint.prototype['GetBodyA'] = function() {
    return wrapPointer(_emscripten_bind_b2DistanceJoint__GetBodyA_p0(this.ptr), Module['b2Body']);
}

b2DistanceJoint.prototype['GetBodyB'] = function() {
    return wrapPointer(_emscripten_bind_b2DistanceJoint__GetBodyB_p0(this.ptr), Module['b2Body']);
}

b2DistanceJoint.prototype['SetFrequency'] = function(arg0) {
    _emscripten_bind_b2DistanceJoint__SetFrequency_p1(this.ptr, arg0);
}

b2DistanceJoint.prototype['GetUserData'] = function() {
    return _emscripten_bind_b2DistanceJoint__GetUserData_p0(this.ptr);
}

b2DistanceJoint.prototype['SetUserData'] = function(arg0) {
    _emscripten_bind_b2DistanceJoint__SetUserData_p1(this.ptr, arg0);
}

b2DistanceJoint.prototype['GetAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2DistanceJoint__GetAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2DistanceJoint.prototype['GetAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2DistanceJoint__GetAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2DistanceJoint.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2DistanceJoint__GetNext_p0(this.ptr), Module['b2Joint']);
}

b2DistanceJoint.prototype['GetLocalAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2DistanceJoint__GetLocalAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2DistanceJoint.prototype['GetLocalAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2DistanceJoint__GetLocalAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2DistanceJoint.prototype['GetFrequency'] = function() {
    return _emscripten_bind_b2DistanceJoint__GetFrequency_p0(this.ptr);
}

b2DistanceJoint.prototype['GetReactionForce'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2DistanceJoint__GetReactionForce_p1(this.ptr, arg0), Module['b2Vec2']);
}

b2DistanceJoint.prototype['GetLength'] = function() {
    return _emscripten_bind_b2DistanceJoint__GetLength_p0(this.ptr);
}

b2DistanceJoint.prototype['GetDampingRatio'] = function() {
    return _emscripten_bind_b2DistanceJoint__GetDampingRatio_p0(this.ptr);
}

b2DistanceJoint.prototype['GetCollideConnected'] = function() {
    return _emscripten_bind_b2DistanceJoint__GetCollideConnected_p0(this.ptr);
}

b2DistanceJoint.prototype['__destroy__'] = function() {
    _emscripten_bind_b2DistanceJoint____destroy___p0(this.ptr);
}

b2DistanceJoint.prototype['Dump'] = function() {
    _emscripten_bind_b2DistanceJoint__Dump_p0(this.ptr);
}

b2DistanceJoint.prototype['GetType'] = function() {
    return _emscripten_bind_b2DistanceJoint__GetType_p0(this.ptr);
}

function b2DistanceJoint(arg0) {
    this.ptr = _emscripten_bind_b2DistanceJoint__b2DistanceJoint_p1(arg0.ptr);
  b2DistanceJoint.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2DistanceJoint;
}
b2DistanceJoint.prototype.__cache__ = {};
Module['b2DistanceJoint'] = b2DistanceJoint;

b2DistanceJoint.prototype['SetDampingRatio'] = function(arg0) {
    _emscripten_bind_b2DistanceJoint__SetDampingRatio_p1(this.ptr, arg0);
}

b2DistanceJoint.prototype['GetReactionTorque'] = function(arg0) {
    return _emscripten_bind_b2DistanceJoint__GetReactionTorque_p1(this.ptr, arg0);
}

b2DistanceJoint.prototype['SetLength'] = function(arg0) {
    _emscripten_bind_b2DistanceJoint__SetLength_p1(this.ptr, arg0);
}

b2DistanceJoint.prototype['IsActive'] = function() {
    return _emscripten_bind_b2DistanceJoint__IsActive_p0(this.ptr);
}

b2Fixture.prototype['GetRestitution'] = function() {
    return _emscripten_bind_b2Fixture__GetRestitution_p0(this.ptr);
}

b2Fixture.prototype['SetFilterData'] = function(arg0) {
    _emscripten_bind_b2Fixture__SetFilterData_p1(this.ptr, arg0.ptr);
}

b2Fixture.prototype['SetFriction'] = function(arg0) {
    _emscripten_bind_b2Fixture__SetFriction_p1(this.ptr, arg0);
}

function b2Fixture() {
    this.ptr = _emscripten_bind_b2Fixture__b2Fixture_p0();
  b2Fixture.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2Fixture;
}
b2Fixture.prototype.__cache__ = {};
Module['b2Fixture'] = b2Fixture;

b2Fixture.prototype['GetShape'] = function() {
    return wrapPointer(_emscripten_bind_b2Fixture__GetShape_p0(this.ptr), Module['b2Shape']);
}

b2Fixture.prototype['SetRestitution'] = function(arg0) {
    _emscripten_bind_b2Fixture__SetRestitution_p1(this.ptr, arg0);
}

b2Fixture.prototype['GetBody'] = function() {
    return wrapPointer(_emscripten_bind_b2Fixture__GetBody_p0(this.ptr), Module['b2Body']);
}

b2Fixture.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2Fixture__GetNext_p0(this.ptr), Module['b2Fixture']);
}

b2Fixture.prototype['GetFriction'] = function() {
    return _emscripten_bind_b2Fixture__GetFriction_p0(this.ptr);
}

b2Fixture.prototype['GetUserData'] = function() {
    return _emscripten_bind_b2Fixture__GetUserData_p0(this.ptr);
}

b2Fixture.prototype['SetDensity'] = function(arg0) {
    _emscripten_bind_b2Fixture__SetDensity_p1(this.ptr, arg0);
}

b2Fixture.prototype['GetMassData'] = function(arg0) {
    _emscripten_bind_b2Fixture__GetMassData_p1(this.ptr, arg0.ptr);
}

b2Fixture.prototype['SetSensor'] = function(arg0) {
    _emscripten_bind_b2Fixture__SetSensor_p1(this.ptr, arg0);
}

b2Fixture.prototype['GetAABB'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2Fixture__GetAABB_p1(this.ptr, arg0), Module['b2AABB']);
}

b2Fixture.prototype['TestPoint'] = function(arg0) {
    return _emscripten_bind_b2Fixture__TestPoint_p1(this.ptr, arg0.ptr);
}

b2Fixture.prototype['SetUserData'] = function(arg0) {
    _emscripten_bind_b2Fixture__SetUserData_p1(this.ptr, arg0);
}

b2Fixture.prototype['__destroy__'] = function() {
    _emscripten_bind_b2Fixture____destroy___p0(this.ptr);
}

b2Fixture.prototype['RayCast'] = function(arg0, arg1, arg2) {
    return _emscripten_bind_b2Fixture__RayCast_p3(this.ptr, arg0.ptr, arg1.ptr, arg2);
}

b2Fixture.prototype['Refilter'] = function() {
    _emscripten_bind_b2Fixture__Refilter_p0(this.ptr);
}

b2Fixture.prototype['Dump'] = function(arg0) {
    _emscripten_bind_b2Fixture__Dump_p1(this.ptr, arg0);
}

b2Fixture.prototype['GetFilterData'] = function() {
    return wrapPointer(_emscripten_bind_b2Fixture__GetFilterData_p0(this.ptr), Module['b2Filter']);
}

b2Fixture.prototype['IsSensor'] = function() {
    return _emscripten_bind_b2Fixture__IsSensor_p0(this.ptr);
}

b2Fixture.prototype['GetType'] = function() {
    return _emscripten_bind_b2Fixture__GetType_p0(this.ptr);
}

b2Fixture.prototype['GetDensity'] = function() {
    return _emscripten_bind_b2Fixture__GetDensity_p0(this.ptr);
}

b2MouseJoint.prototype['GetBodyA'] = function() {
    return wrapPointer(_emscripten_bind_b2MouseJoint__GetBodyA_p0(this.ptr), Module['b2Body']);
}

b2MouseJoint.prototype['GetBodyB'] = function() {
    return wrapPointer(_emscripten_bind_b2MouseJoint__GetBodyB_p0(this.ptr), Module['b2Body']);
}

b2MouseJoint.prototype['SetFrequency'] = function(arg0) {
    _emscripten_bind_b2MouseJoint__SetFrequency_p1(this.ptr, arg0);
}

b2MouseJoint.prototype['GetUserData'] = function() {
    return _emscripten_bind_b2MouseJoint__GetUserData_p0(this.ptr);
}

b2MouseJoint.prototype['SetMaxForce'] = function(arg0) {
    _emscripten_bind_b2MouseJoint__SetMaxForce_p1(this.ptr, arg0);
}

b2MouseJoint.prototype['SetUserData'] = function(arg0) {
    _emscripten_bind_b2MouseJoint__SetUserData_p1(this.ptr, arg0);
}

b2MouseJoint.prototype['GetAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2MouseJoint__GetAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2MouseJoint.prototype['GetAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2MouseJoint__GetAnchorA_p0(this.ptr), Module['b2Vec2']);
}

function b2MouseJoint(arg0) {
    this.ptr = _emscripten_bind_b2MouseJoint__b2MouseJoint_p1(arg0.ptr);
  b2MouseJoint.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2MouseJoint;
}
b2MouseJoint.prototype.__cache__ = {};
Module['b2MouseJoint'] = b2MouseJoint;

b2MouseJoint.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2MouseJoint__GetNext_p0(this.ptr), Module['b2Joint']);
}

b2MouseJoint.prototype['GetMaxForce'] = function() {
    return _emscripten_bind_b2MouseJoint__GetMaxForce_p0(this.ptr);
}

b2MouseJoint.prototype['GetTarget'] = function() {
    return wrapPointer(_emscripten_bind_b2MouseJoint__GetTarget_p0(this.ptr), Module['b2Vec2']);
}

b2MouseJoint.prototype['GetFrequency'] = function() {
    return _emscripten_bind_b2MouseJoint__GetFrequency_p0(this.ptr);
}

b2MouseJoint.prototype['GetReactionForce'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2MouseJoint__GetReactionForce_p1(this.ptr, arg0), Module['b2Vec2']);
}

b2MouseJoint.prototype['GetDampingRatio'] = function() {
    return _emscripten_bind_b2MouseJoint__GetDampingRatio_p0(this.ptr);
}

b2MouseJoint.prototype['GetCollideConnected'] = function() {
    return _emscripten_bind_b2MouseJoint__GetCollideConnected_p0(this.ptr);
}

b2MouseJoint.prototype['__destroy__'] = function() {
    _emscripten_bind_b2MouseJoint____destroy___p0(this.ptr);
}

b2MouseJoint.prototype['Dump'] = function() {
    _emscripten_bind_b2MouseJoint__Dump_p0(this.ptr);
}

b2MouseJoint.prototype['SetTarget'] = function(arg0) {
    _emscripten_bind_b2MouseJoint__SetTarget_p1(this.ptr, arg0.ptr);
}

b2MouseJoint.prototype['GetType'] = function() {
    return _emscripten_bind_b2MouseJoint__GetType_p0(this.ptr);
}

b2MouseJoint.prototype['SetDampingRatio'] = function(arg0) {
    _emscripten_bind_b2MouseJoint__SetDampingRatio_p1(this.ptr, arg0);
}

b2MouseJoint.prototype['GetReactionTorque'] = function(arg0) {
    return _emscripten_bind_b2MouseJoint__GetReactionTorque_p1(this.ptr, arg0);
}

b2MouseJoint.prototype['IsActive'] = function() {
    return _emscripten_bind_b2MouseJoint__IsActive_p0(this.ptr);
}

b2PulleyJoint.prototype['GetBodyA'] = function() {
    return wrapPointer(_emscripten_bind_b2PulleyJoint__GetBodyA_p0(this.ptr), Module['b2Body']);
}

b2PulleyJoint.prototype['__destroy__'] = function() {
    _emscripten_bind_b2PulleyJoint____destroy___p0(this.ptr);
}

b2PulleyJoint.prototype['GetAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2PulleyJoint__GetAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2PulleyJoint.prototype['GetType'] = function() {
    return _emscripten_bind_b2PulleyJoint__GetType_p0(this.ptr);
}

b2PulleyJoint.prototype['GetGroundAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2PulleyJoint__GetGroundAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2PulleyJoint.prototype['GetReactionTorque'] = function(arg0) {
    return _emscripten_bind_b2PulleyJoint__GetReactionTorque_p1(this.ptr, arg0);
}

b2PulleyJoint.prototype['Dump'] = function() {
    _emscripten_bind_b2PulleyJoint__Dump_p0(this.ptr);
}

b2PulleyJoint.prototype['GetGroundAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2PulleyJoint__GetGroundAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2PulleyJoint.prototype['GetLengthB'] = function() {
    return _emscripten_bind_b2PulleyJoint__GetLengthB_p0(this.ptr);
}

b2PulleyJoint.prototype['GetUserData'] = function() {
    return _emscripten_bind_b2PulleyJoint__GetUserData_p0(this.ptr);
}

b2PulleyJoint.prototype['GetLengthA'] = function() {
    return _emscripten_bind_b2PulleyJoint__GetLengthA_p0(this.ptr);
}

b2PulleyJoint.prototype['GetBodyB'] = function() {
    return wrapPointer(_emscripten_bind_b2PulleyJoint__GetBodyB_p0(this.ptr), Module['b2Body']);
}

b2PulleyJoint.prototype['GetCollideConnected'] = function() {
    return _emscripten_bind_b2PulleyJoint__GetCollideConnected_p0(this.ptr);
}

b2PulleyJoint.prototype['SetUserData'] = function(arg0) {
    _emscripten_bind_b2PulleyJoint__SetUserData_p1(this.ptr, arg0);
}

b2PulleyJoint.prototype['GetAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2PulleyJoint__GetAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2PulleyJoint.prototype['GetReactionForce'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2PulleyJoint__GetReactionForce_p1(this.ptr, arg0), Module['b2Vec2']);
}

b2PulleyJoint.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2PulleyJoint__GetNext_p0(this.ptr), Module['b2Joint']);
}

function b2PulleyJoint(arg0) {
    this.ptr = _emscripten_bind_b2PulleyJoint__b2PulleyJoint_p1(arg0.ptr);
  b2PulleyJoint.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2PulleyJoint;
}
b2PulleyJoint.prototype.__cache__ = {};
Module['b2PulleyJoint'] = b2PulleyJoint;

b2PulleyJoint.prototype['IsActive'] = function() {
    return _emscripten_bind_b2PulleyJoint__IsActive_p0(this.ptr);
}

b2PulleyJoint.prototype['GetRatio'] = function() {
    return _emscripten_bind_b2PulleyJoint__GetRatio_p0(this.ptr);
}

b2BroadPhase.prototype['GetTreeQuality'] = function() {
    return _emscripten_bind_b2BroadPhase__GetTreeQuality_p0(this.ptr);
}

b2BroadPhase.prototype['GetFatAABB'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2BroadPhase__GetFatAABB_p1(this.ptr, arg0), Module['b2AABB']);
}

b2BroadPhase.prototype['GetUserData'] = function(arg0) {
    return _emscripten_bind_b2BroadPhase__GetUserData_p1(this.ptr, arg0);
}

b2BroadPhase.prototype['__destroy__'] = function() {
    _emscripten_bind_b2BroadPhase____destroy___p0(this.ptr);
}

b2BroadPhase.prototype['GetTreeHeight'] = function() {
    return _emscripten_bind_b2BroadPhase__GetTreeHeight_p0(this.ptr);
}

function b2BroadPhase() {
    this.ptr = _emscripten_bind_b2BroadPhase__b2BroadPhase_p0();
  b2BroadPhase.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2BroadPhase;
}
b2BroadPhase.prototype.__cache__ = {};
Module['b2BroadPhase'] = b2BroadPhase;

b2BroadPhase.prototype['GetProxyCount'] = function() {
    return _emscripten_bind_b2BroadPhase__GetProxyCount_p0(this.ptr);
}

b2BroadPhase.prototype['GetTreeBalance'] = function() {
    return _emscripten_bind_b2BroadPhase__GetTreeBalance_p0(this.ptr);
}

b2BroadPhase.prototype['TestOverlap'] = function(arg0, arg1) {
    return _emscripten_bind_b2BroadPhase__TestOverlap_p2(this.ptr, arg0, arg1);
}

b2BroadPhase.prototype['TouchProxy'] = function(arg0) {
    _emscripten_bind_b2BroadPhase__TouchProxy_p1(this.ptr, arg0);
}

b2BroadPhase.prototype['CreateProxy'] = function(arg0, arg1) {
    return _emscripten_bind_b2BroadPhase__CreateProxy_p2(this.ptr, arg0.ptr, arg1);
}

b2BroadPhase.prototype['MoveProxy'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2BroadPhase__MoveProxy_p3(this.ptr, arg0, arg1.ptr, arg2.ptr);
}

b2BroadPhase.prototype['DestroyProxy'] = function(arg0) {
    _emscripten_bind_b2BroadPhase__DestroyProxy_p1(this.ptr, arg0);
}

b2World.prototype['QueryAABB'] = function(arg0, arg1) {
    _emscripten_bind_b2World__QueryAABB_p2(this.ptr, arg0.ptr, arg1.ptr);
}

b2World.prototype['SetSubStepping'] = function(arg0) {
    _emscripten_bind_b2World__SetSubStepping_p1(this.ptr, arg0);
}

b2World.prototype['GetTreeQuality'] = function() {
    return _emscripten_bind_b2World__GetTreeQuality_p0(this.ptr);
}

b2World.prototype['GetTreeHeight'] = function() {
    return _emscripten_bind_b2World__GetTreeHeight_p0(this.ptr);
}

b2World.prototype['GetProfile'] = function() {
    return wrapPointer(_emscripten_bind_b2World__GetProfile_p0(this.ptr), Module['b2Profile']);
}

b2World.prototype['GetTreeBalance'] = function() {
    return _emscripten_bind_b2World__GetTreeBalance_p0(this.ptr);
}

b2World.prototype['GetSubStepping'] = function() {
    return _emscripten_bind_b2World__GetSubStepping_p0(this.ptr);
}

b2World.prototype['GetContactManager'] = function() {
    return wrapPointer(_emscripten_bind_b2World__GetContactManager_p0(this.ptr), Module['b2ContactManager']);
}

b2World.prototype['SetContactListener'] = function(arg0) {
    _emscripten_bind_b2World__SetContactListener_p1(this.ptr, arg0.ptr);
}

b2World.prototype['DrawDebugData'] = function() {
    _emscripten_bind_b2World__DrawDebugData_p0(this.ptr);
}

b2World.prototype['SetContinuousPhysics'] = function(arg0) {
    _emscripten_bind_b2World__SetContinuousPhysics_p1(this.ptr, arg0);
}

b2World.prototype['SetGravity'] = function(arg0) {
    _emscripten_bind_b2World__SetGravity_p1(this.ptr, arg0.ptr);
}

b2World.prototype['GetBodyCount'] = function() {
    return _emscripten_bind_b2World__GetBodyCount_p0(this.ptr);
}

b2World.prototype['GetAutoClearForces'] = function() {
    return _emscripten_bind_b2World__GetAutoClearForces_p0(this.ptr);
}

b2World.prototype['GetContinuousPhysics'] = function() {
    return _emscripten_bind_b2World__GetContinuousPhysics_p0(this.ptr);
}

b2World.prototype['GetJointList'] = function() {
    return wrapPointer(_emscripten_bind_b2World__GetJointList_p0(this.ptr), Module['b2Joint']);
}

b2World.prototype['CreateBody'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2World__CreateBody_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2World.prototype['GetBodyList'] = function() {
    return wrapPointer(_emscripten_bind_b2World__GetBodyList_p0(this.ptr), Module['b2Body']);
}

b2World.prototype['SetDestructionListener'] = function(arg0) {
    _emscripten_bind_b2World__SetDestructionListener_p1(this.ptr, arg0.ptr);
}

b2World.prototype['DestroyJoint'] = function(arg0) {
    _emscripten_bind_b2World__DestroyJoint_p1(this.ptr, arg0.ptr);
}

function b2World(arg0) {
    this.ptr = _emscripten_bind_b2World__b2World_p1(arg0.ptr);
  b2World.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2World;
}
b2World.prototype.__cache__ = {};
Module['b2World'] = b2World;

b2World.prototype['GetJointCount'] = function() {
    return _emscripten_bind_b2World__GetJointCount_p0(this.ptr);
}

b2World.prototype['Step'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2World__Step_p3(this.ptr, arg0, arg1, arg2);
}

b2World.prototype['ClearForces'] = function() {
    _emscripten_bind_b2World__ClearForces_p0(this.ptr);
}

b2World.prototype['GetWarmStarting'] = function() {
    return _emscripten_bind_b2World__GetWarmStarting_p0(this.ptr);
}

b2World.prototype['SetAllowSleeping'] = function(arg0) {
    _emscripten_bind_b2World__SetAllowSleeping_p1(this.ptr, arg0);
}

b2World.prototype['DestroyBody'] = function(arg0) {
    _emscripten_bind_b2World__DestroyBody_p1(this.ptr, arg0.ptr);
}

b2World.prototype['GetAllowSleeping'] = function() {
    return _emscripten_bind_b2World__GetAllowSleeping_p0(this.ptr);
}

b2World.prototype['CreateJoint'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2World__CreateJoint_p1(this.ptr, arg0.ptr), Module['b2Joint']);
}

b2World.prototype['GetProxyCount'] = function() {
    return _emscripten_bind_b2World__GetProxyCount_p0(this.ptr);
}

b2World.prototype['RayCast'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2World__RayCast_p3(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr);
}

b2World.prototype['IsLocked'] = function() {
    return _emscripten_bind_b2World__IsLocked_p0(this.ptr);
}

b2World.prototype['GetContactList'] = function() {
    return wrapPointer(_emscripten_bind_b2World__GetContactList_p0(this.ptr), Module['b2Contact']);
}

b2World.prototype['SetDebugDraw'] = function(arg0) {
    _emscripten_bind_b2World__SetDebugDraw_p1(this.ptr, arg0.ptr);
}

b2World.prototype['__destroy__'] = function() {
    _emscripten_bind_b2World____destroy___p0(this.ptr);
}

b2World.prototype['Dump'] = function() {
    _emscripten_bind_b2World__Dump_p0(this.ptr);
}

b2World.prototype['SetAutoClearForces'] = function(arg0) {
    _emscripten_bind_b2World__SetAutoClearForces_p1(this.ptr, arg0);
}

b2World.prototype['GetGravity'] = function() {
    return wrapPointer(_emscripten_bind_b2World__GetGravity_p0(this.ptr), Module['b2Vec2']);
}

b2World.prototype['GetContactCount'] = function() {
    return _emscripten_bind_b2World__GetContactCount_p0(this.ptr);
}

b2World.prototype['SetWarmStarting'] = function(arg0) {
    _emscripten_bind_b2World__SetWarmStarting_p1(this.ptr, arg0);
}

b2World.prototype['SetContactFilter'] = function(arg0) {
    _emscripten_bind_b2World__SetContactFilter_p1(this.ptr, arg0.ptr);
}

b2PrismaticJoint.prototype['GetBodyA'] = function() {
    return wrapPointer(_emscripten_bind_b2PrismaticJoint__GetBodyA_p0(this.ptr), Module['b2Body']);
}

b2PrismaticJoint.prototype['GetBodyB'] = function() {
    return wrapPointer(_emscripten_bind_b2PrismaticJoint__GetBodyB_p0(this.ptr), Module['b2Body']);
}

b2PrismaticJoint.prototype['GetUserData'] = function() {
    return _emscripten_bind_b2PrismaticJoint__GetUserData_p0(this.ptr);
}

b2PrismaticJoint.prototype['GetLocalAxisA'] = function() {
    return wrapPointer(_emscripten_bind_b2PrismaticJoint__GetLocalAxisA_p0(this.ptr), Module['b2Vec2']);
}

b2PrismaticJoint.prototype['GetLowerLimit'] = function() {
    return _emscripten_bind_b2PrismaticJoint__GetLowerLimit_p0(this.ptr);
}

b2PrismaticJoint.prototype['GetAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2PrismaticJoint__GetAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2PrismaticJoint.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2PrismaticJoint__GetNext_p0(this.ptr), Module['b2Joint']);
}

function b2PrismaticJoint(arg0) {
    this.ptr = _emscripten_bind_b2PrismaticJoint__b2PrismaticJoint_p1(arg0.ptr);
  b2PrismaticJoint.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2PrismaticJoint;
}
b2PrismaticJoint.prototype.__cache__ = {};
Module['b2PrismaticJoint'] = b2PrismaticJoint;

b2PrismaticJoint.prototype['GetLocalAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2PrismaticJoint__GetLocalAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2PrismaticJoint.prototype['SetMotorSpeed'] = function(arg0) {
    _emscripten_bind_b2PrismaticJoint__SetMotorSpeed_p1(this.ptr, arg0);
}

b2PrismaticJoint.prototype['GetLocalAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2PrismaticJoint__GetLocalAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2PrismaticJoint.prototype['GetMotorSpeed'] = function() {
    return _emscripten_bind_b2PrismaticJoint__GetMotorSpeed_p0(this.ptr);
}

b2PrismaticJoint.prototype['SetMaxMotorForce'] = function(arg0) {
    _emscripten_bind_b2PrismaticJoint__SetMaxMotorForce_p1(this.ptr, arg0);
}

b2PrismaticJoint.prototype['EnableLimit'] = function(arg0) {
    _emscripten_bind_b2PrismaticJoint__EnableLimit_p1(this.ptr, arg0);
}

b2PrismaticJoint.prototype['IsMotorEnabled'] = function() {
    return _emscripten_bind_b2PrismaticJoint__IsMotorEnabled_p0(this.ptr);
}

b2PrismaticJoint.prototype['SetUserData'] = function(arg0) {
    _emscripten_bind_b2PrismaticJoint__SetUserData_p1(this.ptr, arg0);
}

b2PrismaticJoint.prototype['GetReactionForce'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2PrismaticJoint__GetReactionForce_p1(this.ptr, arg0), Module['b2Vec2']);
}

b2PrismaticJoint.prototype['GetMaxMotorForce'] = function() {
    return _emscripten_bind_b2PrismaticJoint__GetMaxMotorForce_p0(this.ptr);
}

b2PrismaticJoint.prototype['GetCollideConnected'] = function() {
    return _emscripten_bind_b2PrismaticJoint__GetCollideConnected_p0(this.ptr);
}

b2PrismaticJoint.prototype['GetJointSpeed'] = function() {
    return _emscripten_bind_b2PrismaticJoint__GetJointSpeed_p0(this.ptr);
}

b2PrismaticJoint.prototype['EnableMotor'] = function(arg0) {
    _emscripten_bind_b2PrismaticJoint__EnableMotor_p1(this.ptr, arg0);
}

b2PrismaticJoint.prototype['__destroy__'] = function() {
    _emscripten_bind_b2PrismaticJoint____destroy___p0(this.ptr);
}

b2PrismaticJoint.prototype['GetReferenceAngle'] = function() {
    return _emscripten_bind_b2PrismaticJoint__GetReferenceAngle_p0(this.ptr);
}

b2PrismaticJoint.prototype['Dump'] = function() {
    _emscripten_bind_b2PrismaticJoint__Dump_p0(this.ptr);
}

b2PrismaticJoint.prototype['GetMotorForce'] = function(arg0) {
    return _emscripten_bind_b2PrismaticJoint__GetMotorForce_p1(this.ptr, arg0);
}

b2PrismaticJoint.prototype['GetJointTranslation'] = function() {
    return _emscripten_bind_b2PrismaticJoint__GetJointTranslation_p0(this.ptr);
}

b2PrismaticJoint.prototype['GetType'] = function() {
    return _emscripten_bind_b2PrismaticJoint__GetType_p0(this.ptr);
}

b2PrismaticJoint.prototype['IsLimitEnabled'] = function() {
    return _emscripten_bind_b2PrismaticJoint__IsLimitEnabled_p0(this.ptr);
}

b2PrismaticJoint.prototype['GetReactionTorque'] = function(arg0) {
    return _emscripten_bind_b2PrismaticJoint__GetReactionTorque_p1(this.ptr, arg0);
}

b2PrismaticJoint.prototype['SetLimits'] = function(arg0, arg1) {
    _emscripten_bind_b2PrismaticJoint__SetLimits_p2(this.ptr, arg0, arg1);
}

b2PrismaticJoint.prototype['GetUpperLimit'] = function() {
    return _emscripten_bind_b2PrismaticJoint__GetUpperLimit_p0(this.ptr);
}

b2PrismaticJoint.prototype['IsActive'] = function() {
    return _emscripten_bind_b2PrismaticJoint__IsActive_p0(this.ptr);
}

b2PrismaticJoint.prototype['GetAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2PrismaticJoint__GetAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2CircleShape.prototype['__destroy__'] = function() {
    _emscripten_bind_b2CircleShape____destroy___p0(this.ptr);
}

b2CircleShape.prototype['GetType'] = function() {
    return _emscripten_bind_b2CircleShape__GetType_p0(this.ptr);
}

b2CircleShape.prototype['ComputeMass'] = function(arg0, arg1) {
    _emscripten_bind_b2CircleShape__ComputeMass_p2(this.ptr, arg0.ptr, arg1);
}

b2CircleShape.prototype['set_m_radius'] = function(arg0) {
    _emscripten_bind_b2CircleShape__set_m_radius_p1(this.ptr, arg0);
}

b2CircleShape.prototype['get_m_radius'] = function() {
    return _emscripten_bind_b2CircleShape__get_m_radius_p0(this.ptr);
}

b2CircleShape.prototype['GetVertex'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2CircleShape__GetVertex_p1(this.ptr, arg0), Module['b2Vec2']);
}

b2CircleShape.prototype['Clone'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2CircleShape__Clone_p1(this.ptr, arg0.ptr), Module['b2Shape']);
}

b2CircleShape.prototype['GetSupportVertex'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2CircleShape__GetSupportVertex_p1(this.ptr, arg0.ptr), Module['b2Vec2']);
}

b2CircleShape.prototype['RayCast'] = function(arg0, arg1, arg2, arg3) {
    return _emscripten_bind_b2CircleShape__RayCast_p4(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr, arg3);
}

b2CircleShape.prototype['ComputeAABB'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2CircleShape__ComputeAABB_p3(this.ptr, arg0.ptr, arg1.ptr, arg2);
}

b2CircleShape.prototype['GetVertexCount'] = function() {
    return _emscripten_bind_b2CircleShape__GetVertexCount_p0(this.ptr);
}

b2CircleShape.prototype['GetChildCount'] = function() {
    return _emscripten_bind_b2CircleShape__GetChildCount_p0(this.ptr);
}

b2CircleShape.prototype['TestPoint'] = function(arg0, arg1) {
    return _emscripten_bind_b2CircleShape__TestPoint_p2(this.ptr, arg0.ptr, arg1.ptr);
}

function b2CircleShape() {
    this.ptr = _emscripten_bind_b2CircleShape__b2CircleShape_p0();
  b2CircleShape.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2CircleShape;
}
b2CircleShape.prototype.__cache__ = {};
Module['b2CircleShape'] = b2CircleShape;

b2CircleShape.prototype['GetSupport'] = function(arg0) {
    return _emscripten_bind_b2CircleShape__GetSupport_p1(this.ptr, arg0.ptr);
}

b2CircleShape.prototype['set_m_p'] = function(arg0) {
    _emscripten_bind_b2CircleShape__set_m_p_p1(this.ptr, arg0.ptr);
}

b2CircleShape.prototype['get_m_p'] = function() {
    return wrapPointer(_emscripten_bind_b2CircleShape__get_m_p_p0(this.ptr), Module['b2Vec2']);
}

b2WheelJoint.prototype['GetBodyA'] = function() {
    return wrapPointer(_emscripten_bind_b2WheelJoint__GetBodyA_p0(this.ptr), Module['b2Body']);
}

b2WheelJoint.prototype['GetBodyB'] = function() {
    return wrapPointer(_emscripten_bind_b2WheelJoint__GetBodyB_p0(this.ptr), Module['b2Body']);
}

b2WheelJoint.prototype['GetUserData'] = function() {
    return _emscripten_bind_b2WheelJoint__GetUserData_p0(this.ptr);
}

b2WheelJoint.prototype['GetDefinition'] = function(arg0) {
    _emscripten_bind_b2WheelJoint__GetDefinition_p1(this.ptr, arg0.ptr);
}

b2WheelJoint.prototype['GetLocalAxisA'] = function() {
    return wrapPointer(_emscripten_bind_b2WheelJoint__GetLocalAxisA_p0(this.ptr), Module['b2Vec2']);
}

b2WheelJoint.prototype['SetSpringDampingRatio'] = function(arg0) {
    _emscripten_bind_b2WheelJoint__SetSpringDampingRatio_p1(this.ptr, arg0);
}

b2WheelJoint.prototype['GetAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2WheelJoint__GetAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2WheelJoint.prototype['GetAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2WheelJoint__GetAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2WheelJoint.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2WheelJoint__GetNext_p0(this.ptr), Module['b2Joint']);
}

b2WheelJoint.prototype['GetSpringFrequencyHz'] = function() {
    return _emscripten_bind_b2WheelJoint__GetSpringFrequencyHz_p0(this.ptr);
}

b2WheelJoint.prototype['GetLocalAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2WheelJoint__GetLocalAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2WheelJoint.prototype['SetMotorSpeed'] = function(arg0) {
    _emscripten_bind_b2WheelJoint__SetMotorSpeed_p1(this.ptr, arg0);
}

b2WheelJoint.prototype['GetLocalAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2WheelJoint__GetLocalAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2WheelJoint.prototype['GetMotorSpeed'] = function() {
    return _emscripten_bind_b2WheelJoint__GetMotorSpeed_p0(this.ptr);
}

b2WheelJoint.prototype['GetMotorTorque'] = function(arg0) {
    return _emscripten_bind_b2WheelJoint__GetMotorTorque_p1(this.ptr, arg0);
}

function b2WheelJoint(arg0) {
    this.ptr = _emscripten_bind_b2WheelJoint__b2WheelJoint_p1(arg0.ptr);
  b2WheelJoint.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2WheelJoint;
}
b2WheelJoint.prototype.__cache__ = {};
Module['b2WheelJoint'] = b2WheelJoint;

b2WheelJoint.prototype['IsMotorEnabled'] = function() {
    return _emscripten_bind_b2WheelJoint__IsMotorEnabled_p0(this.ptr);
}

b2WheelJoint.prototype['GetJointTranslation'] = function() {
    return _emscripten_bind_b2WheelJoint__GetJointTranslation_p0(this.ptr);
}

b2WheelJoint.prototype['SetUserData'] = function(arg0) {
    _emscripten_bind_b2WheelJoint__SetUserData_p1(this.ptr, arg0);
}

b2WheelJoint.prototype['GetReactionForce'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2WheelJoint__GetReactionForce_p1(this.ptr, arg0), Module['b2Vec2']);
}

b2WheelJoint.prototype['GetSpringDampingRatio'] = function() {
    return _emscripten_bind_b2WheelJoint__GetSpringDampingRatio_p0(this.ptr);
}

b2WheelJoint.prototype['SetMaxMotorTorque'] = function(arg0) {
    _emscripten_bind_b2WheelJoint__SetMaxMotorTorque_p1(this.ptr, arg0);
}

b2WheelJoint.prototype['GetCollideConnected'] = function() {
    return _emscripten_bind_b2WheelJoint__GetCollideConnected_p0(this.ptr);
}

b2WheelJoint.prototype['GetJointSpeed'] = function() {
    return _emscripten_bind_b2WheelJoint__GetJointSpeed_p0(this.ptr);
}

b2WheelJoint.prototype['EnableMotor'] = function(arg0) {
    _emscripten_bind_b2WheelJoint__EnableMotor_p1(this.ptr, arg0);
}

b2WheelJoint.prototype['__destroy__'] = function() {
    _emscripten_bind_b2WheelJoint____destroy___p0(this.ptr);
}

b2WheelJoint.prototype['Dump'] = function() {
    _emscripten_bind_b2WheelJoint__Dump_p0(this.ptr);
}

b2WheelJoint.prototype['GetMaxMotorTorque'] = function() {
    return _emscripten_bind_b2WheelJoint__GetMaxMotorTorque_p0(this.ptr);
}

b2WheelJoint.prototype['GetType'] = function() {
    return _emscripten_bind_b2WheelJoint__GetType_p0(this.ptr);
}

b2WheelJoint.prototype['GetReactionTorque'] = function(arg0) {
    return _emscripten_bind_b2WheelJoint__GetReactionTorque_p1(this.ptr, arg0);
}

b2WheelJoint.prototype['SetSpringFrequencyHz'] = function(arg0) {
    _emscripten_bind_b2WheelJoint__SetSpringFrequencyHz_p1(this.ptr, arg0);
}

b2WheelJoint.prototype['IsActive'] = function() {
    return _emscripten_bind_b2WheelJoint__IsActive_p0(this.ptr);
}

b2Draw.prototype['__destroy__'] = function() {
    _emscripten_bind_b2Draw____destroy___p0(this.ptr);
}

b2Draw.prototype['AppendFlags'] = function(arg0) {
    _emscripten_bind_b2Draw__AppendFlags_p1(this.ptr, arg0);
}

b2Draw.prototype['DrawTransform'] = function(arg0) {
    _emscripten_bind_b2Draw__DrawTransform_p1(this.ptr, arg0.ptr);
}

b2Draw.prototype['ClearFlags'] = function(arg0) {
    _emscripten_bind_b2Draw__ClearFlags_p1(this.ptr, arg0);
}

b2Draw.prototype['DrawPolygon'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2Draw__DrawPolygon_p3(this.ptr, arg0.ptr, arg1, arg2.ptr);
}

b2Draw.prototype['DrawSolidCircle'] = function(arg0, arg1, arg2, arg3) {
    _emscripten_bind_b2Draw__DrawSolidCircle_p4(this.ptr, arg0.ptr, arg1, arg2.ptr, arg3.ptr);
}

b2Draw.prototype['DrawSolidPolygon'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2Draw__DrawSolidPolygon_p3(this.ptr, arg0.ptr, arg1, arg2.ptr);
}

b2Draw.prototype['DrawCircle'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2Draw__DrawCircle_p3(this.ptr, arg0.ptr, arg1, arg2.ptr);
}

b2Draw.prototype['SetFlags'] = function(arg0) {
    _emscripten_bind_b2Draw__SetFlags_p1(this.ptr, arg0);
}

b2Draw.prototype['DrawSegment'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2Draw__DrawSegment_p3(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr);
}

function b2Draw() {
    this.ptr = _emscripten_bind_b2Draw__b2Draw_p0();
  b2Draw.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2Draw;
}
b2Draw.prototype.__cache__ = {};
Module['b2Draw'] = b2Draw;

b2Draw.prototype['GetFlags'] = function() {
    return _emscripten_bind_b2Draw__GetFlags_p0(this.ptr);
}

function b2Joint(){ throw "b2Joint is abstract!" }
b2Joint.prototype.__cache__ = {};
Module['b2Joint'] = b2Joint;

b2Joint.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2Joint__GetNext_p0(this.ptr), Module['b2Joint']);
}

b2Joint.prototype['GetBodyA'] = function() {
    return wrapPointer(_emscripten_bind_b2Joint__GetBodyA_p0(this.ptr), Module['b2Body']);
}

b2Joint.prototype['GetBodyB'] = function() {
    return wrapPointer(_emscripten_bind_b2Joint__GetBodyB_p0(this.ptr), Module['b2Body']);
}

b2Joint.prototype['GetReactionTorque'] = function(arg0) {
    return _emscripten_bind_b2Joint__GetReactionTorque_p1(this.ptr, arg0);
}

b2Joint.prototype['GetAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2Joint__GetAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2Joint.prototype['GetUserData'] = function() {
    return _emscripten_bind_b2Joint__GetUserData_p0(this.ptr);
}

b2Joint.prototype['GetType'] = function() {
    return _emscripten_bind_b2Joint__GetType_p0(this.ptr);
}

b2Joint.prototype['SetUserData'] = function(arg0) {
    _emscripten_bind_b2Joint__SetUserData_p1(this.ptr, arg0);
}

b2Joint.prototype['GetCollideConnected'] = function() {
    return _emscripten_bind_b2Joint__GetCollideConnected_p0(this.ptr);
}

b2Joint.prototype['Dump'] = function() {
    _emscripten_bind_b2Joint__Dump_p0(this.ptr);
}

b2Joint.prototype['GetAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2Joint__GetAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2Joint.prototype['GetReactionForce'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2Joint__GetReactionForce_p1(this.ptr, arg0), Module['b2Vec2']);
}

b2Joint.prototype['IsActive'] = function() {
    return _emscripten_bind_b2Joint__IsActive_p0(this.ptr);
}

b2GearJoint.prototype['GetJoint1'] = function() {
    return wrapPointer(_emscripten_bind_b2GearJoint__GetJoint1_p0(this.ptr), Module['b2Joint']);
}

function b2GearJoint(arg0) {
    this.ptr = _emscripten_bind_b2GearJoint__b2GearJoint_p1(arg0.ptr);
  b2GearJoint.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2GearJoint;
}
b2GearJoint.prototype.__cache__ = {};
Module['b2GearJoint'] = b2GearJoint;

b2GearJoint.prototype['GetAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2GearJoint__GetAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2GearJoint.prototype['GetJoint2'] = function() {
    return wrapPointer(_emscripten_bind_b2GearJoint__GetJoint2_p0(this.ptr), Module['b2Joint']);
}

b2GearJoint.prototype['GetReactionTorque'] = function(arg0) {
    return _emscripten_bind_b2GearJoint__GetReactionTorque_p1(this.ptr, arg0);
}

b2GearJoint.prototype['Dump'] = function() {
    _emscripten_bind_b2GearJoint__Dump_p0(this.ptr);
}

b2GearJoint.prototype['__destroy__'] = function() {
    _emscripten_bind_b2GearJoint____destroy___p0(this.ptr);
}

b2GearJoint.prototype['SetRatio'] = function(arg0) {
    _emscripten_bind_b2GearJoint__SetRatio_p1(this.ptr, arg0);
}

b2GearJoint.prototype['GetType'] = function() {
    return _emscripten_bind_b2GearJoint__GetType_p0(this.ptr);
}

b2GearJoint.prototype['GetUserData'] = function() {
    return _emscripten_bind_b2GearJoint__GetUserData_p0(this.ptr);
}

b2GearJoint.prototype['GetBodyB'] = function() {
    return wrapPointer(_emscripten_bind_b2GearJoint__GetBodyB_p0(this.ptr), Module['b2Body']);
}

b2GearJoint.prototype['GetCollideConnected'] = function() {
    return _emscripten_bind_b2GearJoint__GetCollideConnected_p0(this.ptr);
}

b2GearJoint.prototype['SetUserData'] = function(arg0) {
    _emscripten_bind_b2GearJoint__SetUserData_p1(this.ptr, arg0);
}

b2GearJoint.prototype['GetAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2GearJoint__GetAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2GearJoint.prototype['GetReactionForce'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2GearJoint__GetReactionForce_p1(this.ptr, arg0), Module['b2Vec2']);
}

b2GearJoint.prototype['GetBodyA'] = function() {
    return wrapPointer(_emscripten_bind_b2GearJoint__GetBodyA_p0(this.ptr), Module['b2Body']);
}

b2GearJoint.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2GearJoint__GetNext_p0(this.ptr), Module['b2Joint']);
}

b2GearJoint.prototype['IsActive'] = function() {
    return _emscripten_bind_b2GearJoint__IsActive_p0(this.ptr);
}

b2GearJoint.prototype['GetRatio'] = function() {
    return _emscripten_bind_b2GearJoint__GetRatio_p0(this.ptr);
}

b2RayCastCallback.prototype['ReportFixture'] = function(arg0, arg1, arg2, arg3) {
    return _emscripten_bind_b2RayCastCallback__ReportFixture_p4(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr, arg3);
}

function b2RayCastCallback() {
    this.ptr = _emscripten_bind_b2RayCastCallback__b2RayCastCallback_p0();
  b2RayCastCallback.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2RayCastCallback;
}
b2RayCastCallback.prototype.__cache__ = {};
Module['b2RayCastCallback'] = b2RayCastCallback;

b2RayCastCallback.prototype['__destroy__'] = function() {
    _emscripten_bind_b2RayCastCallback____destroy___p0(this.ptr);
}

b2DynamicTree.prototype['__destroy__'] = function() {
    _emscripten_bind_b2DynamicTree____destroy___p0(this.ptr);
}

function b2DynamicTree() {
    this.ptr = _emscripten_bind_b2DynamicTree__b2DynamicTree_p0();
  b2DynamicTree.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2DynamicTree;
}
b2DynamicTree.prototype.__cache__ = {};
Module['b2DynamicTree'] = b2DynamicTree;

b2DynamicTree.prototype['GetFatAABB'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2DynamicTree__GetFatAABB_p1(this.ptr, arg0), Module['b2AABB']);
}

b2DynamicTree.prototype['GetUserData'] = function(arg0) {
    return _emscripten_bind_b2DynamicTree__GetUserData_p1(this.ptr, arg0);
}

b2DynamicTree.prototype['GetMaxBalance'] = function() {
    return _emscripten_bind_b2DynamicTree__GetMaxBalance_p0(this.ptr);
}

b2DynamicTree.prototype['GetHeight'] = function() {
    return _emscripten_bind_b2DynamicTree__GetHeight_p0(this.ptr);
}

b2DynamicTree.prototype['GetAreaRatio'] = function() {
    return _emscripten_bind_b2DynamicTree__GetAreaRatio_p0(this.ptr);
}

b2DynamicTree.prototype['RebuildBottomUp'] = function() {
    _emscripten_bind_b2DynamicTree__RebuildBottomUp_p0(this.ptr);
}

b2DynamicTree.prototype['CreateProxy'] = function(arg0, arg1) {
    return _emscripten_bind_b2DynamicTree__CreateProxy_p2(this.ptr, arg0.ptr, arg1);
}

b2DynamicTree.prototype['MoveProxy'] = function(arg0, arg1, arg2) {
    return _emscripten_bind_b2DynamicTree__MoveProxy_p3(this.ptr, arg0, arg1.ptr, arg2.ptr);
}

b2DynamicTree.prototype['Validate'] = function() {
    _emscripten_bind_b2DynamicTree__Validate_p0(this.ptr);
}

b2DynamicTree.prototype['DestroyProxy'] = function(arg0) {
    _emscripten_bind_b2DynamicTree__DestroyProxy_p1(this.ptr, arg0);
}

b2WeldJoint.prototype['GetBodyA'] = function() {
    return wrapPointer(_emscripten_bind_b2WeldJoint__GetBodyA_p0(this.ptr), Module['b2Body']);
}

b2WeldJoint.prototype['GetBodyB'] = function() {
    return wrapPointer(_emscripten_bind_b2WeldJoint__GetBodyB_p0(this.ptr), Module['b2Body']);
}

b2WeldJoint.prototype['SetFrequency'] = function(arg0) {
    _emscripten_bind_b2WeldJoint__SetFrequency_p1(this.ptr, arg0);
}

b2WeldJoint.prototype['GetUserData'] = function() {
    return _emscripten_bind_b2WeldJoint__GetUserData_p0(this.ptr);
}

b2WeldJoint.prototype['SetUserData'] = function(arg0) {
    _emscripten_bind_b2WeldJoint__SetUserData_p1(this.ptr, arg0);
}

b2WeldJoint.prototype['GetAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2WeldJoint__GetAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2WeldJoint.prototype['GetAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2WeldJoint__GetAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2WeldJoint.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2WeldJoint__GetNext_p0(this.ptr), Module['b2Joint']);
}

b2WeldJoint.prototype['GetLocalAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2WeldJoint__GetLocalAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2WeldJoint.prototype['GetLocalAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2WeldJoint__GetLocalAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2WeldJoint.prototype['GetFrequency'] = function() {
    return _emscripten_bind_b2WeldJoint__GetFrequency_p0(this.ptr);
}

function b2WeldJoint(arg0) {
    this.ptr = _emscripten_bind_b2WeldJoint__b2WeldJoint_p1(arg0.ptr);
  b2WeldJoint.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2WeldJoint;
}
b2WeldJoint.prototype.__cache__ = {};
Module['b2WeldJoint'] = b2WeldJoint;

b2WeldJoint.prototype['GetReactionForce'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2WeldJoint__GetReactionForce_p1(this.ptr, arg0), Module['b2Vec2']);
}

b2WeldJoint.prototype['GetDampingRatio'] = function() {
    return _emscripten_bind_b2WeldJoint__GetDampingRatio_p0(this.ptr);
}

b2WeldJoint.prototype['GetCollideConnected'] = function() {
    return _emscripten_bind_b2WeldJoint__GetCollideConnected_p0(this.ptr);
}

b2WeldJoint.prototype['__destroy__'] = function() {
    _emscripten_bind_b2WeldJoint____destroy___p0(this.ptr);
}

b2WeldJoint.prototype['GetReferenceAngle'] = function() {
    return _emscripten_bind_b2WeldJoint__GetReferenceAngle_p0(this.ptr);
}

b2WeldJoint.prototype['Dump'] = function() {
    _emscripten_bind_b2WeldJoint__Dump_p0(this.ptr);
}

b2WeldJoint.prototype['GetType'] = function() {
    return _emscripten_bind_b2WeldJoint__GetType_p0(this.ptr);
}

b2WeldJoint.prototype['SetDampingRatio'] = function(arg0) {
    _emscripten_bind_b2WeldJoint__SetDampingRatio_p1(this.ptr, arg0);
}

b2WeldJoint.prototype['GetReactionTorque'] = function(arg0) {
    return _emscripten_bind_b2WeldJoint__GetReactionTorque_p1(this.ptr, arg0);
}

b2WeldJoint.prototype['IsActive'] = function() {
    return _emscripten_bind_b2WeldJoint__IsActive_p0(this.ptr);
}

b2RevoluteJoint.prototype['GetBodyA'] = function() {
    return wrapPointer(_emscripten_bind_b2RevoluteJoint__GetBodyA_p0(this.ptr), Module['b2Body']);
}

b2RevoluteJoint.prototype['GetBodyB'] = function() {
    return wrapPointer(_emscripten_bind_b2RevoluteJoint__GetBodyB_p0(this.ptr), Module['b2Body']);
}

b2RevoluteJoint.prototype['GetUserData'] = function() {
    return _emscripten_bind_b2RevoluteJoint__GetUserData_p0(this.ptr);
}

b2RevoluteJoint.prototype['GetLowerLimit'] = function() {
    return _emscripten_bind_b2RevoluteJoint__GetLowerLimit_p0(this.ptr);
}

b2RevoluteJoint.prototype['GetAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2RevoluteJoint__GetAnchorA_p0(this.ptr), Module['b2Vec2']);
}

function b2RevoluteJoint(arg0) {
    this.ptr = _emscripten_bind_b2RevoluteJoint__b2RevoluteJoint_p1(arg0.ptr);
  b2RevoluteJoint.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2RevoluteJoint;
}
b2RevoluteJoint.prototype.__cache__ = {};
Module['b2RevoluteJoint'] = b2RevoluteJoint;

b2RevoluteJoint.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2RevoluteJoint__GetNext_p0(this.ptr), Module['b2Joint']);
}

b2RevoluteJoint.prototype['GetLocalAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2RevoluteJoint__GetLocalAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2RevoluteJoint.prototype['SetMotorSpeed'] = function(arg0) {
    _emscripten_bind_b2RevoluteJoint__SetMotorSpeed_p1(this.ptr, arg0);
}

b2RevoluteJoint.prototype['GetLocalAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2RevoluteJoint__GetLocalAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2RevoluteJoint.prototype['GetJointAngle'] = function() {
    return _emscripten_bind_b2RevoluteJoint__GetJointAngle_p0(this.ptr);
}

b2RevoluteJoint.prototype['GetMotorSpeed'] = function() {
    return _emscripten_bind_b2RevoluteJoint__GetMotorSpeed_p0(this.ptr);
}

b2RevoluteJoint.prototype['GetMotorTorque'] = function(arg0) {
    return _emscripten_bind_b2RevoluteJoint__GetMotorTorque_p1(this.ptr, arg0);
}

b2RevoluteJoint.prototype['IsLimitEnabled'] = function() {
    return _emscripten_bind_b2RevoluteJoint__IsLimitEnabled_p0(this.ptr);
}

b2RevoluteJoint.prototype['EnableLimit'] = function(arg0) {
    _emscripten_bind_b2RevoluteJoint__EnableLimit_p1(this.ptr, arg0);
}

b2RevoluteJoint.prototype['IsMotorEnabled'] = function() {
    return _emscripten_bind_b2RevoluteJoint__IsMotorEnabled_p0(this.ptr);
}

b2RevoluteJoint.prototype['SetUserData'] = function(arg0) {
    _emscripten_bind_b2RevoluteJoint__SetUserData_p1(this.ptr, arg0);
}

b2RevoluteJoint.prototype['GetReactionForce'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2RevoluteJoint__GetReactionForce_p1(this.ptr, arg0), Module['b2Vec2']);
}

b2RevoluteJoint.prototype['SetMaxMotorTorque'] = function(arg0) {
    _emscripten_bind_b2RevoluteJoint__SetMaxMotorTorque_p1(this.ptr, arg0);
}

b2RevoluteJoint.prototype['GetCollideConnected'] = function() {
    return _emscripten_bind_b2RevoluteJoint__GetCollideConnected_p0(this.ptr);
}

b2RevoluteJoint.prototype['GetJointSpeed'] = function() {
    return _emscripten_bind_b2RevoluteJoint__GetJointSpeed_p0(this.ptr);
}

b2RevoluteJoint.prototype['EnableMotor'] = function(arg0) {
    _emscripten_bind_b2RevoluteJoint__EnableMotor_p1(this.ptr, arg0);
}

b2RevoluteJoint.prototype['__destroy__'] = function() {
    _emscripten_bind_b2RevoluteJoint____destroy___p0(this.ptr);
}

b2RevoluteJoint.prototype['GetReferenceAngle'] = function() {
    return _emscripten_bind_b2RevoluteJoint__GetReferenceAngle_p0(this.ptr);
}

b2RevoluteJoint.prototype['Dump'] = function() {
    _emscripten_bind_b2RevoluteJoint__Dump_p0(this.ptr);
}

b2RevoluteJoint.prototype['SetLimits'] = function(arg0, arg1) {
    _emscripten_bind_b2RevoluteJoint__SetLimits_p2(this.ptr, arg0, arg1);
}

b2RevoluteJoint.prototype['GetMaxMotorTorque'] = function() {
    return _emscripten_bind_b2RevoluteJoint__GetMaxMotorTorque_p0(this.ptr);
}

b2RevoluteJoint.prototype['GetType'] = function() {
    return _emscripten_bind_b2RevoluteJoint__GetType_p0(this.ptr);
}

b2RevoluteJoint.prototype['GetReactionTorque'] = function(arg0) {
    return _emscripten_bind_b2RevoluteJoint__GetReactionTorque_p1(this.ptr, arg0);
}

b2RevoluteJoint.prototype['GetUpperLimit'] = function() {
    return _emscripten_bind_b2RevoluteJoint__GetUpperLimit_p0(this.ptr);
}

b2RevoluteJoint.prototype['IsActive'] = function() {
    return _emscripten_bind_b2RevoluteJoint__IsActive_p0(this.ptr);
}

b2RevoluteJoint.prototype['GetAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2RevoluteJoint__GetAnchorB_p0(this.ptr), Module['b2Vec2']);
}

function b2Timer() {
    this.ptr = _emscripten_bind_b2Timer__b2Timer_p0();
  b2Timer.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2Timer;
}
b2Timer.prototype.__cache__ = {};
Module['b2Timer'] = b2Timer;

b2Timer.prototype['Reset'] = function() {
    _emscripten_bind_b2Timer__Reset_p0(this.ptr);
}

b2Timer.prototype['__destroy__'] = function() {
    _emscripten_bind_b2Timer____destroy___p0(this.ptr);
}

b2Timer.prototype['GetMilliseconds'] = function() {
    return _emscripten_bind_b2Timer__GetMilliseconds_p0(this.ptr);
}

b2ContactListener.prototype['__destroy__'] = function() {
    _emscripten_bind_b2ContactListener____destroy___p0(this.ptr);
}

function b2ContactListener() {
    this.ptr = _emscripten_bind_b2ContactListener__b2ContactListener_p0();
  b2ContactListener.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2ContactListener;
}
b2ContactListener.prototype.__cache__ = {};
Module['b2ContactListener'] = b2ContactListener;

b2ContactListener.prototype['EndContact'] = function(arg0) {
    _emscripten_bind_b2ContactListener__EndContact_p1(this.ptr, arg0.ptr);
}

b2ContactListener.prototype['BeginContact'] = function(arg0) {
    _emscripten_bind_b2ContactListener__BeginContact_p1(this.ptr, arg0.ptr);
}

b2ContactListener.prototype['PreSolve'] = function(arg0, arg1) {
    _emscripten_bind_b2ContactListener__PreSolve_p2(this.ptr, arg0.ptr, arg1.ptr);
}

b2ContactListener.prototype['PostSolve'] = function(arg0, arg1) {
    _emscripten_bind_b2ContactListener__PostSolve_p2(this.ptr, arg0.ptr, arg1.ptr);
}

b2ChainShape.prototype['__destroy__'] = function() {
    _emscripten_bind_b2ChainShape____destroy___p0(this.ptr);
}

b2ChainShape.prototype['GetType'] = function() {
    return _emscripten_bind_b2ChainShape__GetType_p0(this.ptr);
}

b2ChainShape.prototype['CreateChain'] = function(arg0, arg1) {
    _emscripten_bind_b2ChainShape__CreateChain_p2(this.ptr, arg0.ptr, arg1);
}

b2ChainShape.prototype['set_m_radius'] = function(arg0) {
    _emscripten_bind_b2ChainShape__set_m_radius_p1(this.ptr, arg0);
}

b2ChainShape.prototype['get_m_radius'] = function() {
    return _emscripten_bind_b2ChainShape__get_m_radius_p0(this.ptr);
}

b2ChainShape.prototype['get_m_vertices'] = function() {
    return wrapPointer(_emscripten_bind_b2ChainShape__get_m_vertices_p0(this.ptr), Module['b2Vec2']);
}

b2ChainShape.prototype['ComputeMass'] = function(arg0, arg1) {
    _emscripten_bind_b2ChainShape__ComputeMass_p2(this.ptr, arg0.ptr, arg1);
}

b2ChainShape.prototype['Clone'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2ChainShape__Clone_p1(this.ptr, arg0.ptr), Module['b2Shape']);
}

b2ChainShape.prototype['get_m_count'] = function() {
    return _emscripten_bind_b2ChainShape__get_m_count_p0(this.ptr);
}

b2ChainShape.prototype['GetChildEdge'] = function(arg0, arg1) {
    _emscripten_bind_b2ChainShape__GetChildEdge_p2(this.ptr, arg0.ptr, arg1);
}

function b2ChainShape() {
    this.ptr = _emscripten_bind_b2ChainShape__b2ChainShape_p0();
  b2ChainShape.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2ChainShape;
}
b2ChainShape.prototype.__cache__ = {};
Module['b2ChainShape'] = b2ChainShape;

b2ChainShape.prototype['ComputeAABB'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2ChainShape__ComputeAABB_p3(this.ptr, arg0.ptr, arg1.ptr, arg2);
}

b2ChainShape.prototype['RayCast'] = function(arg0, arg1, arg2, arg3) {
    return _emscripten_bind_b2ChainShape__RayCast_p4(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr, arg3);
}

b2ChainShape.prototype['GetChildCount'] = function() {
    return _emscripten_bind_b2ChainShape__GetChildCount_p0(this.ptr);
}

b2ChainShape.prototype['TestPoint'] = function(arg0, arg1) {
    return _emscripten_bind_b2ChainShape__TestPoint_p2(this.ptr, arg0.ptr, arg1.ptr);
}

b2ChainShape.prototype['SetPrevVertex'] = function(arg0) {
    _emscripten_bind_b2ChainShape__SetPrevVertex_p1(this.ptr, arg0.ptr);
}

b2ChainShape.prototype['CreateLoop'] = function(arg0, arg1) {
    _emscripten_bind_b2ChainShape__CreateLoop_p2(this.ptr, arg0.ptr, arg1);
}

b2ChainShape.prototype['set_m_vertices'] = function(arg0) {
    _emscripten_bind_b2ChainShape__set_m_vertices_p1(this.ptr, arg0.ptr);
}

b2ChainShape.prototype['SetNextVertex'] = function(arg0) {
    _emscripten_bind_b2ChainShape__SetNextVertex_p1(this.ptr, arg0.ptr);
}

b2ChainShape.prototype['set_m_count'] = function(arg0) {
    _emscripten_bind_b2ChainShape__set_m_count_p1(this.ptr, arg0);
}

b2QueryCallback.prototype['ReportFixture'] = function(arg0) {
    return _emscripten_bind_b2QueryCallback__ReportFixture_p1(this.ptr, arg0.ptr);
}

b2QueryCallback.prototype['__destroy__'] = function() {
    _emscripten_bind_b2QueryCallback____destroy___p0(this.ptr);
}

function b2QueryCallback() {
    this.ptr = _emscripten_bind_b2QueryCallback__b2QueryCallback_p0();
  b2QueryCallback.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2QueryCallback;
}
b2QueryCallback.prototype.__cache__ = {};
Module['b2QueryCallback'] = b2QueryCallback;

b2BlockAllocator.prototype['__destroy__'] = function() {
    _emscripten_bind_b2BlockAllocator____destroy___p0(this.ptr);
}

b2BlockAllocator.prototype['Clear'] = function() {
    _emscripten_bind_b2BlockAllocator__Clear_p0(this.ptr);
}

b2BlockAllocator.prototype['Free'] = function(arg0, arg1) {
    _emscripten_bind_b2BlockAllocator__Free_p2(this.ptr, arg0, arg1);
}

b2BlockAllocator.prototype['Allocate'] = function(arg0) {
    return _emscripten_bind_b2BlockAllocator__Allocate_p1(this.ptr, arg0);
}

function b2BlockAllocator() {
    this.ptr = _emscripten_bind_b2BlockAllocator__b2BlockAllocator_p0();
  b2BlockAllocator.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2BlockAllocator;
}
b2BlockAllocator.prototype.__cache__ = {};
Module['b2BlockAllocator'] = b2BlockAllocator;

b2RopeJoint.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2RopeJoint__GetNext_p0(this.ptr), Module['b2Joint']);
}

b2RopeJoint.prototype['__destroy__'] = function() {
    _emscripten_bind_b2RopeJoint____destroy___p0(this.ptr);
}

b2RopeJoint.prototype['GetAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2RopeJoint__GetAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2RopeJoint.prototype['GetReactionTorque'] = function(arg0) {
    return _emscripten_bind_b2RopeJoint__GetReactionTorque_p1(this.ptr, arg0);
}

b2RopeJoint.prototype['GetMaxLength'] = function() {
    return _emscripten_bind_b2RopeJoint__GetMaxLength_p0(this.ptr);
}

b2RopeJoint.prototype['GetBodyA'] = function() {
    return wrapPointer(_emscripten_bind_b2RopeJoint__GetBodyA_p0(this.ptr), Module['b2Body']);
}

b2RopeJoint.prototype['GetCollideConnected'] = function() {
    return _emscripten_bind_b2RopeJoint__GetCollideConnected_p0(this.ptr);
}

b2RopeJoint.prototype['GetUserData'] = function() {
    return _emscripten_bind_b2RopeJoint__GetUserData_p0(this.ptr);
}

b2RopeJoint.prototype['GetType'] = function() {
    return _emscripten_bind_b2RopeJoint__GetType_p0(this.ptr);
}

b2RopeJoint.prototype['GetBodyB'] = function() {
    return wrapPointer(_emscripten_bind_b2RopeJoint__GetBodyB_p0(this.ptr), Module['b2Body']);
}

b2RopeJoint.prototype['GetLocalAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2RopeJoint__GetLocalAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2RopeJoint.prototype['Dump'] = function() {
    _emscripten_bind_b2RopeJoint__Dump_p0(this.ptr);
}

b2RopeJoint.prototype['SetMaxLength'] = function(arg0) {
    _emscripten_bind_b2RopeJoint__SetMaxLength_p1(this.ptr, arg0);
}

b2RopeJoint.prototype['GetLocalAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2RopeJoint__GetLocalAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2RopeJoint.prototype['SetUserData'] = function(arg0) {
    _emscripten_bind_b2RopeJoint__SetUserData_p1(this.ptr, arg0);
}

b2RopeJoint.prototype['GetAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2RopeJoint__GetAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2RopeJoint.prototype['GetReactionForce'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2RopeJoint__GetReactionForce_p1(this.ptr, arg0), Module['b2Vec2']);
}

function b2RopeJoint(arg0) {
    this.ptr = _emscripten_bind_b2RopeJoint__b2RopeJoint_p1(arg0.ptr);
  b2RopeJoint.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2RopeJoint;
}
b2RopeJoint.prototype.__cache__ = {};
Module['b2RopeJoint'] = b2RopeJoint;

b2RopeJoint.prototype['GetLimitState'] = function() {
    return _emscripten_bind_b2RopeJoint__GetLimitState_p0(this.ptr);
}

b2RopeJoint.prototype['IsActive'] = function() {
    return _emscripten_bind_b2RopeJoint__IsActive_p0(this.ptr);
}

b2PolygonShape.prototype['__destroy__'] = function() {
    _emscripten_bind_b2PolygonShape____destroy___p0(this.ptr);
}

b2PolygonShape.prototype['Set'] = function(arg0, arg1) {
    _emscripten_bind_b2PolygonShape__Set_p2(this.ptr, arg0.ptr, arg1);
}

b2PolygonShape.prototype['ComputeMass'] = function(arg0, arg1) {
    _emscripten_bind_b2PolygonShape__ComputeMass_p2(this.ptr, arg0.ptr, arg1);
}

b2PolygonShape.prototype['set_m_radius'] = function(arg0) {
    _emscripten_bind_b2PolygonShape__set_m_radius_p1(this.ptr, arg0);
}

b2PolygonShape.prototype['get_m_radius'] = function() {
    return _emscripten_bind_b2PolygonShape__get_m_radius_p0(this.ptr);
}

b2PolygonShape.prototype['Clone'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2PolygonShape__Clone_p1(this.ptr, arg0.ptr), Module['b2Shape']);
}

b2PolygonShape.prototype['GetVertex'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2PolygonShape__GetVertex_p1(this.ptr, arg0), Module['b2Vec2']);
}

b2PolygonShape.prototype['RayCast'] = function(arg0, arg1, arg2, arg3) {
    return _emscripten_bind_b2PolygonShape__RayCast_p4(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr, arg3);
}

b2PolygonShape.prototype['SetAsBox'] = function(arg0, arg1, arg2, arg3) {
  if (arg2 === undefined)
    _emscripten_bind_b2PolygonShape__SetAsBox_p2(this.ptr, arg0, arg1);
  else 
    _emscripten_bind_b2PolygonShape__SetAsBox_p4(this.ptr, arg0, arg1, arg2.ptr, arg3);
}

b2PolygonShape.prototype['set_m_centroid'] = function(arg0) {
    _emscripten_bind_b2PolygonShape__set_m_centroid_p1(this.ptr, arg0.ptr);
}

b2PolygonShape.prototype['ComputeAABB'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2PolygonShape__ComputeAABB_p3(this.ptr, arg0.ptr, arg1.ptr, arg2);
}

b2PolygonShape.prototype['set_m_vertexCount'] = function(arg0) {
    _emscripten_bind_b2PolygonShape__set_m_vertexCount_p1(this.ptr, arg0);
}

b2PolygonShape.prototype['GetVertexCount'] = function() {
    return _emscripten_bind_b2PolygonShape__GetVertexCount_p0(this.ptr);
}

b2PolygonShape.prototype['GetChildCount'] = function() {
    return _emscripten_bind_b2PolygonShape__GetChildCount_p0(this.ptr);
}

b2PolygonShape.prototype['TestPoint'] = function(arg0, arg1) {
    return _emscripten_bind_b2PolygonShape__TestPoint_p2(this.ptr, arg0.ptr, arg1.ptr);
}

b2PolygonShape.prototype['GetType'] = function() {
    return _emscripten_bind_b2PolygonShape__GetType_p0(this.ptr);
}

function b2PolygonShape() {
    this.ptr = _emscripten_bind_b2PolygonShape__b2PolygonShape_p0();
  b2PolygonShape.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2PolygonShape;
}
b2PolygonShape.prototype.__cache__ = {};
Module['b2PolygonShape'] = b2PolygonShape;

b2PolygonShape.prototype['get_m_vertexCount'] = function() {
    return _emscripten_bind_b2PolygonShape__get_m_vertexCount_p0(this.ptr);
}

b2PolygonShape.prototype['get_m_centroid'] = function() {
    return wrapPointer(_emscripten_bind_b2PolygonShape__get_m_centroid_p0(this.ptr), Module['b2Vec2']);
}

b2EdgeShape.prototype['__destroy__'] = function() {
    _emscripten_bind_b2EdgeShape____destroy___p0(this.ptr);
}

b2EdgeShape.prototype['Set'] = function(arg0, arg1) {
    _emscripten_bind_b2EdgeShape__Set_p2(this.ptr, arg0.ptr, arg1.ptr);
}

b2EdgeShape.prototype['ComputeMass'] = function(arg0, arg1) {
    _emscripten_bind_b2EdgeShape__ComputeMass_p2(this.ptr, arg0.ptr, arg1);
}

b2EdgeShape.prototype['set_m_radius'] = function(arg0) {
    _emscripten_bind_b2EdgeShape__set_m_radius_p1(this.ptr, arg0);
}

b2EdgeShape.prototype['get_m_radius'] = function() {
    return _emscripten_bind_b2EdgeShape__get_m_radius_p0(this.ptr);
}

b2EdgeShape.prototype['Clone'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2EdgeShape__Clone_p1(this.ptr, arg0.ptr), Module['b2Shape']);
}

b2EdgeShape.prototype['GetType'] = function() {
    return _emscripten_bind_b2EdgeShape__GetType_p0(this.ptr);
}

b2EdgeShape.prototype['RayCast'] = function(arg0, arg1, arg2, arg3) {
    return _emscripten_bind_b2EdgeShape__RayCast_p4(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr, arg3);
}

b2EdgeShape.prototype['ComputeAABB'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2EdgeShape__ComputeAABB_p3(this.ptr, arg0.ptr, arg1.ptr, arg2);
}

b2EdgeShape.prototype['GetChildCount'] = function() {
    return _emscripten_bind_b2EdgeShape__GetChildCount_p0(this.ptr);
}

b2EdgeShape.prototype['TestPoint'] = function(arg0, arg1) {
    return _emscripten_bind_b2EdgeShape__TestPoint_p2(this.ptr, arg0.ptr, arg1.ptr);
}

function b2EdgeShape() {
    this.ptr = _emscripten_bind_b2EdgeShape__b2EdgeShape_p0();
  b2EdgeShape.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2EdgeShape;
}
b2EdgeShape.prototype.__cache__ = {};
Module['b2EdgeShape'] = b2EdgeShape;

function b2Contact(){ throw "b2Contact is abstract!" }
b2Contact.prototype.__cache__ = {};
Module['b2Contact'] = b2Contact;

b2Contact.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2Contact__GetNext_p0(this.ptr), Module['b2Contact']);
}

b2Contact.prototype['SetEnabled'] = function(arg0) {
    _emscripten_bind_b2Contact__SetEnabled_p1(this.ptr, arg0);
}

b2Contact.prototype['GetWorldManifold'] = function(arg0) {
    _emscripten_bind_b2Contact__GetWorldManifold_p1(this.ptr, arg0.ptr);
}

b2Contact.prototype['GetRestitution'] = function() {
    return _emscripten_bind_b2Contact__GetRestitution_p0(this.ptr);
}

b2Contact.prototype['ResetFriction'] = function() {
    _emscripten_bind_b2Contact__ResetFriction_p0(this.ptr);
}

b2Contact.prototype['GetFriction'] = function() {
    return _emscripten_bind_b2Contact__GetFriction_p0(this.ptr);
}

b2Contact.prototype['IsTouching'] = function() {
    return _emscripten_bind_b2Contact__IsTouching_p0(this.ptr);
}

b2Contact.prototype['IsEnabled'] = function() {
    return _emscripten_bind_b2Contact__IsEnabled_p0(this.ptr);
}

b2Contact.prototype['GetFixtureB'] = function() {
    return wrapPointer(_emscripten_bind_b2Contact__GetFixtureB_p0(this.ptr), Module['b2Fixture']);
}

b2Contact.prototype['SetFriction'] = function(arg0) {
    _emscripten_bind_b2Contact__SetFriction_p1(this.ptr, arg0);
}

b2Contact.prototype['GetFixtureA'] = function() {
    return wrapPointer(_emscripten_bind_b2Contact__GetFixtureA_p0(this.ptr), Module['b2Fixture']);
}

b2Contact.prototype['GetChildIndexA'] = function() {
    return _emscripten_bind_b2Contact__GetChildIndexA_p0(this.ptr);
}

b2Contact.prototype['GetChildIndexB'] = function() {
    return _emscripten_bind_b2Contact__GetChildIndexB_p0(this.ptr);
}

b2Contact.prototype['Evaluate'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2Contact__Evaluate_p3(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr);
}

b2Contact.prototype['SetRestitution'] = function(arg0) {
    _emscripten_bind_b2Contact__SetRestitution_p1(this.ptr, arg0);
}

b2Contact.prototype['GetManifold'] = function() {
    return wrapPointer(_emscripten_bind_b2Contact__GetManifold_p0(this.ptr), Module['b2Manifold']);
}

b2Contact.prototype['ResetRestitution'] = function() {
    _emscripten_bind_b2Contact__ResetRestitution_p0(this.ptr);
}

function b2Shape(){ throw "b2Shape is abstract!" }
b2Shape.prototype.__cache__ = {};
Module['b2Shape'] = b2Shape;

b2Shape.prototype['get_m_radius'] = function() {
    return _emscripten_bind_b2Shape__get_m_radius_p0(this.ptr);
}

b2Shape.prototype['ComputeMass'] = function(arg0, arg1) {
    _emscripten_bind_b2Shape__ComputeMass_p2(this.ptr, arg0.ptr, arg1);
}

b2Shape.prototype['set_m_radius'] = function(arg0) {
    _emscripten_bind_b2Shape__set_m_radius_p1(this.ptr, arg0);
}

b2Shape.prototype['Clone'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2Shape__Clone_p1(this.ptr, arg0.ptr), Module['b2Shape']);
}

b2Shape.prototype['GetType'] = function() {
    return _emscripten_bind_b2Shape__GetType_p0(this.ptr);
}

b2Shape.prototype['RayCast'] = function(arg0, arg1, arg2, arg3) {
    return _emscripten_bind_b2Shape__RayCast_p4(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr, arg3);
}

b2Shape.prototype['ComputeAABB'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2Shape__ComputeAABB_p3(this.ptr, arg0.ptr, arg1.ptr, arg2);
}

b2Shape.prototype['GetChildCount'] = function() {
    return _emscripten_bind_b2Shape__GetChildCount_p0(this.ptr);
}

b2Shape.prototype['TestPoint'] = function(arg0, arg1) {
    return _emscripten_bind_b2Shape__TestPoint_p2(this.ptr, arg0.ptr, arg1.ptr);
}

function b2Body(){ throw "b2Body is abstract!" }
b2Body.prototype.__cache__ = {};
Module['b2Body'] = b2Body;

b2Body.prototype['GetAngle'] = function() {
    return _emscripten_bind_b2Body__GetAngle_p0(this.ptr);
}

b2Body.prototype['GetUserData'] = function() {
    return _emscripten_bind_b2Body__GetUserData_p0(this.ptr);
}

b2Body.prototype['IsSleepingAllowed'] = function() {
    return _emscripten_bind_b2Body__IsSleepingAllowed_p0(this.ptr);
}

b2Body.prototype['SetAngularDamping'] = function(arg0) {
    _emscripten_bind_b2Body__SetAngularDamping_p1(this.ptr, arg0);
}

b2Body.prototype['SetActive'] = function(arg0) {
    _emscripten_bind_b2Body__SetActive_p1(this.ptr, arg0);
}

b2Body.prototype['SetGravityScale'] = function(arg0) {
    _emscripten_bind_b2Body__SetGravityScale_p1(this.ptr, arg0);
}

b2Body.prototype['SetUserData'] = function(arg0) {
    _emscripten_bind_b2Body__SetUserData_p1(this.ptr, arg0);
}

b2Body.prototype['GetAngularVelocity'] = function() {
    return _emscripten_bind_b2Body__GetAngularVelocity_p0(this.ptr);
}

b2Body.prototype['GetFixtureList'] = function() {
    return wrapPointer(_emscripten_bind_b2Body__GetFixtureList_p0(this.ptr), Module['b2Fixture']);
}

b2Body.prototype['ApplyForce'] = function(arg0, arg1) {
    _emscripten_bind_b2Body__ApplyForce_p2(this.ptr, arg0.ptr, arg1.ptr);
}

b2Body.prototype['GetLocalPoint'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2Body__GetLocalPoint_p1(this.ptr, arg0.ptr), Module['b2Vec2']);
}

b2Body.prototype['SetLinearVelocity'] = function(arg0) {
    _emscripten_bind_b2Body__SetLinearVelocity_p1(this.ptr, arg0.ptr);
}

b2Body.prototype['GetJointList'] = function() {
    return wrapPointer(_emscripten_bind_b2Body__GetJointList_p0(this.ptr), Module['b2JointEdge']);
}

b2Body.prototype['GetLinearVelocity'] = function() {
    return wrapPointer(_emscripten_bind_b2Body__GetLinearVelocity_p0(this.ptr), Module['b2Vec2']);
}

b2Body.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2Body__GetNext_p0(this.ptr), Module['b2Body']);
}

b2Body.prototype['SetSleepingAllowed'] = function(arg0) {
    _emscripten_bind_b2Body__SetSleepingAllowed_p1(this.ptr, arg0);
}

b2Body.prototype['SetTransform'] = function(arg0, arg1) {
    _emscripten_bind_b2Body__SetTransform_p2(this.ptr, arg0.ptr, arg1);
}

b2Body.prototype['GetMass'] = function() {
    return _emscripten_bind_b2Body__GetMass_p0(this.ptr);
}

b2Body.prototype['SetAngularVelocity'] = function(arg0) {
    _emscripten_bind_b2Body__SetAngularVelocity_p1(this.ptr, arg0);
}

b2Body.prototype['GetMassData'] = function(arg0) {
    _emscripten_bind_b2Body__GetMassData_p1(this.ptr, arg0.ptr);
}

b2Body.prototype['GetLinearVelocityFromWorldPoint'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2Body__GetLinearVelocityFromWorldPoint_p1(this.ptr, arg0.ptr), Module['b2Vec2']);
}

b2Body.prototype['ResetMassData'] = function() {
    _emscripten_bind_b2Body__ResetMassData_p0(this.ptr);
}

b2Body.prototype['ApplyForceToCenter'] = function(arg0) {
    _emscripten_bind_b2Body__ApplyForceToCenter_p1(this.ptr, arg0.ptr);
}

b2Body.prototype['ApplyTorque'] = function(arg0) {
    _emscripten_bind_b2Body__ApplyTorque_p1(this.ptr, arg0);
}

b2Body.prototype['IsAwake'] = function() {
    return _emscripten_bind_b2Body__IsAwake_p0(this.ptr);
}

b2Body.prototype['SetType'] = function(arg0) {
    _emscripten_bind_b2Body__SetType_p1(this.ptr, arg0);
}

b2Body.prototype['CreateFixture'] = function(arg0, arg1) {
  if (arg1 === undefined)
    return wrapPointer(_emscripten_bind_b2Body__CreateFixture_p1(this.ptr, arg0.ptr), Module['b2Fixture']);
  else 
    return wrapPointer(_emscripten_bind_b2Body__CreateFixture_p2(this.ptr, arg0.ptr, arg1), Module['b2Fixture']);
}

b2Body.prototype['SetMassData'] = function(arg0) {
    _emscripten_bind_b2Body__SetMassData_p1(this.ptr, arg0.ptr);
}

b2Body.prototype['GetTransform'] = function() {
    return wrapPointer(_emscripten_bind_b2Body__GetTransform_p0(this.ptr), Module['b2Transform']);
}

b2Body.prototype['GetWorldCenter'] = function() {
    return wrapPointer(_emscripten_bind_b2Body__GetWorldCenter_p0(this.ptr), Module['b2Vec2']);
}

b2Body.prototype['GetAngularDamping'] = function() {
    return _emscripten_bind_b2Body__GetAngularDamping_p0(this.ptr);
}

b2Body.prototype['ApplyLinearImpulse'] = function(arg0, arg1) {
    _emscripten_bind_b2Body__ApplyLinearImpulse_p2(this.ptr, arg0.ptr, arg1.ptr);
}

b2Body.prototype['IsFixedRotation'] = function() {
    return _emscripten_bind_b2Body__IsFixedRotation_p0(this.ptr);
}

b2Body.prototype['GetLocalCenter'] = function() {
    return wrapPointer(_emscripten_bind_b2Body__GetLocalCenter_p0(this.ptr), Module['b2Vec2']);
}

b2Body.prototype['GetWorldVector'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2Body__GetWorldVector_p1(this.ptr, arg0.ptr), Module['b2Vec2']);
}

b2Body.prototype['GetLinearVelocityFromLocalPoint'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2Body__GetLinearVelocityFromLocalPoint_p1(this.ptr, arg0.ptr), Module['b2Vec2']);
}

b2Body.prototype['GetContactList'] = function() {
    return wrapPointer(_emscripten_bind_b2Body__GetContactList_p0(this.ptr), Module['b2ContactEdge']);
}

b2Body.prototype['GetWorldPoint'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2Body__GetWorldPoint_p1(this.ptr, arg0.ptr), Module['b2Vec2']);
}

b2Body.prototype['SetAwake'] = function(arg0) {
    _emscripten_bind_b2Body__SetAwake_p1(this.ptr, arg0);
}

b2Body.prototype['GetLinearDamping'] = function() {
    return _emscripten_bind_b2Body__GetLinearDamping_p0(this.ptr);
}

b2Body.prototype['IsBullet'] = function() {
    return _emscripten_bind_b2Body__IsBullet_p0(this.ptr);
}

b2Body.prototype['GetWorld'] = function() {
    return wrapPointer(_emscripten_bind_b2Body__GetWorld_p0(this.ptr), Module['b2World']);
}

b2Body.prototype['GetLocalVector'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2Body__GetLocalVector_p1(this.ptr, arg0.ptr), Module['b2Vec2']);
}

b2Body.prototype['SetLinearDamping'] = function(arg0) {
    _emscripten_bind_b2Body__SetLinearDamping_p1(this.ptr, arg0);
}

b2Body.prototype['Dump'] = function() {
    _emscripten_bind_b2Body__Dump_p0(this.ptr);
}

b2Body.prototype['SetBullet'] = function(arg0) {
    _emscripten_bind_b2Body__SetBullet_p1(this.ptr, arg0);
}

b2Body.prototype['GetType'] = function() {
    return _emscripten_bind_b2Body__GetType_p0(this.ptr);
}

b2Body.prototype['GetGravityScale'] = function() {
    return _emscripten_bind_b2Body__GetGravityScale_p0(this.ptr);
}

b2Body.prototype['DestroyFixture'] = function(arg0) {
    _emscripten_bind_b2Body__DestroyFixture_p1(this.ptr, arg0.ptr);
}

b2Body.prototype['GetInertia'] = function() {
    return _emscripten_bind_b2Body__GetInertia_p0(this.ptr);
}

b2Body.prototype['IsActive'] = function() {
    return _emscripten_bind_b2Body__IsActive_p0(this.ptr);
}

b2Body.prototype['SetFixedRotation'] = function(arg0) {
    _emscripten_bind_b2Body__SetFixedRotation_p1(this.ptr, arg0);
}

b2Body.prototype['ApplyAngularImpulse'] = function(arg0) {
    _emscripten_bind_b2Body__ApplyAngularImpulse_p1(this.ptr, arg0);
}

b2Body.prototype['GetPosition'] = function() {
    return wrapPointer(_emscripten_bind_b2Body__GetPosition_p0(this.ptr), Module['b2Vec2']);
}

b2FrictionJoint.prototype['SetMaxTorque'] = function(arg0) {
    _emscripten_bind_b2FrictionJoint__SetMaxTorque_p1(this.ptr, arg0);
}

b2FrictionJoint.prototype['GetMaxForce'] = function() {
    return _emscripten_bind_b2FrictionJoint__GetMaxForce_p0(this.ptr);
}

b2FrictionJoint.prototype['GetAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2FrictionJoint__GetAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2FrictionJoint.prototype['GetReactionTorque'] = function(arg0) {
    return _emscripten_bind_b2FrictionJoint__GetReactionTorque_p1(this.ptr, arg0);
}

b2FrictionJoint.prototype['Dump'] = function() {
    _emscripten_bind_b2FrictionJoint__Dump_p0(this.ptr);
}

b2FrictionJoint.prototype['__destroy__'] = function() {
    _emscripten_bind_b2FrictionJoint____destroy___p0(this.ptr);
}

b2FrictionJoint.prototype['GetCollideConnected'] = function() {
    return _emscripten_bind_b2FrictionJoint__GetCollideConnected_p0(this.ptr);
}

b2FrictionJoint.prototype['GetUserData'] = function() {
    return _emscripten_bind_b2FrictionJoint__GetUserData_p0(this.ptr);
}

b2FrictionJoint.prototype['GetType'] = function() {
    return _emscripten_bind_b2FrictionJoint__GetType_p0(this.ptr);
}

b2FrictionJoint.prototype['SetMaxForce'] = function(arg0) {
    _emscripten_bind_b2FrictionJoint__SetMaxForce_p1(this.ptr, arg0);
}

b2FrictionJoint.prototype['GetBodyB'] = function() {
    return wrapPointer(_emscripten_bind_b2FrictionJoint__GetBodyB_p0(this.ptr), Module['b2Body']);
}

b2FrictionJoint.prototype['GetLocalAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2FrictionJoint__GetLocalAnchorA_p0(this.ptr), Module['b2Vec2']);
}

function b2FrictionJoint(arg0) {
    this.ptr = _emscripten_bind_b2FrictionJoint__b2FrictionJoint_p1(arg0.ptr);
  b2FrictionJoint.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2FrictionJoint;
}
b2FrictionJoint.prototype.__cache__ = {};
Module['b2FrictionJoint'] = b2FrictionJoint;

b2FrictionJoint.prototype['GetLocalAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2FrictionJoint__GetLocalAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2FrictionJoint.prototype['SetUserData'] = function(arg0) {
    _emscripten_bind_b2FrictionJoint__SetUserData_p1(this.ptr, arg0);
}

b2FrictionJoint.prototype['GetAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2FrictionJoint__GetAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2FrictionJoint.prototype['GetReactionForce'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2FrictionJoint__GetReactionForce_p1(this.ptr, arg0), Module['b2Vec2']);
}

b2FrictionJoint.prototype['GetBodyA'] = function() {
    return wrapPointer(_emscripten_bind_b2FrictionJoint__GetBodyA_p0(this.ptr), Module['b2Body']);
}

b2FrictionJoint.prototype['GetNext'] = function() {
    return wrapPointer(_emscripten_bind_b2FrictionJoint__GetNext_p0(this.ptr), Module['b2Joint']);
}

b2FrictionJoint.prototype['GetMaxTorque'] = function() {
    return _emscripten_bind_b2FrictionJoint__GetMaxTorque_p0(this.ptr);
}

b2FrictionJoint.prototype['IsActive'] = function() {
    return _emscripten_bind_b2FrictionJoint__IsActive_p0(this.ptr);
}

b2StackAllocator.prototype['GetMaxAllocation'] = function() {
    return _emscripten_bind_b2StackAllocator__GetMaxAllocation_p0(this.ptr);
}

b2StackAllocator.prototype['__destroy__'] = function() {
    _emscripten_bind_b2StackAllocator____destroy___p0(this.ptr);
}

function b2StackAllocator() {
    this.ptr = _emscripten_bind_b2StackAllocator__b2StackAllocator_p0();
  b2StackAllocator.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2StackAllocator;
}
b2StackAllocator.prototype.__cache__ = {};
Module['b2StackAllocator'] = b2StackAllocator;

b2StackAllocator.prototype['Allocate'] = function(arg0) {
    return _emscripten_bind_b2StackAllocator__Allocate_p1(this.ptr, arg0);
}

b2StackAllocator.prototype['Free'] = function(arg0) {
    _emscripten_bind_b2StackAllocator__Free_p1(this.ptr, arg0);
}

b2DestructionListener.prototype['__destroy__'] = function() {
    _emscripten_bind_b2DestructionListener____destroy___p0(this.ptr);
}

b2DestructionListener.prototype['SayGoodbye'] = function(arg0) {
    _emscripten_bind_b2DestructionListener__SayGoodbye_p1(this.ptr, arg0.ptr);
}

function b2DestructionListener() {
    this.ptr = _emscripten_bind_b2DestructionListener__b2DestructionListener_p0();
  b2DestructionListener.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2DestructionListener;
}
b2DestructionListener.prototype.__cache__ = {};
Module['b2DestructionListener'] = b2DestructionListener;

b2Filter.prototype['__destroy__'] = function() {
    _emscripten_bind_b2Filter____destroy___p0(this.ptr);
}

b2Filter.prototype['set_maskBits'] = function(arg0) {
    _emscripten_bind_b2Filter__set_maskBits_p1(this.ptr, arg0);
}

b2Filter.prototype['set_categoryBits'] = function(arg0) {
    _emscripten_bind_b2Filter__set_categoryBits_p1(this.ptr, arg0);
}

b2Filter.prototype['get_groupIndex'] = function() {
    return _emscripten_bind_b2Filter__get_groupIndex_p0(this.ptr);
}

b2Filter.prototype['set_groupIndex'] = function(arg0) {
    _emscripten_bind_b2Filter__set_groupIndex_p1(this.ptr, arg0);
}

b2Filter.prototype['get_maskBits'] = function() {
    return _emscripten_bind_b2Filter__get_maskBits_p0(this.ptr);
}

function b2Filter() {
    this.ptr = _emscripten_bind_b2Filter__b2Filter_p0();
  b2Filter.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2Filter;
}
b2Filter.prototype.__cache__ = {};
Module['b2Filter'] = b2Filter;

b2Filter.prototype['get_categoryBits'] = function() {
    return _emscripten_bind_b2Filter__get_categoryBits_p0(this.ptr);
}

b2RopeJointDef.prototype['set_localAnchorA'] = function(arg0) {
    _emscripten_bind_b2RopeJointDef__set_localAnchorA_p1(this.ptr, arg0.ptr);
}

b2RopeJointDef.prototype['get_bodyA'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2RopeJointDef__get_bodyA_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2RopeJointDef.prototype['get_bodyB'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2RopeJointDef__get_bodyB_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2RopeJointDef.prototype['set_localAnchorB'] = function(arg0) {
    _emscripten_bind_b2RopeJointDef__set_localAnchorB_p1(this.ptr, arg0.ptr);
}

b2RopeJointDef.prototype['set_bodyA'] = function(arg0) {
    _emscripten_bind_b2RopeJointDef__set_bodyA_p1(this.ptr, arg0.ptr);
}

b2RopeJointDef.prototype['set_bodyB'] = function(arg0) {
    _emscripten_bind_b2RopeJointDef__set_bodyB_p1(this.ptr, arg0.ptr);
}

b2RopeJointDef.prototype['__destroy__'] = function() {
    _emscripten_bind_b2RopeJointDef____destroy___p0(this.ptr);
}

b2RopeJointDef.prototype['get_localAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2RopeJointDef__get_localAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2RopeJointDef.prototype['get_maxLength'] = function() {
    return _emscripten_bind_b2RopeJointDef__get_maxLength_p0(this.ptr);
}

b2RopeJointDef.prototype['get_localAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2RopeJointDef__get_localAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2RopeJointDef.prototype['get_collideConnected'] = function(arg0) {
    return _emscripten_bind_b2RopeJointDef__get_collideConnected_p1(this.ptr, arg0);
}

b2RopeJointDef.prototype['set_collideConnected'] = function(arg0) {
    _emscripten_bind_b2RopeJointDef__set_collideConnected_p1(this.ptr, arg0);
}

function b2RopeJointDef() {
    this.ptr = _emscripten_bind_b2RopeJointDef__b2RopeJointDef_p0();
  b2RopeJointDef.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2RopeJointDef;
}
b2RopeJointDef.prototype.__cache__ = {};
Module['b2RopeJointDef'] = b2RopeJointDef;

b2RopeJointDef.prototype['set_maxLength'] = function(arg0) {
    _emscripten_bind_b2RopeJointDef__set_maxLength_p1(this.ptr, arg0);
}

b2FrictionJointDef.prototype['set_localAnchorA'] = function(arg0) {
    _emscripten_bind_b2FrictionJointDef__set_localAnchorA_p1(this.ptr, arg0.ptr);
}

b2FrictionJointDef.prototype['get_bodyA'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2FrictionJointDef__get_bodyA_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2FrictionJointDef.prototype['get_bodyB'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2FrictionJointDef__get_bodyB_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2FrictionJointDef.prototype['set_localAnchorB'] = function(arg0) {
    _emscripten_bind_b2FrictionJointDef__set_localAnchorB_p1(this.ptr, arg0.ptr);
}

b2FrictionJointDef.prototype['set_bodyA'] = function(arg0) {
    _emscripten_bind_b2FrictionJointDef__set_bodyA_p1(this.ptr, arg0.ptr);
}

b2FrictionJointDef.prototype['set_bodyB'] = function(arg0) {
    _emscripten_bind_b2FrictionJointDef__set_bodyB_p1(this.ptr, arg0.ptr);
}

b2FrictionJointDef.prototype['__destroy__'] = function() {
    _emscripten_bind_b2FrictionJointDef____destroy___p0(this.ptr);
}

b2FrictionJointDef.prototype['get_maxForce'] = function() {
    return _emscripten_bind_b2FrictionJointDef__get_maxForce_p0(this.ptr);
}

function b2FrictionJointDef() {
    this.ptr = _emscripten_bind_b2FrictionJointDef__b2FrictionJointDef_p0();
  b2FrictionJointDef.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2FrictionJointDef;
}
b2FrictionJointDef.prototype.__cache__ = {};
Module['b2FrictionJointDef'] = b2FrictionJointDef;

b2FrictionJointDef.prototype['get_localAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2FrictionJointDef__get_localAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2FrictionJointDef.prototype['set_maxForce'] = function(arg0) {
    _emscripten_bind_b2FrictionJointDef__set_maxForce_p1(this.ptr, arg0);
}

b2FrictionJointDef.prototype['get_localAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2FrictionJointDef__get_localAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2FrictionJointDef.prototype['get_collideConnected'] = function(arg0) {
    return _emscripten_bind_b2FrictionJointDef__get_collideConnected_p1(this.ptr, arg0);
}

b2FrictionJointDef.prototype['set_maxTorque'] = function(arg0) {
    _emscripten_bind_b2FrictionJointDef__set_maxTorque_p1(this.ptr, arg0);
}

b2FrictionJointDef.prototype['set_collideConnected'] = function(arg0) {
    _emscripten_bind_b2FrictionJointDef__set_collideConnected_p1(this.ptr, arg0);
}

b2FrictionJointDef.prototype['Initialize'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2FrictionJointDef__Initialize_p3(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr);
}

b2FrictionJointDef.prototype['get_maxTorque'] = function() {
    return _emscripten_bind_b2FrictionJointDef__get_maxTorque_p0(this.ptr);
}

b2BodyDef.prototype['get_linearDamping'] = function() {
    return _emscripten_bind_b2BodyDef__get_linearDamping_p0(this.ptr);
}

b2BodyDef.prototype['get_awake'] = function() {
    return _emscripten_bind_b2BodyDef__get_awake_p0(this.ptr);
}

b2BodyDef.prototype['get_type'] = function() {
    return _emscripten_bind_b2BodyDef__get_type_p0(this.ptr);
}

b2BodyDef.prototype['get_allowSleep'] = function() {
    return _emscripten_bind_b2BodyDef__get_allowSleep_p0(this.ptr);
}

b2BodyDef.prototype['set_position'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_position_p1(this.ptr, arg0.ptr);
}

b2BodyDef.prototype['set_linearVelocity'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_linearVelocity_p1(this.ptr, arg0.ptr);
}

function b2BodyDef() {
    this.ptr = _emscripten_bind_b2BodyDef__b2BodyDef_p0();
  b2BodyDef.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2BodyDef;
}
b2BodyDef.prototype.__cache__ = {};
Module['b2BodyDef'] = b2BodyDef;

b2BodyDef.prototype['get_bullet'] = function() {
    return _emscripten_bind_b2BodyDef__get_bullet_p0(this.ptr);
}

b2BodyDef.prototype['get_userData'] = function() {
    return _emscripten_bind_b2BodyDef__get_userData_p0(this.ptr);
}

b2BodyDef.prototype['set_angularDamping'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_angularDamping_p1(this.ptr, arg0);
}

b2BodyDef.prototype['set_fixedRotation'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_fixedRotation_p1(this.ptr, arg0);
}

b2BodyDef.prototype['set_allowSleep'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_allowSleep_p1(this.ptr, arg0);
}

b2BodyDef.prototype['get_gravityScale'] = function() {
    return _emscripten_bind_b2BodyDef__get_gravityScale_p0(this.ptr);
}

b2BodyDef.prototype['set_angularVelocity'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_angularVelocity_p1(this.ptr, arg0);
}

b2BodyDef.prototype['set_userData'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_userData_p1(this.ptr, arg0);
}

b2BodyDef.prototype['get_position'] = function() {
    return wrapPointer(_emscripten_bind_b2BodyDef__get_position_p0(this.ptr), Module['b2Vec2']);
}

b2BodyDef.prototype['__destroy__'] = function() {
    _emscripten_bind_b2BodyDef____destroy___p0(this.ptr);
}

b2BodyDef.prototype['set_type'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_type_p1(this.ptr, arg0);
}

b2BodyDef.prototype['set_gravityScale'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_gravityScale_p1(this.ptr, arg0);
}

b2BodyDef.prototype['get_angularDamping'] = function() {
    return _emscripten_bind_b2BodyDef__get_angularDamping_p0(this.ptr);
}

b2BodyDef.prototype['set_bullet'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_bullet_p1(this.ptr, arg0);
}

b2BodyDef.prototype['set_active'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_active_p1(this.ptr, arg0);
}

b2BodyDef.prototype['set_angle'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_angle_p1(this.ptr, arg0);
}

b2BodyDef.prototype['get_angle'] = function() {
    return _emscripten_bind_b2BodyDef__get_angle_p0(this.ptr);
}

b2BodyDef.prototype['get_angularVelocity'] = function() {
    return _emscripten_bind_b2BodyDef__get_angularVelocity_p0(this.ptr);
}

b2BodyDef.prototype['get_linearVelocity'] = function() {
    return wrapPointer(_emscripten_bind_b2BodyDef__get_linearVelocity_p0(this.ptr), Module['b2Vec2']);
}

b2BodyDef.prototype['get_active'] = function() {
    return _emscripten_bind_b2BodyDef__get_active_p0(this.ptr);
}

b2BodyDef.prototype['set_linearDamping'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_linearDamping_p1(this.ptr, arg0);
}

b2BodyDef.prototype['get_fixedRotation'] = function() {
    return _emscripten_bind_b2BodyDef__get_fixedRotation_p0(this.ptr);
}

b2BodyDef.prototype['set_awake'] = function(arg0) {
    _emscripten_bind_b2BodyDef__set_awake_p1(this.ptr, arg0);
}

b2Vec2.prototype['Normalize'] = function() {
    return _emscripten_bind_b2Vec2__Normalize_p0(this.ptr);
}

b2Vec2.prototype['set_x'] = function(arg0) {
    _emscripten_bind_b2Vec2__set_x_p1(this.ptr, arg0);
}

function b2Vec2(arg0, arg1) {
  if (arg0 === undefined)
    this.ptr = _emscripten_bind_b2Vec2__b2Vec2_p0();
  else 
    this.ptr = _emscripten_bind_b2Vec2__b2Vec2_p2(arg0, arg1);
  b2Vec2.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2Vec2;
}
b2Vec2.prototype.__cache__ = {};
Module['b2Vec2'] = b2Vec2;

b2Vec2.prototype['Set'] = function(arg0, arg1) {
    _emscripten_bind_b2Vec2__Set_p2(this.ptr, arg0, arg1);
}

b2Vec2.prototype['get_x'] = function() {
    return _emscripten_bind_b2Vec2__get_x_p0(this.ptr);
}

b2Vec2.prototype['get_y'] = function() {
    return _emscripten_bind_b2Vec2__get_y_p0(this.ptr);
}

b2Vec2.prototype['set_y'] = function(arg0) {
    _emscripten_bind_b2Vec2__set_y_p1(this.ptr, arg0);
}

b2Vec2.prototype['IsValid'] = function() {
    return _emscripten_bind_b2Vec2__IsValid_p0(this.ptr);
}

b2Vec2.prototype['Skew'] = function() {
    return wrapPointer(_emscripten_bind_b2Vec2__Skew_p0(this.ptr), Module['b2Vec2']);
}

b2Vec2.prototype['LengthSquared'] = function() {
    return _emscripten_bind_b2Vec2__LengthSquared_p0(this.ptr);
}

b2Vec2.prototype['op_add'] = function(arg0) {
    _emscripten_bind_b2Vec2__op_add_p1(this.ptr, arg0.ptr);
}

b2Vec2.prototype['SetZero'] = function() {
    _emscripten_bind_b2Vec2__SetZero_p0(this.ptr);
}

b2Vec2.prototype['Length'] = function() {
    return _emscripten_bind_b2Vec2__Length_p0(this.ptr);
}

b2Vec2.prototype['__destroy__'] = function() {
    _emscripten_bind_b2Vec2____destroy___p0(this.ptr);
}

b2Vec2.prototype['op_mul'] = function(arg0) {
    _emscripten_bind_b2Vec2__op_mul_p1(this.ptr, arg0);
}

b2Vec2.prototype['op_sub'] = function() {
    return wrapPointer(_emscripten_bind_b2Vec2__op_sub_p0(this.ptr), Module['b2Vec2']);
}

b2Vec3.prototype['__destroy__'] = function() {
    _emscripten_bind_b2Vec3____destroy___p0(this.ptr);
}

b2Vec3.prototype['set_z'] = function(arg0) {
    _emscripten_bind_b2Vec3__set_z_p1(this.ptr, arg0);
}

b2Vec3.prototype['Set'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2Vec3__Set_p3(this.ptr, arg0, arg1, arg2);
}

b2Vec3.prototype['get_z'] = function() {
    return _emscripten_bind_b2Vec3__get_z_p0(this.ptr);
}

b2Vec3.prototype['op_add'] = function(arg0) {
    _emscripten_bind_b2Vec3__op_add_p1(this.ptr, arg0.ptr);
}

b2Vec3.prototype['SetZero'] = function() {
    _emscripten_bind_b2Vec3__SetZero_p0(this.ptr);
}

function b2Vec3(arg0, arg1, arg2) {
  if (arg0 === undefined)
    this.ptr = _emscripten_bind_b2Vec3__b2Vec3_p0();
  else 
    this.ptr = _emscripten_bind_b2Vec3__b2Vec3_p3(arg0, arg1, arg2);
  b2Vec3.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2Vec3;
}
b2Vec3.prototype.__cache__ = {};
Module['b2Vec3'] = b2Vec3;

b2Vec3.prototype['op_mul'] = function(arg0) {
    _emscripten_bind_b2Vec3__op_mul_p1(this.ptr, arg0);
}

b2Vec3.prototype['op_sub'] = function() {
    return wrapPointer(_emscripten_bind_b2Vec3__op_sub_p0(this.ptr), Module['b2Vec3']);
}

b2AABB.prototype['__destroy__'] = function() {
    _emscripten_bind_b2AABB____destroy___p0(this.ptr);
}

function b2AABB() {
    this.ptr = _emscripten_bind_b2AABB__b2AABB_p0();
  b2AABB.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2AABB;
}
b2AABB.prototype.__cache__ = {};
Module['b2AABB'] = b2AABB;

b2AABB.prototype['set_upperBound'] = function(arg0) {
    _emscripten_bind_b2AABB__set_upperBound_p1(this.ptr, arg0.ptr);
}

b2AABB.prototype['IsValid'] = function() {
    return _emscripten_bind_b2AABB__IsValid_p0(this.ptr);
}

b2AABB.prototype['Contains'] = function(arg0) {
    return _emscripten_bind_b2AABB__Contains_p1(this.ptr, arg0.ptr);
}

b2AABB.prototype['GetExtents'] = function() {
    return wrapPointer(_emscripten_bind_b2AABB__GetExtents_p0(this.ptr), Module['b2Vec2']);
}

b2AABB.prototype['GetCenter'] = function() {
    return wrapPointer(_emscripten_bind_b2AABB__GetCenter_p0(this.ptr), Module['b2Vec2']);
}

b2AABB.prototype['get_upperBound'] = function() {
    return wrapPointer(_emscripten_bind_b2AABB__get_upperBound_p0(this.ptr), Module['b2Vec2']);
}

b2AABB.prototype['GetPerimeter'] = function() {
    return _emscripten_bind_b2AABB__GetPerimeter_p0(this.ptr);
}

b2AABB.prototype['Combine'] = function(arg0, arg1) {
  if (arg1 === undefined)
    _emscripten_bind_b2AABB__Combine_p1(this.ptr, arg0.ptr);
  else 
    _emscripten_bind_b2AABB__Combine_p2(this.ptr, arg0.ptr, arg1.ptr);
}

b2AABB.prototype['RayCast'] = function(arg0, arg1) {
    return _emscripten_bind_b2AABB__RayCast_p2(this.ptr, arg0.ptr, arg1.ptr);
}

b2AABB.prototype['set_lowerBound'] = function(arg0) {
    _emscripten_bind_b2AABB__set_lowerBound_p1(this.ptr, arg0.ptr);
}

b2AABB.prototype['get_lowerBound'] = function() {
    return wrapPointer(_emscripten_bind_b2AABB__get_lowerBound_p0(this.ptr), Module['b2Vec2']);
}

b2FixtureDef.prototype['__destroy__'] = function() {
    _emscripten_bind_b2FixtureDef____destroy___p0(this.ptr);
}

b2FixtureDef.prototype['get_isSensor'] = function() {
    return _emscripten_bind_b2FixtureDef__get_isSensor_p0(this.ptr);
}

b2FixtureDef.prototype['set_userData'] = function(arg0) {
    _emscripten_bind_b2FixtureDef__set_userData_p1(this.ptr, arg0);
}

b2FixtureDef.prototype['set_shape'] = function(arg0) {
    _emscripten_bind_b2FixtureDef__set_shape_p1(this.ptr, arg0.ptr);
}

b2FixtureDef.prototype['get_density'] = function() {
    return _emscripten_bind_b2FixtureDef__get_density_p0(this.ptr);
}

b2FixtureDef.prototype['get_shape'] = function() {
    return _emscripten_bind_b2FixtureDef__get_shape_p0(this.ptr);
}

function b2FixtureDef() {
    this.ptr = _emscripten_bind_b2FixtureDef__b2FixtureDef_p0();
  b2FixtureDef.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2FixtureDef;
}
b2FixtureDef.prototype.__cache__ = {};
Module['b2FixtureDef'] = b2FixtureDef;

b2FixtureDef.prototype['set_density'] = function(arg0) {
    _emscripten_bind_b2FixtureDef__set_density_p1(this.ptr, arg0);
}

b2FixtureDef.prototype['set_restitution'] = function(arg0) {
    _emscripten_bind_b2FixtureDef__set_restitution_p1(this.ptr, arg0);
}

b2FixtureDef.prototype['get_restitution'] = function() {
    return _emscripten_bind_b2FixtureDef__get_restitution_p0(this.ptr);
}

b2FixtureDef.prototype['set_isSensor'] = function(arg0) {
    _emscripten_bind_b2FixtureDef__set_isSensor_p1(this.ptr, arg0);
}

b2FixtureDef.prototype['get_filter'] = function() {
    return wrapPointer(_emscripten_bind_b2FixtureDef__get_filter_p0(this.ptr), Module['b2Filter']);
}

b2FixtureDef.prototype['get_friction'] = function() {
    return _emscripten_bind_b2FixtureDef__get_friction_p0(this.ptr);
}

b2FixtureDef.prototype['set_friction'] = function(arg0) {
    _emscripten_bind_b2FixtureDef__set_friction_p1(this.ptr, arg0);
}

b2FixtureDef.prototype['get_userData'] = function() {
    return _emscripten_bind_b2FixtureDef__get_userData_p0(this.ptr);
}

b2FixtureDef.prototype['set_filter'] = function(arg0) {
    _emscripten_bind_b2FixtureDef__set_filter_p1(this.ptr, arg0.ptr);
}

b2PrismaticJointDef.prototype['set_localAnchorA'] = function(arg0) {
    _emscripten_bind_b2PrismaticJointDef__set_localAnchorA_p1(this.ptr, arg0.ptr);
}

b2PrismaticJointDef.prototype['set_localAnchorB'] = function(arg0) {
    _emscripten_bind_b2PrismaticJointDef__set_localAnchorB_p1(this.ptr, arg0.ptr);
}

b2PrismaticJointDef.prototype['get_motorSpeed'] = function() {
    return _emscripten_bind_b2PrismaticJointDef__get_motorSpeed_p0(this.ptr);
}

b2PrismaticJointDef.prototype['get_enableMotor'] = function() {
    return _emscripten_bind_b2PrismaticJointDef__get_enableMotor_p0(this.ptr);
}

b2PrismaticJointDef.prototype['get_referenceAngle'] = function() {
    return _emscripten_bind_b2PrismaticJointDef__get_referenceAngle_p0(this.ptr);
}

b2PrismaticJointDef.prototype['set_enableLimit'] = function(arg0) {
    _emscripten_bind_b2PrismaticJointDef__set_enableLimit_p1(this.ptr, arg0);
}

b2PrismaticJointDef.prototype['set_motorSpeed'] = function(arg0) {
    _emscripten_bind_b2PrismaticJointDef__set_motorSpeed_p1(this.ptr, arg0);
}

b2PrismaticJointDef.prototype['get_localAxisA'] = function() {
    return wrapPointer(_emscripten_bind_b2PrismaticJointDef__get_localAxisA_p0(this.ptr), Module['b2Vec2']);
}

b2PrismaticJointDef.prototype['set_bodyA'] = function(arg0) {
    _emscripten_bind_b2PrismaticJointDef__set_bodyA_p1(this.ptr, arg0.ptr);
}

b2PrismaticJointDef.prototype['set_bodyB'] = function(arg0) {
    _emscripten_bind_b2PrismaticJointDef__set_bodyB_p1(this.ptr, arg0.ptr);
}

function b2PrismaticJointDef() {
    this.ptr = _emscripten_bind_b2PrismaticJointDef__b2PrismaticJointDef_p0();
  b2PrismaticJointDef.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2PrismaticJointDef;
}
b2PrismaticJointDef.prototype.__cache__ = {};
Module['b2PrismaticJointDef'] = b2PrismaticJointDef;

b2PrismaticJointDef.prototype['Initialize'] = function(arg0, arg1, arg2, arg3) {
    _emscripten_bind_b2PrismaticJointDef__Initialize_p4(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr, arg3.ptr);
}

b2PrismaticJointDef.prototype['set_lowerTranslation'] = function(arg0) {
    _emscripten_bind_b2PrismaticJointDef__set_lowerTranslation_p1(this.ptr, arg0);
}

b2PrismaticJointDef.prototype['get_upperTranslation'] = function() {
    return _emscripten_bind_b2PrismaticJointDef__get_upperTranslation_p0(this.ptr);
}

b2PrismaticJointDef.prototype['get_enableLimit'] = function() {
    return _emscripten_bind_b2PrismaticJointDef__get_enableLimit_p0(this.ptr);
}

b2PrismaticJointDef.prototype['__destroy__'] = function() {
    _emscripten_bind_b2PrismaticJointDef____destroy___p0(this.ptr);
}

b2PrismaticJointDef.prototype['set_referenceAngle'] = function(arg0) {
    _emscripten_bind_b2PrismaticJointDef__set_referenceAngle_p1(this.ptr, arg0);
}

b2PrismaticJointDef.prototype['get_localAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2PrismaticJointDef__get_localAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2PrismaticJointDef.prototype['get_localAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2PrismaticJointDef__get_localAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2PrismaticJointDef.prototype['get_collideConnected'] = function(arg0) {
    return _emscripten_bind_b2PrismaticJointDef__get_collideConnected_p1(this.ptr, arg0);
}

b2PrismaticJointDef.prototype['get_bodyA'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2PrismaticJointDef__get_bodyA_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2PrismaticJointDef.prototype['get_bodyB'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2PrismaticJointDef__get_bodyB_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2PrismaticJointDef.prototype['set_upperTranslation'] = function(arg0) {
    _emscripten_bind_b2PrismaticJointDef__set_upperTranslation_p1(this.ptr, arg0);
}

b2PrismaticJointDef.prototype['get_maxMotorForce'] = function() {
    return _emscripten_bind_b2PrismaticJointDef__get_maxMotorForce_p0(this.ptr);
}

b2PrismaticJointDef.prototype['set_maxMotorForce'] = function(arg0) {
    _emscripten_bind_b2PrismaticJointDef__set_maxMotorForce_p1(this.ptr, arg0);
}

b2PrismaticJointDef.prototype['set_enableMotor'] = function(arg0) {
    _emscripten_bind_b2PrismaticJointDef__set_enableMotor_p1(this.ptr, arg0);
}

b2PrismaticJointDef.prototype['set_collideConnected'] = function(arg0) {
    _emscripten_bind_b2PrismaticJointDef__set_collideConnected_p1(this.ptr, arg0);
}

b2PrismaticJointDef.prototype['get_lowerTranslation'] = function() {
    return _emscripten_bind_b2PrismaticJointDef__get_lowerTranslation_p0(this.ptr);
}

b2PrismaticJointDef.prototype['set_localAxisA'] = function(arg0) {
    _emscripten_bind_b2PrismaticJointDef__set_localAxisA_p1(this.ptr, arg0.ptr);
}

b2WheelJointDef.prototype['set_localAnchorA'] = function(arg0) {
    _emscripten_bind_b2WheelJointDef__set_localAnchorA_p1(this.ptr, arg0.ptr);
}

b2WheelJointDef.prototype['set_localAnchorB'] = function(arg0) {
    _emscripten_bind_b2WheelJointDef__set_localAnchorB_p1(this.ptr, arg0.ptr);
}

b2WheelJointDef.prototype['get_motorSpeed'] = function() {
    return _emscripten_bind_b2WheelJointDef__get_motorSpeed_p0(this.ptr);
}

b2WheelJointDef.prototype['set_maxMotorTorque'] = function(arg0) {
    _emscripten_bind_b2WheelJointDef__set_maxMotorTorque_p1(this.ptr, arg0);
}

b2WheelJointDef.prototype['set_frequencyHz'] = function(arg0) {
    _emscripten_bind_b2WheelJointDef__set_frequencyHz_p1(this.ptr, arg0);
}

b2WheelJointDef.prototype['set_motorSpeed'] = function(arg0) {
    _emscripten_bind_b2WheelJointDef__set_motorSpeed_p1(this.ptr, arg0);
}

b2WheelJointDef.prototype['get_localAxisA'] = function() {
    return wrapPointer(_emscripten_bind_b2WheelJointDef__get_localAxisA_p0(this.ptr), Module['b2Vec2']);
}

b2WheelJointDef.prototype['set_bodyA'] = function(arg0) {
    _emscripten_bind_b2WheelJointDef__set_bodyA_p1(this.ptr, arg0.ptr);
}

b2WheelJointDef.prototype['set_bodyB'] = function(arg0) {
    _emscripten_bind_b2WheelJointDef__set_bodyB_p1(this.ptr, arg0.ptr);
}

b2WheelJointDef.prototype['Initialize'] = function(arg0, arg1, arg2, arg3) {
    _emscripten_bind_b2WheelJointDef__Initialize_p4(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr, arg3.ptr);
}

function b2WheelJointDef() {
    this.ptr = _emscripten_bind_b2WheelJointDef__b2WheelJointDef_p0();
  b2WheelJointDef.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2WheelJointDef;
}
b2WheelJointDef.prototype.__cache__ = {};
Module['b2WheelJointDef'] = b2WheelJointDef;

b2WheelJointDef.prototype['get_frequencyHz'] = function() {
    return _emscripten_bind_b2WheelJointDef__get_frequencyHz_p0(this.ptr);
}

b2WheelJointDef.prototype['set_dampingRatio'] = function(arg0) {
    _emscripten_bind_b2WheelJointDef__set_dampingRatio_p1(this.ptr, arg0);
}

b2WheelJointDef.prototype['__destroy__'] = function() {
    _emscripten_bind_b2WheelJointDef____destroy___p0(this.ptr);
}

b2WheelJointDef.prototype['get_localAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2WheelJointDef__get_localAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2WheelJointDef.prototype['get_maxMotorTorque'] = function() {
    return _emscripten_bind_b2WheelJointDef__get_maxMotorTorque_p0(this.ptr);
}

b2WheelJointDef.prototype['get_localAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2WheelJointDef__get_localAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2WheelJointDef.prototype['get_collideConnected'] = function(arg0) {
    return _emscripten_bind_b2WheelJointDef__get_collideConnected_p1(this.ptr, arg0);
}

b2WheelJointDef.prototype['get_enableMotor'] = function() {
    return _emscripten_bind_b2WheelJointDef__get_enableMotor_p0(this.ptr);
}

b2WheelJointDef.prototype['get_dampingRatio'] = function() {
    return _emscripten_bind_b2WheelJointDef__get_dampingRatio_p0(this.ptr);
}

b2WheelJointDef.prototype['get_bodyA'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2WheelJointDef__get_bodyA_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2WheelJointDef.prototype['get_bodyB'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2WheelJointDef__get_bodyB_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2WheelJointDef.prototype['set_enableMotor'] = function(arg0) {
    _emscripten_bind_b2WheelJointDef__set_enableMotor_p1(this.ptr, arg0);
}

b2WheelJointDef.prototype['set_collideConnected'] = function(arg0) {
    _emscripten_bind_b2WheelJointDef__set_collideConnected_p1(this.ptr, arg0);
}

b2WheelJointDef.prototype['set_localAxisA'] = function(arg0) {
    _emscripten_bind_b2WheelJointDef__set_localAxisA_p1(this.ptr, arg0.ptr);
}

b2RevoluteJointDef.prototype['set_localAnchorA'] = function(arg0) {
    _emscripten_bind_b2RevoluteJointDef__set_localAnchorA_p1(this.ptr, arg0.ptr);
}

b2RevoluteJointDef.prototype['get_lowerAngle'] = function() {
    return _emscripten_bind_b2RevoluteJointDef__get_lowerAngle_p0(this.ptr);
}

b2RevoluteJointDef.prototype['set_localAnchorB'] = function(arg0) {
    _emscripten_bind_b2RevoluteJointDef__set_localAnchorB_p1(this.ptr, arg0.ptr);
}

b2RevoluteJointDef.prototype['set_lowerAngle'] = function(arg0) {
    _emscripten_bind_b2RevoluteJointDef__set_lowerAngle_p1(this.ptr, arg0);
}

b2RevoluteJointDef.prototype['get_enableMotor'] = function() {
    return _emscripten_bind_b2RevoluteJointDef__get_enableMotor_p0(this.ptr);
}

b2RevoluteJointDef.prototype['set_upperAngle'] = function(arg0) {
    _emscripten_bind_b2RevoluteJointDef__set_upperAngle_p1(this.ptr, arg0);
}

b2RevoluteJointDef.prototype['get_referenceAngle'] = function() {
    return _emscripten_bind_b2RevoluteJointDef__get_referenceAngle_p0(this.ptr);
}

b2RevoluteJointDef.prototype['set_enableLimit'] = function(arg0) {
    _emscripten_bind_b2RevoluteJointDef__set_enableLimit_p1(this.ptr, arg0);
}

b2RevoluteJointDef.prototype['get_motorSpeed'] = function() {
    return _emscripten_bind_b2RevoluteJointDef__get_motorSpeed_p0(this.ptr);
}

b2RevoluteJointDef.prototype['set_motorSpeed'] = function(arg0) {
    _emscripten_bind_b2RevoluteJointDef__set_motorSpeed_p1(this.ptr, arg0);
}

b2RevoluteJointDef.prototype['get_maxMotorTorque'] = function() {
    return _emscripten_bind_b2RevoluteJointDef__get_maxMotorTorque_p0(this.ptr);
}

b2RevoluteJointDef.prototype['set_bodyA'] = function(arg0) {
    _emscripten_bind_b2RevoluteJointDef__set_bodyA_p1(this.ptr, arg0.ptr);
}

b2RevoluteJointDef.prototype['set_bodyB'] = function(arg0) {
    _emscripten_bind_b2RevoluteJointDef__set_bodyB_p1(this.ptr, arg0.ptr);
}

function b2RevoluteJointDef() {
    this.ptr = _emscripten_bind_b2RevoluteJointDef__b2RevoluteJointDef_p0();
  b2RevoluteJointDef.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2RevoluteJointDef;
}
b2RevoluteJointDef.prototype.__cache__ = {};
Module['b2RevoluteJointDef'] = b2RevoluteJointDef;

b2RevoluteJointDef.prototype['Initialize'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2RevoluteJointDef__Initialize_p3(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr);
}

b2RevoluteJointDef.prototype['get_enableLimit'] = function() {
    return _emscripten_bind_b2RevoluteJointDef__get_enableLimit_p0(this.ptr);
}

b2RevoluteJointDef.prototype['__destroy__'] = function() {
    _emscripten_bind_b2RevoluteJointDef____destroy___p0(this.ptr);
}

b2RevoluteJointDef.prototype['get_upperAngle'] = function() {
    return _emscripten_bind_b2RevoluteJointDef__get_upperAngle_p0(this.ptr);
}

b2RevoluteJointDef.prototype['set_referenceAngle'] = function(arg0) {
    _emscripten_bind_b2RevoluteJointDef__set_referenceAngle_p1(this.ptr, arg0);
}

b2RevoluteJointDef.prototype['get_localAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2RevoluteJointDef__get_localAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2RevoluteJointDef.prototype['get_localAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2RevoluteJointDef__get_localAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2RevoluteJointDef.prototype['get_collideConnected'] = function(arg0) {
    return _emscripten_bind_b2RevoluteJointDef__get_collideConnected_p1(this.ptr, arg0);
}

b2RevoluteJointDef.prototype['get_bodyA'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2RevoluteJointDef__get_bodyA_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2RevoluteJointDef.prototype['get_bodyB'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2RevoluteJointDef__get_bodyB_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2RevoluteJointDef.prototype['set_maxMotorTorque'] = function(arg0) {
    _emscripten_bind_b2RevoluteJointDef__set_maxMotorTorque_p1(this.ptr, arg0);
}

b2RevoluteJointDef.prototype['set_enableMotor'] = function(arg0) {
    _emscripten_bind_b2RevoluteJointDef__set_enableMotor_p1(this.ptr, arg0);
}

b2RevoluteJointDef.prototype['set_collideConnected'] = function(arg0) {
    _emscripten_bind_b2RevoluteJointDef__set_collideConnected_p1(this.ptr, arg0);
}

b2PulleyJointDef.prototype['set_localAnchorA'] = function(arg0) {
    _emscripten_bind_b2PulleyJointDef__set_localAnchorA_p1(this.ptr, arg0.ptr);
}

b2PulleyJointDef.prototype['set_localAnchorB'] = function(arg0) {
    _emscripten_bind_b2PulleyJointDef__set_localAnchorB_p1(this.ptr, arg0.ptr);
}

b2PulleyJointDef.prototype['set_ratio'] = function(arg0) {
    _emscripten_bind_b2PulleyJointDef__set_ratio_p1(this.ptr, arg0);
}

b2PulleyJointDef.prototype['set_groundAnchorB'] = function(arg0) {
    _emscripten_bind_b2PulleyJointDef__set_groundAnchorB_p1(this.ptr, arg0.ptr);
}

b2PulleyJointDef.prototype['set_groundAnchorA'] = function(arg0) {
    _emscripten_bind_b2PulleyJointDef__set_groundAnchorA_p1(this.ptr, arg0.ptr);
}

b2PulleyJointDef.prototype['get_groundAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2PulleyJointDef__get_groundAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2PulleyJointDef.prototype['get_groundAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2PulleyJointDef__get_groundAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2PulleyJointDef.prototype['set_bodyA'] = function(arg0) {
    _emscripten_bind_b2PulleyJointDef__set_bodyA_p1(this.ptr, arg0.ptr);
}

b2PulleyJointDef.prototype['set_bodyB'] = function(arg0) {
    _emscripten_bind_b2PulleyJointDef__set_bodyB_p1(this.ptr, arg0.ptr);
}

b2PulleyJointDef.prototype['Initialize'] = function(arg0, arg1, arg2, arg3, arg4, arg5, arg6) {
    _emscripten_bind_b2PulleyJointDef__Initialize_p7(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr, arg3.ptr, arg4.ptr, arg5.ptr, arg6);
}

b2PulleyJointDef.prototype['get_ratio'] = function() {
    return _emscripten_bind_b2PulleyJointDef__get_ratio_p0(this.ptr);
}

b2PulleyJointDef.prototype['__destroy__'] = function() {
    _emscripten_bind_b2PulleyJointDef____destroy___p0(this.ptr);
}

b2PulleyJointDef.prototype['get_localAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2PulleyJointDef__get_localAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2PulleyJointDef.prototype['get_localAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2PulleyJointDef__get_localAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2PulleyJointDef.prototype['get_collideConnected'] = function(arg0) {
    return _emscripten_bind_b2PulleyJointDef__get_collideConnected_p1(this.ptr, arg0);
}

b2PulleyJointDef.prototype['set_lengthB'] = function(arg0) {
    _emscripten_bind_b2PulleyJointDef__set_lengthB_p1(this.ptr, arg0);
}

b2PulleyJointDef.prototype['set_lengthA'] = function(arg0) {
    _emscripten_bind_b2PulleyJointDef__set_lengthA_p1(this.ptr, arg0);
}

b2PulleyJointDef.prototype['get_bodyA'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2PulleyJointDef__get_bodyA_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2PulleyJointDef.prototype['get_bodyB'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2PulleyJointDef__get_bodyB_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2PulleyJointDef.prototype['get_lengthB'] = function() {
    return _emscripten_bind_b2PulleyJointDef__get_lengthB_p0(this.ptr);
}

b2PulleyJointDef.prototype['get_lengthA'] = function() {
    return _emscripten_bind_b2PulleyJointDef__get_lengthA_p0(this.ptr);
}

b2PulleyJointDef.prototype['set_collideConnected'] = function(arg0) {
    _emscripten_bind_b2PulleyJointDef__set_collideConnected_p1(this.ptr, arg0);
}

function b2PulleyJointDef() {
    this.ptr = _emscripten_bind_b2PulleyJointDef__b2PulleyJointDef_p0();
  b2PulleyJointDef.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2PulleyJointDef;
}
b2PulleyJointDef.prototype.__cache__ = {};
Module['b2PulleyJointDef'] = b2PulleyJointDef;

b2JointDef.prototype['get_bodyA'] = function() {
    return wrapPointer(_emscripten_bind_b2JointDef__get_bodyA_p0(this.ptr), Module['b2Body']);
}

b2JointDef.prototype['set_userData'] = function(arg0) {
    _emscripten_bind_b2JointDef__set_userData_p1(this.ptr, arg0);
}

b2JointDef.prototype['set_bodyA'] = function(arg0) {
    _emscripten_bind_b2JointDef__set_bodyA_p1(this.ptr, arg0.ptr);
}

b2JointDef.prototype['set_bodyB'] = function(arg0) {
    _emscripten_bind_b2JointDef__set_bodyB_p1(this.ptr, arg0.ptr);
}

b2JointDef.prototype['__destroy__'] = function() {
    _emscripten_bind_b2JointDef____destroy___p0(this.ptr);
}

b2JointDef.prototype['get_bodyB'] = function() {
    return wrapPointer(_emscripten_bind_b2JointDef__get_bodyB_p0(this.ptr), Module['b2Body']);
}

b2JointDef.prototype['set_type'] = function(arg0) {
    _emscripten_bind_b2JointDef__set_type_p1(this.ptr, arg0);
}

b2JointDef.prototype['get_collideConnected'] = function() {
    return _emscripten_bind_b2JointDef__get_collideConnected_p0(this.ptr);
}

b2JointDef.prototype['get_type'] = function() {
    return _emscripten_bind_b2JointDef__get_type_p0(this.ptr);
}

b2JointDef.prototype['set_collideConnected'] = function(arg0) {
    _emscripten_bind_b2JointDef__set_collideConnected_p1(this.ptr, arg0);
}

function b2JointDef() {
    this.ptr = _emscripten_bind_b2JointDef__b2JointDef_p0();
  b2JointDef.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2JointDef;
}
b2JointDef.prototype.__cache__ = {};
Module['b2JointDef'] = b2JointDef;

b2JointDef.prototype['get_userData'] = function() {
    return _emscripten_bind_b2JointDef__get_userData_p0(this.ptr);
}

b2Transform.prototype['__destroy__'] = function() {
    _emscripten_bind_b2Transform____destroy___p0(this.ptr);
}

b2Transform.prototype['Set'] = function(arg0, arg1) {
    _emscripten_bind_b2Transform__Set_p2(this.ptr, arg0.ptr, arg1);
}

b2Transform.prototype['set_p'] = function(arg0) {
    _emscripten_bind_b2Transform__set_p_p1(this.ptr, arg0.ptr);
}

b2Transform.prototype['set_q'] = function(arg0) {
    _emscripten_bind_b2Transform__set_q_p1(this.ptr, arg0.ptr);
}

b2Transform.prototype['get_p'] = function() {
    return wrapPointer(_emscripten_bind_b2Transform__get_p_p0(this.ptr), Module['b2Vec2']);
}

b2Transform.prototype['get_q'] = function() {
    return wrapPointer(_emscripten_bind_b2Transform__get_q_p0(this.ptr), Module['b2Rot']);
}

function b2Transform(arg0, arg1) {
  if (arg0 === undefined)
    this.ptr = _emscripten_bind_b2Transform__b2Transform_p0();
  else 
    this.ptr = _emscripten_bind_b2Transform__b2Transform_p2(arg0.ptr, arg1.ptr);
  b2Transform.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2Transform;
}
b2Transform.prototype.__cache__ = {};
Module['b2Transform'] = b2Transform;

b2Transform.prototype['SetIdentity'] = function() {
    _emscripten_bind_b2Transform__SetIdentity_p0(this.ptr);
}

b2Color.prototype['__destroy__'] = function() {
    _emscripten_bind_b2Color____destroy___p0(this.ptr);
}

b2Color.prototype['Set'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2Color__Set_p3(this.ptr, arg0, arg1, arg2);
}

b2Color.prototype['set_r'] = function(arg0) {
    _emscripten_bind_b2Color__set_r_p1(this.ptr, arg0);
}

b2Color.prototype['get_r'] = function() {
    return _emscripten_bind_b2Color__get_r_p0(this.ptr);
}

function b2Color(arg0, arg1, arg2) {
  if (arg0 === undefined)
    this.ptr = _emscripten_bind_b2Color__b2Color_p0();
  else 
    this.ptr = _emscripten_bind_b2Color__b2Color_p3(arg0, arg1, arg2);
  b2Color.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2Color;
}
b2Color.prototype.__cache__ = {};
Module['b2Color'] = b2Color;

b2Color.prototype['set_b'] = function(arg0) {
    _emscripten_bind_b2Color__set_b_p1(this.ptr, arg0);
}

b2Color.prototype['get_g'] = function() {
    return _emscripten_bind_b2Color__get_g_p0(this.ptr);
}

b2Color.prototype['get_b'] = function() {
    return _emscripten_bind_b2Color__get_b_p0(this.ptr);
}

b2Color.prototype['set_g'] = function(arg0) {
    _emscripten_bind_b2Color__set_g_p1(this.ptr, arg0);
}

b2Rot.prototype['__destroy__'] = function() {
    _emscripten_bind_b2Rot____destroy___p0(this.ptr);
}

b2Rot.prototype['Set'] = function(arg0) {
    _emscripten_bind_b2Rot__Set_p1(this.ptr, arg0);
}

b2Rot.prototype['GetAngle'] = function() {
    return _emscripten_bind_b2Rot__GetAngle_p0(this.ptr);
}

b2Rot.prototype['GetYAxis'] = function() {
    return wrapPointer(_emscripten_bind_b2Rot__GetYAxis_p0(this.ptr), Module['b2Vec2']);
}

b2Rot.prototype['GetXAxis'] = function() {
    return wrapPointer(_emscripten_bind_b2Rot__GetXAxis_p0(this.ptr), Module['b2Vec2']);
}

b2Rot.prototype['set_c'] = function(arg0) {
    _emscripten_bind_b2Rot__set_c_p1(this.ptr, arg0);
}

b2Rot.prototype['SetIdentity'] = function() {
    _emscripten_bind_b2Rot__SetIdentity_p0(this.ptr);
}

function b2Rot(arg0) {
  if (arg0 === undefined)
    this.ptr = _emscripten_bind_b2Rot__b2Rot_p0();
  else 
    this.ptr = _emscripten_bind_b2Rot__b2Rot_p1(arg0);
  b2Rot.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2Rot;
}
b2Rot.prototype.__cache__ = {};
Module['b2Rot'] = b2Rot;

b2Rot.prototype['get_c'] = function() {
    return _emscripten_bind_b2Rot__get_c_p0(this.ptr);
}

b2WeldJointDef.prototype['set_localAnchorA'] = function(arg0) {
    _emscripten_bind_b2WeldJointDef__set_localAnchorA_p1(this.ptr, arg0.ptr);
}

b2WeldJointDef.prototype['get_bodyA'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2WeldJointDef__get_bodyA_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2WeldJointDef.prototype['get_bodyB'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2WeldJointDef__get_bodyB_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2WeldJointDef.prototype['set_localAnchorB'] = function(arg0) {
    _emscripten_bind_b2WeldJointDef__set_localAnchorB_p1(this.ptr, arg0.ptr);
}

b2WeldJointDef.prototype['get_frequencyHz'] = function() {
    return _emscripten_bind_b2WeldJointDef__get_frequencyHz_p0(this.ptr);
}

b2WeldJointDef.prototype['set_bodyA'] = function(arg0) {
    _emscripten_bind_b2WeldJointDef__set_bodyA_p1(this.ptr, arg0.ptr);
}

b2WeldJointDef.prototype['set_bodyB'] = function(arg0) {
    _emscripten_bind_b2WeldJointDef__set_bodyB_p1(this.ptr, arg0.ptr);
}

b2WeldJointDef.prototype['__destroy__'] = function() {
    _emscripten_bind_b2WeldJointDef____destroy___p0(this.ptr);
}

b2WeldJointDef.prototype['set_referenceAngle'] = function(arg0) {
    _emscripten_bind_b2WeldJointDef__set_referenceAngle_p1(this.ptr, arg0);
}

b2WeldJointDef.prototype['get_localAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2WeldJointDef__get_localAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2WeldJointDef.prototype['get_referenceAngle'] = function() {
    return _emscripten_bind_b2WeldJointDef__get_referenceAngle_p0(this.ptr);
}

b2WeldJointDef.prototype['get_localAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2WeldJointDef__get_localAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2WeldJointDef.prototype['get_collideConnected'] = function(arg0) {
    return _emscripten_bind_b2WeldJointDef__get_collideConnected_p1(this.ptr, arg0);
}

b2WeldJointDef.prototype['get_dampingRatio'] = function() {
    return _emscripten_bind_b2WeldJointDef__get_dampingRatio_p0(this.ptr);
}

b2WeldJointDef.prototype['set_collideConnected'] = function(arg0) {
    _emscripten_bind_b2WeldJointDef__set_collideConnected_p1(this.ptr, arg0);
}

b2WeldJointDef.prototype['set_frequencyHz'] = function(arg0) {
    _emscripten_bind_b2WeldJointDef__set_frequencyHz_p1(this.ptr, arg0);
}

b2WeldJointDef.prototype['Initialize'] = function(arg0, arg1, arg2) {
    _emscripten_bind_b2WeldJointDef__Initialize_p3(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr);
}

b2WeldJointDef.prototype['set_dampingRatio'] = function(arg0) {
    _emscripten_bind_b2WeldJointDef__set_dampingRatio_p1(this.ptr, arg0);
}

function b2WeldJointDef() {
    this.ptr = _emscripten_bind_b2WeldJointDef__b2WeldJointDef_p0();
  b2WeldJointDef.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2WeldJointDef;
}
b2WeldJointDef.prototype.__cache__ = {};
Module['b2WeldJointDef'] = b2WeldJointDef;

b2MouseJointDef.prototype['get_bodyA'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2MouseJointDef__get_bodyA_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2MouseJointDef.prototype['get_bodyB'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2MouseJointDef__get_bodyB_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2MouseJointDef.prototype['set_dampingRatio'] = function(arg0) {
    _emscripten_bind_b2MouseJointDef__set_dampingRatio_p1(this.ptr, arg0);
}

b2MouseJointDef.prototype['set_bodyA'] = function(arg0) {
    _emscripten_bind_b2MouseJointDef__set_bodyA_p1(this.ptr, arg0.ptr);
}

b2MouseJointDef.prototype['set_bodyB'] = function(arg0) {
    _emscripten_bind_b2MouseJointDef__set_bodyB_p1(this.ptr, arg0.ptr);
}

function b2MouseJointDef() {
    this.ptr = _emscripten_bind_b2MouseJointDef__b2MouseJointDef_p0();
  b2MouseJointDef.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2MouseJointDef;
}
b2MouseJointDef.prototype.__cache__ = {};
Module['b2MouseJointDef'] = b2MouseJointDef;

b2MouseJointDef.prototype['get_maxForce'] = function() {
    return _emscripten_bind_b2MouseJointDef__get_maxForce_p0(this.ptr);
}

b2MouseJointDef.prototype['set_target'] = function(arg0) {
    _emscripten_bind_b2MouseJointDef__set_target_p1(this.ptr, arg0.ptr);
}

b2MouseJointDef.prototype['set_maxForce'] = function(arg0) {
    _emscripten_bind_b2MouseJointDef__set_maxForce_p1(this.ptr, arg0);
}

b2MouseJointDef.prototype['get_frequencyHz'] = function() {
    return _emscripten_bind_b2MouseJointDef__get_frequencyHz_p0(this.ptr);
}

b2MouseJointDef.prototype['get_target'] = function() {
    return wrapPointer(_emscripten_bind_b2MouseJointDef__get_target_p0(this.ptr), Module['b2Vec2']);
}

b2MouseJointDef.prototype['get_collideConnected'] = function(arg0) {
    return _emscripten_bind_b2MouseJointDef__get_collideConnected_p1(this.ptr, arg0);
}

b2MouseJointDef.prototype['__destroy__'] = function() {
    _emscripten_bind_b2MouseJointDef____destroy___p0(this.ptr);
}

b2MouseJointDef.prototype['set_collideConnected'] = function(arg0) {
    _emscripten_bind_b2MouseJointDef__set_collideConnected_p1(this.ptr, arg0);
}

b2MouseJointDef.prototype['set_frequencyHz'] = function(arg0) {
    _emscripten_bind_b2MouseJointDef__set_frequencyHz_p1(this.ptr, arg0);
}

b2MouseJointDef.prototype['get_dampingRatio'] = function() {
    return _emscripten_bind_b2MouseJointDef__get_dampingRatio_p0(this.ptr);
}

b2DistanceProxy.prototype['get_m_radius'] = function() {
    return _emscripten_bind_b2DistanceProxy__get_m_radius_p0(this.ptr);
}

b2DistanceProxy.prototype['Set'] = function(arg0, arg1) {
    _emscripten_bind_b2DistanceProxy__Set_p2(this.ptr, arg0.ptr, arg1);
}

function b2DistanceProxy() {
    this.ptr = _emscripten_bind_b2DistanceProxy__b2DistanceProxy_p0();
  b2DistanceProxy.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2DistanceProxy;
}
b2DistanceProxy.prototype.__cache__ = {};
Module['b2DistanceProxy'] = b2DistanceProxy;

b2DistanceProxy.prototype['set_m_radius'] = function(arg0) {
    _emscripten_bind_b2DistanceProxy__set_m_radius_p1(this.ptr, arg0);
}

b2DistanceProxy.prototype['__destroy__'] = function() {
    _emscripten_bind_b2DistanceProxy____destroy___p0(this.ptr);
}

b2DistanceProxy.prototype['get_m_vertices'] = function() {
    return _emscripten_bind_b2DistanceProxy__get_m_vertices_p0(this.ptr);
}

b2DistanceProxy.prototype['GetSupportVertex'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2DistanceProxy__GetSupportVertex_p1(this.ptr, arg0.ptr), Module['b2Vec2']);
}

b2DistanceProxy.prototype['get_m_count'] = function() {
    return _emscripten_bind_b2DistanceProxy__get_m_count_p0(this.ptr);
}

b2DistanceProxy.prototype['GetVertexCount'] = function() {
    return _emscripten_bind_b2DistanceProxy__GetVertexCount_p0(this.ptr);
}

b2DistanceProxy.prototype['GetVertex'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2DistanceProxy__GetVertex_p1(this.ptr, arg0), Module['b2Vec2']);
}

b2DistanceProxy.prototype['GetSupport'] = function(arg0) {
    return _emscripten_bind_b2DistanceProxy__GetSupport_p1(this.ptr, arg0.ptr);
}

b2DistanceProxy.prototype['set_m_vertices'] = function(arg0) {
    _emscripten_bind_b2DistanceProxy__set_m_vertices_p1(this.ptr, arg0.ptr);
}

b2DistanceProxy.prototype['set_m_count'] = function(arg0) {
    _emscripten_bind_b2DistanceProxy__set_m_count_p1(this.ptr, arg0);
}

b2DistanceJointDef.prototype['set_localAnchorA'] = function(arg0) {
    _emscripten_bind_b2DistanceJointDef__set_localAnchorA_p1(this.ptr, arg0.ptr);
}

b2DistanceJointDef.prototype['get_bodyA'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2DistanceJointDef__get_bodyA_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2DistanceJointDef.prototype['get_bodyB'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2DistanceJointDef__get_bodyB_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2DistanceJointDef.prototype['set_localAnchorB'] = function(arg0) {
    _emscripten_bind_b2DistanceJointDef__set_localAnchorB_p1(this.ptr, arg0.ptr);
}

b2DistanceJointDef.prototype['set_dampingRatio'] = function(arg0) {
    _emscripten_bind_b2DistanceJointDef__set_dampingRatio_p1(this.ptr, arg0);
}

b2DistanceJointDef.prototype['set_bodyA'] = function(arg0) {
    _emscripten_bind_b2DistanceJointDef__set_bodyA_p1(this.ptr, arg0.ptr);
}

b2DistanceJointDef.prototype['set_bodyB'] = function(arg0) {
    _emscripten_bind_b2DistanceJointDef__set_bodyB_p1(this.ptr, arg0.ptr);
}

b2DistanceJointDef.prototype['get_length'] = function() {
    return _emscripten_bind_b2DistanceJointDef__get_length_p0(this.ptr);
}

b2DistanceJointDef.prototype['get_localAnchorA'] = function() {
    return wrapPointer(_emscripten_bind_b2DistanceJointDef__get_localAnchorA_p0(this.ptr), Module['b2Vec2']);
}

b2DistanceJointDef.prototype['get_frequencyHz'] = function() {
    return _emscripten_bind_b2DistanceJointDef__get_frequencyHz_p0(this.ptr);
}

b2DistanceJointDef.prototype['get_localAnchorB'] = function() {
    return wrapPointer(_emscripten_bind_b2DistanceJointDef__get_localAnchorB_p0(this.ptr), Module['b2Vec2']);
}

b2DistanceJointDef.prototype['get_collideConnected'] = function(arg0) {
    return _emscripten_bind_b2DistanceJointDef__get_collideConnected_p1(this.ptr, arg0);
}

b2DistanceJointDef.prototype['get_dampingRatio'] = function() {
    return _emscripten_bind_b2DistanceJointDef__get_dampingRatio_p0(this.ptr);
}

function b2DistanceJointDef() {
    this.ptr = _emscripten_bind_b2DistanceJointDef__b2DistanceJointDef_p0();
  b2DistanceJointDef.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2DistanceJointDef;
}
b2DistanceJointDef.prototype.__cache__ = {};
Module['b2DistanceJointDef'] = b2DistanceJointDef;

b2DistanceJointDef.prototype['__destroy__'] = function() {
    _emscripten_bind_b2DistanceJointDef____destroy___p0(this.ptr);
}

b2DistanceJointDef.prototype['set_collideConnected'] = function(arg0) {
    _emscripten_bind_b2DistanceJointDef__set_collideConnected_p1(this.ptr, arg0);
}

b2DistanceJointDef.prototype['set_length'] = function(arg0) {
    _emscripten_bind_b2DistanceJointDef__set_length_p1(this.ptr, arg0);
}

b2DistanceJointDef.prototype['set_frequencyHz'] = function(arg0) {
    _emscripten_bind_b2DistanceJointDef__set_frequencyHz_p1(this.ptr, arg0);
}

b2DistanceJointDef.prototype['Initialize'] = function(arg0, arg1, arg2, arg3) {
    _emscripten_bind_b2DistanceJointDef__Initialize_p4(this.ptr, arg0.ptr, arg1.ptr, arg2.ptr, arg3.ptr);
}

b2GearJointDef.prototype['__destroy__'] = function() {
    _emscripten_bind_b2GearJointDef____destroy___p0(this.ptr);
}

b2GearJointDef.prototype['get_bodyA'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2GearJointDef__get_bodyA_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2GearJointDef.prototype['get_bodyB'] = function(arg0) {
    return wrapPointer(_emscripten_bind_b2GearJointDef__get_bodyB_p1(this.ptr, arg0.ptr), Module['b2Body']);
}

b2GearJointDef.prototype['get_joint1'] = function() {
    return wrapPointer(_emscripten_bind_b2GearJointDef__get_joint1_p0(this.ptr), Module['b2Joint']);
}

b2GearJointDef.prototype['set_bodyA'] = function(arg0) {
    _emscripten_bind_b2GearJointDef__set_bodyA_p1(this.ptr, arg0.ptr);
}

b2GearJointDef.prototype['set_bodyB'] = function(arg0) {
    _emscripten_bind_b2GearJointDef__set_bodyB_p1(this.ptr, arg0.ptr);
}

b2GearJointDef.prototype['set_joint2'] = function(arg0) {
    _emscripten_bind_b2GearJointDef__set_joint2_p1(this.ptr, arg0.ptr);
}

b2GearJointDef.prototype['set_ratio'] = function(arg0) {
    _emscripten_bind_b2GearJointDef__set_ratio_p1(this.ptr, arg0);
}

b2GearJointDef.prototype['get_collideConnected'] = function(arg0) {
    return _emscripten_bind_b2GearJointDef__get_collideConnected_p1(this.ptr, arg0);
}

b2GearJointDef.prototype['get_joint2'] = function() {
    return wrapPointer(_emscripten_bind_b2GearJointDef__get_joint2_p0(this.ptr), Module['b2Joint']);
}

b2GearJointDef.prototype['set_collideConnected'] = function(arg0) {
    _emscripten_bind_b2GearJointDef__set_collideConnected_p1(this.ptr, arg0);
}

function b2GearJointDef() {
    this.ptr = _emscripten_bind_b2GearJointDef__b2GearJointDef_p0();
  b2GearJointDef.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2GearJointDef;
}
b2GearJointDef.prototype.__cache__ = {};
Module['b2GearJointDef'] = b2GearJointDef;

b2GearJointDef.prototype['get_ratio'] = function() {
    return _emscripten_bind_b2GearJointDef__get_ratio_p0(this.ptr);
}

b2GearJointDef.prototype['set_joint1'] = function(arg0) {
    _emscripten_bind_b2GearJointDef__set_joint1_p1(this.ptr, arg0.ptr);
}

b2ContactEdge.prototype['__destroy__'] = function() {
    _emscripten_bind_b2ContactEdge____destroy___p0(this.ptr);
}

b2ContactEdge.prototype['set_contact'] = function(arg0) {
    _emscripten_bind_b2ContactEdge__set_contact_p1(this.ptr, arg0.ptr);
}

b2ContactEdge.prototype['get_prev'] = function() {
    return wrapPointer(_emscripten_bind_b2ContactEdge__get_prev_p0(this.ptr), Module['b2ContactEdge']);
}

b2ContactEdge.prototype['get_other'] = function() {
    return wrapPointer(_emscripten_bind_b2ContactEdge__get_other_p0(this.ptr), Module['b2Body']);
}

b2ContactEdge.prototype['set_prev'] = function(arg0) {
    _emscripten_bind_b2ContactEdge__set_prev_p1(this.ptr, arg0.ptr);
}

b2ContactEdge.prototype['get_next'] = function() {
    return wrapPointer(_emscripten_bind_b2ContactEdge__get_next_p0(this.ptr), Module['b2ContactEdge']);
}

b2ContactEdge.prototype['set_other'] = function(arg0) {
    _emscripten_bind_b2ContactEdge__set_other_p1(this.ptr, arg0.ptr);
}

b2ContactEdge.prototype['set_next'] = function(arg0) {
    _emscripten_bind_b2ContactEdge__set_next_p1(this.ptr, arg0.ptr);
}

function b2ContactEdge() {
    this.ptr = _emscripten_bind_b2ContactEdge__b2ContactEdge_p0();
  b2ContactEdge.prototype.__cache__[this.ptr] = this;
  this.__class__ = b2ContactEdge;
}
b2ContactEdge.prototype.__cache__ = {};
Module['b2ContactEdge'] = b2ContactEdge;

b2ContactEdge.prototype['get_contact'] = function() {
    return wrapPointer(_emscripten_bind_b2ContactEdge__get_contact_p0(this.ptr), Module['b2Contact']);
}
