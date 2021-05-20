## Day One

Chapters 1 - 2

Well in this very first day I've read all the initial considerations and started to learn about one of the GLFW configurations, the rendering context. I also started to develop a simple application from chapter 2 example, a rotating triangle. I had some issues with it, the process of draw the triangle occurs without further problems, but the process of rotating the triangle have been very difficult, once the book is a little bit old and I am rewriting the example to GLFW and GLEW technologies it was already expected.

I'll spent tomorrow morning trying to fix it, otherwise I will just let it behind and try to fix it some other day.

Well I came back later and fixed the issues just by changing the triangle vertices values. In the original one I was using the entire screen values, such as half of screen width and screen height, and now it is using hard coded values between -1 and 1.

So tomorrow morning instead of try to fix it I'll try to understand why it wasn't working and develop a base project with mouse and keyboard input to make the next tasks easier to understand, debug and draw.

I am also considering starts to study the book "Foundations of Game Engine Development, Volume 1 Mathematics" at the same time to be more familiarized with 3D maths.

## Day Two

Chapter 2

Today I spent some time learning about full screen window and how to resize it. I also develop a base project to be used in other examples and exercises with mouse and keyboard input already working.

Reading the Full Screen section from the chapter 2 I tried to reproduce it in GLFW, so I've developed a Window class with some functions to resize and full screen the window, althought it's already developed it's not working directly in the code, so tomorrow morning I'll start by using the class instead of coding it inside main function. I'll also transform the entire class into a header to be imported from outside.

In the end of the chapter 2 it have some questions and exercises to do. I've answer all the questions about the chapter and complete the exercise, which was change the triangle's color and the background color, the last one through the glClearColor. Finishing this I've done with chapter 2.

## Day Three
