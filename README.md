# digital_galton
![testing badge](https://github.com/srFelipes/digital_galton/actions/workflows/testing.yml/badge.svg)

Firmware of the digital galton project. This project is a pcb controled by an arduino nano that runs 2 led matrices by writing to its SPI bus that is connected to 2 different array of shift registers whose output drives the leds directly. One of the matrices is the galton table and its represented as a tringle of leds with one more led each level. The idea behind it is to simulate the trajectory that each balls floows while falling into the galton board assuming that when passing to the level below it has 2 leds that it can _fall_ to, one to the left and one to the right each with 50% probability. The second led matrix is the container array where the balls land, each container has 8 leds and at the moment it is displaying the binary representation of the balls it contains. A demo can be seen bellow illustrating the concept and a normal distribution can be seen in the containers, it is a little difficult since the containers are represented in their binary form


https://github.com/srFelipes/digital_galton/assets/37315690/cf0d13b2-bada-46e9-8785-4bcdafcd8a59

## Usage
This is a platformio project, use it to flash an arduino nano and connect it to the board.

## Algorithms
At the moment 2 algorithms have been written to simulate the balls falling into the galton board, both were application specific. The first one would go through each position of the table checking if it had a ball in it and if that was the case it would flip a coin and propagate the ball to the next row, this wasnt very efficient. The second algorithm would generate a random int, assume that each bit in it was random and generate the whole trayectory of the ball, this was faster. TODO: rename algorithms acordingly and generate better benchmarks

| Algorithm name | time benchmark [balls/s]|
|----------|----------|
| Go_to_each_pos   | ~4K   |
| Generate_ball_trajectories    | ~5K |

## TODO

- [] Write the algorithms ina general form in order to be usable in a c/c++ program.
- [] Name algorithms
- [] Define a benchmark and use it to rank the algorithms.
- [] Add encoder functionality.
- [] Write a main that changes certain parameters of the program as the delay and the visualization or so.
- [] Add pcb files and renderizations
