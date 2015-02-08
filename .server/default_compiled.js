
var title = "Classic Active Server Page";

	/*
	debugger;

	switch(Request.QueryString("method"))
	{
		case "query":
			Response.end();
			break;
	}
	*/
Response.write(String("<html>\n"));
Response.write(String("<head>\n"));
Response.write(String("<meta charset=\"UTF-8\">\n"));
Response.write(String("<script type=\"text/javascript\" language=\"JavaScript\" src=\"/js/jquery-1.11.2.js\"></script>\n"));
Response.write(String("<style>\n"));
Response.write(String(".DBTABLE\n"));
Response.write(String("{\n"));
Response.write(String("border:1px solid black;\n"));
Response.write(String("}\n"));
Response.write(String(".DBTABLE *\n"));
Response.write(String("{\n"));
Response.write(String("font-family:consolas;\n"));
Response.write(String("font-size: 10pt;\n"));
Response.write(String("overflow: hidden;\n"));
Response.write(String("wrap: no-wrap;\n"));
Response.write(String("}\n"));
Response.write(String(".DBTABLE thead\n"));
Response.write(String("{\n"));
Response.write(String("font-weight: bold;\n"));
Response.write(String("text-align:center;\n"));
Response.write(String("}\n"));
Response.write(String("</style>\n"));
Response.write(String("<script>\n"));
Response.write(String("$(document).ready(function()\n"));
Response.write(String("{\n"));
Response.write(String("console.log(\"document ready\");\n"));
Response.write(String("});\n"));
Response.write(String("$(window).load(function()\n"));
Response.write(String("{\n"));
Response.write(String("console.log(\"window load\");\n"));
Response.write(String("$(btnGetData).click(function(e)\n"));
Response.write(String("{\n"));
Response.write(String("$.ajax({\n"));
Response.write(String("type: \"POST\",\n"));
Response.write(String("url: \"./default.asp?method=query\",\n"));
Response.write(String("data: \"select(tasks),\n"));
Response.write(String("success: function()\n"));
Response.write(String("{\n"));
Response.write(String("alert(\"data\");\n"));
Response.write(String("},\n"));
Response.write(String("dataType: \"arraybuffer\"\n"));
Response.write(String("});\n"));
Response.write(String("});\n"));
Response.write(String("});\n"));
Response.write(String("</script>\n"));
Response.write(String("</head>\n"));
Response.write(String("<body>\n"));
Response.write(String("This page demostrates\n"));
Response.write(String(title));
Response.write(String("Emulation with node.js and Coconut2D!<br>\n"));
Response.write(String("Write and debug node.js JavaScript and Object Oriented JavaScript code.<br><br>\n"));
Response.write(String("This example demostrates how to open a SQLite database, fetch and update data using disconnected SQLite Datasets.<br>\n"));
// Execute SQL on the server side and get results in a DataSet (similar API with ADO Recordsets)
	// Then display the results in dynamic table element.
	var i;
	var ds = this.execSql("./data/database.db", "select * from test");
	Response.write("<table class='DBTABLE' rules='all'>");
	Response.write("<thead>");
	Response.write("<tr>");
	for(i=0; i<ds.fieldCount; i++)
	{
		Response.write("<td nowrap>" + ds.fieldByIndex(i).NAME + "</td>");
	}
	Response.write("</tr>");
	Response.write("</thead>");
	while(!ds.DB_EOF)
	{
		Response.write("<tr>");
		for(i=0; i<ds.fieldCount; i++)
		{
			Response.write("<td nowrap>" + ds.fieldByIndex(i).value + "</td>");
		}
		Response.write("</tr>");
		ds.moveNext();
	}
	Response.write("</table>");
Response.write(String("<hr>\n"));
Response.write(String("Download a Dataset with AJAX.\n"));
Response.write(String("<button id=\"btnGetData\">Get Data</button>\n"));
Response.write(String("</body></html>\n"));