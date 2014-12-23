
===========================================================================
						Events in Coconut2D
===========================================================================

Events in Coconut2D are very similar to HTML events but in order to offer
a unified cross-platform and cross-device-wrapper event mechanism a native
device-event goes through a pipeline process before it is finally converted
to CocoEvent object that can be used by Coconut2D classes and your classes.

                      __registerCallback
                               |
                               V
              +-----------------------------------+
              |      Device Wrapper Messages      |
              |    (iOS, Android, HTML Browser)   |
              +----------------+------------------+
                               |
           dispatchEvent(uid:Integer, eventType:String)
                               |
                               V

Device Wrappers (eg. iOS, Android, HTML5 Browsers) produce device-specific
events that are handled by the HTMLWidnow object. HTMLWindow converts those
events to HTMLEvent objects and passes them to CocoEngine object in order
to simulate HTML event handling.

              +-----------------------------------+
              |       Received by HTMLWindow      |
              |     (mascuraded as HTMLEvents)    |
              +----------------+------------------+
                               |
                           HTMLEvent
                               |
                               V

CocoEngine processes HTMLEvents and converts them to DEVICE_MESSAGE structures.
A DEVICE_MESSAGE stays alive for 1 tick-cycle before it is dismissed.

              +-----------------------------------+
              |        Handled by CocoEngine      |
              |    Converted to DEVICE_MESSAGE    |
              +----------------+------------------+
                               |
                        DEVICE_MESSAGE
                               |
                               V

During that tick-cycle any ITickable object can peek a device message from
the CocoEngine for processing it in its tick() method. If an ITickable class
is an event source (eg. CocoClip, XMLHTTP, etc.) it converts the DEVICE_MESSAGE
to a CocoEvent object and fires it to its event listeners.

            +---------------------------------------+
            |                                       |
            |       Picked during tick() cycle      |
            |         by a CocoClass object         |
            |       (eg. CocoClip, HTTP, etc.)      |
            |      and converted to a CocoEvent     |
            |   Dispateched through dispatchEvent   |
            |                                       |
            +---------------------------------------+
                               |
                     CocoEvent Derivative
                               |
                               V

All Coconut2D classes should handle only CocoEvent objects through addEventListener,
removeEventListener and dispatchEvent API. Through this abstraction you let device
specific events be handled by device wrappers and you can focus on high-level event
handling.