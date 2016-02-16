#include <iostream>
#include "stackint.h"
#include <sstream>
#include <string>
#include <fstream>
int L_R(StackInt & stack, const bool &left_call){
	const int LEFT = -3, RIGHT = -4;							//setting const values
	std::string result = (left_call) ? "L" : "R";				//if it is function is called with left, set result as "L" else set as "R"
	int top = stack.top();									//Get top value
	while(top == LEFT || top == RIGHT){							//While top is shift left or shift right
		result = (top == LEFT) ? "L" + result : "R" + result;	//Add "L" if left or "R" if right to result string
		stack.pop();											//pop top value off
		if(stack.empty()) return -1;							//if stack is empty, return -1
		else top = stack.top();								//otherwise, get top value
	}
	for(unsigned int i = 0; i < result.length(); i++)	result[i] == 'L' ? top *=2 : top /= 2;		//do apropraite arithmetic
	return (top < 0) ? -1 : top;												//return the value or if top is not a number, -1
}
int evaluate_expression(StackInt & stack){
	const int CLOSE = -2, LEFT = -3, RIGHT = -4, MULT = -5, ADD = -6;
	bool first_time = true, can_mult = true, can_add = true;				//Initialize variables.
	int run_tot = 0, top_val = stack.top();
	while(stack.empty() == false){					//While the stack is not empty
		top_val = stack.top();						//Get top value
		if(stack.empty()) return -1;					//if stack is empty, return -1
		stack.pop();									//Pop this value;
		if(top_val == CLOSE){							//If top is the close paren
			stack.push(run_tot);						//push the running total 
			return run_tot;								//and return the running total
		}
		else if( top_val == LEFT || top_val == RIGHT){		//If the top is left or right		
			int temp = L_R(stack, (top_val == LEFT) ? true : false);	//temp is equal to the output of the L_R function
			if (  temp == -1 )	return -1;					//if temp is equal to -1, return -1
			else stack.push(temp); 						//otherwise, push temp
		} else if(first_time){								//if it is the first time through
			if(top_val < 0) return -1;						//if the top is not a number, return error
			first_time = false;								//set the first time as false
			run_tot = top_val;								// set the running total as the top value;
		} else if( top_val == ADD){							//if the top is an add command
			if(!can_add) return -1;							//if you have already done mult, return error
			int top = stack.top();						//save the new top
			if(top == RIGHT) top = L_R(stack,false);		//if the top is shift right, call L_R
			else if(top == LEFT) top = L_R(stack,true);		//if the top is shift left, call L_R
			run_tot += top;									//add top to running total
			can_mult = false;								//set it so you cant multiply
		} else if( top_val == MULT){							//If the top is muli comand
			if(!can_mult) return -1;						//if you have already done addition, return error
			int top = stack.top();						//save new top
			stack.pop();;								//if the top is shift right or left, call L_R
			if(top == RIGHT) top = L_R(stack,false);
			else if(top == LEFT) top = L_R(stack,true);
			run_tot *= top;									//multiply run tot by top
			can_add = false;								//set so you cant add
		}
	}
	return -1;												//return if there is an error
}
int read_to_stack(const std::string& input, StackInt & stack){
	const int CLOSE = -2, LEFT = -3, RIGHT = -4, MULT = -5, ADD = -6; //const variables
	int return_val = 0, paren_count = 0;
	for(int i = input.length() - 1; i >= 0; i--){					//iterate throgh the string
		if (return_val == -1) return -1;							//if there was an error in evaluating, return that error
		else if( input[i] == '(')	{
			return_val = evaluate_expression(stack);	// if open paren, evaluate the expression
			paren_count++;								//KEEP track of parenthesis
		}
		else if( input[i] == ')')	{
			stack.push(CLOSE);									//PUSH corresponding variables
			paren_count--;
		}
		else if( input[i] == '<')	stack.push(LEFT);			//
		else if( input[i] == '>')	stack.push(RIGHT);			//
		else if( input[i] == '*')	stack.push(MULT);			//
		else if( input[i] == '+')	stack.push(ADD);				//	
		else {														//if the character is a number
			int stop = -1, temp = 0;								//initialize
			for(int j = i; j >= 0; j--){							//Iterate until you find one of these characters and break
				if(input[j] == '(' || input[j] == ')' || input[j] == '<')	stop = j + 1;
				else if(input[j] == '>' || input[j] == '*' || input[j] == '+')	stop = j + 1;
				if(stop != -1) break;
				else if(j == 0) return -1;				//if you didnt find a character, return an error
			}
			std::istringstream(input.substr(stop,i)) >> temp;	//push this number into a temp
			i = stop;											//set it. variable to end of number
			stack.push(temp);								//push this to stack
		}
	}
	return (paren_count == 0 ) ? return_val : -1;
}
int main(int argc, char *argv[]){
	std::string line;										//Initialization				
	std::ifstream infile(argv[1]);
	while( std::getline(infile, line)) {						//Read file
		StackInt stack = StackInt();
		if(line[1] != '(')	line = '(' + line + ')';			//Add parenthesis if they are not around the expression
		for(unsigned int i = 0; i < line.length(); i++) 
			if(line[i] == ' ') line.erase(line.begin()+i);		//Remove spaces
		//line.erase(std::remove(line.begin(), line.end(), ' '), line.end());	//Remove spaces
		int temp = read_to_stack(line,stack);					//store the evaluation result and print if it is not -1
		temp == -1 ? std::cout<<"Malformed"<<std::endl : std::cout<<temp<<std::endl; 
	}
	return 0;
}