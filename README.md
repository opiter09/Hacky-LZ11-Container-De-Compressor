IMPORTANT: It seems this program will not work without Visual Studio being installed. You don't need to do anything with it, just grab the free Community edition, and make sure to choode the Desktop C++ module.
Visual Studio can be found at https://visualstudio.microsoft.com/

This used to be an editor for DS graphics files (NCGR, NCBR, NANR, NCER, etc.). And, as far as I can tell, all of that still works. However, I have used the combined powers of CopyPaste, Stack Overflow, and Trial and Error to learn just enough C to hack this into also doing the following:
- If you open a file compressed using the LZ11 "COMP" format used by the game LEGO Battles, a decompressed version of that file named "testD.bin" will appear in the same directory as the file you inputted
- If you open a non-compressed file, a version of that file compressed in said format named "testC.bin" will appear in the same directory as the file you inputted

This works whether the file is actually viewable/editable by NitroPaint or not.

Obviously, a giant thanks to Garhoogin, who made 99.99% of the code here. I cannot apologize enough for any work you (Garhoogin) did on making a de/compressor for this format at my request, but alas curiosity got the better of me and I felt the need to try and figure this out myself.

Important Note: If you are planning on building this yourself, make sure to set it to Debug and x86 in Visual Studio.
