
// ==================================================================================================================================
//	   __  ______   ______                                             __
//	  / / / /  _/  / ____/________ _____ ___  ___ _      ______  _____/ /__
//	 / / / // /   / /_  / ___/ __ `/ __ `__ \/ _ \ | /| / / __ \/ ___/ //_/
//	/ /_/ // /   / __/ / /  / /_/ / / / / / /  __/ |/ |/ / /_/ / /  / ,<
//	\____/___/  /_/   /_/   \__,_/_/ /_/ /_/\___/|__/|__/\____/_/  /_/|_|
//
// ==================================================================================================================================

UIView is a CocoClip descendant class that represents a rectangular surface with fixed width and height.
In principle, all UIView descendants such as CocoUIButton, CocoUILabel, etc., are capable of composing and
setting their own texture image.

The texture is composed from a set of properties that each UIView descendant holds, such as captions, images,
margins, paddings, etc. All UIView-descendant properties are implemented as actual setter/getter properties
and the setter calls the UIView::invalidate() method which sets a "dirty" flag. This flag indicates that on
the next CocoClip::paint() call the control must regenerate its texture.

Since UIView is a CocoClip descendant, texture generation takes place when CocoClip::paint() is called from
its parent clip. Inside UIView::paint() the control flag UIView::__textureIsInvalid is checked and if it is
set a temporary HTML5 canvas is created and passed to UIView::repaint() of each UIView descendant in order to
paint its assets on it. When the canvas is paited, we create a new CocoImage and set CocoClip::__image object
which holds and binds the texture to the clip.




