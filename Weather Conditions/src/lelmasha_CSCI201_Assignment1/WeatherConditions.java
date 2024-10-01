package lelmasha_CSCI201_Assignment1;

import java.io.IOException;
import java.util.*;
import com.google.gson.JsonSyntaxException;
import java.io.FileNotFoundException;

public class WeatherConditions {

    // Static list to hold weather data for multiple locations
    private static List<WeatherData> weatherList = new ArrayList<>();

    public static void main(String[] args) {
        // Create a scanner to get user input
    	Scanner scanner = new Scanner(System.in);
        boolean exit = false;

        // Loop to continuously ask for the weather file name until the user chooses to exit
        while (!exit) {
            System.out.print("What is the name of the weather file? ");
            String filename = scanner.nextLine();

            // Try to read the weather data from the specified file
            try {
                weatherList = WeatherFileReader.readWeatherFile(filename);
                System.out.println("The file has been properly read.");
            } catch (JsonSyntaxException e) {
                // Handle error for incorrect JSON formatting
                System.out.println("The file " + filename + " is not formatted properly.");
                continue;
            } catch (FileNotFoundException e) {
                // Handle error if file cannot be found
                System.out.println("The file " + filename + " could not be found.");
                continue;
            } catch (IOException e) {
                // Handle I/O errors
                System.out.println("I/O Error.");
                continue;
            }
            
            // Loop for menu options until the user chooses to exit
            while (!exit) {
                // Display the available actions for the user
                System.out.println("1) Display weather on all locations");
                System.out.println("2) Search for weather on a location");
                System.out.println("3) Add a new location");
                System.out.println("4) Remove a location");
                System.out.println("5) Sort locations");
                System.out.println("6) Exit");
                System.out.print("What would you like to do? ");

                int choice = -1;

                // Check if the input is an integer for the menu choice
                if (scanner.hasNextInt()) {
                    choice = scanner.nextInt();
                    scanner.nextLine();  // Consume newline
                } else {
                    System.out.println("That is not a valid option.");
                    scanner.nextLine();  // Consume invalid input
                    continue;
                }

                // Handle user choice based on the menu options
                switch (choice) {
                    case 1:
                        displayAllLocations();
                        break;
                    case 2:
                        searchLocation(scanner);
                        break;
                    case 3:
                        addLocation(scanner);
                        break;
                    case 4:
                        removeLocation(scanner);
                        break;
                    case 5:
                        sortLocations(scanner);
                        break;
                    case 6:
                        // Prompt to save changes before exiting
                        System.out.println("1) Yes");
                        System.out.println("2) No");
                    	System.out.println("Would you like to save your edits? ");
                        int saveChoice = scanner.nextInt();
                        if (saveChoice == 1) {
                            saveWeatherData(filename); // Save the changes to the file
                        }
                        System.out.println("Thank you for using my program!");
                        exit = true; // Exit the loop
                        break;
                    default:
                        // Handle invalid menu option
                        System.out.println("That is not a valid option.");
                }
            }
        }
        // Close the scanner to avoid resource leaks
        scanner.close();
    }

    // Method to display weather data for all locations
    private static void displayAllLocations() {
        // Loop through each location in the weather list
        for (WeatherData data : weatherList) {
            System.out.println(data.getLocation());
            System.out.println("temperature is " + data.getTemperature() + " degrees Fahrenheit,");
            System.out.println("low temperature is " + data.getTemperatureMin() + " degrees Fahrenheit,");
            System.out.println("high temperature is " + data.getTemperatureMax() + " degrees Fahrenheit,");
            System.out.println("humidity is " + data.getHumidity() + "%.");
            System.out.println("pressure is " + String.format("%.2f", data.getPressureSeaLevel()) + " Inch Hg,");
            System.out.println("visibility is " + data.getVisibility() + " miles,");
            System.out.println("wind speed is " + data.getWindSpeed() + " miles/hour,");
            System.out.println("wind direction is " + data.getWindDirection() + " degreed,");
            System.out.println("weather can be described as " + data.getCondition().toLowerCase());
            System.out.println();
        }
    }

    // Method to search for a location's weather data
    private static void searchLocation(Scanner scanner) {
        System.out.print("What is the location you would like to search for? ");
        String toSearch = scanner.nextLine();
        String location = toSearch.toLowerCase();
        
        // Use stream to find the location in the weather list
        WeatherData result = weatherList.stream()
            .filter(data -> data.getLocation().toLowerCase().equals(location))
            .findFirst()
            .orElse(null);
        
        if (result == null) {
            // If the location is not found, display a message
            System.out.println(toSearch + " could not be found.");
            return;
        }

        // Display detailed weather info for the location in a sub-menu
        boolean returnToMenu = false;
        System.out.println("I have information about the weather in " + result.getLocation() + ".");
        while (!returnToMenu) {
            System.out.println("1) temperature");
            System.out.println("2) high and low temperature");
            System.out.println("3) humidity");
            System.out.println("4) pressure");
            System.out.println("5) visibility");
            System.out.println("6) wind speed and direction");
            System.out.println("7) weather conditions");
            System.out.println("8) Return to main menu");
            System.out.print("What weather information do you want to know for " + result.getLocation() + "? ");
            
            // Get the user's choice and display the corresponding weather info
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline
            
            switch (choice) {
                case 1:
                    System.out.println("The temperature in " + result.getLocation() + " is " + result.getTemperature() + " degrees Fahrenheit.");
                    break;
                case 2:
                    System.out.println("The high /low temperature in " + result.getLocation() + " is " + result.getTemperatureMax() + " / " + result.getTemperatureMin() + " degrees Fahrenheit.");
                    break;
                case 3:
                    System.out.println("The humidity in " + result.getLocation() + " is " + result.getHumidity() + "%.");
                    break;
                case 4:
                    System.out.println("The pressure in " + result.getLocation() + " is " + result.getPressureSeaLevel() + " Inch Hg.");
                    break;
                case 5:
                    System.out.println("The visibility in " + result.getLocation() + " is " + result.getVisibility() + " miles.");
                    break;
                case 6:
                    System.out.println("The wind speed and direction in " + result.getLocation() + " is " + result.getWindSpeed() + " miles/hour and " + result.getWindDirection() + " degreed.");
                    break;
                case 7:
                    System.out.println("The weather in " + result.getLocation() + " can be described as " + result.getCondition() + ".");
                    break;
                case 8:
                    // Return to the main menu
                    returnToMenu = true;
                    break;
                default:
                    // Handle invalid option
                    System.out.println("That is not a valid option.");
            }
        }
    }

