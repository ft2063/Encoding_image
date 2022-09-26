“The software presents the user with a main menu, with (three) options to encode a message, decode a
message, and exit the program”.
In our context, encoding a message means to hide a secret text message inside a Bitmap image. Both
secret message and name of Bitmap image are provided by the user.
Decoding means to extract a secret message embedded in the encoded bitmap image. The name of the
encoded bitmap image is provided by the user.
Solution must be arranged into separate header files (encoding.h and decoding.h ), and program must
be written in reusable functions.
Bitmap images will be read and written on trough functions provided in header file bitmapHelper1.h.
Release memory function should be added to bitmapHelper1.h to deallocate dynamic memory correctly
Step 2: Gathering Information
The software makes use of the technique of Steganography which hides “ data (file, text, image, etc.)
within another data file (file, text, image, etc.)” . Which can be implemented as follows:
• To encode: find ascii of each letter in message provided by casting character variable to integer
• Convert the ascii of each letter to its binary form by creating a function which converts decimal
form of a number to its binary
• Take the least significant bit (lsb) of the binary of each pixel channel through bitwise operators.
(Eg. lsbpixel = (imageData[i][j][channel] >> 0) & 1U)
• Compare this lsb with the most significant bit of character provided in its binary form
• If they differ toggle (change from 0 to 1 or vice versa) the last bit in the binary of each pixels
channels through bitwise operators. (Eg. imageData[i][j][channel] ^= 1UL << 0)
• To decode: store lsb of the binary of each pixel channel by groups of 8 bits (1 character)
• Find the ascii corresponding to the character by creating function which converts binary form of
a number to decimal
• Cast the character’s ascii to type character
• Display character
