Here is a hint to integrate Node.js with IIS7 on a Windows 64-bit Server. The following hint also solves some poor performance issues with iisnode and demonstrates how to use Node.js Native Extensions as well.

**Summary:**

> Create a new **Unmanaged Integrated 32-bit Application Pool**
> dedicated for node.js. No other applications should use this pool.

This works for 64-bit as well but some node.js Native Extensions such as Coconut2D require 32-bit because of SQLite wrapping. If you are not using Native Extensions then you can go 64-bit all the way!

1. Download: `iisnode-core-iis7-v0.1.19.0-x64.msi`.

2. Install it using this command: `msiexec /i iisnode-core-iis7-v0.1.19.0-x64.msi WOW=1`. This will install the 32-bit version of iisnode on a 64-bit machine. Note that `iisnode.dll` will be installed in `C:\Program Files (x86)\iisnode\iisnode.dll`.

3. Download the 32-bit version of node.js (eg. `node-v0.12.0-x86.msi`) and install it in `C:\nodejs`

4. Create a new Application Pool

    <pre>
    Name: node.js
    Managed pipeline mode: Integrated
    </pre>

    <pre>
    .NET Framework Version: No Managed Code
    Enable 32-Bit Applications: True
    Identity: administrator
    </pre>

5. Assuming your **Node.js Server Script** file is `node.js`. Go the the web folder and create file `node_start.cmd`. In the command file you should change the current path to your `wwwroot` and start node.js with your `node.js` file. You should use double quoted paths.

    <pre>
    C:
    cd "C:\HostingSpaces\...\wwwroot"
    "C:\nodejs\node.exe" "C:\HostingSpaces\...\wwwroot\node.js"
    </pre>

5. In your `node.js` make sure you have `process.env.PORT`

    <pre>
    var http = require('http');
    http.createServer(function (req, res) {
      	... your code here ...
    }).listen(process.env.PORT);
    </pre>

6. *(Optional)* If you are using any node.js **Native Extensions** such as Coconut2D, SQLite, Cairo or WebKit modules, you must copy the `*.node` files and DLLs in your `wwwroot\node_modules` folder. Make sure you also set NTFS security to allow execution of those files or elevate the Application Pool to impersonate the Administrator. To load the native extensions use `require()` as shown below.

    <pre>
    var http = require('http');
    var Coconut2D = require("Coconut2D.node");
    http.createServer(function (req, res) {
      	... your code here ...
    }).listen(process.env.PORT);
    </pre>

7. Place the following `web.config` in your web root (eg. `C:\HostingSpaces\...\wwwroot`). This will enable IIS7 to process any **non-node** files such as images, static html files and xml files, and let node.js handle only its own **server-side scripts**.

 > Having IIS handling static files and running server-side scripts on
> node.js side-by-side is a highly recommended practice and really boosts the
> performance of your web sites.

 In this example I am handling `.asp` files with `iisnode` by using a Rewrite Rule. Replace `*.asp*` with your node.js server script extension (eg. `*.njs*`). Note that there is not a root slash in the wildcard pattern; this is important as well as the last `*` at the end of the pattern.

<!-- language: lang-xml -->

    <?xml version="1.0" encoding="utf-8"?>
    <configuration>
      <system.webServer>
        <handlers>
          <add name="iisnode" path="node.js" verb="*" modules="iisnode" />
        </handlers>
    	<iisnode nodeProcessCommandLine="&quot;C:\...\start_node.cmd&quot;" />
        <defaultDocument>
          <files>
            <remove value="index.php" />
            <remove value="default.aspx" />
            <remove value="iisstart.htm" />
            <remove value="index.html" />
            <remove value="index.htm" />
            <remove value="Default.htm" />
          </files>
        </defaultDocument>
        <httpProtocol>
          <customHeaders>
            <remove name="X-Powered-By" />
          </customHeaders>
        </httpProtocol>
        <rewrite>
          <rules>
            <rule name="CavoBoutique" patternSyntax="Wildcard">
              <match url="*.asp*" />
              <action type="Rewrite" url="node.js" logRewrittenUrl="true" />
            </rule>
          </rules>
        </rewrite>
      </system.webServer>
    </configuration>
    </code>

<!-- language: lang-xml -->
