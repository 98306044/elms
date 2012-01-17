$(document).ready(function(){
  /*!
 * detectBrowserFeatures function is based heavily on Piwik - Web Analytics
 *
 * JavaScript tracking client
 *
 * @link http://piwik.org
 * @source http://dev.piwik.org/trac/browser/trunk/js/piwik.js
 * @license http://www.opensource.org/licenses/bsd-license.php Simplified BSD
 */
 //extend the drupal js object by adding in an elms_helpdesk name-space
  Drupal.elms_helpdesk = Drupal.elms_helpdesk || { functions: {} };
  //allow for adding messages after page load
  Drupal.elms_helpdesk.detectBrowserFeatures = function () {
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
    browserFeatures.width = screenAlias.width;
    browserFeatures.height = screenAlias.height;
    return browserFeatures;
  }
  /*
    Copyright (c) Copyright (c) 2007, Carl S. Yestrau All rights reserved.
    Code licensed under the BSD License: http://www.featureblend.com/license.txt
    Version: 1.0.4
    */
    var FlashDetect = new function(){
    var self = this;
    self.installed = false;
    self.raw = "";
    self.major = -1;
    self.minor = -1;
    self.revision = -1;
    self.revisionStr = "";
    var activeXDetectRules = [
        {
            "name":"ShockwaveFlash.ShockwaveFlash.7",
            "version":function(obj){
                return getActiveXVersion(obj);
            }
        },
        {
            "name":"ShockwaveFlash.ShockwaveFlash.6",
            "version":function(obj){
                var version = "6,0,21";
                try{
                    obj.AllowScriptAccess = "always";
                    version = getActiveXVersion(obj);
                }catch(err){}
                return version;
            }
        },
        {
            "name":"ShockwaveFlash.ShockwaveFlash",
            "version":function(obj){
                return getActiveXVersion(obj);
            }
        }
    ];
    /**
     * Extract the ActiveX version of the plugin.
     * 
     * @param {Object} The flash ActiveX object.
     * @type String
     */
    var getActiveXVersion = function(activeXObj){
        var version = -1;
        try{
            version = activeXObj.GetVariable("$version");
        }catch(err){}
        return version;
    };
    /**
     * Try and retrieve an ActiveX object having a specified name.
     * 
     * @param {String} name The ActiveX object name lookup.
     * @return One of ActiveX object or a simple object having an attribute of activeXError with a value of true.
     * @type Object
     */
    var getActiveXObject = function(name){
        var obj = -1;
        try{
            obj = new ActiveXObject(name);
        }catch(err){
            obj = {activeXError:true};
        }
        return obj;
    };
    /**
     * Parse an ActiveX $version string into an object.
     * 
     * @param {String} str The ActiveX Object GetVariable($version) return value. 
     * @return An object having raw, major, minor, revision and revisionStr attributes.
     * @type Object
     */
    var parseActiveXVersion = function(str){
        var versionArray = str.split(",");//replace with regex
        return {
            "raw":str,
            "major":parseInt(versionArray[0].split(" ")[1], 10),
            "minor":parseInt(versionArray[1], 10),
            "revision":parseInt(versionArray[2], 10),
            "revisionStr":versionArray[2]
        };
    };
    /**
     * Parse a standard enabledPlugin.description into an object.
     * 
     * @param {String} str The enabledPlugin.description value.
     * @return An object having raw, major, minor, revision and revisionStr attributes.
     * @type Object
     */
    var parseStandardVersion = function(str){
        var descParts = str.split(/ +/);
        var majorMinor = descParts[2].split(/\./);
        var revisionStr = descParts[3];
        return {
            "raw":str,
            "major":parseInt(majorMinor[0], 10),
            "minor":parseInt(majorMinor[1], 10), 
            "revisionStr":revisionStr,
            "revision":parseRevisionStrToInt(revisionStr)
        };
    };
    /**
     * Parse the plugin revision string into an integer.
     * 
     * @param {String} The revision in string format.
     * @type Number
     */
    var parseRevisionStrToInt = function(str){
        return parseInt(str.replace(/[a-zA-Z]/g, ""), 10) || self.revision;
    };
    /**
     * Is the major version greater than or equal to a specified version.
     * 
     * @param {Number} version The minimum required major version.
     * @type Boolean
     */
    self.majorAtLeast = function(version){
        return self.major >= version;
    };
    /**
     * Is the minor version greater than or equal to a specified version.
     * 
     * @param {Number} version The minimum required minor version.
     * @type Boolean
     */
    self.minorAtLeast = function(version){
        return self.minor >= version;
    };
    /**
     * Is the revision version greater than or equal to a specified version.
     * 
     * @param {Number} version The minimum required revision version.
     * @type Boolean
     */
    self.revisionAtLeast = function(version){
        return self.revision >= version;
    };
    /**
     * Is the version greater than or equal to a specified major, minor and revision.
     * 
     * @param {Number} major The minimum required major version.
     * @param {Number} (Optional) minor The minimum required minor version.
     * @param {Number} (Optional) revision The minimum required revision version.
     * @type Boolean
     */
    self.versionAtLeast = function(major){
        var properties = [self.major, self.minor, self.revision];
        var len = Math.min(properties.length, arguments.length);
        for(i=0; i<len; i++){
            if(properties[i]>=arguments[i]){
                if(i+1<len && properties[i]==arguments[i]){
                    continue;
                }else{
                    return true;
                }
            }else{
                return false;
            }
        }
    };
    /**
     * Constructor, sets raw, major, minor, revisionStr, revision and installed public properties.
     */
    self.FlashDetect = function(){
        if(navigator.plugins && navigator.plugins.length>0){
            var type = 'application/x-shockwave-flash';
            var mimeTypes = navigator.mimeTypes;
            if(mimeTypes && mimeTypes[type] && mimeTypes[type].enabledPlugin && mimeTypes[type].enabledPlugin.description){
                var version = mimeTypes[type].enabledPlugin.description;
                var versionObj = parseStandardVersion(version);
                self.raw = versionObj.raw;
                self.major = versionObj.major;
                self.minor = versionObj.minor; 
                self.revisionStr = versionObj.revisionStr;
                self.revision = versionObj.revision;
                self.installed = true;
            }
        }else if(navigator.appVersion.indexOf("Mac")==-1 && window.execScript){
            var version = -1;
            for(var i=0; i<activeXDetectRules.length && version==-1; i++){
                var obj = getActiveXObject(activeXDetectRules[i].name);
                if(!obj.activeXError){
                    self.installed = true;
                    version = activeXDetectRules[i].version(obj);
                    if(version!=-1){
                        var versionObj = parseActiveXVersion(version);
                        self.raw = versionObj.raw;
                        self.major = versionObj.major;
                        self.minor = versionObj.minor; 
                        self.revision = versionObj.revision;
                        self.revisionStr = versionObj.revisionStr;
                    }
                }
            }
        }
    }();
  };
  FlashDetect.JS_RELEASE = "1.0.4";
  //The BrowserDetect object's code was found at http://www.quirksmode.org/js/detect.html
  var BrowserDetect = {
    init: function () {
        this.browser = this.searchString(this.dataBrowser) || "An unknown browser";
        this.version = this.searchVersion(navigator.userAgent)
            || this.searchVersion(navigator.appVersion)
            || "an unknown version";
        this.OS = this.searchString(this.dataOS) || "an unknown OS";
    },
    searchString: function (data) {
        for (var i=0;i<data.length;i++)    {
            var dataString = data[i].string;
            var dataProp = data[i].prop;
            this.versionSearchString = data[i].versionSearch || data[i].identity;
            if (dataString) {
                if (dataString.indexOf(data[i].subString) != -1)
                    return data[i].identity;
            }
            else if (dataProp)
                return data[i].identity;
        }
    },
    searchVersion: function (dataString) {
        var index = dataString.indexOf(this.versionSearchString);
        if (index == -1) return;
        return parseFloat(dataString.substring(index+this.versionSearchString.length+1));
    },
    dataBrowser: [
        {
            string: navigator.userAgent,
            subString: "Chrome",
            identity: "Chrome"
        },
        {     string: navigator.userAgent,
            subString: "OmniWeb",
            versionSearch: "OmniWeb/",
            identity: "OmniWeb"
        },
        {
            string: navigator.vendor,
            subString: "Apple",
            identity: "Safari",
            versionSearch: "Version"
        },
        {
            prop: window.opera,
            identity: "Opera"
        },
        {
            string: navigator.vendor,
            subString: "iCab",
            identity: "iCab"
        },
        {
            string: navigator.vendor,
            subString: "KDE",
            identity: "Konqueror"
        },
        {
            string: navigator.userAgent,
            subString: "Firefox",
            identity: "Firefox"
        },
        {
            string: navigator.vendor,
            subString: "Camino",
            identity: "Camino"
        },
        {        // for newer Netscapes (6+)
            string: navigator.userAgent,
            subString: "Netscape",
            identity: "Netscape"
        },
        {
            string: navigator.userAgent,
            subString: "MSIE",
            identity: "Explorer",
            versionSearch: "MSIE"
        },
        {
            string: navigator.userAgent,
            subString: "Gecko",
            identity: "Mozilla",
            versionSearch: "rv"
        },
        {         // for older Netscapes (4-)
            string: navigator.userAgent,
            subString: "Mozilla",
            identity: "Netscape",
            versionSearch: "Mozilla"
        }
    ],
    dataOS : [
        {
            string: navigator.platform,
            subString: "Win",
            identity: "Windows"
        },
        {
            string: navigator.platform,
            subString: "Mac",
            identity: "Mac"
        },
        {
               string: navigator.userAgent,
               subString: "iPhone",
               identity: "iPhone/iPod"
        },
        {
            string: navigator.platform,
            subString: "Linux",
            identity: "Linux"
        }
    ]
    };
    BrowserDetect.init();
  //get the features of the browser
  var bfeatures = Drupal.elms_helpdesk.detectBrowserFeatures();
  var user_features = "\n";
	var user_tech = '';
	var msg_class = 'info';
	var zebra = 'odd';
  //add in operating system
  user_features += Drupal.t('Operating System') + ': ' + BrowserDetect.OS + "\n";
	user_tech += '<tr class="'+ msg_class +' '+ zebra +'"><td>Operating System</td><td>'+ BrowserDetect.OS +'</td></tr>';
	zebra = 'even';
  //start to add in enabled plugins
  user_features += '===' + Drupal.t('Enabled Plugins') + '===' + "\n";
  //detect functionality and print to user message if it exists
  var trigger_messages = false;
	//browser / browser and version check
	msg_class = 'info';
	if (typeof Drupal.settings.elms_helpdesk.browser_list[BrowserDetect.browser.toLowerCase()] == 'undefined') {
		Drupal.elms_navigation.add_message('browser', Drupal.t(BrowserDetect.browser +' is currently an unsupported browser.'));
    trigger_messages = true;
		msg_class = 'warning';
	}
	else {
		//version check, need to wait til I get a browser version per browser property
		/*
		if (typeof Drupal.settings.elms_helpdesk.browser_list[BrowserDetect.browser.toLowerCase() + BrowserDetect.version] == 'undefined') {
	    Drupal.elms_navigation.add_message('browser', Drupal.t(BrowserDetect.browser +' is a supported browser but your version ('+ BrowserDetect.version +') is too low.  Please ugrade if possible.'));
      trigger_messages = true;
		}*/
	}
	//add in browser
  user_features += Drupal.t('Browser') + ': ' + BrowserDetect.browser + " " + BrowserDetect.version + "\n";
	user_tech += '<tr class="'+ msg_class +' '+ zebra +'"><td>Browser</td><td>'+ BrowserDetect.browser +' '+ BrowserDetect.version +'</td></tr>';
	zebra = 'odd';
	var user_plugins = '';
	msg_class = 'info';
  //cookies
  if (navigator.cookieEnabled == true) {
    user_features += Drupal.t('Cookies') + "\n";
		user_plugins += Drupal.t('Cookies') +'<br/>';
  }
  else {
    Drupal.elms_navigation.add_message('plugin', Drupal.t('Cookies must be enabled!')); 
    trigger_messages = true;
		msg_class = 'warning';
  }
  //PDFs
  if (bfeatures.pdf == 1) {
    user_features += Drupal.t('PDF') + "\n";
		user_plugins += Drupal.t('PDF') +'<br/>';
  }
  else {
		//only throw a PDF error if we're not on a mac since we can't detect for Preview yet it'll open it correctly
    if (typeof Drupal.settings.elms_helpdesk.plugin_list.pdf  != 'undefined' && BrowserDetect.OS != 'Mac') {
      Drupal.elms_navigation.add_message('plugin-pdf', Drupal.t('If you experience issues viewing PDFs make sure that you download Adobe Acrobat or a similar reader.'));
      trigger_messages = true;
			msg_class = 'warning';
    }
  }
  //Adobe Flash
  if (bfeatures.fla == 1) {
    user_features += Drupal.t('Adobe Flash') + ' ' + FlashDetect.major + "\n";
		user_plugins += Drupal.t('Adobe Flash') + ' ' + FlashDetect.major + '<br/>';
		if (FlashDetect.major < 10) {
			Drupal.elms_navigation.add_message('flash-version', Drupal.t('Flash 10 or higher is required to ensure accurate video streaming.'));
      trigger_messages = true;
			msg_class = 'warning';
		}
  }
  else {
    if (typeof Drupal.settings.elms_helpdesk.plugin_list.flash  != 'undefined') {
      Drupal.elms_navigation.add_message('flash', Drupal.t('Flash is required to see some media in this course.'));
      trigger_messages = true;
			msg_class = 'warning';
    }
  }
  //Microsoft SilverLight
  if (bfeatures.ag == 1) {
    user_features += Drupal.t('Microsoft Silverlight') + "\n";
		user_plugins += Drupal.t('Microsoft Silverlight') +'<br/>';
  }
  else {
    if (typeof Drupal.settings.elms_helpdesk.plugin_list.silverlight != 'undefined') {
      Drupal.elms_navigation.add_message('plugin', Drupal.t('Silverlight is required to see some media in this course.'));
      trigger_messages = true;
			msg_class = 'warning';
    }
  }
  //Quicktime
  if (bfeatures.qt == 1) {
    user_features += Drupal.t('QuickTime') + "\n";
		user_plugins += Drupal.t('QuickTime') +'<br/>';
  }
  else {
    if (typeof Drupal.settings.elms_helpdesk.plugin_list.quicktime != 'undefined') {
      Drupal.elms_navigation.add_message('plugin', Drupal.t('Quicktime is required to see some media in this course.'));
      trigger_messages = true;
			msg_class = 'warning';
    }
  }
  //Real Player
  if (bfeatures.realp == 1) {
    user_features += Drupal.t('Real Player') + "\n";
		user_plugins += Drupal.t('Real Player') +'<br/>';
  }
  else {
		if (typeof Drupal.settings.elms_helpdesk.plugin_list.realplayer != 'undefined') {
      Drupal.elms_navigation.add_message('plugin', Drupal.t('Real Player is required to see some media in this course.'));
      trigger_messages = true;
			msg_class = 'warning';
		}
  }
  //windows media player
  if (bfeatures.wma == 1) {
    user_features += Drupal.t('Windows Media Player') + "\n";
    user_plugins += Drupal.t('Windows Media Player') +'<br/>';
  }
  else {
		if (typeof Drupal.settings.elms_helpdesk.plugin_list.wmp != 'undefined') {
      Drupal.elms_navigation.add_message('plugin', Drupal.t('Windows Media Player is required to see some media in this course.'));
      trigger_messages = true;
			msg_class = 'warning';
		}
  }
  //Adobe Director
  if (bfeatures.dir == 1) {
    user_features += Drupal.t('Adobe Director') + "\n";
		user_plugins += Drupal.t('Adobe Director') +'<br/>';
  }
  else {
		if (typeof Drupal.settings.elms_helpdesk.plugin_list.director != 'undefined') {
      Drupal.elms_navigation.add_message('plugin', Drupal.t('Adobe Director is required to see some media in this course.'));
      trigger_messages = true;
			msg_class = 'warning';
		}
  }
  //Java
  if (bfeatures.java == 1) {
    user_features += Drupal.t('Java') + "\n";
		user_plugins += Drupal.t('Java') +'<br/>';
  }
  else {
		if (typeof Drupal.settings.elms_helpdesk.plugin_list.java != 'undefined') {
      Drupal.elms_navigation.add_message('plugin', Drupal.t('Java is required to see some media in this course.'));
      trigger_messages = true;
			msg_class = 'warning';
		}
  }
  //Google Gears
  if (bfeatures.gears == 1) {
    user_features += Drupal.t('Google Gears') + "\n";
		user_plugins += Drupal.t('Google Gears') +'<br/>';
  }
  else {
		if (typeof Drupal.settings.elms_helpdesk.plugin_list.gears != 'undefined') {
      Drupal.elms_navigation.add_message('plugin', Drupal.t('Google Gears is required to see some media in this course.'));
      trigger_messages = true;
			msg_class = 'warning';
		}
  }
  user_tech += '<tr class="'+ msg_class +' '+ zebra +'"><td>Plugins</td><td>'+ user_plugins +'</td></tr>';
	zebra = 'even';
  //val property displays things to the user
  $('#edit-field-tech-details').val($('#edit-field-tech-details').val() + user_features);  
  //Javascript based speed test, based on http://www.ehow.com/how_5804819_detect-connection-speed-javascript.html#ixzz1biXCAScB
  function getResults() {
    //get the current time stamp
    endTime = (new Date()).getTime();
    var duration = (endTime - startTime) / 1000;
    //size of our sample file
    var downloadSize = 271446;
    //convert to bits
    var bitsLoaded = downloadSize * 8;
    //calculate bits per sectond
    var speedBps = Math.round(bitsLoaded / duration);
    //convert to KB
    var speedKbps = (speedBps / 1024).toFixed(2);
    var speedMbps = (speedKbps / 1024).toFixed(2);
    return speedMbps;
  }
  var endTime = 0;
  var download = new Image();
	msg_class = 'info';
	user_tech += '<tr class="'+ msg_class +' '+ zebra +'"><td>Est Connection Speed</td><td class="elms_helpdesk_est_connection_speed"></td></tr>';
	zebra = 'odd';
  var startTime = (new Date()).getTime();  
  $.ajax({
    url: Drupal.settings.elms_helpdesk.test_image,
    success: function(){
      var speed = getResults();
			$('.elms_helpdesk_est_connection_speed').html(speed +' Mpbs');
      $('#edit-field-tech-details').val(Drupal.t('Estimated Connection Speed: ') + speed + " Mbps" + "\n" + $('#edit-field-tech-details').val());
      //display connection speed as warning if it's below 500k
      if (speed < 0.5) {
        Drupal.elms_navigation.add_message('connection-speed', Drupal.t('You may experience performance issues because of slow connection speed: '+ speed));
				$('.elms_helpdesk_est_connection_speed').parent().addClass('warning').removeClass('info');
      }
    }
  });
  //test for small screens. this shouldn't be much of an issue but nice to tell mobile users
  var smallres = false;
  if (bfeatures.width <= 800) {
    smallres = true;
  }
  if (bfeatures.height <= 600) {
    smallres = true;
  }
  //add message if screen is very small
	msg_class = 'info';
  if (smallres) {
    Drupal.elms_navigation.add_message('screen', Drupal.t('Your screen size may make it difficult to navigate course content:'+ bfeatures.res));
		trigger_messages = true;
		msg_class = 'warning';
  }
	//add in screen res
  user_features += Drupal.t('Screen Resolution') + ': ' + bfeatures.res + "\n";
	user_tech += '<tr class="'+ msg_class +' '+ zebra +'"><td>Screen Resolution</td><td>'+ bfeatures.res +'</td></tr>';
	zebra = 'even';
  //message for those outside the origin country if its set
	msg_class = 'info';
  if (Drupal.settings.elms_helpdesk.server_country != '') {
    //if they don't match, tell them
    if (Drupal.settings.elms_helpdesk.country != Drupal.settings.elms_helpdesk.server_country) {
      Drupal.elms_navigation.add_message('connection-country', Drupal.t('You are connecting from a country outside of '+ Drupal.settings.elms_helpdesk.server_country +', this could negatively impact connection speed or some media may be blocked as a result. Country code: '+ Drupal.settings.elms_helpdesk.country));
			trigger_messages = true;
			msg_class = 'warning';
    }
  }
	user_tech += '<tr class="'+ msg_class +' '+ zebra +'"><td>Country</td><td>'+ Drupal.settings.elms_helpdesk.country +'</td></tr>';
	zebra = 'odd';
  //simulate a click so these messages are more apparent
  if (trigger_messages) {
    $('#regions_block_elms_navigation_top_1 .regions_block_title').click();
  }
	//contact form page we should add the user's values
	if (Drupal.settings.elms_helpdesk.contact_form) {
		var output = '<table class="system-status-report"><th title="Category" alt="Category">Category</th><th title="Your Value" alt="Your Value">Your Value</th><tbody>'+ user_tech + '</tbody></table>';
		$('#edit-message-wrapper').after(output);
	}
}); 
