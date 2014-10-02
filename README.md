EngineBase
==========

Game engine written in C++

Features:
--------

GameObject and Component based structure
Automated Memory management

Scene module:
-Transform parenting
-Tag and Layer support
-Multi-stage initialization
-Basic and Dynamic components for performance
-Component inheritance for custom scripting
	
Graphics module:
-Sprite and text rendering
-Multiple camera support
-Extendible renderers for custom drawing

Physics module (Box2D integration):
-Rigid bodies
-Supported colliders: Circle, Rectangle, Custom (by inheritance)
-Collision callbacks

Resource management - loading and releasing
-Textures
-Music and sounds
-Shaders
-Fonts
	
Input handling
-Mouse enter/leave callbacks for GameObjects
-Mouse click on GameObjects
-Custom shapes for GameObject-Mouse intersection

Watch pointer for nullable objects
Frame time measurement and scaling
Configuration file loading