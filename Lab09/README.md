CruzID: atorre83@ucsc.edu

Solo Lab Group: 28

I WROTE:
-AGENT.C
-NEGOTIATION.C
-AGENTTEST.C
-NEGOTIATIONTEST.C
-FIELD.C
-FIELDTEST.C

Introduction:
	I worked alone on this lab. The lab over forty hours and I dont think it works

correctly. Today, the last day, I wasn't able to play the game even when excluding my

files. I'm out of time anyways and at least I wrote some version of the functions I was

required too. 

	Initialy the task seemed very overwhelming although I had some idea of what the

state machine should look like. The battleboats system sends messages between the Uno32s

to communicate what state the game is in as well as modify the fields of each board based

on the events that occur. The game is started through a virtual coinflip based on the

number of ones in a bitstring. The system that goes first is prompted to make a decision

of which square to target. That system sends the coordinates of the square the have 

"attacked" along with an appropriate message, then the responding system locates that 

square on their field and relays what the contents of the square were. Each time a state

is finished each system enters another state in a cycle that ends when someone wins or 

presses the reset button, though I do not think I implemented this correctly. Each board

keeps its own record of the fields.

	The negotiation seemed to work well although I was still not passing the auto-

grader completely. The strategy I found most effective was to set a marker with a printf

statement in the test files so that I could see which functions were failing at which

points. Planning better and writing better pseudo code way have been more effective in

understanding where my problems were. I always start writing the code too early, get 

slightly hysteric, and overwhelmed. I learned basic hash functionality, checksums, and

understand some of the UART fuctionality. I liked the idea of creating a game and 

creating a statemachine although I could not get it to run correctly which was a let down.

In a world without covid I would have liked to work with a partner in person and not had

to use the python script. I don't know what was wrong in the end although it wouldn't 

run correctly even using the .o files. I'll try to keep getting this to work on my own

before I have to return the Uno32 although I rather submit ontime then take the

automatic ten percent loss. 