<p align="center">
    <img src="./Public/static/res/AFlogo.png" width="188" title="Sfatto" alt="Sfatto">
</p>

# Sfatto

Hello and welcome to Sfatto!<br>
	  
Sfatto is a light, simple, skinnable software on premise to own your social status and spec, like an avatar or robot as well.<br>

Sfatto gives you three possible sources to feed your status:<br>
<ol>
<li>Your status uploaded by your through the youravatar/detail</li>
<li>Your status produced by APP_YOURAVATAR_STATUS_CMD</li>
<li>Your default status saved in APP_YOURAVATAR_GENERIC_STATUS</li>
</ol> 
	   
Sfatto is released under GPLv3 license, it is supplied AS-IS and we do not take any responsibility for its misusage.<br>
	   
First step, use the password box and salt fields to create the hash to insert in the config file. Remember to manually set there also the salt value.<br>
	   
As you are going to run Sfatto in the PHP process context, using a limited web server or phpfpm user, you must follow some simple directives for an optimal first setup:<br>

<ol>
<li>Check the write permissions of your "data" folder in your web app Private path; and set its path in the config file.</li>
<li>Set the default Locale.</li>
<li>Set FILE_MAX_SIZE (remember that some PHP settings could limit the upload behaviour of Avatar Free too)</li>
<li>Set BLOG_MAX_POSTS to limit the number of visible posts in the blog.</li>
<li>Set YOURAVATAR_GENERIC_STATUS, your avatar default status.</li>
<li>Set YOURAVATAR_STATUS_CMD, your avatar default status command.</li>
</ol> 

You can access your avatar status by http://yoursitename.xyz/<your_avatar>.<br>
You can access your avatar detail and spec by http://yoursitename.xyz/<your_avatar>/detail. Login with the password for the admin view. Drag-n-drop all your resources in the browser window. Files .txt feed your status, .png and .jpg your gallery, text links your network, etc.<br>

For any need of software additions, plugins and improvements please write to <a href="mailto:info@numode.eu">info@numode.eu</a>  

To help please donate by clicking <a href="https://gaox.io/l/dona1">https://gaox.io/l/dona1</a> and filling the form.  

### Screenshots:

![Sfatto in action #1](/Public/static/res/screenshot1.png)<br>

![Sfatto in action #2](/Public/static/res/screenshot2.png)<br>

![Sfatto in action #3](/Public/static/res/screenshot3.png)<br>

Feedback: <a href="mailto:code@gaox.io" style="color:#e6d236;">code@gaox.io</a>
