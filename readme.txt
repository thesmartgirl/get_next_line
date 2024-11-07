FUNC:: get_next_line
    - main function that calls the others
    - initializes bytes_read and line_draft
    - checks the input fd and BUFF_SIZE for errors 
    - returns: line or NULL (provided by extract_line() )

                FUNC:: read_more
                    - basically the function for reading from fd
                    - called to read more data if the line_draft doesnt have a new line so far
                    - allocates (and frees) buff
                    - concatinates the new read buff into line_draft

                FUNC:: extract_line
                    - called if a new line is found in line_draft
                    - extracts the full line needed
                    - keeps the remaining in line_draft for the next call

bytes_read: 
    - number of read bytes returned by read(). 
    - starts at 1 to enable the while loop
    - initialized in get_next_line and updated in read_more

buff:
    - contains the actual data returned by read(). 
    - should be added to line_draft

line_draft:
    - this is the static variable
    - array of pointers to txt
    - one element per fd
    - contains raw data read so far 
    - may / may not contain a full line
    - holds the remaining data for the next call

line:
    - the returned line (the ultimate answer)
    - returned by extract_line() and progagated to get_next_line()
tmp:
    - temporary variable 










