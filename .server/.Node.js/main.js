
/*
var http = require('http');

http.Server(function(req, res)
{
	res.writeHead(200);
	res.end("This answer comes from the process " + process.pid);
	console.log("Message sent from http server");

}).listen(80);

*/

var Fiber = require('fibers');

function SomethingAsync()
{
	console.log("async start");

	var fiber = Fiber.current;
	var t;

	setTimeout(function()
	{
		t = Date.now();
		fiber.run();

	}, 1000);

	Fiber.yield();

	console.log('async end');
	return t;
}

Fiber(function()
{
	var x = SomethingAsync();
	console.log(x);

	var y = SomethingAsync();
	console.log(y);

}).run();

console.log('done');








































