<html><head>
    <meta charset="utf-8">

    <title>Coconut2D</title>

	<meta name="author" content="mobileFX">
	<meta name="copyright" content="mobileFX, Copyright (c) 2015">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">

	<!-- Icons -->
	<link rel="shortcut icon" href="favicon.ico">
	<link rel="apple-touch-icon" href="apple-touch-icon-114x114.png">
	<link rel="apple-touch-icon" sizes="72x72" href="apple-touch-icon-72x72.png">
	<link rel="apple-touch-icon" sizes="114x114" href="apple-touch-icon-114x114.png">
	<link rel="apple-touch-icon" sizes="144x144" href="apple-touch-icon-144x144.png">
	<link rel="apple-touch-icon-precomposed" href="apple-touch-icon-114x114.png">

	<!-- for Google -->
	<meta name="application-name" content="Coconut2D">
	<meta name="keywords" content="$(PAGE_KEYWORDS)">
	<meta name="description" content="$(PAGE_DESCRIPTION)&gt;">

	<!-- for Facebook -->
	<meta property="fb:app_id" content="294194444062993">
	<meta property="og:type" content="article">
	<meta property="og:title" content="$(PAGE_TITLE)">
	<meta property="og:image" content="$(PAGE_IMAGE)">
	<meta property="og:url" content="$(PAGE_URL)">
	<meta property="og:description" content="$(PAGE_DESCRIPTION)">

	<!-- for Twitter -->
	<meta name="twitter:card" content="summary">
	<meta name="twitter:title" content="$(PAGE_TITLE)">
	<meta name="twitter:image" content="$(PAGE_IMAGE)">
	<meta name="twitter:description" content="$(PAGE_DESCRIPTION)">

	<!-- CSS  -->
	<link rel="stylesheet" type="text/css" href="css/bootstrap.css">
	<link rel="stylesheet" type="text/css" href="http://fonts.googleapis.com/css?family=Open+Sans:300,400,600,700,800|Shadows+Into+Light">
    <link rel="stylesheet" type="text/css" href="https://fonts.googleapis.com/css?family=Chivo:900">

	<link rel="stylesheet" type="text/css" href="css/css.css">
</head>

<body>

<div style="width:620px">

<h1>1. The Coconut 2D Project idea</h1>
<p>Coconut2D is a software project for creating HTML5, iOS, Android and PC games
that your really design and code once, and play everywhere!</p>
<p><img src="./img/Process.png" alt="Process" style="max-width:100%;"></p>
<p>This GitHub Repository contains the Open Source <strong>Coconut2D SDK</strong>,
which is the Toolchain and Core Frameworks of Coconut2D project. Please note that
this repository does not contain Coconut2D Studio IDE which is a commercial product
(or at least will be when we manage to finish it :)</p>
<h1>2. Coconut2D SDK Architecture</h1>
<p>Coconut2D virtualizes the <strong>HTML5 Canvas</strong> and uses <strong>Object
Oriented JavaScript</strong> as the single code-base language. Developers can write
and debug their games in Object Oriented JavaScript against the virtual HTML5 Canvas
using Coconut2D Studio IDE.</p>
<p>Once a games is ready for release, it can be compiled to <strong>HTML5 and ECMA
JavaScript</strong> code, as well as <strong>Native C++11</strong> code for iOS,
Android and x86 apps. We developed a state of the art open source compiler, that
generates cross-browser ECMA JavaScript and portable C++11 code from Object Oriented
JavaScript source code.</p>
<p><img src="./img/Architecture.jpg" alt="Architecture" style="max-width:100%;"></p>
<h2>2.1. Coconut2D Frameworks</h2>
<p>We encapsulated all <strong>Core Frameworks</strong>, such as <strong>Animations</strong>,
<strong>2D Game Engine</strong>, <strong>User Interface</strong>, <strong>Networking</strong>,
etc. inside a <strong>Common Runtime Layer (CRL)</strong> also written in Object
Oriented JavaScript.</p>
<table>
	<thead>
		<tr>
			<th>Framework</th>
			<th>Description</th>
		</tr>
	</thead>
	<tbody><tr>
		<td>org.coconut2d.sdk.anim</td>
		<td>Core Animations Framework, implements <code>Game Engine</code>.</td>
	</tr>
	<tr>
		<td>org.coconut2d.sdk.ui</td>
		<td>User Interface Framework, implements Controls, Buttons, Forms, etc.</td>
	</tr>
	<tr>
		<td>org.coconut2d.sdk.game2d</td>
		<td>2D Games Framework, implements Sprite, TiledLayer, Parallax Layers,
		etc.</td>
	</tr>
	<tr>
		<td>org.coconut2d.sdk.html5</td>
		<td>HTML5 Emulation Framework (Window, Document, Elements, Events)</td>
	</tr>
	<tr>
		<td>org.coconut2d.sdk.webgl</td>
		<td>HTML5 WebGL Emulation Framework, implements WebGL Context.</td>
	</tr>
	<tr>
		<td>org.coconut2d.sdk.net</td>
		<td>Networking Framework (XMLHttp, Facebook, Twitter, etc.)</td>
	</tr>
	<tr>
		<td>org.coconut2d.sdk.server</td>
		<td>node.js Server Side Framework, implements basic HTTP Server.</td>
	</tr>
	<tr>
		<td>org.coconut2d.sdk.tests</td>
		<td>General Purpose Testing Framework.</td>
	</tr>
	<tr>
		<td>org.emscripten.box2d</td>
		<td>Emscripten derived Box2D Physics Framework (compiled from C++)</td>
	</tr>
