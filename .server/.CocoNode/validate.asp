<%

	var key = Request.Form("key");
	var data = Request.Form("data");
	Response.Write("OK:\n\nTicket Data:\n\n" + data.replace(/\|/g, "\n") + "\n\n\n");


%>

