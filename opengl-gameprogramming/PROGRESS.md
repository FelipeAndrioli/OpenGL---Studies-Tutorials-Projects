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

What You Have Learned - Chapter 3

- You can query current settings from the OpenGL state machine by usint the glGet() and glIsEnabled() frunctions.

- Primitives are drawn by firts specifying the primitive type with the glBegin() function, then sending the vertices and following up with the glEnd() function.

- The glVertex() function specifies a vertex in a glBegin()/glEnd() block and is available in several variations that allow you to define the number of coordinates, the coordinates' data type, and whether the coordinates are being passed individually or as an array.

- You can draw points by passing GL_POINTS as the parameter to glBegin(), modify point size by using the glPointSize() function, turn point antialiasing on by passing GL_POINT_SMOOTH to glEnable(), and control the effect of distance on points with glPointParameter().

- Lines are drawn by passing GL_LINES as the parameter to glBegin(). You can modify line width with the glLineWidth() function, and line antialising is turned on by sending GL_LINE_SMOOTH to glEnable(). Line stippling is accomplished through the use of the glLineStipple() function.

- You can change the way OpenGL draw polygons by using the glPolygonMode() function. Passing GL_POINT forces OpenGL to draw only the vertices of polygons; GL_LINE forces OpenGL to draw the edges between polygon vertices as lines; GL_FILL is the default behaviour, which renders polygons with the interior filled and allows polygon smoothing and stippling.

- Passing GL_CULL_FACE to glEnable() tells OpenGL to enable its face culling mechanism. Using the glCullFace() function then allows you to specify which polygon side OpenGL should cull.

- By default, OpenGL treats vertices that are ordered counterclockwise in a polygon as the front face of the polygon, while the clockwise vertices are the back face. The glFrontFace() function allows you to modify this setting.

- Triangles are the most important polygon in 3D graphics as any polygon can be broken down into a set of triangles. You draw a triangle in OpenGL by passing GL_TRIANGLES to glBegin().

- You can draw a set of triangles more efficiently by passing GL_TRIANGLE_STRIP or GL_TRIANGLE_FAN to glBegin(). GL_TRIANGLE_STRIP draws a triangle strip, which creates a strip of triangles by combining vertices into sets of triplets. GL_TRIANGLE_FAN starts with the first vertex as the center vertex and draws the rest as a fan of vertices around the center.

- Quadrilaterals may also be drawn by passing GL_QUADS or QL_QUAD_TRIP to glBegin().

- n-sided convex polygons may be drawn by passing GL_POLYGON to glBegin().

- You can save and restore OpenGL state variables using the glPushAtrtrib() and glPopAttrib() functions.

### Review Questions

    1. How would you determine if OpenGL is drawing antialiased lines?
        A: Sending GL_LINE_SMOOTH to glEnable().
    2. How is culling enabled?
        A: Sending GL_CULL_FACE to glEnable().
    3. In what order does OpenGL draw vertices for a GL_TRIANGLE_STRIP?
        A: The front face of the polygon the order is counterclockwise, and the back face is clockwise.
    4. In what order does OpenGL draw vertices for a GL_TRIANGLE_FAN?
        A: The front face of the polygon the order is counterclockwise, and the back face is clockwise.
    5. What do the following variations of glVertex() mean?
        a. glVertex3f()
            A: Receives 3 coordinates values (x, y, z) as floats.
        b. glVertex2iv()
            A: Specifies a pointer to an array of two, three or four int elements.
        c. glVertex4d()
            A: Specifies x, y, z and w coordinates of a vertex, receiving double values.
        d. glVertex3fv()
            A: Specifies a pointer to an array of two, three or four float elements.
        e. glVertex2s()
            A: Specifies two short points, x and y.

### On Your Own

    1. You have been tasked to write a function that draws a 2D circle approximation with the option of drawing only the edge of the circle or drawing the circle filled at the world origin (0, 0, 0). Your function must accept the radius of the circle and a value for the number of edges in the circle approximation. Write a function to draw the circle approximation given the following prototype:

        void DrawCircleApproximation(float radius, int numberOfSides, bool edgeOnly);