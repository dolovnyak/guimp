# guimp

Part of functionality GIMP, written with our own ui library (libui)
--------
[Demo Video](https://youtu.be/U8Oa-Rer3aY)
###

## How work with libui:
In json, the user creates as many windows as he wants, manually assigning them id, position, size and events.

For each window, the user creates interface elements in the form of a tree: the basic element (canvas) is assigned as a parent to new elements, in turn, elements whose parent is canvas can also be set as parents for other elements, etc., after that we have a tree of interface elements.

This tree is rendered using bfs and each child layer overlaps parent layer (and user can controll overlap) 

For each element, the user sets its id, position, size, events, textures, parameters and the parent (if it's not a canvas).

User can hang functions (either standard or manually written by the user) on the element event (for example by pressing the left mouse button).

Element has parametrs - for example hidden, ignoring mouse, etc.

With the help of events and element parameters, you can achieve absolutely any prefabs of the interface, for example, a drop-down menu, if you set an event to one element, which will hide / show another element when clicked.
