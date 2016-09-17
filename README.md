This program was made by Mitchell Hewitt for CS430 Computer Graphics (Section 1), Project 1 - Images, in Fall 2016
This program reads in either p3 or p6 image files and writes the data into the opposite filetype.

To use this program...

	1.  Compile it with the provided makefile (requires gcc).

	2a. Use the command "ppmrw 3 inputp3.ppm output.ppm" to read a p3 input image file
	    and write it to a p6 output.ppm image file.

	2b. Use the command "ppmrw 6 inputp6.ppm output.ppm" to read a p6 input image file
	    and write it to a p3 output.ppm image file.

If you would like to verify the conversion...

	1.  Open the input file using a program that can read .ppm P3 and P6 file types.

	2.  Verify the filetype by opening the input file in a text editor.
		> A P3 file in a text editor will display all ascii.
		> A P6 file in a text editor will display a header in ascii followed by nonsensical characters.

	3.  Open the output file using a program that can read .ppm P3 and P6 file types.
	    A correctly written output file will appear identical to the original input file.

	4.  Verify the filetype by opening the output file in a text editor.
		> A P3 file in a text editor will display all ascii.
		> A P6 file in a text editor will display a header in ascii followed by nonsensical characters.

Invalid inputs and file contents will close the program. 
This program is designed to use eight bits per color channel.