if(!this['include']) this.include=function(f){};

include('./obj/Constants.jobj');
include('./obj/CocoAudio.jobj');
include('./obj/CocoClip.jobj');
include('./obj/CocoEngine.jobj');
include('./obj/CocoEvent.jobj');
include('./obj/CocoEventConnectionPoint.jobj');
include('./obj/CocoEventSource.jobj');
include('./obj/CocoGraphics.jobj');
include('./obj/CocoImage.jobj');
include('./obj/CocoMatrix.jobj');
include('./obj/CocoRenderContext.jobj');
include('./obj/CocoRenderContext2D.jobj');
include('./obj/CocoRenderContextGL.jobj');
include('./obj/CocoScene.jobj');
include('./obj/CocoText.jobj');
include('./obj/CocoTickable.jobj');
include('./obj/CocoTimeline.jobj');
include('./obj/CocoUIButton.jobj');
include('./obj/CocoUICheckBox.jobj');
include('./obj/CocoUIComboBox.jobj');
include('./obj/CocoUIControl.jobj');
include('./obj/CocoUILabel.jobj');
include('./obj/CocoUIPage.jobj');
include('./obj/CocoUITextBox.jobj');
include('./obj/CocoUIView.jobj');
include('./obj/DeviceMessage.jobj');
include('./obj/DeviceTouches.jobj');
include('./obj/GameEngine.jobj');
include('./obj/NewAnimation.jobj');
include('./obj/Page1.jobj');
include('./obj/TestDelegates.jobj');
include('./obj/TestEvents.jobj');
include('./obj/TestInterfaces.jobj');
include('./obj/Tests.jobj');
include('./obj/TestThis.jobj');

////////////////////////////////////////////////////////////////////////////////////////////////////
var global = this;
var engine = null;
var gl = null;

global.__native = false;

if(!global.window) 		{ global.window = new HTMLWindow(); global.__native = true; }
if(!global.document)	global.document = window.document;
if(!global.trace)		global.trace = function(msg) { console.log(msg); };

////////////////////////////////////////////////////////////////////////////////////////////////////
if(global["EventTarget"]) global.EventTarget = function() {};
global.EventTarget = function() {};

////////////////////////////////////////////////////////////////////////////////////////////////////
function State(){};

////////////////////////////////////////////////////////////////////////////////////////////////////
Image.prototype.load = function(src) { this.src = src; };

////////////////////////////////////////////////////////////////////////////////////////////////////
// Extensions of JavaScript Array and Object classes to match C++ Vector and Map.

Object.defineProperty(Array.prototype, "size", { value: function()
{
	return this.length;
}});

Object.defineProperty(Array.prototype, "clear", { value: function()
{
	while(this.length) { this.pop(); }
}});

Object.defineProperty(String.prototype, "size", { value: function()
{
	return this.length;
}});
