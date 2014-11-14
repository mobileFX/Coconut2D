
// ==================================================================================================================================
//	    ______                __                __      ____      __                        __  _
//	   / ____/___ _________  / /_  ____  ____  / /__   /  _/___  / /____  ____ __________ _/ /_(_)___  ____
//	  / /_  / __ `/ ___/ _ \/ __ \/ __ \/ __ \/ //_/   / // __ \/ __/ _ \/ __ `/ ___/ __ `/ __/ / __ \/ __ \
//	 / __/ / /_/ / /__/  __/ /_/ / /_/ / /_/ / ,<    _/ // / / / /_/  __/ /_/ / /  / /_/ / /_/ / /_/ / / / /
//	/_/    \__,_/\___/\___/_.___/\____/\____/_/|_|  /___/_/ /_/\__/\___/\__, /_/   \__,_/\__/_/\____/_/ /_/
//	                                                                   /____/
// ==================================================================================================================================

////////////////////////////////////////////////////////////////////////////////////////////////////
function __Facebook_Initialize(FacebookAppID, ImageSize)
{
	console.log("Loading Facebook JSDK for AppID " + FacebookAppID);

	window.fbAsyncInit = function()
	{
		function __FacebookCallback(response)
		{
			if(response.status === 'connected')
			{
	            FB.api("/me", function(response_user)
	            {
		            FB.api("/me/picture", {"redirect":true, "type":'square', "height":ImageSize, "width":ImageSize}, function(response_image)
		            {
		            	response_user.image_is_silhouette = response_image.data.is_silhouette;
		            	response_user.image_url = response_image.data.url;
		            	trace(response_user);
		            	CocoFacebook.__Facebook_Login_Callback(response_user);
		            });
	            });
			}
			else
			{
			}
		}

		FB.init({appId:FacebookAppID, cookie:true, status:true, oauth:true, xfbml:false, frictionlessRequests:true, version:'v2.1'});
		FB.getLoginStatus(__FacebookCallback);
	};

	if(document.getElementById('facebook-jssdk')) return true;

	var script = document.createElement('script');
	script.id = 'facebook-jssdk';
	script.src = "https://connect.facebook.net/en_US/sdk.js";
	var first_script = document.getElementsByTagName('script')[0];
	first_script.parentNode.insertBefore(script, first_script);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
function __Facebook_Login(Permissions, ImageSize)
{
	function __facebook_login_callback(response)
	{
        if(response.authResponse)
        {
            FB.api("/me", function(response_user)
            {
	            FB.api("/me/picture", {"redirect":true, "type":'square', "height":ImageSize, "width":ImageSize}, function(response_image)
	            {
	            	response_user.image_is_silhouette = response_image.data.is_silhouette;
	            	response_user.image_url = response_image.data.url;
	            	trace(response_user);
	            	CocoFacebook.__Facebook_Login_Callback(response_user);
	            });
            });
        }
        else
        {
            CocoFacebook.__Facebook_Login_Callback(null);
        }
	}
    FB.login(__facebook_login_callback, {scope:Permissions,auth_type:"rerequest",return_scopes:true,enable_profile_selector:true});
}

////////////////////////////////////////////////////////////////////////////////////////////////////
function __Facebook_Share(URL)
{
	FB.ui({method:'share', href: URL}, function(response)
	{
		CocoFacebook.__Facebook_Action_Callback(response && !response.error_code);
	});
}

////////////////////////////////////////////////////////////////////////////////////////////////////
function __Facebook_Invite(message)
{
	FB.ui({method:'apprequests', message:message}, function(response)
	{
		CocoFacebook.__Facebook_Action_Callback(response && !response.error_code);
	});
}

////////////////////////////////////////////////////////////////////////////////////////////////////
function __Facebook_Post(toUserID, URL)
{
	FB.ui({method:'send', to:toUserID, link: URL}, function(response)
	{
		CocoFacebook.__Facebook_Action_Callback(true);
	});
}

// ==================================================================================================================================
//	  ______         _ __  __               ____      __                        __  _
//	 /_  __/      __(_) /_/ /____  _____   /  _/___  / /____  ____ __________ _/ /_(_)___  ____
//	  / / | | /| / / / __/ __/ _ \/ ___/   / // __ \/ __/ _ \/ __ `/ ___/ __ `/ __/ / __ \/ __ \
//	 / /  | |/ |/ / / /_/ /_/  __/ /     _/ // / / / /_/  __/ /_/ / /  / /_/ / /_/ / /_/ / / / /
//	/_/   |__/|__/_/\__/\__/\___/_/     /___/_/ /_/\__/\___/\__, /_/   \__,_/\__/_/\____/_/ /_/
//	                                                       /____/
// ==================================================================================================================================

window.twttr = (function (d, s, id)
{
  var t, js, fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) return;
  js = d.createElement(s); js.id = id;
  js.src= "https://platform.twitter.com/widgets.js";
  fjs.parentNode.insertBefore(js, fjs);
  return window.twttr || (t = { _e: [], ready: function (f) { t._e.push(f) } });
}(document, "script", "twitter-wjs"));


// ==================================================================================================================================
//	    ____                 ____
//	   / __ \__  ______     / / /
//	  / /_/ / / / / __ \   / / /
//	 / _, _/ /_/ / / / /  /_/_/
//	/_/ |_|\__,_/_/ /_/  (_|_)
//
// ==================================================================================================================================

////////////////////////////////////////////////////////////////////////////////////////////////////
function main()
{
	// Create a new Engine
	engine = new GameEngine();

	// Run !!
	requestAnimationFrame(tickAndPaint);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
function tickAndPaint(time)
{
	engine.run(time);
	requestAnimationFrame(tickAndPaint);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// We give the browser 3 sec to resize properly.
// We need this especially for Fancy Box.

/////////////////////////////////////////////////////////////////////////////////////
function __cancelEvent(e)
{
	if(e==null && window.event) e = window.event;
	if(e && !e.__cancelled)
	{
		e.preventDefault();
		e.stopPropagation();
		e.cancelBubble=true;
		e.returnValue=false;
		e.__cancelled = true;
	}
	return false;
};

/////////////////////////////////////////////////////////////////////////////////////
function wait_fancy_box_to_resize()
{
	// Disable Window Scrolling
	document.ontouchmove = function(e)
	{
		e.preventDefault();
	}

	// Reposition window to (0,0)
	document.ontouchend = function(e)
	{
		try { window.scrollTo(0,0); } catch(e) {}
	}

	window.scrollTo(0,0);
	window.setTimeout(main, 1000);
}

/////////////////////////////////////////////////////////////////////////////////////
window.addEventListener("load", wait_fancy_box_to_resize);

/////////////////////////////////////////////////////////////////////////////////////
// For mobile browsers, hide the address bar
window.setTimeout(function(){ try { window.scrollTo(0,0); } catch(e) {} }, 1);
