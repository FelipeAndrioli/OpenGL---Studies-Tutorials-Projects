# Beginning OpenGL Game Programming

This directory is from my studies from the book Beginning OpenGL Game Programming. It will contains book examples, exercises and a day to day progress.

## TODO's

    - Create a base project to use in other examples and exercises
        - Mouse input
        - Keyboard input

## Day One

Chapters 1 - 2

Well in this very first day I've read all the initial considerations and started to learn about one of the GLFW configurations, the rendering context. I also started to develop a simple application from chapter 2 example, a rotating triangle. I had some issues with it, the process of draw the triangle occurs without further problems, but the process of rotating the triangle have been very difficult, once the book is a little bit old and I am rewriting the example to GLFW and GLEW technologies it was already expected.

I'll spent tomorrow morning trying to fix it, otherwise I will just let it behind and try to fix it some other day.

Well I came back later and fixed the issues just by changing the triangle vertices values. In the original one I was using the entire screen values, such as half of screen width and screen height, and now it is using hard coded values between -1 and 1.

So tomorrow morning instead of try to fix it I'll try to understand why it wasn't working and develop a base project with mouse and keyboard input to make the next tasks easier to understand, debug and draw.

I am also considering starts to study the book "Foundations of Game Engine Development, Volume 1 Mathematics" at the same time to be more familiarized with 3D maths.

## Day Two