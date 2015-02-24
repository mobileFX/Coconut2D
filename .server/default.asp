<%
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
			Response.End();
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
				Response.End();
			}
		}
		break;
	}
%><html><head>
	<title><%=title%></title>
	<meta charset="UTF-8">
	<script type="text/javascript" language="JavaScript" src="/js/jquery-1.11.2.js"></script>
	<script type="text/javascript" language="JavaScript" src="/js/extends.js"></script>
	<script type="text/javascript" language="JavaScript" src="/obj/CocoHttpRequest.jobj"></script>
	<script type="text/javascript" language="JavaScript" src="/obj/CocoDataset.jobj"></script>

<style>
	.DBTABLE
	{
		border:1px solid black;
	}
	.DBTABLE *
	{
		font-family:consolas;
		font-size: 10pt;
		overflow: hidden;
		wrap: no-wrap;
	}
	.DBTABLE thead
	{
		font-weight: bold;
		text-align:center;
	}
</style>

</head>

<body>

This page demostrates Classic Active Server Page Emulation with node.js and Coconut2D!<br>
Write and debug node.js JavaScript and Object Oriented JavaScript code.<br><br>

<%
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
%>

<hr>
Download a Dataset with AJAX.
<button id="btnGetData">Get Data</button>

<div id="data"></div>

<script>

$(window).load(function()
{
	$(btnGetData).click(function(e)
	{
		var dataset = window.dataset = new CocoDataset();

		if(dataset.openURL('./default.asp?method=query', false))
		{
			var html = [];
			html.push("<table class='DBTABLE' rules='all'>");
			html.push("<thead>");
			html.push("<tr>");
			for(i=0; i<dataset.fieldCount; i++)
			{
				html.push("<td nowrap>" + dataset.fieldByIndex(i).NAME + "</td>");
			}
			html.push("</tr>");
			html.push("</thead>");
			while(!dataset.DB_EOF)
			{
				html.push("<tr>");
				for(i=0; i<dataset.fieldCount; i++)
				{
					html.push("<td nowrap>" + dataset.fieldByIndex(i).value + "</td>");
				}
				html.push("</tr>");
				dataset.moveNext();
			}
			html.push("</table><br><button id='btnUpdateData'>Update Data</button>");
			$(data).html(html.join("\n"));

			$(btnUpdateData).click(function(e)
			{
				window.dataset.moveFirst();
				window.dataset.fieldByName("TEXT").value = "Ίριδα";
				window.dataset.updateURL("./default.asp?method=update");
			});
		}
	});
});

</script>

</body></html>