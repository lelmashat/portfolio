package lelmasha_CSCI201_Assignment1;

import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonObject;
import com.google.gson.JsonArray;

public class WeatherFileWriter {
    
	// Method to write weather data to a JSON file
    public static void writeWeatherFile(String filename, List<WeatherData> weatherList) throws IOException {
        // Create a Gson object with pretty printing enabled for better readability        
    	Gson gson = new GsonBuilder().setPrettyPrinting().create();
        
        // Create the root JSON object
        JsonObject rootObject = new JsonObject();
        
        // Create the array of weather data
        JsonArray dataArray = new JsonArray();
        
        // Add each weather data entry to the array
        for (WeatherData data : weatherList) {
            JsonObject dataObject = new JsonObject();
            dataObject.addProperty("location", capitalize(data.getLocation()));
            dataObject.addProperty("temperature", data.getTemperature());
            dataObject.addProperty("temperatureMin", data.getTemperatureMin());
            dataObject.addProperty("temperatureMax", data.getTemperatureMax());
            dataObject.addProperty("humidity", data.getHumidity());
            dataObject.addProperty("pressureSeaLevel", data.getPressureSeaLevel());
            dataObject.addProperty("visibility", data.getVisibility());
            dataObject.addProperty("windSpeed", data.getWindSpeed());
            dataObject.addProperty("windDirection", data.getWindDirection());
            dataObject.addProperty("condition", capitalize(data.getCondition()));
            dataArray.add(dataObject);
        }
        
        // Add the array to the root object with the key "data"
        rootObject.add("data", dataArray);
        
        // Write the JSON to the file
        try (FileWriter fileWriter = new FileWriter(filename)) {
            gson.toJson(rootObject, fileWriter);
        }
    }

    // Helper method to capitalize the first letter of each word
    private static String capitalize(String str) {
        // Check if the string is null or empty        
    	if (str == null || str.isEmpty()) {
            return str;
        }
        // Split the string into individual words
        String[] words = str.split(" ");
        StringBuilder capitalized = new StringBuilder();
        // Loop through each word, capitalize the first letter and append it to the result        
        for (String word : words) {
            if (!word.isEmpty()) {
                capitalized.append(Character.toUpperCase(word.charAt(0)))
                           .append(word.substring(1).toLowerCase())
                           .append(" ");
            }
        }
        // Return the capitalized string, trimmed to remove any trailing spaces
        return capitalized.toString().trim();
    }
}



