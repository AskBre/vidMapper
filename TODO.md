##############
#### BUGS ####
##############

'FIXED' The warper-edge is also masked out

'FIXED' When going back to mask edit mode, everything's black

'FIXED' When going to mask edit after mask creation, it disappears.

'FIXED' When resetting mask, everything goes black

'FIXED' When going to mask creation mode after mask is created, nothing is showed.

'FIXED!!!' Why the fuck doesn't the great openGL-masking work?

'FIXED' There are two squares around the warps now - one seemes to be inside the warp itself

'Fixed' The line around the warps doesn't actually follow the image

##############
#### TODO ####
##############

Need a way to be able to reset either the mask or the warper
	Maybe even go back one notch in warper editing too.

'DONE' Create classes out of both warper and masker

'DONE' Possibly figure out how to circumvent not having to call warper.draw() and masker.draw() all the time

'DONE' Separate public and private variables and functions in warper and maskCreator

'FIXED' Figure out a nice interface!
        Press the number button once to select a screen
	'w': Edit the warp
	'm': Enable mask creation mode
	        Left click to add vertex
	        Right click to pop back
	        Double click to finish and go to mask edit mode
		Right click on vertices to delete them
	        'm' again to go back to mask creation mode
        Change the color to reflect what mode I'm in

# For Warper
#################

Need a way to toggle whether it should maintain the aspect ratio or not

'DONE' Save all the positions!

'DONE' Save warper coordinates on exit?

'DONE' Deactivate all the warpers not in use

'DONE' Prettify the code, creating functions and stuff

Colorize the square around the warps?
        Indivudual colors for each warper
        Have to go into ofxGLWarper's source code I believe

'DONE' Flash screen on save

Be able to move the whole screen

'DONE' Mask the warps!
        Mask with vertex

'DONE' Create a function which automagically goes through the data-folder
	        Add a new warper for each new folder with .png's in them
	        Videoify the .png-sequences

Add a reset button
        For individual warps
        Maybe use VIM-style <num>+"r"?


# For Masker
#################

'DONE' One mask per warper!

'DONE' Disable editing when no screen is selected

'DONE' Draw a line, then connect everything on double click

'DONE' Add a dot as the first mousePress

'DONE' Be able to edit the individual vertices postcreation

Double click when not in creation mode to add a vertex
        Add it between the two closest, connected vertices

'DONE' Prettify the code with functions

Make the circles pop up organically and fancy (animation)

'DONE' Right click on vertex in view mode to delete vertex

Save and load the shape!
        Can link it to the same as warper
        Press 's' and save everything
        Press 'l' and load everything
        No reason to save individually, is it?