    // Method to add a new location's weather data
    private static void addLocation(Scanner scanner) {
        System.out.print("What is the location you would like to add weather info? ");
        String location = capitalize(scanner.nextLine()); // Capitalize input

        // Check if the location already exists in the weather list
        if (weatherList.stream().anyMatch(data -> data.getLocation().equalsIgnoreCase(location))) {
            System.out.println("There is already an entry for " + location + ".");
            return;
        }

        // Collect weather data for the new location
        WeatherData newWeather = new WeatherData();
        newWeather.setLocation(location);
        
        System.out.print("What is the temperature? ");
        newWeather.setTemperature(scanner.nextInt());
        System.out.print("What is the low temperature? ");
        newWeather.setTemperatureMin(scanner.nextInt());
        System.out.print("What is the high temperature? ");
        newWeather.setTemperatureMax(scanner.nextInt());
        System.out.print("What is the humidity? ");
        newWeather.setHumidity(scanner.nextInt());
        System.out.print("What is the pressure? ");
        newWeather.setPressureSeaLevel(scanner.nextFloat());
        System.out.print("What is the visibility? ");
        newWeather.setVisibility(scanner.nextFloat());
        System.out.print("What is the wind speed? ");
        newWeather.setWindSpeed(scanner.nextFloat());
        System.out.print("What is the wind direction? ");
        newWeather.setWindDirection(scanner.nextInt());
        scanner.nextLine();  // Consume newline
        System.out.print("What is the weather condition? ");
        newWeather.setCondition(capitalize(scanner.nextLine())); // Capitalize input

        // Add the new weather data to the list
        weatherList.add(newWeather);
        System.out.println("There is now a new entry for " + location + ".");
    }

    // Method to remove a location's weather data
    private static void removeLocation(Scanner scanner) {
        // Check if there are locations to remove
    	if(weatherList.isEmpty()) {
        	System.out.println("No locations to remove.");
        	return;
        }
    	
    	while (true) {

            for (int i = 0; i < weatherList.size(); i++) {
                System.out.println((i + 1) + ") " + weatherList.get(i).getLocation());
            }
            System.out.println("Which location would you like to remove?");
            
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline
            
            // Attempt to remove the location if it exists
            
            if (choice < 1 || choice > weatherList.size()) {
                System.out.println("Invalid choice.");
                continue;
            }
            
            String location = weatherList.get(choice - 1).getLocation();
            weatherList.remove(choice - 1);
            System.out.println(location + " is now removed.");
            break;
        }
    }

    // Method to sort the weather data
    private static void sortLocations(Scanner scanner) {
        System.out.println("1) A to Z");
        System.out.println("2) Z to A");
        System.out.print("How would you like to sort by? ");
        
        int choice = scanner.nextInt();
        scanner.nextLine();  // Consume newline
        
        switch (choice) {
            case 1:
                weatherList.sort(Comparator.comparing(WeatherData::getLocation, String.CASE_INSENSITIVE_ORDER));
                System.out.println("Your locations are now sorted in alphabetical order (A-Z).");
                break;
            case 2:
                weatherList.sort(Comparator.comparing(WeatherData::getLocation, String.CASE_INSENSITIVE_ORDER).reversed());
                System.out.println("Your locations are now sorted in reverse alphabetical order (Z-A).");

                break;
            default:
                System.out.println("Invalid choice.");
                return;
        }
        

    }

    // Helper method to save weather data back to the file
    private static void saveWeatherData(String filename) {
        try {
            WeatherFileWriter.writeWeatherFile(filename, weatherList);
            System.out.println("Your edits have been saved to " + filename);
        } catch (IOException e) {
            System.out.println("Failed to save the file.");
        }
    }

    // Helper method to capitalize the first letter of each word
    private static String capitalize(String str) {
        if (str == null || str.isEmpty()) {
            return str;
        }
        String[] words = str.split(" ");
        StringBuilder capitalized = new StringBuilder();
        for (String word : words) {
            if (!word.isEmpty()) {
                capitalized.append(Character.toUpperCase(word.charAt(0)))
                           .append(word.substring(1).toLowerCase())
                           .append(" ");
            }
        }
        return capitalized.toString().trim();
    }
}

