<h1>Obstacle Avoidance Car</h1>
The algorithm is desined to avoide any obstacle by rotaiting to left or right based on the free distane <br>
the car will follow the obstacle till it ends then rotate to the original direction <br>
then continue to move forward<br>
it's originaly designed to path from this certain type of obstacles: <br>
<br>
<img src = 'https://github.com/Ahmedzaid16/Obstacle-avoidance-car/assets/84353686/820fa2a0-cba5-4131-93bc-6b0bdf6a4db6' alt="Example Image"">
<br>
but in general the algorithm will work with any type of obstacle in another words the obstacle must have an end <br>
<h2> Explaining Algorithm</h2>
<pre>
1. **Initial Setup:**
   - Calculate the initial distance using the `calculate_distance` function.
   - Print the initial distance using the Serial monitor.

2. **Loop While Distance is Greater Than or Equal to 20:**
   - While the distance is greater than or equal to 20 units:
     - Move the motors backward ('b').
     - Recalculate the distance and print it.
   - Once the distance is less than 20, stop the motors ('s').

3. **Perform a Series of Movements Using a Servo:**
   - Move the servo to position 0.
   - Measure the distance to the right ('right_distance') and print it.
   - Move the servo to position 180.
   - Measure the distance to the left ('left_distance') and print it.
   - Move the servo to position 90 with a short delay.

4. **Make a Decision Based on Distances:**
   - If the distance to the left is less than or equal to the distance to the right:
     - Rotate the motors clockwise ('m') for a short duration.
     - Move the servo to position 180.
     - Stop the motors.
     - Delay for a while.
     - Recalculate the distance, print it, and move the motors backward until the distance is greater than
       or equal to 20.
     - Move the servo to the center position (90).
     - Stop the motors.
     - Delay and perform a specific motor action ('t').
   - If the distance to the left is greater than the distance to the right:
     - Perform a different set of movements to turn left.
  </pre>
<h2>Testing Car </h2>
<br>

<video src='https://github.com/Ahmedzaid16/Obstacle-avoidance-car/assets/84353686/23d2c8df-00b2-40cc-93de-e0875f37df02' muted autoplay loop></video>


<br>
<h2>Future Work</h2>
Adding an ir obstacle sensor in front of the car will certinaly solve the problem of following infinite obstacle <br>
simply use ir sensor as interrupt to change the car direction in case of detectig another obstacle in front of car
