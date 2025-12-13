# Single Linked List Bus Route Implementation

## Overview
Implement a singly linked list to represent a city bus route, where each node corresponds to a bus stop in the order the bus visits them. The list should support operations such as adding new stops to the route, removing stops, and traversing the stops sequentially as the bus moves along its route.

## Problem Statement
A city bus travels along a fixed route, visiting multiple stops in a specific order. We need to model this route using a singly linked list where:
- Each node represents a bus stop
- Nodes are ordered sequentially by stop position in the route
- The list starts with the first stop and ends with the last stop

## Data Structure

### Node Structure
```c
struct Stop {
    int stopID;           // Unique identifier for the bus stop
    char stopName[100];   // Name of the bus stop
    struct Stop* next;    // Pointer to the next stop
};
```

### List Structure
The bus route is represented as a series of linked nodes, starting from a `head` pointer that points to the first stop.

## Required Operations

### 1. Initialize Route
- Create an empty bus route
- Set the head pointer to NULL

### 2. Add Stop to Route
**addStop(int stopID, char* stopName, int position)**
- Add a new stop at a specified position in the route
- If position is 0, insert at the beginning
- If position is at the end, append to the route
- Support insertion in the middle of the route

### 3. Remove Stop from Route
**removeStop(int stopID)**
- Remove a stop with the given ID from the route
- Properly free memory allocated for the removed node
- Adjust pointers to maintain route continuity

### 4. Traverse Route
**traverseRoute()**
- Display all stops in the route in order
- Show stop ID and stop name
- Useful for viewing the complete bus route

### 5. Find Stop
**findStop(int stopID)**
- Search for a specific stop in the route
- Return the stop details if found
- Return NULL if not found

### 6. Display Stop Details
**displayStop(struct Stop* stop)**
- Print details of a single stop
- Format: "Stop ID: X, Name: Y"

### 7. Free Route
**freeRoute()**
- Deallocate all memory used by the linked list
- Set head pointer to NULL

## Example Usage

```
Initial Route:
Stop 1 -> Stop 2 -> Stop 3 -> NULL

Add Stop 2A at position 2:
Stop 1 -> Stop 2 -> Stop 2A -> Stop 3 -> NULL

Remove Stop 2:
Stop 1 -> Stop 2A -> Stop 3 -> NULL

Traverse:
- Display: Stop 1 -> Stop 2A -> Stop 3
```

## Implementation Details

### Key Features
- **Memory Allocation**: Dynamically allocate memory for each new stop
- **Error Handling**: Check for NULL pointers and invalid positions
- **Pointer Manipulation**: Properly update next pointers when adding/removing
- **Traversal**: Iterate through the list using pointers

### Time Complexity
- Add Stop: O(n) - need to traverse to find insertion position
- Remove Stop: O(n) - need to find and remove the node
- Traverse: O(n) - visit all nodes once
- Find Stop: O(n) - search through all nodes

### Space Complexity
- O(n) - where n is the number of stops in the route

## Testing Recommendations
1. Test adding stops to empty route
2. Test adding stops at beginning, middle, and end
3. Test removing stops from different positions
4. Test removing non-existent stops
5. Test traversing empty and non-empty routes
6. Test finding existing and non-existing stops
7. Test memory deallocation

## Files
- `busroute.c` - Implementation of the singly linked list bus route
- `README.md` - This documentation file

## OUTPUT OF THE CODE (reference)

![refernce image](/screenshots/output.png)