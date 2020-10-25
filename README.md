Socket-Programming Fundamentals on Linux Platform Written in C environment 
Steps to compuile and run the program
gcc <nameofthe file> 
./a.out <any valid port number above 1024>
  
  Example:
  gcc tcp-server.c 
  ./a.out 6500      #server will start at port number 6500
  
  To test with telnet
  ---------------------------
  telnet localhost 6500
