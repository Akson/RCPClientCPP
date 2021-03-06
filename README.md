C++ RemoteConsolePlus Client<br>
============

This is a C++ client for the "RemoteConsolePlus3" project (https://github.com/Akson/RemoteConsolePlus3).

<h3>Requirements:</h3>
<ol>
<li>Visual Studio 2013 <i>(Visual Studio 2012 should also work but it is not tested, 2010 will not work because C++11 is used in this project)</i></li>
<li>GIT</li>
</ol>

<h3>How to get it:</h3>
<ol>
<li>Decide where you want to put it. The easiest way, from an integration point of view, is to clone it to the folder where your solution (.sln) file is. I would reacommend to read this readme file completely to understand where to put it</li>
<li>Download it: "git clone --recursive https://github.com/Akson/RCPClientCPP.git"</li>
</ol>

<h3>How to build it:</h3>
<ol>
<li>Open the "RCPClientCPP\Project\RCPClientCPP.sln" solution<br>
<li>Select appropriate build configuration (Release/Debug and Static/Dynamic linking)</li>
<li>If you use something different from MSVS2013, you may want to change Platform Toolset</li>
<ol>
<li>Open Solution Explorer</li>
<li>Select all projects</li>
<li>Click on: Menu -> Project -> Properties</li>
<li>Select: Configuration Properties -> General</li>
<li>Select "All Configurations" in "Configuration" dropdown menu</li>
<li>Change Platform Toolset to an appropriate value</li>
</ol>
<li>Build the "RCPClient" project <i>(NOT an entire solution, if you build an entire solution, you'll get some errors because some test projects can be built with static/dynamic linking only)</i><br>
</ol>

<h3>How to test it:</h3>
<ol>
<li>Select dynamic linking configuration (Debug/Release)</li>
<li>Build and run the "RCPClientTest" project</li>
<li>Select static linking configuration (StaticDebug/StaticRelease)</li>
<li>Build and run the "RCPClientTestStatic" project</li>
<li>Build and run the "VariousTestsStatic" project</li>
</ol>

<h3>How to integrate it with your project:</h3>
<h4>Simplest way</h4>
<ol>
<li>Copy (or just download) "RCPClientCPP" project folder right next to your solution (.sln) file</li>
<li>Build the "RCPClient" project using both StaticDebug and StaticRelease configurations</li>
<li>Add "RCPClientCPPStatic.props" property sheet to your project properties
<ol>
<li>Open Property Manager</li>
<li>Right click on your project name</li>
<li>Add existing property sheet</li>
<li>Navigate to "<Your solution folder>\RCPClientCPP\Project\"</li>
<li>Select "RCPClientCPPStatic.props"</li>
</ol>
</li>
<li>Include "RCP.h" to your source files</li>
</ol>
<h4>Complicated way</h4>
If your are reading this, you probably already know how to use 3rd party libraries:)<br>
So you just need to know that:
<ol>
<li>Header files live in "RCPClientCPP\Include\"</li>
<li>Binaries (.dll) and libraries (.lib for both static and dynamic linking) live in "RCPClientCPP\Bin\"</li>
<ol>
