This project was a very quick (5 hours) prototype to test the feasibility of moving an array of lights on winches using live stock data from the yahoo finance api. Please get in contact for visual reference.

The project accesses the api repeatedly using python, saves that needed data to a json file, where the openframeworks app reads the json and creates the ever updating picture below (mirrored due to a quirk of spout flipping the sent video)

![image](https://user-images.githubusercontent.com/88803350/169157974-f49ebb67-004a-439d-99ca-3bed6cd8effc.png)


The grey bands represent a value between 0 and 255 which has been remapped from the day's market low and high and the current stock value.

This animation is then sent across to the lighting sequencing software using spout (https://spout.zeal.co/) which reads the value between 0 and 255 as a position on the winch.

