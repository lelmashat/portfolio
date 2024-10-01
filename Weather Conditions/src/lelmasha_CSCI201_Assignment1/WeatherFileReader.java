package lelmasha_CSCI201_Assignment1;

import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;
import com.google.gson.reflect.TypeToken;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.Type;
import java.util.List;
import java.util.Map;

public class WeatherFileReader {

    // Method to read weather data from a file and return a list of WeatherData objects
    public static List<WeatherData> readWeatherFile(String filename) throws FileNotFoundException, IOException {
        try (FileReader reader = new FileReader(filename)) {
            Gson gson = new Gson(); // Create a Gson object for parsing JSON
            
            // Define the type for the JSON data structure
            Type type = new TypeToken<Map<String, List<WeatherData>>>() {}.getType();
            
            // Parse the JSON file
            Map<String, List<WeatherData>> data = gson.fromJson(reader, type);
            
            // Return the list of WeatherData objects
            return data.get("data");
        } catch (JsonSyntaxException e) {
            throw new JsonSyntaxException("File is not formatted properly");  // Propagate the JSON formatting error
        } catch (FileNotFoundException e) {
            throw new FileNotFoundException();  // File not found, propagate the exception
        } catch (IOException e) {
            throw new IOException();  // General IO error
        }
    }
}




