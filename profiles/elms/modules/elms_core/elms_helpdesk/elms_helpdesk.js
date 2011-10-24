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
  var bfeatures = detectBrowserFeatures();
  var user_features = "\n";
  //add in browser
  user_features += Drupal.t('Browser') + ': ' + BrowserDetect.browser + " " + BrowserDetect.version + "\n";
  //add in operating system
  user_features += Drupal.t('Operating System') + ': ' + BrowserDetect.OS + "\n";
  //add in screen res
  user_features += Drupal.t('Screen Resolution') + ': ' + bfeatures.res + "\n";
  //start to add in enabled plugins
  user_features += '===' + Drupal.t('Enabled Plugins') + '===' + "\n";
  //detect functionality and print to user message if it exists
  //cookies
  if (navigator.cookieEnabled == true) {
	user_features += Drupal.t('Cookies') + "\n";  
  }
  //PDFs
  if (bfeatures.pdf == 1) {
    user_features += Drupal.t('PDF') + "\n";
  }
  //Adobe Flash
  if (bfeatures.fla == 1) {
    user_features += Drupal.t('Adobe Flash') + ' ' + FlashDetect.major + "\n";
  }
  //Microsoft SilverLight
  if (bfeatures.ag == 1) {
    user_features += Drupal.t('Microsoft Silverlight') + "\n";
  }
  //Quicktime
  if (bfeatures.qt == 1) {
    user_features += Drupal.t('QuickTime') + "\n";
  }
  //Real Player
  if (bfeatures.realp == 1) {
    user_features += Drupal.t('Real Player') + "\n";
  }
  //windows media player
  if (bfeatures.wma == 1) {
    user_features += Drupal.t('Windows Media Player') + "\n";
  }
  //Adobe Director
  if (bfeatures.dir == 1) {
    user_features += Drupal.t('Adobe Director') + "\n";
  }
  //Java
  if (bfeatures.java == 1) {
    user_features += Drupal.t('Java') + "\n";
  }
  //Google Gears
  if (bfeatures.gears == 1) {
    user_features += Drupal.t('Google Gears') + "\n";
  }
  //val property displays things to the user
  $('#edit-field-tech-details').val($('#edit-field-tech-details').val() + user_features);
  //html property is what gets sent via email
  //$('#edit-field-tech-details').html($('#edit-field-tech-details').html() + user_features);
  
  //Javascript based speed test, based on http://www.ehow.com/how_5804819_detect-connection-speed-javascript.html#ixzz1biXCAScB
  function getResults() {
    //get the current time stamp
    endTime = (new Date()).getTime();
    var duration = (endTime - startTime) / 1000;
	//size of our sample file
    var downloadSize = 71736;
	//convert to bits
    var bitsLoaded = downloadSize * 8;
	//calculate bits per sectond
    var speedBps = Math.round(bitsLoaded / duration);
	//convert to KB
    var speedKbps = (speedBps / 1024);
	var speedMbps = (speedKbps / 1024).toFixed(2);
    return Drupal.t('Estimated Connection Speed: ') + speedMbps + " Mbps" + "\n";
  }
  var endTime = 0;
  var download = new Image();
  download.onload = function() {
    var speed = getResults();
    $('#edit-field-tech-details').val(speed + $('#edit-field-tech-details').val());
  };
  var startTime = (new Date()).getTime();
  download.src = Drupal.settings.elms_helpdesk.test_image + "?n=" + Math.random();
});