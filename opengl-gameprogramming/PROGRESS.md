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

Chapter 3

So today I've started the chapter 3 and it already starts giving me some trouble. Following a example from the book, I find out that my y axis looks to be inverted or not working properly. The first evidence I have from this is my click output, it suppose to show me the cursor position to make the draw task easier, but instead of 100 for example it's showing up 500, which is the screen height less the 100 that it was suppose to be showed. 

I am going to stop for today, I'm pretty tired, but for tomorrow I need to fix it, otherwise all the book examples will need to be even more reworked.

## Day Four

Chapter 3

Well, today I started fixing the y axis that look to be inverted to me. Using the function to get the mouse position, the x axis looks correct, from left to right, and 0 to max, but the y axis was being from top to bottom, zero to max, which doesn't make sense, once I was drawing and my draws are getting inverted becauses seens to be only inverted when getting the cursor position, and in the draw the y axis value seens correct, from bottom to top, zero to max. To fix it I just subtract the give value from the total height of the window. It can cause a mess if it is just some window configuration, so I put the left mouse click as the subtracted value and right mouse click as the original function output.

So once I've decided to not get stuck into boring questions, I decided to move up even not reproducing the stippled line example, it doesn't show any error but it also doesn't stipple the line.

By the end of the day I was able to reach the end of the chapter, however we've found an very interesting example wich hold me and due to this I wasn't able to finish the chapter. The example is an application with 6 grids on it, each one with its own primitive. So with the rest of the day I'll start it and finish it tomorrow by morning.

## Day Five

Chapter 3

Today I've started to reproduce the drid draws example from the chapter, for practice and for a better understanding of grid system, draw system and the coordinate system from OpenGL. 

The first grid draw was fine, the points grid, but the second one is out of position when I've tried to put it aside the first grid draw. So I've decided to draw all the grid examples in the same position, commenting the past draws to move forward faster but have to face another problem.

Some grids should not be filled, like the square grid or the triangle strip grid, once their are filled it's just transform into a giant square. It should be just some configuration, but it'll require some documentation research.

So from today I've finished with two main issues, the position of the grids except the first one and how to not fill some primitives.

I am acumulating all this issues to take at least one day in the week just to solve them, probably friday to saturday, otherwise I am going to stay stucked for too long and will not progride in the book.

## Day Six

Chapter 3

Well, today I've decided to move forward from the examples to do some progress in chapter 3, I'm going to answer the final questions and do the final chapter exercise.

By the end of the day I've finished the On Your Own section of the chapter, but I'm feeling itsn't right. I mean, to draw the edge circles I've used the OpenGL primitive GL_LINE_STRIP, and to draw the filled circle I've used the OpenGL primitive GL_TRIANGLE_FAN. I'd like to find out a way to draw only the edges of the GL_TRIANGLE_STRIP, it's on TODO's list.

Tomorrow it's gonna be the day to fix some of the TODO's issues.

## Day Seven

Fixing Issues

The first issue I fixed was the draw function, it was inside the window header, so I've decided to create a new header, exclusive to draw.

The second issue was the cursor, once the cursor I was using were a square and it was not that intuitive about where I was clicking at, so I've added the default windows cursor. After I did this, I decided to split the function that was creating the cursor, one to create a default cursor and the other to create a standard cursor.

The third issue I fixed was the nvidia logo stucking into full screen. I had to reformulate the entire Window class to make it more simple and functional, but is not ready yet, I need to read the GLFW Window properties and events documentation and finish it later in another issue.