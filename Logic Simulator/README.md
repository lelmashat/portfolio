This project simulates digital circuits with gates (AND, OR, NOT) and wires. The simulator processes events where wire states change over time. Gates output new states based on inputs, and events are processed using a min-heap to maintain order by time.

Key Components:
- Gates: AND, OR, NOT gates determine output based on input states. You’ll implement a NotGate and modify the parser to support it.
- Wires: Maintain states ('high', 'low', or 'undefined'). Changes trigger events in connected gates.
- Min-Heap: Stores events sorted by time, using the EventLess functor to maintain the heap.

The goal is to correctly simulate circuits, output timing diagrams, and ensure gates behave as expected.
