# Computer Graphics CSCI 441

**NOTE: This is a live document and is subject to change throughout the
semester.**

Computer graphics is a field of computer science that involves generating visual
content.  Applications of computer graphics includes modeling and animation
software, CAD design software, image manipulation packages such as Photoshop or
Illustrator, video games, medical visualisation tools and much, much more. In
this class, we will cover some of the fundamentals of computer graphics; from
transformations and camera projections, to light and shading models, to
simulations that approximate phenomena in the real world. We will use C++, Qt
and OpenGL to explore practical, realtime, graphics programming while learning
the theory behind it so you can apply it to other environments.

## Assignments

Class will be a mix of lecture and in class lab assignments.  There will be many
lab assignments that are designed to give you a better understanding of the
topics taught in lecture. Code will be provided to get you up and running with
the labs. You may work in groups of two or three.  You must demo your labs to me
in class or office hours and push your code up to Bitbucket in a repository
you've shared with me prior to class on the due date.  There will also be a few
major programming assignments as well. The program assignments will take
significantly more time than the labs and are designed to inspire individual
creativity and self expression. I’ll try to keep lectures as short as possible
to give you time in class to work on your assignments with me available to ask
questions.  All assignments and other resources for the class will be made
available via Bitbucket:

https://bitbucket.org/msu-cs/csci440-spring2018

## Meeting Times

Tuesdays and Thursdays 15:05 - 16:20 in Barnard Hall 108.

## Instructor

David L. Millman, Ph.D.

**Office hours**

Tuesdays and Thursdays 16:30 - 17:30 or by appointment.  in EPS 359

## Textbook

Textbooks are optional but recommended

* [Fundamentals of Computer Graphics, 4th Edition](https://www.amazon.com/Fundamentals-Computer-Graphics-Fourth-Marschner/dp/1482229390),
(FoCG in recommended reading below).
* [OpenGL Programming Guide, 9th Edition](https://www.amazon.com/OpenGL-Programming-Guide-Official-Learning/dp/0134495497)
(referred to as GL Guide in recommended reading below).

## Online Resources

* [OpenGL Reference Pages](https://www.opengl.org/sdk/docs/man/)
* [Qt 5 Documentation](http://doc.qt.io/qt-5/)
* [C++ Documentation](http://www.cplusplus.com/doc/tutorial/)

## Class schedule

The lecture schedule is subject to change throughout the semester, but here is
the current plan. Assignments and due dates will be updated as they're assigned in class.

**TODO**

### January

| Date     | Description                                       | Assigned     | Due       | Recommended Reading               |
|----------|---------------------------------------------------|--------------|-----------|-----------------------------------|
| 1/11     | Intro - applications of computer graphics         |              |           |                                   |
| 1/16     | C++ overview / git basics                         | [Lab 0]()    |           |                                   |
| 1/18     | Overview of graphics pipeline                     |              |           |                                   |
| 1/23     | Rasterization / Barycentric coordinates / Color   | [Lab 1]()    | [Lab 0]() |                                   |
| 1/25     | OpenGL basics / 2D coordinate systems             |              |           |                                   |
| 1/30     | Graphics math - vectors and matrices              | [Lab 2]()    | [Lab 1]() |                                   |

### February

| Date     | Description                                               | Assigned     | Due       | Recommended Reading               |
|----------|-----------------------------------------------------------|--------------|-----------|-----------------------------------|
| 2/1      | Orthographic projection / OpenGL primitives               |              |           |                                   |
| 2/6      | Qt / OpenGL / C++ Lab Overview and Program 1 Assigment    | [Lab 3](), [Program 1]()||                                   |
| 2/8      | Lab day                                                   |              | [Lab 2]() |                                   |
| 2/13     | Model, View, Projection Matrices                          | [Lab 4]()    | [Lab 3]() |                                   |
| 2/15     | Transform Matrices - Translation, Rotation and Scale      |              |           |                                   |
| 2/20     | Perspective Projection and the Depth Buffer               |              |           |                                   |
| 2/22     | Lab day                                                   |              | [Lab 4]() |                                   |
| 2/27     | Virtual Trackball                                         | [Lab 5]()    | [Program 1]() |                               |

### March

| Date     | Description                                     | Assigned     | Due           | Recommended Reading |
|----------|-------------------------------------------------|--------------|---------------|---------------------|
| 3/1      | Lab Day                                         |              |               |                     |
| 3/6      | Materials and Lights                            | [Lab 6]()    | [Lab5]()      |                     |
| 3/8      | Midterm                                         | [Program 2]()|               |                     |
| 3/13     | Spring break - no class                         |              |               |                     |
| 3/15     | Spring break - no class                         |              |               |                     |
| 3/20     | Hierarchical Modeling                           |              | [Lab 6]()     |                     |
| 3/22     | OpenGL Element Arrays / Smooth vs Flat shading  |              |               |                     |
| 3/27     | TBA                                             | [Lab 7]()    |               |                     |
| 3/29     | Textures / Mipmaps                              |              |               |                     |

### April

| Date     | Description                                 | Assigned     | Due                          | Recommended Reading |
|----------|---------------------------------------------|--------------|------------------------------|---------------------|
| 4/3      | Animation basics                            | [Lab 8]()    | [Program 2](), [Lab 7]()     |                     |
| 4/5      | First person camera                         | [Program 3]()|                              |                     |
| 4/10     | Animating Orientation / Quaternions         | [Lab 9]()    | [Lab 8]()                    |                     |
| 4/12     | Bezier Curves                               |              |                              |                     |
| 4/17     | Blending                                    | [Lab 10]()   | [Lab 9]()                    |                     |
| 4/19     | Particle Systems                            |              |                              |                     |
| 4/24     | TBA                                         |              | [Lab 10]()                   |                     |
| 4/26     | TBA                                         |              | [Program 3]()                |                     |

### May

| Date     | Description                                 |
|----------|---------------------------------------------|
| 5/4      | Final - 12-1:50pm                           |


## Catalog Information

PREREQUISITE: M 221 and CSCI 232. High resolution computer graphics. 3D graphics
programming using a high level API. Vector mathematics for graphics. Graphics
primitives.  Curve and surface representations. Transformations using matrices
and quaternions.  Representing natural objects with particle systems and
fractals. Shading and lighting models.  Global illumination models. Color
representations.

## Course Offerings

At the end of the course, students should be able to
* Write basic graphical applications using OpenGL and C++
* Understand the modern graphics pipeline and how to leverage hardware to write
  realtime graphics applications
* Use vectors and matrices to transform geometry in 3D space
* Understand common shading and lighting models for displaying 3D models
* Use particle systems to simulate real world phenomena.

## Course Evaluation

* Labs 20%
* Programs 40%
* Midterm 20%
* Final 20%

## Discussion Board

Group discussions, questions and announcements will take place on
[Piazza](https://piazza.com/montana/spring2018/csci441/home). It is OK to send
me an email if you have a question that you feel is not appropriate to share
with the class.  If, however, you send me an email with a question for which the
response would be useful to the rest of the class, I will likely ask you to post
it to Piazza.

## Policy on Collaboration and Academic Misconduct

## Policy on Assignments

## Policy on Class Attendance

## Classroom Etiquette

Except for note taking and coding, please keep electronic devices off during
class, they can be distractions to other students. Disruptions to the class will
result in you being asked to leave the lecture and will negatively impact your
grade.

## Special needs information

If you have a documented disability for which you are or may be requesting an
accommodation(s), you are encouraged to contact your instructor and Disabled
Student Services as soon as possible.
