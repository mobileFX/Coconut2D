#==============================================================================
# iOS Build Makefile
#==============================================================================

CERTIFICATES = ios_development.cer:AppleIncRootCertificate.cer:AppleWWDRCA.cer
PRIVATE_KEY  = ios_development.key
PASSPHRASE   = puerre
PROVISION    = Coconut2D.mobileprovision
IOSMINVER    = 5
CPUSET       = armv7
LDFLAGS		 = -LD:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/.SDK/DeviceWrappers/native/_Libraries/iOS

CFLAGS =  -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\iOS\src \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\_Common\animations \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\_Common \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.webgl\native\src \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\views \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\interfaces \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\graphics \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\audio \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Fonts \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Events \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Audio \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Arrays \
 -ID:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common \
 -I..\..\..\.SDK\DeviceWrappers\native\_Includes

SRC = D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\iOS\src\main.m \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\iOS\src\fxKeyWrap.m \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\iOS\src\fxGLWrap.m \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\iOS\src\fxDeviceWrapper.m \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\_Common\animations\Page1.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\_Common\animations\NewAnimation.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\_Common\TestInterfaces.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\_Common\GameEngine.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.webgl\native\src\WebGLRenderingContext.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\views\CocoUIView.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\views\CocoUIPage.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls\CocoUITextBox.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls\CocoUILabel.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls\CocoUIControl.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls\CocoUIComboBox.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls\CocoUICheckBox.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls\CocoUIButton.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\ImageData.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLWindow.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLImageElement.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLEvent.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLAudioElement.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLTextMetrics.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLElement.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLDocument.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLCanvasPattern.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLCanvasGradient.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLCanvasElement.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLCanvasContext.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\CanvasRenderingContext2D.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\interfaces\ITickable.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\interfaces\IEventTarget.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\interfaces\IEventListener.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\graphics\CocoText.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\graphics\CocoImage.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine\DeviceTouches.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine\DeviceMessage.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine\CocoEvents.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine\CocoEngine.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\audio\CocoAudio.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\Constants.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoTimeline.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoScene.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoMatrix.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoClip.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Fonts\fxFontFace.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Fonts\CocoFont.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Events\EventTarget.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Coconut2D.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Audio\fxAudioStream.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Arrays\TypedArray.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Arrays\ArrayBufferView.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Arrays\ArrayBuffer.cpp

RES = D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/sounds/Background.ogg \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/sounds/click_001.ogg \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/icon.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ActionSheetButtonPress_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ActionSheetButtonPress_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ActionSheetButton_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ActionSheetButton_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ActionSheetDefaultButton_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ActionSheetDefaultButton_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ActionSheetDeleteButtonNormal_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ActionSheetDeleteButtonNormal_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ActionSheetDeleteButtonPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ActionSheetDeleteButtonPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ActionSheet_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ActionSheet_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_AlertButton_Dark_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_AlertButton_Dark_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_AlertButton_Light_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_AlertButton_Light_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_Alert_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_Alert_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ComboBoxPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ComboBoxPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ComboBox_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ComboBox_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_CommandButtonPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_CommandButtonPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_CommandButton_Black_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_CommandButton_Black_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_CommandButton_RedPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_CommandButton_RedPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_CommandButton_Red_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_CommandButton_Red_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_CommandButton_White_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_CommandButton_White_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_EditBox_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_EditBox_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ListTable_BodyPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ListTable_BodyPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ListTable_Body_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ListTable_Body_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ListTable_FooterPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ListTable_FooterPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ListTable_Footer_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ListTable_Footer_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ListTable_HeaderPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ListTable_HeaderPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ListTable_Header_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_ListTable_Header_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButtonPressed_alpha_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButtonPressed_alpha_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButtonPressed_Back_alpha_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButtonPressed_Back_alpha_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButtonPressed_Next_alpha_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButtonPressed_Next_alpha_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_alpha_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_alpha_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_Back_alpha_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_Back_alpha_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_Back_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_Back_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_Command_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_Command_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_Next_alpha_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_Next_alpha_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_Next_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_Next_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_white_alpha_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBarButton_white_alpha_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_Alpha_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_Alpha_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackOpaqueBackPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackOpaqueBackPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackOpaqueBack_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackOpaqueBack_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackOpaqueButtonPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackOpaqueButtonPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackOpaqueButton_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackOpaqueButton_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackTranslucentBackPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackTranslucentBackPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackTranslucentBack_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackTranslucentBack_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackTranslucentButtonPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackTranslucentButtonPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackTranslucentButton_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_BlackTranslucentButton_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_DefaultBackPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_DefaultBackPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_DefaultBack_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_DefaultBack_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_DefaultButtonPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_DefaultButtonPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_DefaultButton_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_DefaultButton_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_DoneButtonPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_DoneButtonPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_DoneButton_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_DoneButton_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_RemoveButtonPressed_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_RemoveButtonPressed_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_RemoveButton_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_RemoveButton_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_Standard_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_NavBar_Standard_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_Notification_Pill_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_Notification_Pill_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_SearchBox_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_SearchBox_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_TabBarSelector_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_TabBarSelector_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_TabBar_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_TabBar_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_UIActionSheetTableDecoration_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/iPhone_UIActionSheetTableDecoration_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/metal_slug_mdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/metal_slug_xhdpi.png \
D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/assets/images/Sparrow.png

