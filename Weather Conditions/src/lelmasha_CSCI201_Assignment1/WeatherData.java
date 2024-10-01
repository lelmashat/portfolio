package lelmasha_CSCI201_Assignment1;

public class WeatherData {

    // Fields representing various weather attributes
    private String location;
    private String condition;
    private int temperature;
    private int temperatureMin;
    private int temperatureMax;
    private int windDirection;
    private int humidity;
    private float pressureSeaLevel;
    private float visibility;
    private float windSpeed;

  
    // Getter and setter for 'location' field
    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    // Getter and setter for 'temperature' field
    public int getTemperature() {
        return temperature;
    }

    public void setTemperature(int temperature) {
        this.temperature = temperature;
    }

    // Getter and setter for 'temperatureMin' field
    public int getTemperatureMin() {
        return temperatureMin;
    }

    public void setTemperatureMin(int temperatureMin) {
        this.temperatureMin = temperatureMin;
    }

    // Getter and setter for 'temperatureMax' field
    public int getTemperatureMax() {
        return temperatureMax;
    }

    public void setTemperatureMax(int temperatureMax) {
        this.temperatureMax = temperatureMax;
    }

    // Getter and setter for 'humidity' field
    public int getHumidity() {
        return humidity;
    }

    public void setHumidity(int humidity) {
        this.humidity = humidity;
    }

    // Getter and setter for 'pressureSeaLevel' field
    public float getPressureSeaLevel() {
        return pressureSeaLevel;
    }

    public void setPressureSeaLevel(float pressureSeaLevel) {
        this.pressureSeaLevel = pressureSeaLevel;
    }

    // Getter and setter for 'visibility' field
    public float getVisibility() {
        return visibility;
    }

    public void setVisibility(float visibility) {
        this.visibility = visibility;
    }

    // Getter and setter for 'windSpeed' field
    public float getWindSpeed() {
        return windSpeed;
    }

    public void setWindSpeed(float windSpeed) {
        this.windSpeed = windSpeed;
    }

    // Getter and setter for 'windDirection' field
    public int getWindDirection() {
        return windDirection;
    }

    public void setWindDirection(int windDirection) {
        this.windDirection = windDirection;
    }

    // Getter and setter for 'condition' field
    public String getCondition() {
        return condition;
    }

    public void setCondition(String condition) {
        this.condition = condition;
    }
}
