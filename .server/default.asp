
<%
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

%>

<html>

<head>
	<meta charset="UTF-8">
	<script type="text/javascript" language="JavaScript" src="/js/jquery-1.11.2.js"></script>

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

<script>

	$(document).ready(function()
	{
		console.log("document ready");
	});

	$(window).load(function()
	{
		console.log("window load");

		$(btnGetData).click(function(e)
		{
			$.ajax({
				type: "POST",
				url: "./default.asp?method=query",
				data: "select(tasks),
				success: function()
				{
					alert("data");
				},
				dataType: "arraybuffer"
			});
		});
	});

</script>

</head>

<body>

This page demostrates <%=title%> Emulation with node.js and Coconut2D!<br>
Write and debug node.js JavaScript and Object Oriented JavaScript code.<br><br>

This example demostrates how to open a SQLite database, fetch and update data using disconnected SQLite Datasets.<br>
<%
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
%>

<hr>
Download a Dataset with AJAX.
<button id="btnGetData">Get Data</button>

</body></html>
