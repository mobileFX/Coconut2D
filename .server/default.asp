<html>

<body>

<%

	var ds:CocoDataset = new Data.CocoDataset;
	if(!ds.open("./data/database.db", "SELECT * FROM [TEST]"))
	{
		Response.Write("Failed to open database");
		Response.End();
	}

	ds.moveFirst();
	while(!ds.EOF)
	{
%>

<div>test</div>

<%
		ds.moveNext();
	}
%>

</body>

</html>