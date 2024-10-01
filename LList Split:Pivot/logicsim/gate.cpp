#include <vector>
#include <random>
#include <iostream>

#include "gate.h"
#include "wire.h"

Gate::Gate(int num_inputs, Wire* output) 
	: m_output(output), m_inputs(num_inputs), m_delay(0), m_current_state('X')
{
    
}

Gate::~Gate(){}

void Gate::wireInput(unsigned int id, Wire* in)
{
    if(id < m_inputs.size())
    {
        m_inputs[id] = in;
    }
}

And2Gate::And2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}

Event* And2Gate::update(uint64_t current_time)
{
    
  char state = '1';
  Event* e = nullptr;
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '0')
		{
			state = '0';
			break;
		}
		else if(in == 'X')
		{
			state = 'X';
		}
	}
    if(state != m_current_state)
	{
    m_current_state = state;
    uint64_t next = current_time + m_delay;
		e = new Event {next,m_output,state};
         
	}
    return e;
}

Or2Gate::Or2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}

Event* Or2Gate::update(uint64_t current_time)
{
    
  char state = '0';
  Event* e = nullptr;
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '1')
		{
			state = '1';
			break;
		}
		else if(in == 'X')
		{
			state = 'X';
		}
	}
  if(state != m_current_state)
	{
    m_current_state = state;
		uint64_t next = current_time + m_delay;
		e = new Event {next,m_output,state};
         
	}
  return e;
}

// Constructor for NotGate class
NotGate::NotGate(Wire* input, Wire* output) : Gate(1, output) {
    // Connect the input wire to the specified index
    wireInput(0, input);
}

Event* NotGate::update(uint64_t current_time) {
    // Retrieve the state of the input wire and create variable for output state
    char inputState = m_inputs[0]->getState();
    char outputState;

    // Logic for NOT gate operation: 'X' input results in 'X', '0' input results in '1', and '1' input results in '0'
    if (inputState == 'X') {
        outputState = 'X';
    } else if (inputState == '0') {
        outputState = '1';
    } else { // inputState == '1'
        outputState = '0';
    }

    // Check if the computed output state is different from the current state
    if (outputState != m_current_state) {
        // Update the current state and schedule an Event for the next state change        
        m_current_state = outputState;
        uint64_t next = current_time + m_delay;
        return new Event{next, m_output, outputState};
    }
    
    // Return nullptr if the output state remains the same
    return nullptr;
}

