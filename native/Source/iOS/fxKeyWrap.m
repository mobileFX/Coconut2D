#import "fxKeyWrap.h"

@implementation fxKeyWrap

- (BOOL)canBecomeFirstResponder { return YES; }

- (BOOL)hasText { return YES; }
- (void)insertText:(NSString *)theText
{
    fxCRL::handleEvent(0, fxCRL::fxEvent::KEYDOWN, (void*)[theText cStringUsingEncoding:NSUTF32LittleEndianStringEncoding]);
    fxCRL::handleEvent(0, fxCRL::fxEvent::KEYPRESS, (void*)[theText cStringUsingEncoding:NSUTF32LittleEndianStringEncoding]);
    fxCRL::handleEvent(0, fxCRL::fxEvent::KEYUP, (void*)[theText cStringUsingEncoding:NSUTF32LittleEndianStringEncoding]);
}
- (void)deleteBackward
{
    static uint32_t _v = 8;
    fxCRL::handleEvent(0, fxCRL::fxEvent::KEYDOWN, (void*)(&_v));
    fxCRL::handleEvent(0, fxCRL::fxEvent::KEYUP, (void*)(&_v));
}

- (UITextAutocapitalizationType)autocapitalizationType { return UITextAutocapitalizationTypeNone; }
- (UITextAutocorrectionType)autocorrectionType { return UITextAutocorrectionTypeNo; }
- (UITextSpellCheckingType)spellCheckingType { return UITextSpellCheckingTypeNo; }
- (BOOL)enablesReturnKeyAutomatically { return NO; }
- (UIKeyboardAppearance)keyboardAppearance { return UIKeyboardAppearanceDefault; }
- (UIKeyboardType)keyboardType { return UIKeyboardTypeDefault; }
- (UIReturnKeyType)returnKeyType { return UIReturnKeyDefault; }

@end