</tbody></table>
<h2>2.2. Coconut2D Layering</h2>
<p><img src="./img/Layering.jpg" alt="Layering" style="max-width:100%;"></p>
<h2>2.3. 2D Game Engine</h2>
<p><strong>Coconut2D Game Engine</strong> is a <strong>Finite State Machine Automaton</strong>
controlled by a new programming entity called <strong>State</strong>. States define
a singularity in the execution context of Game Loop, they have explicit <strong>
enter</strong> and <strong>exit</strong> points and they offer distinction between
<strong>tick</strong> and <strong>paint</strong>.</p>
<p>To unify Native and HTML5 worlds under a single API while getting the best performance
every time, we designed a set of <strong>Native Device Wrappers</strong> that virtualize
the <strong>HTML5 Canvas</strong> across desktop, tablet, mobile and other devices.</p>
<h1>3. Technologies</h1>
<h2>3.1. Renderering Engines</h2>
<p>Coconut2D core rendering engine is OpenGL ES2 but we have implemented special
renderers for WebGL, CanvasRenderingContext2D and CSS3 for supporting Mobile HTML5
Browsers.</p>
<h2>3.2. Integrating with Emscripten</h2>
<p>Especially for HTML5, a game can also be compiled to C++ and post-compiled with
<strong>Emscripten</strong> to JavaScript byte code. Compiled JavaScript can be
up to x10 times faster than "regular" handwritten JavaScript and runs on all browsers.</p>
<p>Emscripten is a C++ to JavaScript compiler developed by Alon Zakai (Kripken).
Coconut2D uses Emscripten both for binding 3rd party C++ libraries (such as Box2D
Physics) with generated ECMA JavaScript code, and also for post-compiling and optimizing
a game for HTML5 Browsers.</p>
<h2>3.3. Compiling iOS Apps on Windows</h2>
<p>Coconut2D Studio IDE is capable of compiling C++11 code directly into a native
iOS, Android and x86 applications. Especially for iOS apps, they are trully compiled
on Windows, using a special port of the LLVM compiler developed by Pierre-Marie
Baty; that is the same compiler Apple uses in XCode. iOS compilation process of
Coconut2D Studio also code signs your apps with your official developer certificate.</p>
<h2>3.4. Object Oriented JavaScript</h2>
<img src="./img/CocoScript.png" alt="CocoScript" style="max-width:100%;">
<p><img src="./img/CocoScriptCode.png" alt="CocoScriptCode" style="max-width:100%;"></p>
<p>Language Features:</p>
<ul class="task-list">
	<li>Real Classes as first-class citizens</li>
	<li>Constructor with constructor arguments and inline base class initialization</li>
	<li>Destructor (invoked on delete)</li>
	<li>Public, Private, Protected Access Modifiers</li>
	<li>Published Access Modififer for Design-Time binding</li>
	<li>Abstract Functions </li>
	<li>Static Functions and Fields</li>
	<li>Virtual Functions and base class access with super keyword</li>
	<li>Function Overloads</li>
	<li>Constants and Enums</li>
	<li>Properties (setter, getter)</li>
	<li>Events Registration and Notification System</li>
	<li>Interfaces and implements keyword</li>
	<li>Structs (with super fast instantiation)</li>
	<li>States (for Game Loop FSM)</li>
	<li>Class and Interface Inheritance Model</li>
	<li>Class Delegation Model</li>
	<li>Strong Type System</li>
	<li>Explicit Integer, Float, Time, String, Boolean and Date datatypes</li>
	<li>Stream and DataStream datatype</li>
	<li>Typed Arrays and Arrays of Objects</li>
	<li>Conditional Compilation and Compiler Directives (eg. #ifdef BOX_2D )</li>
	<li>Export of Debug Symbol Tables for real Debugging</li>
	<li>Export of Code Symbols for IntelliSyntax Editing</li>
	<li>Export of State Machine and Class Diagrams</li>
	<li>Compiles to ECMA JavaScript cross-browser code</li>
	<li>Compiles to C++11 Portable Code</li>
</ul>
<p>We also developed <strong>CocoPlayer</strong>, a Simulator powered by <strong>
Google V8 JavaScript VM Engine</strong> where developers can test, debug and profile
their games and apps. CocoPlayer is capable of simulating various screen resolutions
taking into account the different dpi of numerous iOS and Android devices. The full-fledged
Object Oriented JavaScript Debugger is one of Coconut2D Studio's unique features!</p>
<h1>4. Work in Progress</h1>
<p><img src="./img/WIP.png" alt="WIP" style="max-width:100%;"></p>
<h1>5. Sample Games</h1>
<p><img src="./img/Game1.png" alt="Sample" style="max-width:100%;"></p>
<p><img src="./img/Game2.png" alt="Sample" style="max-width:100%;"></p>
<p><img src="./img/Game3.png" alt="Sample" style="max-width:100%;"></p>
<p><img src="./img/Game4.png" alt="Sample" style="max-width:100%;"></p>
<h1>6. Credits</h1>
<h2>6.1. Authors</h2>
<ul class="task-list">
	<li>Elias G. Politakis (<a href="mailto:epolitakis@mobilefx.com">epolitakis@mobilefx.com</a>)</li>
	<li>George Mathioudakis (<a href="mailto:YiamiYo@mobilefx.com">YiamiYo@mobilefx.com</a>)</li>
</ul>
<h2>6.2. Coconut2D Team </h2>
<p><img src="./img/CocoTeam1.jpg" alt="CocoTeam" style="max-width:100%;"></p>
<p><img src="./img/CocoTeam2.png" alt="CocoTeam" style="max-width:100%;"></p>
<ul class="task-list">
	<li>Lina Kalostipi (Coconut2D Commercial Product Manager)</li>
	<li>Elias G. Politakis (Architect)</li>
	<li>George Mathioudakis (Lead Developer)</li>
	<li>Irida Kalostipi (Sample Games Programmer)</li>
	<li>Despina Leonti (Illustrator - Sample Games Designer)</li>
	<li>Sakis Garnelis (Animator - Concept Designer)</li>
</ul>
<h2>6.3. Coconut2D Video</h2>
<p><img src="./img/Designer_1920x960.png" alt="Coconut2D Technology" style="max-width:100%;"></p>
<h2>6.4. Coconut2D on Social Media</h2>
<p><img src="./img/facebook.png" alt="facebook" style="max-width:100%;"></p>
<p><img src="./img/twitter.png" alt="twitter" style="max-width:100%;"></p>
<h2>6.5. Contribute / Donate</h2>
<p>If this project is useful for you, you can help us sustain it either by contributing
or by donating with Paypal.</p>
<p><img src="./img/donate.png" style="max-width:100%;"></p>

</div>

</body></html>