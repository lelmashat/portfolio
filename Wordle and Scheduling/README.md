There are two parts to this folder:

**Wordle Solver**

This project involves the development of a recursive Wordle-like game-solving tool, aimed at assisting players in generating potential word guesses based on specific constraints. The tool enables players to input partial word knowledge (both fixed-position and floating-position letters) and generates a set of possible English-language words that fit the given criteria.

Input: The user provides two inputs—a string representing known letters in fixed positions (with unknown positions marked by hyphens) and a string containing floating letters (letters that must appear in the word but in any position).
Output: The tool generates all valid n-letter English words that meet the criteria using a recursive approach. The list of valid words is checked against a provided dictionary of words to ensure correctness.

Key Features:
- Recursive backtracking to generate all possible word combinations.
- Handling of both fixed and floating letters in word generation.
- Utilizes a dictionary (std::set<std::string>) to validate potential word guesses.

**Scheduling Algorithm for Schedwork**

This project involves a recursive scheduling algorithm designed to meet specific staffing requirements. The task is to generate a work schedule for a group of workers over a set number of days, subject to worker availability and shift limits.

Input: An availability matrix indicating which workers are available on which days, along with the number of workers needed per day and the maximum shifts any worker can be assigned across the entire schedule.
Output: A valid schedule (if one exists) that assigns the required number of workers to each day while respecting the availability and maximum shift constraints.

Key Features:
- Recursive backtracking to explore possible worker assignments.
- Ensures that no worker is assigned more shifts than allowed.
- Optimizes worker assignments based on availability and requirements.
