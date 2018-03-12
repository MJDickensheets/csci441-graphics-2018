# "Simple Modeler"
## Program 1
## Computer Graphics
## CSCI 441, Spring 2018

# Due Date: March 12, 2018 at 5:59 AM

Table of Contents
=================

  * [Instructions]
    * [Modes]
      * [View]
      * [Edit]
        * [Stamp]
        * [User Defined Primitive]
        * [Group]
        * [Modify]
  * [Write-Up]

# Instructions
All of the commands in this program are either performed through the command line or through direct interaction with the screen. Information and prompts appear on the command line.

# Modes
There are two modes, view and edit. By clicking on the display window and pressing the 'v' button, you can toggle between modes. The program starts in view mode.

# View
In the view mode, you can move around the viewport by clicking and dragging the screen. You can also zoom in or out using the '=' or '-' buttons, respectively.

# Edit
In the edit mode, you can access submodes to add shapes, group shapes and modify shapes.

# Stamp
The stamp submode has several options for adding primitive shapes. First click on the window and press "t" to add a triangle, "s" to add a square, or "c" to add a circle. You will then be prompted at the command line to enter an rgb value in the range 0-1. You will then select the location for the shape by clicking the desired location on the display window. Afterwards you will be prompted to give values for scale and rotation.

# User Defined Primitive
To create a user defined primitive, click the window and press "u". The user defined primitive mode is much like the stamp mode in terms of operation. However, after choosing the location for the primitive, you will be prompted to click the screen several times to add the vertices for the primitive. **The edges for your primitive must be centered around the center of the screen (point 0,0) for the primitive to render properly!** Afterwards you will see the same prompt for scale and rotation values.

# Group
The group mode is accessed by clicking the window and pressing "g". You will then see a list of possible shapes to group on the command line. Type the shape name **exactly** and press enter to add it to the group. When you have finished, type "end" and press enter. If there is already a group, you will be asked whether or not you would like to ungroup it. Type 'y' to ungroup, or 'n' to cancel.

# Modify
The modify function is accessed by clicking the window and pressing "m". If a group exists, you can modify the whole group by typing "y" when prompted. Otherwise you will be able to modify a single shape by typing the shape name in the displayed list. At this point you will be able to specify the origin of transformation by clicking the desired point in the display window. Next, you can select the type of modification you would like by typing in the command line 's' for scale, 'r' for rotate, 't' for translate and 'c' for color change. Each option will prompt you for input, similar to the input when creating primitives.

# Writeup
The image I created showcases the different possibilities of the program that I created. Each of the primitives as well as a user created shape are displayed. The center piece, the yin yang, is a more complex shape composed of several primitives. I personally like the image because it displays the different transformations on the shapes and there are few things more soothing than an MS-Paint 'esque yin yang. It also has lots of interesting angles and layers which are fun to experiment with. By framing the yin yang with other shapes, we can really feel the idea of complexity being built from simplicity, which is a thought-worthy concept for a programmer. I'd like to use the symbol in future projects.
