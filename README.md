# Overview

Comparative Evaluation of Data Compression through binary, four-way, and pairing heaps without any standard lib. container except vector. Encoder reads and generates the compressed version of input file and code table. 
Decoder parses encoded message and code table, constructs decode tree using code table and decodes the encoded message.

## Implementation Details

### Encoder

- Encoder Input format: Input file name will be given as a command line argument. This file can have up to 100,000,000 lines and each line will contain a decimal value in the range of 0 to 999,999.
- Building frequency table: First step towards Huffman encoding is to build the frequency table for each value in input. As values will be within 0 to 999999, an array can be used for storing frequency for each value. 
- Input/Output: Build Huffman Tree & Code Table, Encode data and Encoder program has two output files. One is encoded message in binary format. Second output is the code table

### Decoder

- The decoder reads two input files - encoded message and code table. The decoder first constructs the decode tree using the code table. Then the decoded message can be generated from the encoded message using the decode tree.
- Decoder-Input format: The decoder takes two input files - encoded message and code table. File names will be given as command line arguments. The format of these files is the same as the output format of the encoder, so that the output files of the encoder program can be directly used by the decoder program. 
Note that the input encoded message will be in binary format, not ASCII characters. You can use ios::binary flag for C++ or InputStream for Java.
- Decoder-Output format: Output of decoder program is the decoded message. It should be saved as "decoded.txt". The format of this file is same as the input format for the encoder.

## Testing 

Correctness will be tested by:
- For encoder only: Size of encoded message
- For decoder only: Correctness of decoded message
- For both encoder and decoder: Input message => encoder => decoder => output message. Output message should be same as input message

