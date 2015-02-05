Response.write(String("<html>\n"));
Response.write(String("<head>\n"));
Response.write(String("<script type=\"text/javascript\" language=\"JavaScript\" src=\"/js/jquery-1.11.2.js\"></script>\n"));
Response.write(String("</head>\n"));
Response.write(String("<body>\n"));
Response.write(String("Classic Active Server Page Emulation with node.js and Coconut2D!<br>\n"));
Response.write(String("Write and debug node.js JavaScript and Object Oriented JavaScript code.\n"));
for(var i=0; i<10; i++)
	{
Response.write(String("<div>test</div>\n"));
}
Response.write(String("</body>\n"));
Response.write(String("<script language=\"JavaScript\">\n"));
Response.write(String("alert(\"test\");\n"));
Response.write(String("$(document).ready(function()\n"));
Response.write(String("{\n"));
Response.write(String("alert(\"document ready occurred!\");\n"));
Response.write(String("});\n"));
Response.write(String("$(window).load(function()\n"));
Response.write(String("{\n"));
Response.write(String("alert(\"window load occurred!\");\n"));
Response.write(String("});\n"));
Response.write(String("</script>\n"));
Response.write(String("</html>\n"));