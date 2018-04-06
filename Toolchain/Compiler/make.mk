var __global = this;

var isNodeJS = (typeof process !== 'undefined') && (process.release.name === 'node');

if(isNodeJS)
{
	if(!process.env.COCONODE_MODULE)
	{
		trace("ERROR: Missing COCONODE_MODULE environement variable.");
		return;
	}

	var Toolchain = process.argv[2];
	var Method = process.argv[3];
	var Command = process.argv[4];
	var Params = process.argv[5];

	__global.CocoNode = require(process.env.COCONODE_MODULE);
	__global.CocoNode.Compile(Toolchain, Method, Command, Params);
}
