// vmake.js

console.log("\nRunning VMake v.0.0.1");

debugger;

var cnf = process.argv[3].substr(3);
require("fs").readFile(cnf, function(e, buff)
{
	if(e)
	{
		console.log("");
		return e;
	}
	else
	{
		var config = JSON.parse(buff);

	}
});


process.argv.forEach(function(val, index, array)
{
  console.log(index + ': ' + val);
});


