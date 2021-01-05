//coding for multiplication
      @R2            //Suppose this is RAM[2] we need to save the result in R2 
	  M=0            //initializing it to zero for sum 
(LOOP)
      @R0            //suppose this is RAM[0]
	  D=M            //at first its value is 0 saving the result to data register from memory
	  @END           //we need to compare the d register if it's still equal to zero then goto label end by putting 
      D;JEQ          //jump condition JEQ which means if equal to zero 
      @R0	         // taking R0 as a counter
	  M=D-1          //decrementing the counter by 1
	  @R2            //taking R2 to store the result
	  D=M            //saving the result to data register
	  @R1            //taking R1 to add
	  D=D+M          //
	  @R2            //again taking R2 to store the result
	  M=D            //storing the result to memory
	  @LOOP          //label loop to loop the program until we get our required result
	  0;JMP          //this indicates the unconditional loop
(END)
      @END           //created a unconditional loop so that after getting our required result 
	  0;JMP          //the program continues looping here.
	  
	  
	  
