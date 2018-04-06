
if( SEMICOLON.isMobile.any() && !element.hasClass('no-placeholder') ) {
	var placeholderImg = elementVideo.attr('poster');

	if( placeholderImg != '' ) {
		element.append('<div class="video-placeholder" style="background-image: url('+ placeholderImg +');"></div>');
	}

	elementVideo.hide();
}