#==============================================================================
VSCOMPILE 	= yes
NAME		= $(shell "$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundleExecutable)
PAYLOAD		= Payload
BIN			= bin
OUTDIR		= $(PAYLOAD)\$(NAME).app
CFLAGS		+= -DIOS_APPLICATION -DENABLE_OPENGL_SUPPORT -DENABLE_PNG_SUPPORT -DENABLE_JPG_SUPPORT -DENABLE_OGG_SUPPORT -DENABLE_OPENAL_SUPPORT -DENABLE_FREETYPE_SUPPORT -DENABLE_CURL_SUPPORT
CFLAGS		+= -O2 -W -Wall -Wno-unused-private-field -Wno-sign-compare -Wno-delete-non-virtual-dtor -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wunused-value -Wempty-body -Wuninitialized -x objective-c++ -std=gnu++11
CFLAGS		+= -target $(CPUSET)-apple-ios$(IOSMINVER).0.0 --sysroot "$(IOSBUILDENV_PATH)/SDK" -integrated-as -fdiagnostics-format=msvc -fconstant-cfstrings -miphoneos-version-min=$(IOSMINVER).0.0 -DIPHONE -D__IPHONE_OS_VERSION_MIN_REQUIRED=$(IOSMINVER)0000
LDFLAGS 	+= -lbz2 -lfreetype -lTremolo -lcurl -ljpeg -lz -lpng
LDFLAGS 	+= -ios_version_min $(IOSMINVER).0 -syslibroot "$(IOSBUILDENV_PATH)/SDK" -lSystem -lcrt1.o -lgcc_s.1 -lstdc++ -F"$(IOSBUILDENV_PATH)/SDK/System/Library/Frameworks" $(shell "$(IOSBUILDENV_PATH)/Toolchain/cat" "$(IOSBUILDENV_PATH)/Frameworks.iOS$(IOSMINVER)")
OBJDIR		= obj
OBJ			= $(addsuffix .obj, $(basename $(SRC)))
OBJ_OBJ		= $(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $(SRC)))))

#==============================================================================
compile:	$(OBJ)

#link codesign ipa end

#==============================================================================
# Prepare Compilation
#==============================================================================
prepare:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Compiling iOS Project ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(OUTDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(PAYLOAD)"
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" *.log
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" *.lastbuildstate
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" *.successfulbuild
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" *.unsuccessfulbuild
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(BIN)\$(NAME).ipa"
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OBJDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OUTDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(BIN)"

#==============================================================================
# The following rule takes all the specified resource items one after the
# other (whether they are files or directories) ; files are copied in place
# and directories are recursively copied only if their content changed.
# During this process, all property lists are converted in binary format.
#	   ) else ( \
#	      "$(IOSBUILDENV_PATH)/Toolchain/copy" "%%I" "$(OUTDIR)/%%I" \
#==============================================================================
resources:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Copying resources ..."
	@for %%I in ($(RES)) do ( \
	   if "%%I"=="Info.plist" ( \
	      "$(IOSBUILDENV_PATH)/Toolchain/plconvert" "%%I" "$(OUTDIR)/%%I" -binary -MinimumOSVersion=string:$(IOSMINVER).0 \
	   ) \
	)
	@"$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundlePackageType > "$(OUTDIR)/PkgInfo"
	@"$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundleSignature >> "$(OUTDIR)/PkgInfo"
	@"$(IOSBUILDENV_PATH)/Toolchain/copy" "iTunesArtwork.*" "$(OUTDIR)/iTunesArtwork"

#==============================================================================
# Compile C/C++ and Objective-C files
#==============================================================================
%.obj:	%.c
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.cc
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj: %.cpp
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.cxx
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.m
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.mm
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.mx
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.mxx
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.s
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Assembling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"

#==============================================================================
# Hack: static libs are treated like source files, except that they aren't
# compiled but just copied to .obj. The linker will figure out what to do.
#==============================================================================
%.obj:	%.a
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Using static library or framework: $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/copy" "$<" "$@"

#==============================================================================
# The following rule first ensures the output directory exists, creates it if
# necessary, then links the compiled .obj files together in that directory
#==============================================================================
link:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Linking project files ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/ld" $(LDFLAGS) -o "$(OUTDIR)/$(NAME)" $(OBJ_OBJ)

#==============================================================================
# The following rule generates the SHA1 checksums for the resource files, then
# insert a code signature blob in the binary, seals the binary code, resources
# and Info.plist and sign it with the specified application identifier.
#==============================================================================
codesign:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Signing code ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/copy" "$(IOSBUILDENV_PATH)\Keychain\$(PROVISION)" "$(OUTDIR)\embedded.mobileprovision"
	@"$(IOSBUILDENV_PATH)/Toolchain/ldid" -k"$(IOSBUILDENV_PATH)/Keychain" -S$(CERTIFICATES):$(PRIVATE_KEY):$(PASSPHRASE) -C -E -I "$(OUTDIR)/$(NAME)"

#==============================================================================
# The following rule builds an IPA bundle out of the compiled app directory.
#==============================================================================
ipa:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Building iTunes package ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/zip" -q -r "$(BIN)/$(NAME).ipa" "$(PAYLOAD)" "iTunesArtwork" -x \*.log \*.lastbuildstate \*successfulbuild

#==============================================================================
# This simple rule displays the success message after a successful build
#==============================================================================
end:
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(OUTDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(PAYLOAD)"
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(OBJDIR)"
