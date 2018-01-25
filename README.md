# Computer Graphics CSCI 441

**NOTE: This is a live document and is subject to change throughout the
semester.**

Computer graphics is a field of computer science that involves generating visual
content.  Applications of computer graphics includes modeling and animation
software, CAD design software, image manipulation packages such as Photoshop or
Illustrator, video games, medical visualisation tools and much, much more. In
this class, we will cover some of the fundamentals of computer graphics; from
transformations and camera projections, to light and shading models, to
simulations that approximate phenomena in the real world. We will use C++ and
OpenGL to explore practical, realtime, graphics programming while learning the
theory behind it so you can apply it to other environments.

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

https://bitbucket.org/msu-cs/csci441-spring2018

## Meeting Times

Tuesdays and Thursdays 15:05 - 16:20 in Barnard Hall 108.

## Instructor

David L. Millman, Ph.D.

**Email**: david.millman@montana.edu

**Office hours**: Mon 15:00 - 16:00 and Thurs 12:00 - 13:00

## Grader

Amy Peerlinck

**Email**: amy.peerlinch@student.montana.edu

## Textbook

Textbooks are optional but recommended

* [Fundamentals of Computer Graphics, 4th Edition](https://www.amazon.com/Fundamentals-Computer-Graphics-Fourth-Marschner/dp/1482229390),
(FoCG in recommended reading below).
* [OpenGL Programming Guide, 9th Edition](https://www.amazon.com/OpenGL-Programming-Guide-Official-Learning/dp/0134495497)
(referred to as GL Guide in recommended reading below).

## Online Resources

* [OpenGL Reference Pages](https://www.opengl.org/sdk/docs/man/)
* [Learn OpenGL Website](https://learnopengl.com/)(referred to as LoGL in recommended reading below)
* [C++ Documentation](http://www.cplusplus.com/doc/tutorial/)

## Class schedule

The lecture schedule is subject to change throughout the semester, but here is
the current plan. Assignments and due dates will be updated as they're assigned in class.

### January

| Date     | Description                                                                | Assigned                       | Due                               | Recommended Reading               |
|----------|----------------------------------------------------------------------------|--------------------------------|-----------------------------------|-----------------------------------|
| 1/11     | [Intro - applications of computer graphics](./notes/1-11.pdf)              | [Lab 0](./labs/lab0/README.md) |                                   | FoCG Chapter 1                    |
| 1/16     | C++ overview / git basics                                                  |                                |                                   |                                   |
| 1/18     | [Rasterization / Barycentric coordinates / Color](./notes/1-18.pdf)        | [Lab 1](./labs/lab1/README.md) | [Lab 0](./labs/lab0/README.md)    | FoCG 2.7.1, 3.3                   |
| 1/23     | [Barycentric coordinates](./notes/1-23.pdf)                                |                                |                                   | FoCG 8.1.2                        |
| 1/25     | Overview of graphics pipeline                                              | [Lab 2]()                      | [Lab 1](./labs/lab0/README.md)    | GL Chapter 1, LoGL "Hello Tri"    |
| 1/30     |                                                                            |                                |                                   |                                   |

### February

| Date     | Description                                               | Assigned                 | Due           | Recommended Reading               |
|----------|-----------------------------------------------------------|--------------------------|---------------|-----------------------------------|
| 2/1      |                                                           |                          |               |                                   |
| 2/6      |                                                           | [Lab 3](), [Program 1]() | [Lab 2]()     |                                   |
| 2/8      |                                                           |                          |               |                                   |
| 2/13     |                                                           | [Lab 4]()                | [Lab 3]()     |                                   |
| 2/15     |                                                           |                          |               |                                   |
| 2/20     |                                                           |                          |               |                                   |
| 2/22     |                                                           |                          | [Lab 4]()     |                                   |
| 2/27     |                                                           | [Lab 5]()                | [Program 1]() |                                   |

### March

| Date     | Description                                     | Assigned     | Due           | Recommended Reading |
|----------|-------------------------------------------------|--------------|---------------|---------------------|
| 3/1      |                                                 |              |               |                     |
| 3/6      |                                                 | [Lab 6]()    | [Lab5]()      |                     |
| 3/8      |                                                 | [Program 2]()|               |                     |
| 3/13     |                                                 |              |               |                     |
| 3/15     |                                                 |              |               |                     |
| 3/20     |                                                 |              | [Lab 6]()     |                     |
| 3/22     |                                                 |              |               |                     |
| 3/27     |                                                 | [Lab 7]()    |               |                     |
| 3/29     |                                                 |              |               |                     |

### April

| Date     | Description                                 | Assigned     | Due                          | Recommended Reading |
|----------|---------------------------------------------|--------------|------------------------------|---------------------|
| 4/3      |                                             | [Lab 8]()    | [Program 2](), [Lab 7]()     |                     |
| 4/5      |                                             | [Program 3]()|                              |                     |
| 4/10     |                                             | [Lab 9]()    | [Lab 8]()                    |                     |
| 4/12     |                                             |              |                              |                     |
| 4/17     |                                             | [Lab 10]()   | [Lab 9]()                    |                     |
| 4/19     |                                             |              |                              |                     |
| 4/24     |                                             |              | [Lab 10]()                   |                     |
| 4/26     |                                             |              | [Program 3]()                |                     |

### May

| Date     | Description                                 |
|----------|---------------------------------------------|
| 5/4      | Final - 12-1:50pm                           |


###

Potential Upcoming topics:
- OpenGL basics / 2D coordinate systems
- Graphics math - vectors and matrices
- Orthographic projection
- OpenGL
- Model, View, Projection Matrices
- Transform Matrices - Translation, Rotation and Scale
- Perspective Projection and the Depth Buffer
- Virtual Trackball
- Materials and Lights
- Hierarchical Modeling
- OpenGL Element Arrays
- Smooth vs Flat shading
- Textures / Mipmaps
- Animation basics
- First person camera
- Animating Orientation / Quaternions
- Bezier Curves
- Blending
- Particle Systems

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

* Participation 5%
* Labs 20%
* Programs 40%
* Midterm 15%
* Final 20%

## Discussion Board

Group discussions, questions, and announcements will take place using
Brightspace.  It is OK to send me an email if you have a question that you feel
is not appropriate to share with the class.  If, however, you send me an email
with a question for which the response would be useful to the rest of the class,
I will likely ask you to post it.

## Policy on Collaboration and Academic Misconduct

Collaboration IS encouraged, however, all submitted individual work must be your
own and you must acknowledge your collaborators at the beginning of the
submission.

On any group project, every team member is expected to make a substantial
contribution. The distribution of the work, however, is up to the team.

A few specifics for the assignments.  You may:

* Work with the other people on your team.
* Share ideas with other teams.
* Help other teams debug their code.

You may NOT:

* Share code that you wrote with other teams.
* Submit code that someone on your team did not write.
* Modify another's code and claim it as your own.

Using resources in addition to the course materials is encouraged. But, be sure
to properly cite additional resources. Remember, it is NEVER acceptable to pass
others work off as your own.

Paraphrasing or quoting another’s work without citing the source is a form of
academic misconduct. Even inadvertent or unintentional misuse or appropriation
of another’s work (such as relying heavily on source material that is not
acknowledged) is considered plagiarism. If you have any questions about using
and citing sources, you are expected to ask for clarification. My rule of thumb
is if I am in doubt, I cite.

By participating in this class, you agree to abide by the [student code of
conduct](http://www.montana.edu/policy/student_conduct/).  Please review the
policy.

## Policy on Assignments

All assignments must be submitted by the start of class on the due date. Late
assignments will not be accepted.

For descriptive assignments and reports, the submission should be typed up and
submitted as a PDF (LaTeX suggested but not required). For code assignments,
well organized source code with clear comments should be submitted.

## Policy on Class Attendance

Class attendance is required. If a student must miss a class, please notify me
as soon as possible. Note that class participation is part of your final grade.
If you do not show up you cannot participate.

## Classroom Etiquette

Except for note taking and coding, please keep electronic devices off during
class, they can be distractions to other students. Disruptions to the class will
result in you being asked to leave the lecture and will negatively impact your
grade.

## Special needs information

If you have a documented disability for which you are or may be requesting an
accommodation(s), you are encouraged to contact me and Disabled
Student Services as soon as possible.
