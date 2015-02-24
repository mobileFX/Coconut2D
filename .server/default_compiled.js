
var title = "Classic Active Server Page";

	switch(Request.QueryString("method"))
	{
	case "query":
		var dataset = Server.CreateObject("CocoDataset");
		if(dataset.open("./data/database.db", "SELECT * FROM TEST"))
		{
			console.log("User query returned " + dataset.recordCount() + " records");
			Response.Clear();
			Response.BinaryWrite(dataset.toArrayBuffer());
			{ Response.End(); return; }
		}
		break;

	case "update":
		var ab = Request.BinaryRead(Request.TotalBytes);
		var dataset = Server.CreateObject("CocoDataset");
		if(dataset.openFromArrayBuffer(ab))
		{
			if(dataset.update())
			{
				Response.Clear();
				Response.BinaryWrite(dataset.toArrayBuffer());
				{ Response.End(); return; }
			}
		}
		break;
	}
Response.Write(String("<html>\n"));
Response.Write(String("<head>\n"));
Response.Write(String("<title>\n"));
Response.Write(String(title));
Response.Write(String("</title>\n"));
Response.Write(String("<meta charset=\"UTF-8\">\n"));
Response.Write(String("<script type=\"text/javascript\" language=\"JavaScript\" src=\"/js/jquery-1.11.2.js\"></script>\n"));
Response.Write(String("<script type=\"text/javascript\" language=\"JavaScript\" src=\"/js/extends.js\"></script>\n"));
Response.Write(String("<script type=\"text/javascript\" language=\"JavaScript\" src=\"/obj/CocoHttpRequest.jobj\"></script>\n"));
Response.Write(String("<script type=\"text/javascript\" language=\"JavaScript\" src=\"/obj/CocoDataset.jobj\"></script>\n"));
Response.Write(String("<style>\n"));
Response.Write(String(".DBTABLE\n"));
Response.Write(String("{\n"));
Response.Write(String("border:1px solid black;\n"));
Response.Write(String("}\n"));
Response.Write(String(".DBTABLE *\n"));
Response.Write(String("{\n"));
Response.Write(String("font-family:consolas;\n"));
Response.Write(String("font-size: 10pt;\n"));
Response.Write(String("overflow: hidden;\n"));
Response.Write(String("wrap: no-wrap;\n"));
Response.Write(String("}\n"));
Response.Write(String(".DBTABLE thead\n"));
Response.Write(String("{\n"));
Response.Write(String("font-weight: bold;\n"));
Response.Write(String("text-align:center;\n"));
Response.Write(String("}\n"));
Response.Write(String("</style>\n"));
Response.Write(String("</head>\n"));
Response.Write(String("<body>\n"));
Response.Write(String("This page demostrates Classic Active Server Page Emulation with node.js and Coconut2D!<br>\n"));
Response.Write(String("Write and debug node.js JavaScript and Object Oriented JavaScript code.<br><br>\n"));
// Execute SQL on the server side and get results in a DataSet (similar API with ADO Recordsets)
	// Then display the results in dynamic table element.
	var i;
	var dataset = Server.CreateObject("CocoDataset");
	if(dataset.open("./data/database.db", "SELECT * FROM TEST"))
	{
		Response.Write("<table class='DBTABLE' rules='all'>");
		Response.Write("<thead>");
		Response.Write("<tr>");
		for(i=0; i<dataset.fieldCount; i++)
		{
			Response.Write("<td nowrap>" + dataset.fieldByIndex(i).NAME + "</td>");
		}
		Response.Write("</tr>");
		Response.Write("</thead>");
		while(!dataset.DB_EOF)
		{
			Response.Write("<tr>");
			for(i=0; i<dataset.fieldCount; i++)
			{
				Response.Write("<td nowrap>" + dataset.fieldByIndex(i).value + "</td>");
			}
			Response.Write("</tr>");
			dataset.moveNext();
		}
		Response.Write("</table>");
	}
Response.Write(String("<hr>\n"));
Response.Write(String("Download a Dataset with AJAX.\n"));
Response.Write(String("<button id=\"btnGetData\">Get Data</button>\n"));
Response.Write(String("<div id=\"data\"></div>\n"));
Response.Write(String("<script>\n"));
Response.Write(String("$(window).load(function()\n"));
Response.Write(String("{\n"));
Response.Write(String("$(btnGetData).click(function(e)\n"));
Response.Write(String("{\n"));
Response.Write(String("var dataset = window.dataset = new CocoDataset();\n"));
Response.Write(String("if(dataset.openURL('./default.asp?method=query', false))\n"));
Response.Write(String("{\n"));
Response.Write(String("var html = [];\n"));
Response.Write(String("html.push(\"<table class='DBTABLE' rules='all'>\");\n"));
Response.Write(String("html.push(\"<thead>\");\n"));
Response.Write(String("html.push(\"<tr>\");\n"));
Response.Write(String("for(i=0; i<dataset.fieldCount; i++)\n"));
Response.Write(String("{\n"));
Response.Write(String("html.push(\"<td nowrap>\" + dataset.fieldByIndex(i).NAME + \"</td>\");\n"));
Response.Write(String("}\n"));
Response.Write(String("html.push(\"</tr>\");\n"));
Response.Write(String("html.push(\"</thead>\");\n"));
Response.Write(String("while(!dataset.DB_EOF)\n"));
Response.Write(String("{\n"));
Response.Write(String("html.push(\"<tr>\");\n"));
Response.Write(String("for(i=0; i<dataset.fieldCount; i++)\n"));
Response.Write(String("{\n"));
Response.Write(String("html.push(\"<td nowrap>\" + dataset.fieldByIndex(i).value + \"</td>\");\n"));
Response.Write(String("}\n"));
Response.Write(String("html.push(\"</tr>\");\n"));
Response.Write(String("dataset.moveNext();\n"));
Response.Write(String("}\n"));
Response.Write(String("html.push(\"</table><br><button id='btnUpdateData'>Update Data</button>\");\n"));
Response.Write(String("$(data).html(html.join(\"\\n\"));\n"));
Response.Write(String("$(btnUpdateData).click(function(e)\n"));
Response.Write(String("{\n"));
Response.Write(String("window.dataset.moveFirst();\n"));
Response.Write(String("window.dataset.fieldByName(\"TEXT\").value = \"Ίριδα\";\n"));
Response.Write(String("window.dataset.updateURL(\"./default.asp?method=update\");\n"));
Response.Write(String("});\n"));
Response.Write(String("}\n"));
Response.Write(String("});\n"));
Response.Write(String("});\n"));
Response.Write(String("</script>\n"));
Response.Write(String("</body></html>\n"));