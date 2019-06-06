# Readme

I've always wanted to write a Sudoku solver and this was a great excuse to do some work in C++. This blog post is part 1 of a series on automatically solving Sudoku puzzles where we build a solver. Part 2 is focused on building an automated system to scan a Sudoku puzzle in a newspaper, feed it to our solver, and send the solved (or unsolved) puzzle back.

## Part 1: The Solver

The solver first generates lists of possible solutions. It then goes through two steps of solving the puzzle. First, it "prunes" solutions from the puzzle by meeting the three constraints of sudoku:

1) Each row contains the numbers 1 through 9,
2) Each column contains the numbers 1 through 9, and
3) Each "box" contains the numbers 1 through 9.

After pruning away impossibilities, the solver finds cells that only have one possible answer. It fills in the cell with that answer, removes that possiblity from the solution lists of the corresponding row, column, and box

## Part 2: Computer Vision Input System

### Easy: Picture Lined Up With Photo Edges

[Open CV](http://aishack.in/tutorials/sudoku-grabber-opencv-plot/)

Idea: assume the corners of the image are the square corners of the puzzle box. Then:

- Pre-process the entire image for tesseract recognition.
- Divide the puzzle into a grid of 9 by 9 images of numbers
- Run each of these 81 images through tesseract to recognize the characters
- Add these numbers to a text file and feed it to the solver as before


## Harder example: based on https://stackoverflow.com/questions/48954246/find-sudoku-grid-using-opencv-and-python. 


I started following the steps from the article above to recognize grid lines in a slanted sudoky image. I created some Jupyter notebooks to explore some topics:

	- Downsampling with Pyrup
	- Averaging, blurring, edge detection
	- Edge Detection
	- Hough Line Transform

I noticed:
	
	- Median filtering looked great for filtering out bad noise.
	- Bilateral filtering made a very crisp image
	- Suprisingly, downsampling, gaussian filtering, then Canny seemed to give the best edge detection (downsampling then bilateral filtering before Canny performed worst). However I don't yet know how to quantify this other than "looks good!". 

















Where I'm at: Hough transform isn't working yet.



Continue from here.

