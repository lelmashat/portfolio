The program is designed to parse weather data from a JSON file and provides a command-line interface for users to query and manage weather conditions for various locations.

Key Features
- JSON Parsing: Utilized the GSON library to read and parse weather data from a JSON file formatted with essential weather attributes, such as location, temperature, humidity, pressure, visibility, wind speed, and conditions.
- File I/O: Implemented error handling to ensure the correct loading of the JSON file, validating both file existence and formatting. The program prompts users to retry in case of issues, providing specific error messages.
- User Interaction: Developed a command-line interface that allows users to complete many different tasks
- Sub-Menus: Included sub-menus for detailed weather inquiries, such as temperature, humidity, pressure, and wind conditions, with case-insensitive input handling for location searches.

Technical Implementation
- Data Structure: The program uses Java's collections framework to manage weather data, ensuring efficient data retrieval and manipulation.
- Sorting Algorithms: Implemented sorting capabilities to organize location data based on user preference.
- Error Handling: Comprehensive error checking to handle invalid inputs and file parsing issues, enhancing user experience and reliability.

The program begins by asking for a JSON file containing weather data. Upon successful parsing, it presents a menu of options to the user. Example interactions include querying temperature for specific locations and displaying all weather information in a structured format.
This project not only reinforced my Java programming skills but also enhanced my understanding of data parsing, file management, and user interface design in command-line applications. The experience gained through this assignment has laid a solid foundation for future projects involving more complex data structures and user interactions.
