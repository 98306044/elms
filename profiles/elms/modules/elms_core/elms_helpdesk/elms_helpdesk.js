/*!
 * detectBrowserFeatures function is based heavily on Piwik - Web Analytics
 *
 * JavaScript tracking client
 *
 * @link http://piwik.org
 * @source http://dev.piwik.org/trac/browser/trunk/js/piwik.js
 * @license http://www.opensource.org/licenses/bsd-license.php Simplified BSD
 */
function detectBrowserFeatures() {
    /* alias frequently used globals for added minification */
    var i,
    browserFeatures = {},
    navigatorAlias = navigator,
    screenAlias = screen,
    windowAlias = window,
    mimeType,
    pluginMap = {
      //document types
      pdf: 'application/pdf',
      //media players
      qt: 'video/quicktime',
      realp: 'audio/x-pn-realaudio-plugin',
      wma: 'application/x-mplayer2',
      //interactive multimedia
      dir: 'application/x-director',
      fla: 'application/x-shockwave-flash',
      //RIA
      java: 'application/x-java-vm',
      gears: 'application/x-googlegears',
      ag: 'application/x-silverlight'
    };
    // general plugin detection
    if (navigatorAlias.mimeTypes && navigatorAlias.mimeTypes.length) {
      for (i in pluginMap) {
        if (Object.prototype.hasOwnProperty.call(pluginMap, i)) {
          mimeType = navigatorAlias.mimeTypes[pluginMap[i]];
          browserFeatures[i] = (mimeType && mimeType.enabledPlugin) ? '1' : '0';
        }
      }
    }
    // Safari and Opera
    // IE6/IE7 navigator.javaEnabled can't be aliased, so test directly
    if (typeof navigator.javaEnabled !== 'unknown' &&
      typeof navigatorAlias.javaEnabled !== 'undefined' &&
      navigatorAlias.javaEnabled()) {
      browserFeatures.java = '1';
    }
    // Firefox
    if (typeof windowAlias.GearsFactory === 'function') {
      browserFeatures.gears = '1';
    }
    // other browser features
    browserFeatures.res = screenAlias.width + 'x' + screenAlias.height;
    return browserFeatures;
}
$(document).ready(function(){
 console.log(detectBrowserFeatures());
 var bfeatures = detectBrowserFeatures();
 var user_features = 'Screen Resolution: ' + bfeatures.res + "\n" + 'Enabled Plugins:' + "\n";
  //detect functionality and print to user message if it exists
  //PDFs
  if (bfeatures.pdf == 1) {
    user_features+= 'PDF' + "\n";
  }
  //Quicktime
  if (bfeatures.qt == 1) {
    user_features+= 'QuickTime' + "\n";
  }
  //Real Player
  if (bfeatures.realp == 1) {
    user_features+= 'Real Player' + "\n";
  }
  //windows media player
  if (bfeatures.wma == 1) {
    user_features+= 'Windows Media Player' + "\n";
  }
  //Adobe Director
  if (bfeatures.dir == 1) {
    user_features+= 'Adobe Director' + "\n";
  }
  //Adobe Flash
  if (bfeatures.fla == 1) {
    user_features+= 'Adobe Flash' + "\n";
  }
  //Java
  if (bfeatures.java == 1) {
    user_features+= 'Java' + "\n";
  }
  //Google Gears
  if (bfeatures.gears == 1) {
    user_features+= 'Google Gears' + "\n";
  }
  //Microsoft SilverLight
  if (bfeatures.ag == 1) {
    user_features+= 'Microsoft Silverlight' + "\n";
  }
  $('#edit-field-tech-details').val($('#edit-field-tech-details').val() + user_features);
});