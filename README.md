# TBAGame
<p>The project has no name currently. I hope this screams out that I know what I want to do. This project is technically a two-three in one. It is a graphics library, graphical user interface, and the third can be anything else.</p>
<h1>How to Setup Workspace</h1>
<p>Ensure you create a development branch for your changes. Master will be the fall back branch if something breaks. Follow the steps below once you've pulled the branch and created a remote branch on your computer: </p>
<ol>
  <li>Run command sudo apt-get update</li>
  <li>Run command sudo apt-get upgrade</li>
  <li>Run command sudo apt-get make</li>
  <li>Run command sudo apt-get install gcc-mingw-w64-x86-64 g++-mingw-w64-x86-64 wine64 </li>
  <li>On the terminal CD into the src directory</li>
  <li>On the terminal run make</li>
  <li>That's it! If there are no issues with the code, this should build every file automatically</li>
</ol>
<h1>TODO</h1>
<p>There is lots to do but here is a quick run down of what is needed.</p>
<ol>
  <li>Create different shaders</li>
  <li>Create a caching system for shaders</li>
  <li>Create a font renderer (Crucial)</li>
  <li>Create abstraction for event polling (ie. Mouse clicks etc)</li>
  <li>Creating the GUI library</li>
</ol>
<h1>How to use graphics library</h1>
<p>There is a lot to really learn from OpenGL, so this will be a quick rundown.</p>
<p>Vertex Buffer Object or VBO: This is a big blob of memory that contains our data for a shape. For example when creating a square a VBO would contain <x,y,z> coordinartes and an RGB value for each square within the VBO</p>
<p>Vertex Attribute Object or VAO: This object is used to interpret the VBO. Without it the computer would not understand what the hell our VBO is. It would just be memory. The above VBO would be described as follows in a VAO, 3 floats for <x,y,z> coordinates and 4 8-bit values for RGB.</p>
<p>Index Buffer Object or IBO: This allows the computer to differentiate when the shapes we are drawing should be two separate shapes. Otherwise, if we wanted to draw to squares, without an IBO we would get 1 giant weird square.</p>
<p>Batch Buffer: This is an original created class. It essentially abstracts the creation of a VAO, VBO, and IBO (may add shaders later.) This means that all you need to do is create a Batch Buffer object and call it's draw call. No other setup necessary!</p>
<p>With the current graphics library, setting up a window should be rather easy. Simply call the constructor for our RenderWindow class and call these two functions in this order: RenderWindow::clear() and RenderWindow::display(). Ensure you are using an infinite loop to keep the window rendered. When drawing shapes you would creaate a VBO, VAO, IBO, and Shader for each shape or opt for the BatchBuffer class.</p>
