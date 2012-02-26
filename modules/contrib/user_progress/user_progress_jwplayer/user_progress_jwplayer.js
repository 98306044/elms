// JavaScript Document
$(document).ready(function() {
	// record the fact that they started watching the video
	jwplayer().onPlay(function() {
    var params = 'value=1&data=play&upregid='+ Drupal.settings.user_progress.upregid;
    Drupal.user_progress.ajax_call('set', 'value', params);
  });
	// flag that the user finished watching the video
	jwplayer().onComplete(function() {
    var params = 'value='+ jwplayer().getBuffer() +'&data=finished&upregid='+ Drupal.settings.user_progress.upregid;
    Drupal.user_progress.ajax_call('set', 'value', params);
  });
	// Determine if the user jumped ahead of back in the video
	jwplayer().onSeek(function(event) {
		var pos = event.offset - event.position;
		if (pos > 0) {
			var direction = 'skip ahead';
		}
    else {
			var direction = 'skip back';
		}
		var params = 'value='+ jwplayer().getBuffer() +'&data='+ direction +'&upregid='+ Drupal.settings.user_progress.upregid;
    Drupal.user_progress.ajax_call('set', 'value', params);
  });
	// onTime -- % completion if it's not overkill to monitor, prolly is
});
